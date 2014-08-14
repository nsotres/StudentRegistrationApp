#ifndef XMLFILEPARSER_H
#define XMLFILEPARSER_H

#include <QObject>
#include <QMap>
#include <QXmlStreamReader>
#include <QFile>
#include "utils.h"

class XmlFileParser : public QObject
{
    Q_OBJECT
    public:
        XmlFileParser();
        ~XmlFileParser();
        bool parseXML( QString fileName );
        QList< QMap<QString,QString> >* users;
        QList< QMap<QString,QString> >* subjects;
        QList< QMap<QString,QString> >* courses;

    signals:

    public slots:

    private:
        QMap<QString, QString> parseUser(QXmlStreamReader& xml);
        QMap<QString, QString> parseSubject(QXmlStreamReader& xml);
        QMap<QString, QString> parseCourse(QXmlStreamReader& xml);

        void addElementDataToMap(QXmlStreamReader& xml,
                                 QMap<QString, QString>& map) const;

        //void addPersonsToUI(QList< QMap<QString,QString> >& persons);
    private slots:
};

#endif // XMLFILEPARSER_H
