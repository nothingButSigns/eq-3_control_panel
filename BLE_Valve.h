#ifndef DISCOVEREDDEVICE_H
#define DISCOVEREDDEVICE_H

#include "QObject"
#include <QBluetoothDeviceDiscoveryAgent>
#include <qbluetoothdeviceinfo.h>
#include "eq-3.h"
#include "BLE_Service.h"
#include "BLE_Characteristic.h"

class BLE_Valve: public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString devName READ getName NOTIFY devChanged)
    Q_PROPERTY(QString devAddress READ getAddress NOTIFY devChanged)

public:
    BLE_Valve() = default; //the compiler creates constructor with no args even if other constructors are present
    BLE_Valve(const QBluetoothDeviceInfo &d);
    ~BLE_Valve();

    void setDevice(const QBluetoothDeviceInfo &device);
    QBluetoothDeviceInfo getDevice();
    QString getName();
    QString getAddress();
    void setCustomName(QString name);

public slots:
    void setTemperature(QString temperature);
    void setAutoManual(bool mode);
    void lock(bool onOff);
    void setReduced(bool onOff);
    void setComfort(bool onOff);
    void boost(bool onOff);
    void getCharacteristicWritten(const QLowEnergyCharacteristic &info,
                                              const QByteArray &value);



Q_SIGNALS:
    void devChanged();

    friend class BLE_device;

private:
    QBluetoothDeviceInfo BtDevice;
    QString customName;
    float temperature;

protected:
    QList <QObject *> Services;
    QList <QObject *> Characteristics;
    BLE_Characteristic *eqCharacteristic = nullptr;
    BLE_Service *eqService = nullptr;


};

#endif // DISCOVEREDDEVICE_H
