#include <QtGui/QApplication>
#include <QtSql>
//#include "loginview.h"
#include "windowcontroller.h"
#include "db.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow* mainWindow = new MainWindow;
    WindowController* wc = new WindowController( mainWindow );
    //QObject::connect( mainWindow, SIGNAL( loginSubmitted( QString, QString ) ),
                      //wc, SLOT( handle_login( QString, QString ) ) );


    wc->show();   //shows window

    return a.exec(); //exec
}
