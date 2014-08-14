#include "coursemodel.h"

CourseModel::CourseModel( QString _name, int _nSubject, QString _description, int _nCreditHours )
{
    name = _name;
    nSubject = _nSubject;
    description = _description;
    nCreditHours = _nCreditHours;
    insertCourse();
}

CourseModel::CourseModel( QSqlRecord DB )
{
    name = DB.value( "name" ).toString();
    nSubject = DB.value ( "id_subject" ).toInt();
    description = DB.value( "description" ).toString();
    nCreditHours = DB.value( "credithours" ).toInt();
    nID = DB.value( "id_course" ).toInt();
}

CourseModel::~CourseModel()
{
#ifdef DEBUGGING
       cout << "destructor of CourseModel ID:" << nID << "is called." << endl;
#endif

       db.mysql_query( "DELETE FROM course WHERE id_course = '" + QString::number(nID) + "'" );

       emit sendMessage( "Course: " + name + " deleted from database." );
}

bool CourseModel::insertCourse()
{
    bool query = db.mysql_query( "INSERT INTO kabukiU_cs440.course ( id_course, name, id_subject, description, credithours ) VALUES ( '' , '" + name + "', '" + QString::number(nSubject) + "', '" + description + "', '" + QString::number(nCreditHours) + "')" );

    if( query )
    {
    #ifdef DEBUGGING
           cout << "course query insertion successful" << endl;
    #endif
        db.mysql_query( "SELECT LAST_INSERT_ID()" );
           nID = db.getField( "LAST_INSERT_ID()", 0 ).toInt();
    #ifdef DEBUGGING
           cout << "inserted course id: " << nID << endl;
    #endif
       }

    return query;
}

bool CourseModel::updateCourse()
{
    return db.mysql_query( "UPDATE kabukiU_cs440.course SET name = '" + name + "', id_subject = '" + QString::number(nSubject) + "', description = '" + description + "', credithours = '" + QString::number(nCreditHours) + "' WHERE course.id_course = " + QString::number(nID) );
}

int CourseModel::getID()
{
    return nID;
}
