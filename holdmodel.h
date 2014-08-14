#ifndef HOLDMODEL_H
#define HOLDMODEL_H

#include <QObject>
#include "db.h"

class HoldModel : public QObject
{
    Q_OBJECT
    public:

        HoldModel(int _id_student, int _id_user_academic, QString _description, int _id_user_tuition, QString _balance, int _id_user_advising, int _id_user_medical, bool _immunization, bool _insurance);
        HoldModel( QSqlRecord DB );
        HoldModel(int _id_student);
        ~HoldModel();
        bool updateHold(int _id_user_academic, QString _description, int _id_user_tuition, QString _balance, int _id_user_advising, int _id_user_medical, bool _immunization, bool _insurance);
        bool placeHold();
        int id_hold,id_student,  id_user_academic, id_user_tuition,id_user_medical, id_user_advising;
        QString description,  balance;
        bool immunization, insurance;

signals:

    private:

};

#endif // HOLDMODEL_H
