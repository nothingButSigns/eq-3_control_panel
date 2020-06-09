#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QList>
#include <QVariant>
#include "BLE_Valve.h"
#include "BLE_Service.h"
#include "BLE_Characteristic.h"

class BLE_device: public QObject
{
    Q_OBJECT
  //  Q_PROPERTY(QVariant searching READ discoveryFinished NOTIFY startConnecting)
//    Q_PROPERTY(QVariant characteristicList READ getCharacteristics NOTIFY characteristicsUpdated)
    Q_PROPERTY(QVariant foundValves READ getFoundValves NOTIFY valvesDiscovered)
    Q_PROPERTY(QString state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(quint8 characteristicsAmount READ getCharAmount WRITE updateCharAmount NOTIFY characteristicsUpdated)


public:
    BLE_device();
    ~BLE_device();

    QString getState();
    QVariant getCharacteristics();
    QVariant getFoundValves();
    quint8 getCharAmount(); //to know if all characteristics has been found and enable communicating with a valve if so



public slots:
    void startDeviceDiscovery();
    void connectToDevice(QString address);
//    void readCharacteristic();
    void discoverServiceDetails(QLowEnergyService::ServiceState sState);
    void getCharacteristicValue(const QLowEnergyCharacteristic &char_info,
                                const QByteArray &char_value);
    void set_temp(QString temp);
    void setAutoManual(bool mode);
    void lock(bool onOff);
    void setReduced(bool onOff);
    void setComfort(bool onOff);
    void boost(bool onOff);


private slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void discoveryFinished();
    void addDevice(const QBluetoothDeviceInfo &device);
    void deviceConnected();
    void addService(const QBluetoothUuid &uuid);
    void addCharacteristics();

Q_SIGNALS:
    void startConnecting();
    void serviceAdded();
    void characteristicsUpdated();
    void nextCharacteristic();
    void characteristicFound();
    void valvesDiscovered();
    void stateChanged();

private:
    void setState(const QString &new_state);
    void updateCharAmount(const quint8 amount);
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QList <QObject *> Valves;
    QList <QObject *> Lightbulbs;
    BLE_Valve* connectedDevice;

    QLowEnergyController *LEcontroller = nullptr;

    QString state;
    quint8 serviceIndex = 0;
    quint8 charAmount = 0;
};


#endif // DEVICE_H
