#ifndef SUBMODEL_H
#define SUBMODEL_H

#include <QObject>


class Event: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString temp READ temp WRITE setTemp NOTIFY tempChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
public:
    Event(QString temp, QString time);
    ~Event();


    QString temp();
    QString time();
    void setTemp(QString temp);
    void setTime(QString time);

    //QAbstract model interface

Q_SIGNALS:
    void tempChanged();
    void timeChanged();


//public:
//    int rowCount(const QModelIndex &parent) const;
//    QVariant data(const QModelIndex &index, int role) const;
//    QHash<int, QByteArray> roleNames() const;

protected:
    QString m_temp;
    QString m_time;
};

#endif // SUBMODEL_H
