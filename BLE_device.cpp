#include "BLE_device.h"
#include "eq-3.h"

#include <QtGlobal>
#include <QtDebug>
#include <QTimer>
#include <QString>
#include <QList>
#include <cmath>
#include <QMetaEnum>


BLE_device::BLE_device()
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    discoveryAgent->setLowEnergyDiscoveryTimeout(5000); //set how much time the scan will take
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this,
            &BLE_device::deviceDiscovered);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this,
            &BLE_device::discoveryFinished);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled, this,
            &BLE_device::discoveryCanceled);
    connect(discoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),
            this, &BLE_device::discoveryError);


    beginInsertRows(QModelIndex(), userProfiles.size(), userProfiles.size());
    userProfiles.append(new Event("17.0"));
    endInsertRows();

}

BLE_device::~BLE_device()
{
    delete discoveryAgent;
    discoveryAgent = nullptr;
    delete connectedDevice;
    connectedDevice = nullptr;
    delete LEcontroller;
    LEcontroller = nullptr;

    Valves.clear();
}

QString BLE_device::getState()
{
    return state;
}

void BLE_device::startDeviceDiscovery()
{
    Valves.clear();

    state = "Searching for devices...";
    emit stateChanged();

    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BLE_device::addDevice(const QBluetoothDeviceInfo &device)
{
    // Search for BLE devices only
    if(device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        BLE_Valve *element = new BLE_Valve(device);
        QString devName = device.name();

        // append only radiator valves
        if (devName == "CC-RT-BLE")
            Valves.append(element);
    }
}

void BLE_device::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    addDevice(device);
    emit valvesDiscovered();
}

void BLE_device::discoveryFinished()
{
    QString temp_state = state;

    state = "Discovery finished";
    emit stateChanged();

    QTimer::singleShot(1000,[&,temp_state]{
        if(state != "Discovery finished")
            return;
        else {
            state = temp_state;
            emit stateChanged();
        }
    });

}

void BLE_device::deviceConnected()
{
    state = "Discovering services ...";
    emit stateChanged();

    LEcontroller->discoverServices();
}

void BLE_device::deviceDisconnected()
{
    state = "Device disconnected";
    emit stateChanged();
}

void BLE_device::discoveryCanceled()
{
    state = "Discovery canceled";
    emit stateChanged();
}

void BLE_device::discoveryError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    static QMetaEnum meta_enum = discoveryAgent->metaObject()->enumerator(
                discoveryAgent->metaObject()->indexOfEnumerator("Error"));

    QString errorCode = QLatin1String(meta_enum.valueToKey(error));

    state = "Error occured (error code: " + errorCode + "). Re-running discovery";

    emit stateChanged();
    startDeviceDiscovery();
}

void BLE_device::connectionError(QLowEnergyController::Error newError)
{
    static QMetaEnum meta_enum = LEcontroller->metaObject()->enumerator(
                LEcontroller->metaObject()->indexOfEnumerator("Error"));

    QString errorCode = QLatin1String(meta_enum.valueToKey(newError));

    if (state == "Connection error occured: cannot connect to the device")
        return;
    else
        state = "Connection error occured: " + errorCode;

    emit stateChanged();

}

void BLE_device::connectToDevice(QString address)
{

    BLE_Valve *dev = nullptr;

    for(auto v : Valves)
    {
        dev = qobject_cast<BLE_Valve *>(v);
        if (dev->getDevice().address().toString() == address)
            break;
    }

    // check if there is any existing connection
    if(LEcontroller && connectedDevice)
    {
        // disconnect from current device
            LEcontroller->disconnectFromDevice();
            delete connectedDevice;
            connectedDevice = nullptr;
            delete LEcontroller;
            LEcontroller = nullptr;
    }

    state = "Connecting to device (address: " + address + ") ...";
    emit stateChanged();


    connectedDevice = dev;

    LEcontroller = QLowEnergyController::createCentral(connectedDevice->getDevice());
    connect(LEcontroller, &QLowEnergyController::connected, this, &BLE_device::deviceConnected);
    connect(LEcontroller, &QLowEnergyController::disconnected, this, &BLE_device::deviceDisconnected);
    connect(LEcontroller, &QLowEnergyController::serviceDiscovered, this, &BLE_device::addService);
    connect(LEcontroller, &QLowEnergyController::discoveryFinished, this, &BLE_device::discoveryFinished);
    connect(LEcontroller, &QLowEnergyController::discoveryFinished,
            this, &BLE_device::serviceScanDone);
    connect(LEcontroller, QOverload<QLowEnergyController::Error>::of(&QLowEnergyController::error),
            this, &BLE_device::connectionError);


    if (isRandomAddress())
        LEcontroller->setRemoteAddressType(QLowEnergyController::RandomAddress);
    else
        LEcontroller->setRemoteAddressType(QLowEnergyController::PublicAddress);

    LEcontroller->connectToDevice();
}

void BLE_device::stopConnectingToDevice()
{
    LEcontroller->disconnectFromDevice();
    state = "Connection error occured: cannot connect to the device";
    emit stateChanged();
}


void BLE_device::addService(const QBluetoothUuid &uuid)
{
    QLowEnergyService *serv = LEcontroller->createServiceObject(uuid);
    BLE_Service *s = new BLE_Service(serv);
    connectedDevice->Services.append(s);

    if(s->get_uuid() == SERVICE_UUID)
        connectedDevice->eqService = s;

    emit serviceAdded();

}

void BLE_device::addCharacteristics(int serviceIndex)
{

    QLowEnergyService * service = nullptr;


    BLE_Service *ble_s = qobject_cast <BLE_Service *> (connectedDevice->Services.at(serviceIndex));
    service = ble_s->getService();

    if (service->state() == QLowEnergyService::DiscoveryRequired)
    {
        connect(service, &QLowEnergyService::stateChanged, this, &BLE_device::discoverServiceDetails);
        service->discoverDetails();
        return;
    }

    const QList<QLowEnergyCharacteristic> LE_ch = service->characteristics();

    for (auto ch : LE_ch)
    {
        BLE_Characteristic *c = new BLE_Characteristic(ch);

        connectedDevice->Characteristics.append(c);

        // check whether given characteristic is one which allows reading/writing control commands
        if (ch.uuid().toString() == CHAR_UUID)
            connectedDevice->eqCharacteristic = new BLE_Characteristic(ch);
        else if (ch.uuid().toString() == NOTIFICATION)
            connectedDevice->notifCharacteristic = new BLE_Characteristic(ch);
    }
}

void BLE_device::serviceScanDone()
{
    for (int i = 0; i< connectedDevice->Services.size(); i++)
        addCharacteristics(i);

    connectionS = true;
    emit connectionSucceeed();
    state = "Connection succeeded";
    emit stateChanged();

}

void BLE_device::setState(const QString &new_state)
{
    state = new_state;
}


void BLE_device::discoverServiceDetails(QLowEnergyService::ServiceState sState)
{

    if (sState != QLowEnergyService::ServiceDiscovered)
        return;


    QLowEnergyService *service = qobject_cast <QLowEnergyService *> (sender());

    if(!service)
        return;


    const QList <QLowEnergyCharacteristic> qChars = service->characteristics();

    for (auto ch : qChars)
    {
        BLE_Characteristic *c = new BLE_Characteristic(ch);

        c->populateDescriptors();

        connectedDevice->Characteristics.append(c);

        // check whether given characteristic is one which allows reading/writing control commands
        if (ch.uuid().toString() == CHAR_UUID)
            connectedDevice->eqCharacteristic = new BLE_Characteristic(ch);       
        else if (ch.uuid().toString() == NOTIFICATION)
            connectedDevice->notifCharacteristic = new BLE_Characteristic(ch);


        emit characteristicsUpdated();
    }


}

QVariant BLE_device::getCharacteristics()
{
    return QVariant::fromValue(connectedDevice->Characteristics);
}

QVariant BLE_device::getFoundValves()
{
    return QVariant::fromValue(Valves);
}


bool BLE_device::getConnectionS()
{
    return connectionS;
}

bool BLE_device::isRandomAddress() const
{
    return randomAddress;
}


int BLE_device::rowCount(const QModelIndex &parent) const
{
    return userProfiles.size();
}

QVariant BLE_device::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == CONNECTEDDEVICE)
        return QVariant::fromValue(connectedDevice);
    else if (role == USERSPROFILE)
        return QVariant::fromValue(userProfiles);
    else if (role == PROFILETEMP)
        return QVariant::fromValue(userProfiles.at(index.row())->temp());
    else if (role == PROFILEHOURSfrom)
    {
        if (!index.row())
            return "00";
        else
            return QVariant::fromValue(userProfiles.at(index.row()-1)->getProfileHour());
    }
    else if (role == PROFILEMINSfrom)
    {
        if (!index.row())
            return "00";
        else
            return QVariant::fromValue(userProfiles.at(index.row()-1)->getProfileMins());
    }

    return QVariant();
}

QHash<int, QByteArray> BLE_device::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles[CONNECTEDDEVICE] = "ConnectedDevice";
    roles[USERSPROFILE] = "usersProfile";
    roles[PROFILETEMP] = "profileTemp";
    roles[PROFILEHOURSfrom] = "profileHourFrom";
    roles[PROFILEMINSfrom] = "profileMinsFrom";

    return roles;
}

BLE_Valve *BLE_device::getDevice()
{
    return connectedDevice;
}
void BLE_device::set_temp(QString temp)
{
    connectedDevice->setTemperature(temp);
}

void BLE_device::setAutoManual(bool mode)
{
    connectedDevice->setAutoManual(mode);
}

void BLE_device::lock(bool onOff)
{
    connectedDevice->lock(onOff);
}

void BLE_device::setReduced(bool onOff)
{
    connectedDevice->setReduced(onOff);
}

void BLE_device::setComfort(bool onOff)
{
    connectedDevice->setComfort(onOff);
}

void BLE_device::boost(bool onOff)
{
    connectedDevice->boost(onOff);
}

void BLE_device::setDateTime(const QDate newDate, const QTime newTime)
{
    connectedDevice->setDateTime(newDate, newTime);
}

void BLE_device::modifyComfortReducedTemp(const QString &newComfort, const QString &newReduced)
{
    double comfTemp = newComfort.toDouble();
    double redTemp = newReduced.toDouble();

    if (comfTemp > (floor(comfTemp)+0.5)) comfTemp = floor(comfTemp) + 0.5;
    else comfTemp = floor(comfTemp);

    if (redTemp > (floor(redTemp)+0.5)) redTemp = floor(redTemp) + 0.5;
    else redTemp = floor(redTemp);


    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getComfortReducedModified);

    connectedDevice->modifyComfortReducedTemp(static_cast<float>(comfTemp), static_cast<float>(redTemp));

}

void BLE_device::setOffsetTemp(const QString &offset)
{
    float offsetTemp = offset.toFloat();

    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getOffsetTempSet);

    connectedDevice->setOffsetTemp(offsetTemp);

}

void BLE_device::modifyWindowMode(const float windowTemp, const int durationTime)
{
    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getWindowModeModified);

    connectedDevice->modifyWindowMode(windowTemp, durationTime);
}

void BLE_device::setHolidayMode(const QString hTemp, const QTime hTime, const QString daytime, const QDate hDate)
{
    connectedDevice->setHolidayMode(hTemp, hTime, daytime, hDate);
}

void BLE_device::askForDailyProfiles()
{
    if (connectedDevice->m_models.size() >= 7)
        return;

    BLE_Characteristic *bch = nullptr;

    for (auto ch : connectedDevice->Characteristics)
    {
        bch = qobject_cast <BLE_Characteristic *>(ch);
        if (bch->getCharacteristic().uuid().toString() == NOTIFICATION)
            break;
    }

    if (bch)
    {
        QLowEnergyDescriptor d = bch->getCharacteristic().descriptor(
                    QBluetoothUuid::ClientCharacteristicConfiguration);

        if(d.isValid())
        {

            if(bch->getCharacteristic().properties() & QLowEnergyCharacteristic::Notify)
                // enable receiving notifications ("0100" - enable; "0000" - disable)
                connectedDevice->eqService->getService()->writeDescriptor(d, QByteArray::fromHex("0100"));
        }

        connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicChanged, connectedDevice, &BLE_Valve::getDailyProfileResponse);
        connect(connectedDevice, &BLE_Valve::dailyProfileReceived, this, &BLE_device::askForNextProfile);


        connectedDevice->askForDailyProfiles(0);

    }

}

bool BLE_device::createNewEvent()
{
    // only 7 events can be defined
    if (userProfiles.size() >= 7)
        return false;

    int lastHour, lastByOneHour, lastMin, lastByOneMin = 0;

    if (userProfiles.size() >= 2) {

        lastHour = userProfiles.last()->getProfileHour().toInt();
        lastByOneHour = userProfiles.at(userProfiles.size()-2)->getProfileHour().toInt();
        lastMin = userProfiles.last()->getProfileMins().toInt();
        lastByOneMin = userProfiles.at(userProfiles.size()-2)->getProfileMins().toInt();

        // check, whether last insterted time is greater than the previous one
        if ((lastHour <= lastByOneHour) && (lastMin <= lastByOneMin))
            return false;
        else {
            beginInsertRows(QModelIndex(), userProfiles.size(), userProfiles.size());
            userProfiles.append(new Event("17.0"));
            endInsertRows();
        }
    }

    else {

        lastHour = userProfiles.at(0)->getProfileHour().toInt();
        lastMin = userProfiles.at(0)->getProfileMins().toInt();

        if (!lastHour && !lastMin)
            return false;
        else {
            beginInsertRows(QModelIndex(), userProfiles.size(), userProfiles.size());
            userProfiles.append(new Event("17.0"));
            endInsertRows();
        }
    }

    return true;

}

void BLE_device::removeLastEvent()
{
    if (userProfiles.size() <= 1)
        return;

    beginRemoveRows(QModelIndex(), userProfiles.size()-1, userProfiles.size()-1);
    userProfiles.removeLast();
    endRemoveRows();
}

void BLE_device::updateHour(int index, QString hour)
{
    userProfiles.at(index)->setProfileHour(hour);
}

void BLE_device::updateMins(int index, QString mins)
{
    userProfiles.at(index)->setProfileMins(mins);
}

void BLE_device::updateTemp(int index, float temp)
{
    userProfiles.at(index)->setTemp(temp);
}

void BLE_device::setNewDailyProfiles(QString day)
{
    QByteArray profilesData;
    char data;

    for(auto i: userProfiles)
    {

        data = static_cast<char>(2 * i->getTemp().toFloat());
        profilesData.append(data);
        data = static_cast<char>(i->getProfileHour().toInt() * 6 + i->getProfileMins().toInt()/10);
        profilesData.append(data);
    }

    if (userProfiles.size() < 7)
    {
        for (int i = 0; i< 2 * (7 - userProfiles.size()); i++)
        {
            profilesData.append("0");
        }
    }

    connectedDevice->setNewDailyProfiles(day, profilesData);
}

void BLE_device::disconnectFromDevice()
{
    if (LEcontroller->state() != QLowEnergyController::UnconnectedState)
    {
        LEcontroller->disconnectFromDevice();
        delete connectedDevice;
        delete LEcontroller;
        connectedDevice = nullptr;
        LEcontroller = nullptr;

        state = "Disconnected";
        emit stateChanged();

    }

}

void BLE_device::askForNextProfile()
{
    if (connectedDevice->m_models.size() >= 7)
        return;

    ++day;
    connectedDevice->askForDailyProfiles(day);
}

