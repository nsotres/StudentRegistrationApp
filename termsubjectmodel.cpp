#include "termsubjectmodel.h"
#include "db.h"

TermSubjectModel::TermSubjectModel( QString _name, int _nTermID, int _nSubjectId )
{
    name = _name;
    nTermID = _nTermID;
    nSubjectId = _nSubjectId;
    insertTermSubject();
}

TermSubjectModel::TermSubjectModel(QSqlRecord DB)
{
    name = DB.value("name").toString();
    nTermID = DB.value("id_term").toInt();
    nSubjectId = DB.value("id_subject").toInt();
    nID = DB.value("id_termsubject").toInt();
}

TermSubjectModel::~TermSubjectModel()
{
#ifdef DEBUGGING
       cout << "destructor of TermSubjectModel ID:" << nID << "is called." << endl;
#endif

       db.mysql_query( "DELETE FROM termsubject WHERE id_termsubject = '" + QString::number(nID)+ "'" );

       emit sendMessage( "Term Subject: " + name + " deleted from database." );
}

bool TermSubjectModel::insertTermSubject()
{
    bool query =  db.mysql_query( "INSERT INTO kabukiU_cs440.termsubject ( id_termsubject, id_term, id_subject, name) VALUES ( '' , '" + QString::number(nTermID) + "', '" + QString::number(nSubjectId) + "', '" + name +"')" );

    if( query )
    {
    #ifdef DEBUGGING
           cout << "term subject query insertion successful" << endl;
    #endif
        db.mysql_query( "SELECT LAST_INSERT_ID()" );
           nID = db.getField( "LAST_INSERT_ID()", 0 ).toInt();
    #ifdef DEBUGGING
           cout << "inserted term subject id: " << nID << endl;
    #endif
       }

    return query;
}

bool TermSubjectModel::updateTermSubject()
{
    return db.mysql_query( "UPDATE kabukiU_cs440.termsubject SET name = '" + name + "', id_subject = '" + QString::number(nSubjectId) + "', id_term = '" + QString::number(nTermID) + "' WHERE termsubject.id_termsubject = " + QString::number(nID) );
}
