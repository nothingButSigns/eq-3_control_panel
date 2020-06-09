#include "BLE_device.h"
#include "eq-3.h"

#include <QtGlobal> //for qDebug()
#include <QtDebug> //for qDebug()
#include <QTimer>
#include <QString>
#include <QList>


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
