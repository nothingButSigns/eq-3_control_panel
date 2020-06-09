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

