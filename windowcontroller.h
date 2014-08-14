#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <QObject>
#include "mainwindow.h"
//#include "userinformation.h"

class WindowController : public QObject
{
    Q_OBJECT

    private:
        MainWindow* mainWindow;
        //UserInformation* userInfo;

    public:
        WindowController( MainWindow* _mainWindow );
        void showLoginWindow();
        void setRegularWindowSize();
        void show();

    public slots:
        void handle_login( QString _user, QString _pass );
        void logoutHack();
};

#endif // WINDOWCONTROLLER_H
