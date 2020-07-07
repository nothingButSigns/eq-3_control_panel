#include "event.h"


Event::Event(QString temp, QString time)
{
    m_temp = temp;
    m_time = time;
}

Event::Event(QString temp)
{
    m_temp = temp;
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

QString Event::getProfileHour()
{
    return profileHour;
}

QString Event::getProfileMins()
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

QString Event::getTemp()
{
    return m_temp;
}

void Event::setTemp(QString temp)
{
    m_temp = temp;
}

void Event::setTemp(float temp)
{
    //m_temp =
}

void Event::setTime(QString time)
{
    m_time = time;
}
