#ifndef DB_H
#define DB_H

#include "utils.h"
#include <QtSql>
#include <QMap>

/*db class establishes and maintains a connection. The connection is done once in globals.cpp, so wherever db communication is needed, 
* include globals.h and use the methods from DB class to send queries and retrieve values.
*/

class DB
{
    public:
        DB( QString _hostname, int _port, QString _database, QString _username, QString _password );
        ~DB();
        bool mysql_query( QString _query );
        QString getField( QString _field, int _nRec );
        list<QString>* getField( QString _field );
        QSqlRecord getRecord();
        int count();
        bool nextQuery();
        bool firstQuery();


    private:
        QSqlDatabase db;
        QSqlQuery* query;
        bool connect();
        void disconnect();
};

#endif // DB_H
