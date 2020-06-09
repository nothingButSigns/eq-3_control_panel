#ifndef CHARACTERISTIC_H
#define CHARACTERISTIC_H

#include <QObject>
#include <QtBluetooth/QLowEnergyCharacteristic>


class BLE_Characteristic: public QObject
{
    Q_OBJECT

public:
    BLE_Characteristic(QLowEnergyCharacteristic &characteristic);
    ~BLE_Characteristic();

    QLowEnergyCharacteristic getCharacteristic();


    private:

    QLowEnergyCharacteristic ble_characteristic;
};



#endif // CHARACTERISTIC_H
