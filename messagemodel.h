#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QObject>
#include "db.h"
#include "globals.h"

class MessageModel : public QObject
{
    Q_OBJECT
public:
    MessageModel(QString _suject, QString _content, int nTo, int _from);
	MessageModel(QSqlRecord DB);   
	bool insertMessage();
	//bool updateMessage;

    QString subject, content;
    int nID, nTo, nFrom;
    
signals:
    
public slots:
    
};

#endif // MESSAGEMODEL_H
