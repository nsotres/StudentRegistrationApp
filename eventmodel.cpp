#include "eventmodel.h"

EventModel::EventModel( QString _name, QString _description, int _nIDUser, QDate _date )
{
    name = _name;
    description = _description;
    nIDUser = _nIDUser;
    date = _date;
    insertEvent();
}

EventModel::EventModel( QSqlRecord DB )
{
    nID = DB.value( "id_event" ).toInt();
    name = DB.value( "name" ).toString();
    description = DB.value( "description" ).toString();
    nIDUser = DB.value( "id_user" ).toInt();
    date = DB.value( "date" ).toDate();
}

EventModel::~EventModel()
{
#ifdef DEBUGGING
       cout << "destructor of EventModel ID:" << nID << "is called." << endl;
#endif

       db.mysql_query( "DELETE FROM event WHERE id_event = '" + QString::number(nID) + "'" );

       emit sendMessage( "Event: " + name + " deleted from database." );
}

bool EventModel::insertEvent()
{
    //date.tostring not tested
    bool query = db.mysql_query( "INSERT INTO event ( id_event, name, description, id_user, date ) VALUES ( '' , '" + name + "', '" + description + "', '" + QString::number(nIDUser) + "', '" + date.toString() + "')" );

    if( query )
    {
    #ifdef DEBUGGING
           cout << "event query insertion successful" << endl;
    #endif
        db.mysql_query( "SELECT LAST_INSERT_ID()" );
           nID = db.getField( "LAST_INSERT_ID()", 0 ).toInt();
    #ifdef DEBUGGING
           cout << "inserted event id: " << nID << endl;
    #endif
       }

    return query;
}

bool EventModel::updateEvent()
{
    return db.mysql_query( "UPDATE event SET name = '" + name + "', description = '" + description + "', id_user = '" + QString::number(nIDUser) + "', date = '" + date.toString() + "' WHERE event.id_event = " + QString::number(nID) );
}
