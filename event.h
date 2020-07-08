#ifndef SUBMODEL_H
#define SUBMODEL_H

#include <QObject>
#include <QAbstractListModel>


class Event: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString temp READ temp WRITE setTemp NOTIFY tempChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)

public:
    Event (QString temp, QString time);
    Event (QString temp);
    ~Event();

    QString temp();
    QString time();
    void setTemp(QString temp);
    void setTemp(float temp);
    void setTime(QString time);
    QString getProfileHour();
    QString getProfileMins();
    void setProfileHour(QString hour);
    void setProfileMins(QString mins);
    QString getTemp();



Q_SIGNALS:
    void tempChanged();
    void timeChanged();

    
protected:
    QString m_temp;
    QString m_time = "00:00";

    QString profileHour;
    QString profileMins;

};

#endif // SUBMODEL_H
