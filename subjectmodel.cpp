#include "subjectmodel.h"

SubjectModel::SubjectModel( QString _name, QString _college )
{
    name = _name;
    college = _college;
    insertSubject();
}

SubjectModel::SubjectModel( QSqlRecord DB )
{
    name = DB.value( "name" ).toString();
    college = DB.value("college").toString();
    nID = DB.value( "id_subject" ).toInt();
}

bool SubjectModel::insertSubject()
{
    bool query = db.mysql_query( "INSERT INTO kabukiU_cs440.subject ( id_subject, name, college ) VALUES ( '' , '" + name + "', '" + college+ "')" );

    if( query )
    {
    #ifdef DEBUGGING
           cout << "subject query insertion successful" << endl;
    #endif
        db.mysql_query( "SELECT LAST_INSERT_ID()" );
           nID = db.getField( "LAST_INSERT_ID()", 0 ).toInt();
    #ifdef DEBUGGING
           cout << "inserted subject id: " << nID << endl;
    #endif
       }

    return query;
}

bool SubjectModel::updateSubject()
{
    return db.mysql_query( "UPDATE kabukiU_cs440.subject SET name = '" + name + "', college = '" + college + "' WHERE subject.id_subject = " + QString::number(nID) );
}

int SubjectModel::getID()
{
    return nID;
}

SubjectModel::~SubjectModel()
{
#ifdef DEBUGGING
       cout << "destructor of SubjectModel ID:" << nID << "is called." << endl;
#endif

       db.mysql_query( "DELETE FROM subject WHERE id_subject = '" + QString::number(nID)+ "'" );

       emit sendMessage("Subject: "+name+" deleted from database.");
}
