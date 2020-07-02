#include "BLE_device.h"
#include "eq-3.h"

#include <QtGlobal> //for qDebug()
#include <QtDebug> //for qDebug()
#include <QTimer>
#include <QString>
#include <QList>
#include <cmath>


BLE_device::BLE_device()
{
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    discoveryAgent->setLowEnergyDiscoveryTimeout(5000); //set how much time the scan will take
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this,
            &BLE_device::deviceDiscovered);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this,
            &BLE_device::discoveryFinished);
//    connect(this, &BLE_device::startConnecting, this, &BLE_device::connectToDevice);
    connect(LEcontroller, &QLowEnergyController::connected, this, &BLE_device::deviceConnected);
    connect(this, &BLE_device::serviceAdded, this, &BLE_device::addCharacteristics);


    beginInsertRows(QModelIndex(), userProfiles.size(), userProfiles.size());
    userProfiles.append(new Event("17.0", "00:00"));
    endInsertRows();

}

BLE_device::~BLE_device()
{
    delete discoveryAgent;
    delete LEcontroller;
}

QString BLE_device::getState()
{
    return state;
}

void BLE_device::startDeviceDiscovery()
{
     discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BLE_device::addDevice(const QBluetoothDeviceInfo &device)
{
    // Search for BLE devices only
    if(device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        BLE_Valve *element = new BLE_Valve(device);
        QString letter = device.name();

        // determine what type of BLE device was found (a radiator valve or a lightbulb)
        if (letter[0] == 'B')
        {
            Lightbulbs.append(element);
        }
        else if (letter[0] == 'C')
        {
            Valves.append(element);
        }

        qDebug() << "Device " << letter[0] <<" added";
    }
}

void BLE_device::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    qDebug() << "Found new device: "<< device.name() << "(" << device.address().toString() << ")";
    addDevice(device);
    emit valvesDiscovered();
}

void BLE_device::discoveryFinished()
{
    qDebug() << "Scan finished!";
   // emit startConnecting();
}

void BLE_device::deviceConnected()
{
    qDebug() << "Device connected";
    LEcontroller->discoverServices();

}

void BLE_device::connectToDevice(QString address)
{
    BLE_Valve *dev = nullptr;

    for(auto v : Valves)
    {
        dev = qobject_cast<BLE_Valve *>(v);
        if (dev->getDevice().address().toString() == address)
        {
            break;
        }
    }

    // check if there is any existing connection
    if(LEcontroller)
    {
        // disconnect from current device
        if (connectedDevice->getAddress() != address)
        {
            LEcontroller->disconnectFromDevice();
            delete connectedDevice;
        }

        else return;

    }

    connectedDevice = dev;

    LEcontroller = QLowEnergyController::createCentral(connectedDevice->getDevice());
    connect(LEcontroller, &QLowEnergyController::connected, this, &BLE_device::deviceConnected);
    connect(LEcontroller, &QLowEnergyController::serviceDiscovered, this, &BLE_device::addService);
    connect(LEcontroller, &QLowEnergyController::discoveryFinished, this, &BLE_device::addCharacteristics);
    connect(this, &BLE_device::nextCharacteristic, this, &BLE_device::addCharacteristics);
    //connect(this, &BLE_device::characteristicFound, connectedDevice, &BLE_Valve::setTemperature);

    LEcontroller->setRemoteAddressType(QLowEnergyController::PublicAddress);
    qDebug() << "connecting to device";
    LEcontroller->connectToDevice();
}


void BLE_device::addService(const QBluetoothUuid &uuid)
{
    QLowEnergyService *serv = LEcontroller->createServiceObject(uuid);
    BLE_Service *s = new BLE_Service(serv);
    connectedDevice->Services.append(s);

    // Check whether given service is the one allowing valve control
    if (uuid.toString() == SERVICE_UUID)
    {
        connectedDevice->eqService = new BLE_Service(serv);
        qDebug() << "EQ-3 control service has been found";

    }
  //  QLowEnergyCharacteristic QLEch = serv->characteristic(uuid);
  /*  qDebug() << "Name: " << serv->characteristics().at(0).name();
        qDebug() << "Name: " << serv->characteristics().at(0).properties();
            qDebug() << "Name: " << serv->characteristics().at(0).handle();*/


    qDebug() << "Service added";
}

void BLE_device::addCharacteristics()
{
    QLowEnergyService * service = nullptr;
    if (serviceIndex >= connectedDevice->Services.size())
    {
       // emit characteristicFound("14");
        return;
    }

        BLE_Service *ble_s = qobject_cast <BLE_Service *> (connectedDevice->Services.at(serviceIndex));
        service = ble_s->getService();

//    qDebug() << "Service: " << service->serviceName();
//    qDebug() << "Service UUID: " << service->serviceUuid();
//    qDebug() << "State: " << service->state();

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
  /*      qDebug() << "Name: " << ch.name();
        qDebug() << "Properties: " << ch.properties();
        qDebug() << "Handler: " << ch.handle();
                qDebug() << "UUID: " << ch.uuid();
                        qDebug() << "value: " << ch.value();
                        */
        connectedDevice->Characteristics.append(c);
        charAmount++;
        // check whether given characteristic is one which allows reading/writing control commands
        if (ch.uuid().toString() == CHAR_UUID)
        {
            connectedDevice->eqCharacteristic = new BLE_Characteristic(ch);

        }
        else if (ch.uuid().toString() == NOTIFICATION)
        {
            connectedDevice->notifCharacteristic = new BLE_Characteristic(ch);
        }
    }

    qDebug() << "Characteristics amount: " << connectedDevice->Characteristics.size();

//    if (connectedDevice->Characteristics.size() == 8) emit characteristicFound();

    QTimer::singleShot(0, this, &BLE_device::characteristicsUpdated);


}

void BLE_device::setState(const QString &new_state)
{
    state = new_state;
}

void BLE_device::updateCharAmount(const quint8 amount)
{
    charAmount = amount;
}

void BLE_device::discoverServiceDetails(QLowEnergyService::ServiceState sState)
{
    if (sState != QLowEnergyService::ServiceDiscovered)
    {
        // queue the signal up
        if (sState != QLowEnergyService::DiscoveringServices)
        {
            QMetaObject::invokeMethod(this, "characteristicsUpdated", Qt::QueuedConnection);
        }
        return;
    }

    QLowEnergyService *service = qobject_cast <QLowEnergyService *> (sender());

    if(!service)
    {
        return;
    }

    const QList <QLowEnergyCharacteristic> qChars = service->characteristics();
    for (auto ch : qChars)
    {
        BLE_Characteristic *c = new BLE_Characteristic(ch);
        qDebug() << "ch.uuid: " << ch.uuid().toString();
        c->populateDescriptors();
        c->getDescInfo();

        connectedDevice->Characteristics.append(c);

 /*       qDebug() << "Name: " << ch.name();
        qDebug() << "Properties: " << ch.properties();
        qDebug() << "Handler: " << ch.handle();
                qDebug() << "UUID: " << ch.uuid();
                        qDebug() << "value: " << ch.value();
   */

        // check whether given characteristic is one which allows reading/writing control commands
        if (ch.uuid().toString() == CHAR_UUID)
        {
            connectedDevice->eqCharacteristic = new BLE_Characteristic(ch);
            qDebug() << "EQ-3 control characteristic has been found";
        }
        else if (ch.uuid().toString() == NOTIFICATION)
        {
            connectedDevice->notifCharacteristic = new BLE_Characteristic(ch);
        }

        charAmount++;
        emit characteristicsUpdated();
    }

        qDebug() << "Characteristics amount: " << connectedDevice->Characteristics.size();
    serviceIndex++;
    emit nextCharacteristic();

}

QVariant BLE_device::getCharacteristics()
{
    return QVariant::fromValue(connectedDevice->Characteristics);
}

QVariant BLE_device::getFoundValves()
{
    return QVariant::fromValue(Valves);
}

quint8 BLE_device::getCharAmount()
{
    return charAmount;
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
            return QVariant::fromValue(userProfiles.at(index.row()-1)->hour());
    }
    else if (role == PROFILEMINSfrom)
    {
        if (!index.row())
            return "00";
        else
            return QVariant::fromValue(userProfiles.at(index.row()-1)->mins());
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

//void BLE_device::connected()
//{
//    qDebug() << "COnnected";
////    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicRead, this, &BLE_device::getCharacteristicValue);
////    connectedDevice->eqService->characteristicReading(connectedDevice->eqCharacteristic->getCharacteristic());
//}



void BLE_device::getCharacteristicValue(const QLowEnergyCharacteristic &char_info,
                            const QByteArray &char_value)
{
    qDebug() << "Characteristics value: " << char_value;
    qDebug() << "Ch. UUID: " << char_info.uuid().toString();
}

void BLE_device::set_temp(QString temp)
{
    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getCharacteristicWritten);

    connectedDevice->setTemperature(temp);
}

void BLE_device::setAutoManual(bool mode)
{
    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getCharacteristicWritten);

    connectedDevice->setAutoManual(mode);
}

void BLE_device::lock(bool onOff)
{
    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getCharacteristicWritten);

    connectedDevice->lock(onOff);
}

void BLE_device::setReduced(bool onOff)
{
    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getCharacteristicWritten);

    connectedDevice->setReduced(onOff);

}

void BLE_device::setComfort(bool onOff)
{
    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getCharacteristicWritten);

    connectedDevice->setComfort(onOff);

}

void BLE_device::boost(bool onOff)
{
    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getCharacteristicWritten);

    connectedDevice->boost(onOff);

}

void BLE_device::setDateTime(const QDate newDate, const QTime newTime)
{
    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getCharacteristicWritten);

    connectedDevice->setDateTime(newDate, newTime);

}

void BLE_device::modifyComfortReducedTemp(const QString &newComfort, const QString &newReduced)
{
    float comfTemp = newComfort.toFloat();
    float redTemp = newReduced.toFloat();

    if (comfTemp > (floor(comfTemp)+0.5)) comfTemp = floor(comfTemp) + 0.5;
    else comfTemp = floor(comfTemp);

    if (redTemp > (floor(redTemp)+0.5)) redTemp = floor(redTemp) + 0.5;
    else redTemp = floor(redTemp);


    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getComfortReducedModified);

    connectedDevice->modifyComfortReducedTemp(comfTemp, redTemp);

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
    connect(connectedDevice->eqService->getService(), &QLowEnergyService::characteristicWritten, connectedDevice
            , &BLE_Valve::getCharacteristicWritten);

    connectedDevice->setHolidayMode(hTemp, hTime, daytime, hDate);

}

void BLE_device::askForDailyProfiles()
{
    qDebug() << "inside askFor...";

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
        //connect(connectedDevice, &BLE_Valve::dailyProfileReceived, this, &BLE_device::dailyProfilesFound);
        connect(connectedDevice, &BLE_Valve::dailyProfileReceived, this, &BLE_device::askForNextProfile);


            connectedDevice->askForDailyProfiles(0);

    }

}

void BLE_device::createNewEvent()
{
    // only 7 events can be defined
    if (userProfiles.size() >= 7)
        return;

    QString defaultTime = "00:00";
    QString defaultTemp = "17.0";

    beginInsertRows(QModelIndex(), userProfiles.size(), userProfiles.size());
    userProfiles.append(new Event("17.0", userProfiles.at(userProfiles.size())->getProfileTime()));
    endInsertRows();
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
    qDebug() <<"inside updateHOur, index = " << index;
    userProfiles.at(index)->setProfileHour(hour);
}

void BLE_device::updateMins(int index, QString mins)
{
    userProfiles.at(index)->setProfileMins(mins);
}

void BLE_device::askForNextProfile()
{
    qDebug() << "inside 'askForNextProfile'";

    if (connectedDevice->m_models.size() >= 7)
        return;

    ++day;
    connectedDevice->askForDailyProfiles(day);

}

