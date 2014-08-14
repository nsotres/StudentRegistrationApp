#include "db.h"

//to do: handle a bad connection
/*db class establishes and maintains a connection. The connection is done once in globals.cpp, so wherever db communication is needed, 
* include globals.h and use the methods from DB class to send queries and retrieve values.
*/
DB::DB( QString _hostname, int _port, QString _database, QString _username, QString _password )
    : db( QSqlDatabase::addDatabase("QMYSQL") )
{
    db.setHostName( _hostname );
    db.setDatabaseName( _database );
    db.setUserName( _username );
    db.setPassword( _password );
    db.setPort( _port );
    db.open();
}

// how many rows query returns
int DB::count(){
cout << query->size()<<endl;
    return query->size();
}

bool DB::firstQuery(){

    return query->first();
}

bool DB::nextQuery(){

    return query->next();
}


// for easier data retrieval.
// @return QSqlRecord returned by value
QSqlRecord DB::getRecord(){

    return query->record();
}


DB::~DB()
{
    disconnect();
    if( query != NULL )
        delete query;
}

bool DB::connect()
{
    return db.open();
}

void DB::disconnect()
{
    db.close();
}

bool DB::mysql_query( QString _query )
{
    QString temp;
    if( query != NULL )
        delete query;
    query = new QSqlQuery( db );
#ifdef DEBUGGING
       cout << _query.toLocal8Bit().constData() << endl;
#endif
    return query->exec( _query );
}

//get the field attribute from the nth record
QString DB::getField( QString _field, int _nRec )
{
    QSqlRecord rec = query->record();
    int nameCol = rec.indexOf( _field );// index of the field
    query->seek( _nRec );
    return query->value( nameCol ).toString();
}

//get the field attributes from all records
//CAREFUL, UNTESTED CODE
list<QString>* DB::getField( QString _field )
{
    query->first();
    QSqlRecord* rec = &(query->record());
    int nameCol = rec->indexOf( _field );// index of the field
    list<QString>* attributes = new list<QString>;

    do{
        rec = &(query->record());
        attributes->push_back( rec->value( nameCol ).toString() );
    }while(query->next());
    return attributes;
}
