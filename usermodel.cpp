#include "globals.h"
#include "usermodel.h"
#include "db.h"

/*  UserModel class: Has an authentication method that uses the DB class to check the
* provided credentials. It retrieve the role of the user and then hides the login view 
* and displays the profile view for that user. 
*/

UserModel::UserModel( QString _login, QString _password, QString _firstname, QString _lastname, QString _address1, QString _address2, QString _city, QString _dob, int _nZip, int _nRole, int _nState, int _nSS, int _nTelephone, int _nMajor )
{
    login = _login;
    password = _password;
    firstname = _firstname;
    lastname = _lastname;
    address1 = _address1;
    address2 = _address2;
    city = _city;
    dob = _dob;
    nZip = _nZip;
    nRole = _nRole;
    nState = _nState;
    nSS = _nSS;
    nTelephone =_nTelephone;
    nMajor = _nMajor;
#ifdef DEBUGGING
    cout << "inside usermodel constructor" << endl;
#endif
    insertUser();
}

UserModel::UserModel( QSqlRecord DB )
{
    login = DB.value( "login" ).toString();
    password = DB.value( "password" ).toString();
    firstname = DB.value( "firstname" ).toString();
    lastname = DB.value( "lastname" ).toString();
    address1 = DB.value( "address1" ).toString();
    address2 = DB.value( "address2" ).toString();
    city = DB.value( "city" ).toString();
    dob = DB.value( "dob" ).toString();
    nID = DB.value( "id_user" ).toInt();
    nZip = DB.value( "zip" ).toInt();
    nRole = DB.value( "role" ).toInt();
    nState = DB.value( "state" ).toInt();
    nSS = DB.value( "ss" ).toInt();
    nTelephone = DB.value( "telephone" ).toInt();
    nMajor = DB.value( "major" ).toInt();
}

bool UserModel::insertUser()
{
    bool query = db.mysql_query( "INSERT INTO kabukiU_cs440.user ( id_user, login, password, role, firstname, lastname, address1, address2, city, zip, state, dob, ss, telephone, major ) VALUES ( '' , '" + login + "', '" + password + "', '" + QString::number(nRole) + "', '" + firstname + "', '" + lastname + "', '" + address1 + "', '" + address2 + "', '" + city + "', '" + QString::number(nZip) + "', '" + QString::number(nState) + "', '" + dob + "', '" + QString::number(nSS) + "', '" + QString::number(nTelephone) + "', '" + QString::number(nMajor) + "')" );
   if( query )
   {
#ifdef DEBUGGING
       cout << "user query insertion successful" << endl;
#endif
       db.mysql_query( "SELECT LAST_INSERT_ID()" );
       nID = db.getField( "LAST_INSERT_ID()", 0 ).toInt();
#ifdef DEBUGGING
       cout << "inserted user id: " << nID << endl;
#endif
   }
   return query;
}

bool UserModel::updateUser()
{
    return db.mysql_query( "UPDATE kabukiU_cs440.user SET login = '" + login + "', password = '" + password + "', role = '" + QString::number(nRole) + "', firstname = '" + firstname + "', lastname = '" + lastname + "', address1 = '" + address1 + "', address2 = '" + address2 + "', city = '" + city + "', zip = '" + QString::number(nZip) + "', state = '" + QString::number(nState) + "', dob = '" + dob + "', ss = '" + QString::number(nSS) + "', telephone = '" + QString::number(nTelephone) + "', major = '" + QString::number(nMajor) + "' WHERE user.id_user = " + QString::number(nID) );
}

QString UserModel::authenticate( QString _user, QString _password )
{
    db.mysql_query("SELECT * FROM user, user_role WHERE user.role = user_role.id_user_role AND login='" + _user + "' AND password='" + _password + "'");
    #ifdef DEBUGGING
    cout << "id: " << _user.toLocal8Bit().constData() << " has role: " << db.getField( "name", 0 ).toLocal8Bit().constData() << endl;
    #endif

    return db.getField( "name", 0 );
}

int UserModel::getUserId(QString _user, QString _password)
{
    db.mysql_query("SELECT * FROM user WHERE login='" + _user + "' AND password='" + _password + "'");
    #ifdef DEBUGGING
    cout << "id: " << _user.toLocal8Bit().constData() << " has id: " << db.getField( "id_user", 0 ).toLocal8Bit().constData() << endl;
    #endif

    return db.getField( "id_user", 0 ).toInt();
}
UserModel::~UserModel(){

#ifdef DEBUGGING
       cout << "destructor of UserModel ID:" << nID << "is called." << endl;
#endif

       //To-Do query for delete:

       db.mysql_query("DELETE FROM user WHERE id_user = '"+QString::number(nID)+"';");

       emit sendMessage("User: "+firstname+" "+lastname+" deleted from database.");
}

//void UserModel::updateUser(/*UserModel *user*/ QString name )
