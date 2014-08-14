#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include "db.h"

/*  UserModel class: Has an authentication method that uses the DB class to check the
* provided credentials. It retrieve the role of the user and then hides the login view 
* and displays the profile view for that user. 
*/

class UserModel : public QObject
{
    Q_OBJECT
    public:
        UserModel( QString _login, QString _password, QString _firstname, QString _lastname, QString _address1, QString _address2, QString _city, QString _dob, int _nZip, int _nRole, int _nState, int _nSS, int _nTelephone, int _nMajor );
        UserModel( QSqlRecord DB );
        ~UserModel();
        static QString authenticate( QString, QString );
        static int getUserId(QString, QString);
        //void updateUser(/*UserModel *user*/ QString name );
        bool updateUser();
        QString login, password, firstname, lastname, address1, address2, city, dob;
        int nID, nZip, nRole, nState, nSS, nTelephone, nMajor;
signals:
        void sendMessage(QString _message);
    private:
        bool insertUser();
};

#endif // USERMODEL_H
