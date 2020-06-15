#ifndef DAILY_PROFILE_H
#define DAILY_PROFILE_H


#include "QObject"
#include "cmath"
#include "QMap"
#include <QDebug>
#include <QMetaType>
///#include "eventsmodel.h"
#include <QAbstractListModel>
#include <submodel.h>



class DailyProfile: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString Day READ readDay NOTIFY DayChanged)
    Q_PROPERTY(QString temp1 READ getTemp1 NOTIFY temp1Changed)


public:
    enum SomeModelRoles {
        DAY = Qt::UserRole+1,
        TEMP,
        TIME
    };

    //Abstract model interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

protected:
    QVector<Submodel*> m_models;
    QHash<int, QByteArray> m_roles;

public:
    DailyProfile(const QByteArray &array);
    ~DailyProfile();

    QString readDay();
    QVariant Profile();
    QByteArray retProfile();
    QString assignDay(int num);
   // EventsModel *getSchedule();
    QString getTemp1();


private:
Q_SIGNALS:
    void DayChanged();
    void temp1Changed();


private:
    QByteArray *profile;
    QString day;
    QMap <QString, QString> events;
    QMap <QString, QString> example;
    //EventsModel evModel;
    QString m_temp1;
};

#endif // DAILY_PROFILE_H
