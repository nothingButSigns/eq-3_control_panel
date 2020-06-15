#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QList>
#include <QVariant>
#include <QDate>
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
    Q_PROPERTY(QVariant dailyProfiles READ getDailyProfiles NOTIFY dailyProfilesFound)
    Q_PROPERTY(QVariant Profile READ getProfile NOTIFY newProfile)


public:
    BLE_device();
    ~BLE_device();

    QString getState();
    QVariant getCharacteristics();
    QVariant getFoundValves();
    quint8 getCharAmount(); //to know if all characteristics has been found and enable communicating with a valve if so
    QVariant getDailyProfiles();
    QVariant getProfile();




public slots:
    BLE_Valve *getDevice();

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
    void setDateTime(const QDate newDate, const QTime newTime);
    void modifyComfortReducedTemp(const QString &newComfort, const QString &newReduced);
    void setOffsetTemp(const QString &offset);
    void modifyWindowMode(const float windowTemp, const int durationTime);
    void setHolidayMode(const QString hTemp, const QTime hTime, const QString daytime, const QDate hDate);
    void askForDailyProfiles();
    void askForNextProfile();


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
    void reducedChanged();
    void comfortChanged();
    void dailyProfilesFound();
    void newProfile();

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
    quint8 day = 0;

};


#endif // DEVICE_H
