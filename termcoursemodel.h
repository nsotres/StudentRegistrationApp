#ifndef TERMCOURSEMODEL_H
#define TERMCOURSEMODEL_H

#include <QObject>
#include "db.h"
#include "globals.h"

class TermCourseModel : public QObject
{
    Q_OBJECT
    public:
        TermCourseModel( int _ncourseId, int _nclassroomId, QString _meetingDays, int _meetingTime, int _ninstructorId, int _ntaId, QString _termSubject, vector< int > _studentListIDs, int _ntermsubject);
        TermCourseModel( QSqlRecord DB );
        ~TermCourseModel();
        bool insertTermCourse();
        bool updateTermCourse();
        QString  meetingDays, termSubject;
        int nID, ncourseId, nclassroomId, ninstructorId, ntaId,nmeetingTime, ntermsubject;

    signals:
        void sendMessage(QString _message);
    public slots:

    private:
        vector< int > studentListIDs;

};

#endif // TERMCOURSEMODEL_H
