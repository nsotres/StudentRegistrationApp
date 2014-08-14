#ifndef TERMSUBJECTMODEL_H
#define TERMSUBJECTMODEL_H

#include <QObject>
#include "db.h"
#include "globals.h"

class TermSubjectModel : public QObject
{
    Q_OBJECT
    public:
        TermSubjectModel( QString name, int nTermID, int nSubjectId );
        TermSubjectModel( QSqlRecord DB );
        ~TermSubjectModel();
        bool insertTermSubject();
        bool updateTermSubject();
        QString name;
        int nID, nTermID, nSubjectId;

    signals:
        void sendMessage(QString _message);
    public slots:
    
    private:

};

#endif // TERMSUBJECTMODEL_H
