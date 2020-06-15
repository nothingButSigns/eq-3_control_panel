#include "BLE_Characteristic.h"

BLE_Characteristic::BLE_Characteristic(QLowEnergyCharacteristic &characteristic)
{
    ble_characteristic = characteristic;
}

BLE_Characteristic::~BLE_Characteristic()
{

}

QLowEnergyCharacteristic BLE_Characteristic::getCharacteristic()
{
    return ble_characteristic;
}

QLowEnergyCharacteristic BLE_Characteristic::getNoifCharacteristic()
{
    return notification_char;
}

void BLE_Characteristic::populateDescriptors()
{
    descriptors = ble_characteristic.descriptors();
}

void BLE_Characteristic::getDescInfo()
{
    for (auto desc : descriptors)
        qDebug() << "desc name: " << desc.name() << "desc type: " << desc.type();
}

