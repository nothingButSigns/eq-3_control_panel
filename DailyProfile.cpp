#include "DailyProfile.h"

int DailyProfile::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return events.count();
}

QVariant DailyProfile::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if (role == TEMP)
        return events.at(index.row())->temp();
    else if (role == TIME)
        return events.at(index.row())->time();

    return QVariant();

}

QHash<int, QByteArray> DailyProfile::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles[TIME] = "Time";
    roles[TEMP] = "Temperature";

    return roles;
}

DailyProfile::DailyProfile(const QByteArray &array)
{
    profile = new QByteArray(array);

    // retirive data from the array
    // get day of the week
    //DaysOfTheWeek dayName = static_cast<DaysOfTheWeek>(profile->at(1));
   // day = static_cast<QString>(profile->at(1));

    setDay(assignDay(static_cast<int>(profile->at(1))));


    qDebug() << "day from BAILY PROFILE CLASS: " << day;

    // get end time of an event
    auto _begin = profile->begin();
    ++_begin;
    ++_begin;

    auto _end = profile->end();

    for(; _begin != _end; _begin++)
    {
        // retrive temeprature
        float temp = static_cast<float>(*_begin);
        temp /= 2;
        QString temperature = "";
        int intTemp = static_cast<int>(abs(temp));
        int remTemp = static_cast<int>((temp - abs(temp)) * 100);

        temperature += QString::number(intTemp);
        temperature.append(".");
        temperature += QString::number(remTemp);

        //increment the iterator to get access to end time for a given event
        ++_begin;

        float minutes = static_cast<float>(*_begin);
        // retrived value is equal to amount of 10-minutes intervals since 00:00
        minutes *= 10;
        minutes /= 60;
        int hour = static_cast<int>(abs(minutes));
        int mins = static_cast<int>((minutes - abs(minutes))*60);
        QString time = "";

        // append 0 at the beggining to get a proper time format (e.g. 01:00)
        if(hour < 10) time.append("0");

        time += QString::number(hour);
        time.append(":");

        // similarly, add '0' to get proper time format
        if(mins < 10) time.append("0");
        time += QString::number(mins);

        beginInsertRows(QModelIndex(), events.size(), events.size());
        events.append(new Event(temperature, time));
        endInsertRows();

//        m_temp1 = "22.0";

//        evModel.addEvent(Event("22", "14"));
//        evModel.addEvent(Event("14", "18"));
//        evModel.addEvent(Event("10", "33"));

//        m_models.append(new Submodel("22", "54"));
//        m_models.append(new Submodel("55", "66"));
//        m_models.append(new Submodel("33", "44"));

    }
}


DailyProfile::~DailyProfile(){}

QString DailyProfile::readDay()
{
    return day;
}

void DailyProfile::setDay(QString newDay)
{
    day = newDay;
}

QByteArray DailyProfile::retProfile()
{
    return *profile;
}

QString DailyProfile::assignDay(int num)
{
    QList<QString> days {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    return days.at(num);
}
