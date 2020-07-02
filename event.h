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
    Event(QString temp, QString time);
    ~Event();

    QString temp();
    QString time();
    void setTemp(QString temp);
    void setTime(QString time);
    int hour();
    QString mins();
    void setProfileHour(QString hour);
    void setProfileMins(QString mins);
    QString getProfileTime();



Q_SIGNALS:
    void tempChanged();
    void timeChanged();

    
protected:
    QString m_temp;
    QString m_time;
    // End time of the profile event
    QString profileHour;
    QString profileMins;

};

#endif // SUBMODEL_H
