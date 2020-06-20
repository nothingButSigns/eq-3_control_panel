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

void Event::setTemp(QString temp)
{
    m_temp = temp;
}

void Event::setTime(QString time)
{
    m_time = time;
}
