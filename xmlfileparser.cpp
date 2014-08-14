#include "xmlfileparser.h"

//xml parser implementation based on example from http://www.developer.nokia.com/Community/Wiki/Using_QXmlStreamReader_to_parse_XML_in_Qt

XmlFileParser::XmlFileParser()
{
    users = new QList< QMap<QString,QString> >;
    subjects = new QList< QMap<QString,QString> >;
    courses = new QList< QMap<QString,QString> >;
}

XmlFileParser::~XmlFileParser()
{
    delete users;
    delete subjects;
    delete courses;
}

bool XmlFileParser::parseXML( QString fileName ) {
    /* We'll parse the example.xml */
    QFile* file = new QFile( fileName );
    /* If we can't open it, let's show an error message. */
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
#ifdef DEBUGGING
        cout << "couldn't open " << fileName.toLocal8Bit().constData() << endl;
#endif
        return false;
        //QMessageBox::critical(this,
          //                    "QXSRExample::parseXML",
          //                    "Couldn't open example.xml",
          //                    QMessageBox::Ok);
    }
    /* QXmlStreamReader takes any QIODevice. */
    QXmlStreamReader xml(file);
    /* We'll parse the XML until we reach end of it.*/
    while(!xml.atEnd() && !xml.hasError())
    {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = xml.readNext();
        /* If token is just StartDocument, we'll go to next.*/
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement)
        {
            /* If it's named users, we'll go to the next.*/
            if(xml.name() == "data" || xml.name() == "users" || xml.name() == "subjects" || xml.name() == "courses") {
                continue;
            }
            /* If it's named user, we'll dig the information from there.*/
            if(xml.name() == "user")
            {
                #ifdef DEBUGGING
                        cout << "parsing a user" << endl;
                #endif
                users->append(this->parseUser(xml));
            }
            else if(xml.name() == "subject")
            {
                #ifdef DEBUGGING
                        cout << "parsing a subject" << endl;
                #endif
                subjects->append(this->parseSubject(xml));
            }
            else if(xml.name() == "course")
            {
                #ifdef DEBUGGING
                        cout << "parsing a course" << endl;
                #endif
                courses->append(this->parseCourse(xml));
            }
        }
    }
    /* Error handling. */
    if(xml.hasError())
    {
#ifdef DEBUGGING
        cout << "error encountered in xml parser: " << xml.errorString().toLocal8Bit().constData() << endl;
#endif
        return false;
        //QMessageBox::critical(this,
          //                    "QXSRExample::parseXML",
          //                    xml.errorString(),
            //                  QMessageBox::Ok);
    }
    xml.clear();
    return true;
}

QMap<QString, QString> XmlFileParser::parseUser(QXmlStreamReader& xml)
{
    QMap<QString, QString> user;
    /* Let's check that we're really getting a user. */
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "user")
    {
        return user;
    }
    /* Next element... */
    xml.readNext();
    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named person.
     */
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "user"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            /* We've found login. */
            if(xml.name() == "login") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found password. */
            if(xml.name() == "password") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found role. */
            if(xml.name() == "nRole") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found first name. */
            if(xml.name() == "firstname") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found lastname. */
            if(xml.name() == "lastname") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found address1. */
            if(xml.name() == "address1") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found address2. */
            if(xml.name() == "password") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found city. */
            if(xml.name() == "city") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found zip. */
            if(xml.name() == "nZip") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found state. */
            if(xml.name() == "nState") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found dob. */
            if(xml.name() == "dob") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found SS. */
            if(xml.name() == "nSS") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found telephone. */
            if(xml.name() == "nTelephone") {
                this->addElementDataToMap(xml, user);
            }
            /* We've found major. */
            if(xml.name() == "nMajor") {
                this->addElementDataToMap(xml, user);
            }
        }
        /* ...and next... */
        xml.readNext();
    }
    return user;
}

QMap<QString, QString> XmlFileParser::parseSubject(QXmlStreamReader& xml)
{
    QMap<QString, QString> subject;
    /* Let's check that we're really getting a user. */
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "subject")
    {
        return subject;
    }
    /* Next element... */
    xml.readNext();
    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named person.
     */
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "subject"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            /* We've found name. */
            if(xml.name() == "name") {
                this->addElementDataToMap(xml, subject);
            }
            /* We've found college. */
            if(xml.name() == "college") {
                this->addElementDataToMap(xml, subject);
            }
        }
        /* ...and next... */
        xml.readNext();
    }
    return subject;
}

QMap<QString, QString> XmlFileParser::parseCourse(QXmlStreamReader& xml)
{
    QMap<QString, QString> course;
    /* Let's check that we're really getting a user. */
    if(xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "course")
    {
        return course;
    }
    /* Next element... */
    xml.readNext();
    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named person.
     */
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "course"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            /* We've found name. */
            if(xml.name() == "name") {
                this->addElementDataToMap(xml, course);
            }
            /* We've found subject. */
            if(xml.name() == "nSubject") {
                this->addElementDataToMap(xml, course);
            }
            /* We've found description. */
            if(xml.name() == "description") {
                this->addElementDataToMap(xml, course);
            }
            /* We've found credit hours. */
            if(xml.name() == "nCreditHours") {
                this->addElementDataToMap(xml, course);
            }
        }
        /* ...and next... */
        xml.readNext();
    }
    return course;
}

void XmlFileParser::addElementDataToMap(QXmlStreamReader& xml,
                                      QMap<QString, QString>& map) const {
    /* We need a start element, like <foo> */
    if(xml.tokenType() != QXmlStreamReader::StartElement) {
        return;
    }
    /* Let's read the name... */
    QString elementName = xml.name().toString();
    /* ...go to the next. */
    xml.readNext();
    /*
     * This elements needs to contain Characters so we know it's
     * actually data, if it's not we'll leave.
     */
    if(xml.tokenType() != QXmlStreamReader::Characters) {
        return;
    }
    /* Now we can add it to the map.*/
    map.insert(elementName, xml.text().toString());
}

//void QXSRExample::addPersonsToUI(QList< QMap<QString,QString> >& persons) {
//    while(!persons.isEmpty()) {
//        QGroupBox* personGB = new QGroupBox("Person");
//        QFormLayout* layout = new QFormLayout;
//        QMap<QString,QString> person = persons.takeFirst();
//        layout->addRow("First name", new QLineEdit(person["firstname"]));
//        layout->addRow("Surname", new QLineEdit(person["surname"]));
//        layout->addRow("E-mail", new QLineEdit(person["email"]));
//        layout->addRow("Website", new QLineEdit(person["website"]));
//        personGB->setLayout(layout);
//        this->_layout->addWidget(personGB);
//    }
//}
