#ifndef SUBJECTMODEL_H
#define SUBJECTMODEL_H

#include <QObject>
#include "db.h"
#include "globals.h"


class SubjectModel : public QObject
{
    Q_OBJECT
    public:
        SubjectModel( QString _name, QString _college );
        SubjectModel( QSqlRecord DB );
        bool insertSubject();
        bool updateSubject();
        int getID();
        ~SubjectModel();
        QString name, college;
        int nID;
    signals:
        void sendMessage(QString _message);
    public slots:

    private:

};

#endif // SUBJECTMODEL_H
