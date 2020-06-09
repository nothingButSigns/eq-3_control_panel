#include "BLE_Valve.h"

BLE_Valve::BLE_Valve(const QBluetoothDeviceInfo &d)
{
    BtDevice = d;
}

BLE_Valve::~BLE_Valve()
{

}

void BLE_Valve::setDevice(const QBluetoothDeviceInfo &device)
{
    BtDevice = device;
}

QBluetoothDeviceInfo BLE_Valve::getDevice()
{
    return BtDevice;
}

QString BLE_Valve::getName()
{
    return BtDevice.name();
}

QString BLE_Valve::getAddress()
{
    QBluetoothAddress address =  BtDevice.address();
    QString addr = address.toString();
    return addr;
}

void BLE_Valve::setCustomName(QString name)
{
    customName = name;
}

void BLE_Valve::setTemperature(QString temperature)
{
    qDebug() << "Inside 'writeCHaracteristic'";



    int tempInt = temperature.toInt();
    QByteArray value;
    value.resize(2);
    value[0] = SET_TEMP;
    value[1] = 2 * static_cast<char>(tempInt);
    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);

}

void BLE_Valve::setAutoManual(bool mode)
{
    qDebug() << "Inside set MODE 'writeCHaracteristic'";


    QByteArray value;
    value.resize(2);

    if (mode)
    {
        // set auto mode
        value[0] = AUTO_1_BIT;
        value[1] = AUTO_2_BIT;
    }
    else
    {
        // set manual mode
        value[0] = MANUAL_1_BIT;
        value[1] = MANUAL_2_BIT;
    }

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}

void BLE_Valve::lock(bool onOff)
{
    qDebug() << "Inside LOCK 'writeCHaracteristic'";

    QByteArray value;
    value.resize(2);

    if (onOff)
    {
        // lock the valve
        value[0] = LOCK;
        value[1] = ON;
    }
    else
    {
        // unlock the valve
        value[0] = LOCK;
        value[1] = OFF;
    }

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}

void BLE_Valve::setReduced(bool onOff)
{
    QByteArray value;
    value.resize(1);

    if (onOff)
    {
        // activate Reduced temperature
        value[0] = SET_REDUCED;
    }
    else
    {
        // deactivate Reduced temperature
        //value[0] = LOCK;
    }

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);

}

void BLE_Valve::setComfort(bool onOff)
{
    QByteArray value;
    value.resize(1);

    if (onOff)
    {
        // activate Reduced temperature
        value[0] = SET_COMFORT;
    }
    else
    {
        // deactivate Reduced temperature
        //value[0] = LOCK;
    }

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);

}

void BLE_Valve::boost(bool onOff)
{

    QByteArray value;
    value.resize(2);

    if (onOff)
    {
        // activate boost mode
        value[0] = BOOST;
        value[1] = ON;
    }
    else
    {
        // deactivate boost mode
        value[0] = BOOST;
        value[1] = OFF;
    }

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);

}

void BLE_Valve::getCharacteristicWritten(const QLowEnergyCharacteristic &info,
                                          const QByteArray &value)
{
/*    QString value_text = "";
    QString info_text = "";
    for (auto i : value)
    {
        value_text += QString(i) + " ";
    }
    for (auto i : info.value())
    {
        info_text += QString(i) + " ";
    }
*/


    qDebug() << "Response characteristic UUID: " << info.uuid();
    qDebug() << "Response characteristic VALUE: " << info.value().size();
    qDebug() << "Response characteristic QByteArray SIZE: " << value.size();
}
