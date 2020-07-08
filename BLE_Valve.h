#ifndef DISCOVEREDDEVICE_H
#define DISCOVEREDDEVICE_H

#include "QObject"
#include "eq-3.h"
#include "BLE_Service.h"
#include "BLE_Characteristic.h"
#include "DailyProfile.h"
#include <QBluetoothDeviceDiscoveryAgent>
#include <qbluetoothdeviceinfo.h>
#include <QDate>
#include <QMetaType>
#include <QTimer>
#include <QAbstractListModel>


class BLE_Valve: public QAbstractListModel
{

    Q_OBJECT
    Q_PROPERTY(QString devName READ getName NOTIFY devChanged)
    Q_PROPERTY(QString devAddress READ getAddress NOTIFY devChanged)

public:

    // AbstractLIstModel interface
    enum SubModelRoles {
        DAY = Qt::UserRole+1,
        DPROFILE
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

protected:
    QVector <DailyProfile*> m_models;
    QHash<int, QByteArray> m_roles;

public:

    BLE_Valve() = default;
    BLE_Valve(const QBluetoothDeviceInfo &d);
    ~BLE_Valve();

    void setDevice(const QBluetoothDeviceInfo &device);
    QBluetoothDeviceInfo getDevice();
    QString getName();
    QString getAddress();
    void setCustomName(QString name);

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
    void setNewDailyProfiles(const QString day, const QByteArray &data);
    char weekdaysResolver(QString day);

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


    BLE_Characteristic *eqCharacteristic = nullptr;
    BLE_Characteristic *notifCharacteristic = nullptr;
    BLE_Service *eqService = nullptr;


};

#endif // DISCOVEREDDEVICE_H
