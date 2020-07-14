#ifndef DEVICE_H
#define DEVICE_H

#include "BLE_Valve.h"
#include "BLE_Service.h"
#include "BLE_Characteristic.h"

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QList>
#include <QVariant>
#include <QDate>
#include <QAbstractListModel>


class BLE_device: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVariant foundValves READ getFoundValves NOTIFY valvesDiscovered)
    Q_PROPERTY(QString programState READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(bool connectionS READ getConnectionS NOTIFY connectionSucceeed)


public:
    BLE_device();
    ~BLE_device();

    QString getState();
    QVariant getCharacteristics();
    QVariant getFoundValves();
    quint8 getCharAmount();
    bool getConnectionS();
    bool isRandomAddress() const;


    // QAbstract model interface
    enum SOmeModelRoles {
        CONNECTEDDEVICE = Qt::UserRole+1,
        USERSPROFILE,
        PROFILEHOURSfrom,
        PROFILEMINSfrom,
        PROFILETEMP
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void askForDailyProfiles();
    Q_INVOKABLE bool createNewEvent();
    Q_INVOKABLE void removeLastEvent();
    Q_INVOKABLE void updateHour(int index, QString hour);
    Q_INVOKABLE void updateMins(int index, QString mins);
    Q_INVOKABLE void updateTemp(int index, float temp);


protected:
    QHash<int, QByteArray> m_roles;
    BLE_Valve* connectedDevice;
    QVector <Event *> userProfiles;


public slots:
    BLE_Valve *getDevice();

    void startDeviceDiscovery();
    void connectToDevice(QString address);
    void stopConnectingToDevice();
    void discoverServiceDetails(QLowEnergyService::ServiceState sState);

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

    void askForNextProfile();
    void setNewDailyProfiles(QString day);
    void disconnectFromDevice();


private slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void discoveryFinished();
    void addDevice(const QBluetoothDeviceInfo &device);
    void deviceConnected();
    void deviceDisconnected();
    void discoveryCanceled();
    void discoveryError(const QBluetoothDeviceDiscoveryAgent::Error error);
    void connectionError(QLowEnergyController::Error newError);
    void addService(const QBluetoothUuid &uuid);
    void addCharacteristics(int serviceIndex);
    void serviceScanDone();


Q_SIGNALS:
    void serviceAdded();
    void characteristicsUpdated();
    void characteristicFound();
    void valvesDiscovered();
    void stateChanged();
    void reducedChanged();
    void comfortChanged();
    void cannotConnectToDevice();
    void connectionSucceeed();

private:
    void setState(const QString &new_state);
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QList <QObject *> Valves;

    QLowEnergyController *LEcontroller = nullptr;

    QString state = "Program state";
    quint8 day = 0;
    bool connectionS = false;
    bool randomAddress = false;

};


#endif // DEVICE_H
