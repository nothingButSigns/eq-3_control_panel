#include "event.h"

Event::Event(QString temp, QString time)
{
    m_temp = temp;
    m_time = time;
}

Event::~Event()
{

}

QString Event::temp()
{
    return m_temp;
}

QString Event::time()
{
    return m_time;
}

int Event::hour()
{
    return profileHour.toInt();
}

QString Event::mins()
{
    return profileMins;
}

void Event::setProfileHour(QString hour)
{
    profileHour = hour;
}

void Event::setProfileMins(QString mins)
{
    profileMins = mins;
}

QString Event::getProfileTime()
{
    return profileHour + ":" + profileMins;
}

void Event::setTemp(QString temp)
{
    m_temp = temp;
}

void Event::setTime(QString time)
{
    m_time = time;
}
