#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QLowEnergyService>


class BLE_Service: public QObject
{

    Q_OBJECT

public:
    BLE_Service(QLowEnergyService *service);
    ~BLE_Service();

   QLowEnergyService *getService();
   QString get_uuid();
   void characteristicReading(const QLowEnergyCharacteristic &characteristic);
   void characteristicWriting(const QLowEnergyCharacteristic &charact, const QByteArray &value);


Q_SIGNALS:
   void characteristicWritten();

private:
    QLowEnergyService *ble_service = nullptr;

};


#endif // SERVICE_H


