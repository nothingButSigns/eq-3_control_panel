#include "submodel.h"

Submodel::Submodel(QString temp, QString time)
{
    m_temp = temp;
    m_time = time;
}

Submodel::~Submodel()
{

}

QString Submodel::temp()
{
    return m_temp;
}

QString Submodel::time()
{
    return m_time;
}

void Submodel::setTemp(QString temp)
{
    m_temp = temp;
}

void Submodel::setTime(QString time)
{
    m_time = time;
}

int Submodel::rowCount(const QModelIndex &parent) const
{

}

QVariant Submodel::data(const QModelIndex &index, int role) const
{

}

QHash<int, QByteArray> Submodel::roleNames() const
{

}
