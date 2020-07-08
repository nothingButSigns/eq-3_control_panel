#include "BLE_Valve.h"

int BLE_Valve::rowCount(const QModelIndex &parent) const
{
    return m_models.size();
}

QVariant BLE_Valve::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == DAY)
        return m_models.at(index.row())->readDay();
    else if(role == DPROFILE)
        return QVariant::fromValue(m_models.at(index.row()));

    return QVariant();
}

QHash<int, QByteArray> BLE_Valve::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles[DAY] = "DayM";
    roles[DPROFILE] = "dailyProfile";

    return roles;
}

BLE_Valve::BLE_Valve(const QBluetoothDeviceInfo &d)
{
    BtDevice = d;
}

BLE_Valve::~BLE_Valve()
{

}

void BLE_Valve::setDevice(const QBluetoothDeviceInfo &device)
{
    BtDevice = device;
}

QBluetoothDeviceInfo BLE_Valve::getDevice()
{
    return BtDevice;
}

QString BLE_Valve::getName()
{
    return BtDevice.name();
}

QString BLE_Valve::getAddress()
{
    QBluetoothAddress address =  BtDevice.address();
    QString addr = address.toString();
    return addr;
}

void BLE_Valve::setCustomName(QString name)
{
    customName = name;
}

void BLE_Valve::setTemperature(QString temperature)
{
    int tempInt = static_cast<int>(2 * temperature.toFloat());
    QByteArray value;
    value.resize(2);
    value[0] = SET_TEMP;
    value[1] = static_cast<char>(tempInt);
    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);

}

void BLE_Valve::setAutoManual(bool mode)
{

    QByteArray value;
    value.resize(2);

    if (mode)
    {
        // set auto mode
        value[0] = AUTO_1_BIT;
        value[1] = AUTO_2_BIT;
    }
    else
    {
        // set manual mode
        value[0] = MANUAL_1_BIT;
        value[1] = MANUAL_2_BIT;
    }

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}

void BLE_Valve::lock(bool onOff)
{

    QByteArray value;
    value.resize(2);

    if (onOff)
    {
        // lock the valve
        value[0] = LOCK;
        value[1] = ON;
    }
    else
    {
        // unlock the valve
        value[0] = LOCK;
        value[1] = OFF;
    }

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}

void BLE_Valve::setReduced(bool onOff)
{
    QByteArray value;
    value.resize(1);

    if (onOff)
    {
        // activate Reduced temperature
        value[0] = SET_REDUCED;
    }

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}

void BLE_Valve::setComfort(bool onOff)
{
    QByteArray value;
    value.resize(1);

    if (onOff)
    {
        // activate Reduced temperature
        value[0] = SET_COMFORT;
    }

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);

}

void BLE_Valve::boost(bool onOff)
{

    QByteArray value;
    value.resize(2);

    if (onOff)
    {
        // activate boost mode
        value[0] = BOOST;
        value[1] = ON;
    }
    else
    {
        // deactivate boost mode
        value[0] = BOOST;
        value[1] = OFF;
    }

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);

}

void BLE_Valve::setDateTime(const QDate &newDate, const QTime &newTime)
{

    QByteArray value;
    value.resize(7);

        // set date and time
        value[0] = SET_DATE_TIME;
        value[1] = static_cast<char>(newDate.year() % 100);
        value[2] = static_cast<char>(newDate.month());
        value[3] = static_cast<char>(newDate.day());
        value[4] = static_cast<char>(newTime.hour());
        value[5] = static_cast<char>(newTime.minute());
        value[6] = static_cast<char>(newTime.second());

        eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}

void BLE_Valve::modifyComfortReducedTemp(const float &newComfort, const float &newReduced)
{
    QByteArray value;
    value.resize(3);
    value[0] = MODIFY_COMF_RED;

    if(!static_cast<bool>(newComfort))
        value[1] = static_cast<char>(comfortTemp*2);
    else
        value[1] = static_cast<char>(newComfort*2);


    if(!static_cast<bool>(newReduced))
        value[2] = static_cast<char>(reducedTemp*2);
    else
        value[2] = static_cast<char>(newReduced*2);

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}

void BLE_Valve::setOffsetTemp(const float offset)
{
    QByteArray value;
    value.resize(2);
    value[0] = SET_OFFSET;
    value[1] = static_cast<char>((2*offset)+7);

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}

void BLE_Valve::modifyWindowMode(const float windowTemp, const int durationTime)
{
    QByteArray value;
    value.resize(3);

    value[0] = WINDOW_MODE;
    value[1] = static_cast<char>(windowTemp * 2);
    value[2] = static_cast<char>(durationTime/5);

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}

void BLE_Valve::setHolidayMode(const QString hTemp, const QTime hTime, const QString daytime, const QDate hDate)
{
    QByteArray value;
    value.resize(6);

    int hour_2 = 0;
    if (daytime == "am")
        hour_2 = hTime.hour();
    else
        hour_2 = hTime.hour() + 12;

    value[0] = HOLIDAY;
    value[1] = static_cast<char>((hTemp.toFloat() * 2) + 128);
    value[2] = static_cast<char>(hDate.day());
    value[3] = static_cast<char>(hDate.year() % 100);
    value[4] = static_cast<char>((hour_2 * 2) + (hTime.minute() / 30));
    value[5] = static_cast<char>(hDate.month());

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}


void BLE_Valve::getCharacteristicWritten(const QLowEnergyCharacteristic &info,
                                          const QByteArray &value)
{

    qDebug() << "Response characteristic UUID: " << info.uuid();
    qDebug() << "Response characteristic VALUE: " << info.value().size();
    qDebug() << "Response characteristic QByteArray SIZE: " << value.size();
    qDebug() << "Response SENT VALUE: " << info.value().toHex();
}



void BLE_Valve::getComfortReducedModified(const QLowEnergyCharacteristic &info,
                                          const QByteArray &value)
{
    comfortTemp = value.at(1);
    reducedTemp = value.at(2);
}

void BLE_Valve::getOffsetTempSet(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
    offsetTemp = value.at(1);
}

void BLE_Valve::getWindowModeModified(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
    windowModeTemp = value.at(1)/2;
    windowModeDuration = value.at(2) * 5;
}

void BLE_Valve::getDailyProfileResponse(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
    qDebug() << "inside daily response";
    DailyProfile * ptr = new DailyProfile(value);
    beginInsertRows(QModelIndex(), m_models.size(), m_models.size());

    m_models.append(ptr);
    endInsertRows();

    QString result = value.toHex();
    result += QLatin1Char('\n');


    qDebug() << "Result: " <<result;

      emit dailyProfileReceived();


}

void BLE_Valve::getDailyProfileResponse2(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
    qDebug() << "REceived notif";

    QString result = value;
    result += QLatin1Char('\n');
    result += value.toHex();

    qDebug() << result;
}

void BLE_Valve::askForDailyProfiles(int day)
{
    qDebug() << "inside BLE_Valve; day = " << day;
    QByteArray value;
    value.resize(2);

    value[0] = READ_PROFILE;
    value[1] = static_cast<char>(day);

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), value);
}

void BLE_Valve::setNewDailyProfiles(const QString day, const QByteArray &data)
{
    QByteArray dataToBeSend;

    dataToBeSend.append(CREATE_PROFILE);
    dataToBeSend.append(weekdaysResolver(day));
    dataToBeSend += data;

    eqService->characteristicWriting(eqCharacteristic->getCharacteristic(), dataToBeSend);


}

char BLE_Valve::weekdaysResolver(QString day)
{
    char index = 0;

    QVector <QString> days = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    auto it = std::find(days.begin(), days.end(), day);
    index = static_cast<char>(std::distance(days.begin(), it));

    return index;
}
