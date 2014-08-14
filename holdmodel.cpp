
#include "globals.h"
#include "holdmodel.h"
#include "db.h"

HoldModel::HoldModel(int _id_student){
id_student = _id_student;

}

HoldModel::HoldModel(int _id_student, int _id_user_academic, QString _description, int _id_user_tuition, QString _balance, int _id_user_advising, int _id_user_medical, bool _immunization, bool _insurance)
{
    id_hold = 0;
    id_student = _id_student;
    id_user_academic = _id_user_academic;
    id_user_tuition = _id_user_tuition;
    id_user_medical = _id_user_medical;
    id_user_advising = _id_user_advising;
    description = _description;
    balance = _balance;
    immunization = _immunization;
    insurance = _insurance;
#ifdef DEBUGGING
    cout << "inside hold constructor" << endl;
#endif
    placeHold();
}

HoldModel::HoldModel( QSqlRecord DB )
{
    id_hold = DB.value( "id_hold" ).toInt();
    id_student = DB.value( "id_student" ).toInt();
    id_user_academic = DB.value( "id_user_academic" ).toInt();
    id_user_tuition = DB.value( "id_user_tuition" ).toInt();
    id_user_medical = DB.value( "id_user_medical" ).toInt();
    id_user_advising = DB.value( "id_user_advising" ).toInt();
    description = DB.value( "description" ).toString();
    balance = DB.value( "balance" ).toString();
    immunization = DB.value( "immunization" ).toInt();
    insurance = DB.value( "insurance" ).toInt();
}

bool HoldModel::placeHold()
{

    bool query = db.mysql_query("INSERT INTO `kabukiU_cs440`.`hold` (`id_hold`, `id_student`, `id_user_academic`, `description`, `id_user_tuition`, `balance`, `id_user_advising`, `id_user_medical`, `immunization`, `insurance`) VALUES (NULL, '"+QString::number(id_student)+"', '"+QString::number(id_user_academic)+"', '"+description+"', '"+QString::number(id_user_tuition)+"', '"+balance+"', '"+QString::number(id_user_advising)+"', '"+QString::number(id_user_medical)+"', '"+QString::number(immunization)+"', '"+QString::number(insurance)+"')");

                if( query )
    {
            #ifdef DEBUGGING
                cout << "hold inserted" << endl;
        #endif
            db.mysql_query( "SELECT LAST_INSERT_ID()" );
    id_hold = db.getField( "LAST_INSERT_ID()", 0 ).toInt();
#ifdef DEBUGGING
    cout << "Hold placed. " << endl;
#endif
}

return query;
}

bool HoldModel::updateHold(int _id_user_academic, QString _description, int _id_user_tuition, QString _balance, int _id_user_advising, int _id_user_medical, bool _immunization, bool _insurance){

    QString query = "UPDATE  hold SET ";

    if(id_user_academic != _id_user_academic)
    {
        query.append("id_user_academic =  '"+QString::number(_id_user_academic)+"', ");
    }
    if(description != _description)
    {
        query.append("description =  '"+_description+"', ");
    }
    if(id_user_tuition != _id_user_tuition)
    {
        query.append("id_user_tuition =  '"+_description+"', ");
    }
    if(balance != _balance)
    {
        query.append("balance =  '"+_balance+"', ");
    }
    if(id_user_advising != _id_user_advising)
    {
        query.append("id_user_advising =  '"+QString::number(_id_user_advising)+"', ");
    }
    if(immunization != _immunization || insurance != _insurance)
    {
        query.append("id_user_medical =  '"+QString::number(_id_user_medical)+"', ");
        query.append("immunization =  '"+QString::number(_immunization)+"', ");
        query.append("insurance =  '"+QString::number(_insurance)+"', ");

    }
    query.append(" WHERE  id_student = '"+QString::number(id_student)+"';");

    return db.mysql_query(query);
}

HoldModel::~HoldModel(){

#ifdef DEBUGGING
    cout << "destructor of holdModel ID:" << id_student << "is called." << endl;
#endif

    //To-Do query for delete:

    db.mysql_query("DELETE FROM hold WHERE id_student = '"+QString::number(id_student)+"';");

    //emit sendMessage("Hold removed.");

}

