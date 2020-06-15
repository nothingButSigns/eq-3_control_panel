#ifndef DISCOVEREDDEVICE_H
#define DISCOVEREDDEVICE_H

#include "QObject"
#include <QBluetoothDeviceDiscoveryAgent>
#include <qbluetoothdeviceinfo.h>
#include <QDate>
#include "eq-3.h"
#include "BLE_Service.h"
#include "BLE_Characteristic.h"
#include "DailyProfile.h"
#include <QMetaType>
#include <QTimer>


Q_DECLARE_METATYPE (QList <QByteArray *>);

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

    enum ProfileRequestState {
        ProcessingProfileData = 0,
        ReadyForMore
    } reqState;
    Q_ENUM(ProfileRequestState)

public slots:
    void setTemperature(QString temperature);
    void setAutoManual(bool mode);
    void lock(bool onOff);
    void setReduced(bool onOff);
    void setComfort(bool onOff);
    void boost(bool onOff);
    void setDateTime(const QDate &newDate, const QTime &newTime);
    void modifyComfortReducedTemp(const float &newComfort, const float &newReduced);
    void setOffsetTemp(const float offset);
    void modifyWindowMode(const float windowTemp, const int durationTime);
    void setHolidayMode(const QString hTemp, const QTime hTime, const QString daytime, const QDate hDate);
    void askForDailyProfiles(int day);

    void getCharacteristicWritten(const QLowEnergyCharacteristic &info,
                                              const QByteArray &value);
    void getComfortReducedModified(const QLowEnergyCharacteristic &info,
                                   const QByteArray &value);
    void getOffsetTempSet(const QLowEnergyCharacteristic &info,
                          const QByteArray &value);
    void getWindowModeModified(const QLowEnergyCharacteristic &info,
                               const QByteArray &value);
    void getDailyProfileResponse(const QLowEnergyCharacteristic &info,
                                 const QByteArray &value);
    void getDailyProfileResponse2(const QLowEnergyCharacteristic &info,
                                 const QByteArray &value);


Q_SIGNALS:
    void devChanged();
    void dailyProfileReceived();

    friend class BLE_device;

private:
    QBluetoothDeviceInfo BtDevice;
    QString customName;
    float temperature;
    float comfortTemp = 20.0;
    float reducedTemp = 22.0;
    float offsetTemp = 0.0;
    float windowModeTemp = 16.0;
    int windowModeDuration = 0;

protected:
    QList <QObject *> Services;
    QList <QObject *> Characteristics;
    QList <QObject *> dailyProfiles;


    BLE_Characteristic *eqCharacteristic = nullptr;
    BLE_Characteristic *notifCharacteristic = nullptr;
    BLE_Service *eqService = nullptr;


};

#endif // DISCOVEREDDEVICE_H
