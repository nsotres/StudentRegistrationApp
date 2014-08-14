#include "messagemodel.h"

MessageModel::MessageModel(QString _subject, QString _content, int _nTo, int _nfrom)
{
    subject = _subject;
    content = _content;
    nTo = _nTo;
    nFrom = _nfrom;

    insertMessage();
}

MessageModel::MessageModel(QSqlRecord DB)
{
        subject = DB.value( "topic" ).toString();
        content = DB.value ( "text" ).toString();
        nTo = DB.value( "receiver" ).toInt();
        nFrom = DB.value( "sender" ).toInt();
        nID = DB.value( "id_message" ).toInt();
}

bool MessageModel:: insertMessage()
{
    bool query = db.mysql_query( "INSERT INTO kabukiU_cs440.message ( id_message, sender, receiver, topic, text ) VALUES ( '' , '" + QString::number(nFrom) + "', '" + QString::number(nTo) + "', '" + subject + "', '" + content + "')" );

        if( query )
        {
        #ifdef DEBUGGING
               cout << "message query insertion successful" << endl;
        #endif
            db.mysql_query( "SELECT LAST_INSERT_ID()" );
               nID = db.getField( "LAST_INSERT_ID()", 0 ).toInt();
        #ifdef DEBUGGING
               cout << "inserted message id: " << nID << endl;
        #endif
           }

        return query;

}
