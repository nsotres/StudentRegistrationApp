#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <QObject>
#include "db.h"
#include "globals.h"

class EventModel : public QObject
{
    Q_OBJECT
public:
    EventModel( QString _name, QString _description, int _nIDUser, QDate _date );
    EventModel( QSqlRecord DB );
    ~EventModel();
    bool insertEvent();
    bool updateEvent();
    QString name, description;
    int nID, nIDUser;
    QDate date;

signals:
    void sendMessage(QString _message);
public slots:
    
};

#endif // EVENTMODEL_H
