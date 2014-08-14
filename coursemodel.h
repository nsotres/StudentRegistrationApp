#ifndef COURSEMODEL_H
#define COURSEMODEL_H

#include <QObject>
#include "db.h"
#include "globals.h"

class CourseModel : public QObject
{
    Q_OBJECT
    public:
        CourseModel( QString _name, int _nSubject, QString _description, int _nCreditHours );
        CourseModel( QSqlRecord DB );
        ~CourseModel();
        bool insertCourse();
        bool updateCourse();
        int getID();
        QString name, description;
        int nID, nCreditHours, nSubject;
    signals:
        void sendMessage(QString _message);
    public slots:

    private:

};

#endif // COURSEMODEL_H
