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
    QLowEnergyCharacteristic getNoifCharacteristic();
    void populateDescriptors();
    void getDescInfo();


    private:
    QList <QLowEnergyDescriptor> descriptors;


    QLowEnergyCharacteristic ble_characteristic;
    QLowEnergyCharacteristic notification_char;
};



#endif // CHARACTERISTIC_H
