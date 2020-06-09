#include <BLE_Service.h>

BLE_Service::BLE_Service(QLowEnergyService *service)
{
    ble_service = service;
}

BLE_Service::~BLE_Service(){};

QLowEnergyService *BLE_Service::getService()
{
    return ble_service;
}

QString BLE_Service::get_uuid()
{
    QBluetoothUuid bt_uuid = ble_service->serviceUuid();
    return bt_uuid.toString();
}

void BLE_Service::characteristicReading(const QLowEnergyCharacteristic &characteristic)
{
    if(ble_service)
    {
        ble_service->readCharacteristic(characteristic);
    }
}

void BLE_Service::characteristicWriting(const QLowEnergyCharacteristic &charact, const QByteArray &value)
{
    if(ble_service)
    {
        ble_service->writeCharacteristic(charact, value);
        emit characteristicWritten();
    }
}
