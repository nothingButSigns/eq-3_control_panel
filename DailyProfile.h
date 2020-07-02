#ifndef DAILY_PROFILE_H
#define DAILY_PROFILE_H


#include "QObject"
#include "cmath"
#include "QMap"
#include <QDebug>
#include <QMetaType>
///#include "eventsmodel.h"
#include <QAbstractListModel>
#include <event.h>

#define QT_NO_CAST_TO_ASCII

class DailyProfile: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString Day READ readDay WRITE setDay NOTIFY DayChanged)
    //Q_PROPERTY(QString temp1 READ getTemp1 NOTIFY temp1Changed)



public:
    enum SomeModelRoles {
        TIME = Qt::UserRole+1,
        TEMP,
        TIME_PREV
    };

    //Abstract model interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

protected:
    QVector<Event*> events;
    QHash<int, QByteArray> m_roles;


public:
    DailyProfile(const QByteArray &array);
    //DailyProfile(const QString someText);
    ~DailyProfile();

    QByteArray retProfile();
    QString assignDay(int num);

public slots:
     QString readDay();
     void setDay(QString newDay);




Q_SIGNALS:
    void DayChanged();
    void temp1Changed();


private:
    QByteArray *profile;
    QString day;
};

#endif // DAILY_PROFILE_H
