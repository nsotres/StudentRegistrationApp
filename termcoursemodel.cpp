#include "termcoursemodel.h"

TermCourseModel::TermCourseModel( int _ncourseId, int _nclassroomId, QString _meetingDays, int _meetingTime, int _ninstructorId, int _ntaId, QString _termSubject, vector< int > _studentListIDs, int _ntermsubject )
{
    ncourseId = _ncourseId;
    nclassroomId = _nclassroomId;
    meetingDays = _meetingDays;
    nmeetingTime = _meetingTime;
    ninstructorId = _ninstructorId;
    ntaId = _ntaId;
    termSubject = _termSubject;
    studentListIDs = _studentListIDs;
    ntermsubject = _ntermsubject;
    insertTermCourse();
}

TermCourseModel::TermCourseModel( QSqlRecord DB )
{
    nID = DB.value("id_termcourse").toInt();
    ntermsubject = DB.value("id_termsubject").toInt();
    ncourseId = DB.value( "id_course" ).toInt();
    nclassroomId = DB.value( "id_classroom" ).toInt();
    nmeetingTime = DB.value( "meeting_time" ).toInt();
    meetingDays = DB.value("meeting_days").toString();
    ninstructorId = DB.value( "id_instructor" ).toInt();
    ntaId = DB.value( "id_ta" ).toInt();
}

TermCourseModel::~TermCourseModel()
{
#ifdef DEBUGGING
       cout << "destructor of TermCourseModel ID:" << nID << "is called." << endl;
#endif

       db.mysql_query( "DELETE FROM termcourse WHERE id_termcourse = '" + QString::number(nID)+ "'" );

       emit sendMessage( "Term Course: " + QString::number(ncourseId) + " deleted from database." );
}

bool TermCourseModel :: insertTermCourse()
{
    bool query = db.mysql_query( "INSERT INTO kabukiU_cs440.termcourse ( id_termcourse, id_termsubject, id_course, id_classroom, meeting_time, meeting_days, id_instructor, id_ta ) VALUES ( '' , '" + QString::number(ncourseId) + "', '" + QString::number(ntermsubject)+ "', '" + QString::number(nclassroomId) + "', '" + QString::number(nmeetingTime) + "', '" +meetingDays+"', '"+ QString::number(ninstructorId) + "', '" + QString::number(ntaId) +"')" );

    if( query )
    {
        #ifdef DEBUGGING
        cout << "termcourse query insertion successful" << endl;
        #endif
        db.mysql_query( "SELECT LAST_INSERT_ID()" );
        nID = db.getField( "LAST_INSERT_ID()", 0 ).toInt();
        #ifdef DEBUGGING
        cout << "inserted termcourse id: " << nID << endl;
        #endif
    }

    return query;
}

bool TermCourseModel :: updateTermCourse()
{
    return db.mysql_query( "UPDATE kabukiU_cs440.termcourse SET id_termsubject = '"+ QString::number(ntermsubject) +"', id_course = '" + QString::number(ncourseId) + "', id_classroom = '" + QString(nclassroomId) + "', meeting_time = '" + QString::number(nmeetingTime)+", meeting_days = '"+meetingDays + "', id_instructor = '" + QString(ninstructorId) + "', id_ta = '"+QString(ntaId) +"' WHERE course.id_termcourse = " + QString::number(nID) );
}
