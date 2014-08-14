#include "windowcontroller.h"
#include "utils.h"
#include "usermodel.h"

WindowController::WindowController( MainWindow* _mainWindow )
{
    mainWindow = _mainWindow;
    QObject::connect( mainWindow, SIGNAL( logoutAction() ),
                      this, SLOT( logoutHack() ) );
    QObject::connect( mainWindow, SIGNAL( loginSubmitted( QString, QString ) ),
                      this, SLOT( handle_login( QString, QString ) ) );
}

void WindowController::show()
{
    mainWindow->show();
}

void WindowController::handle_login( QString _user, QString _pass )
{
    #ifdef DEBUGGING
    cout << "user: " << _user.toLocal8Bit().constData() << endl;
    cout << "password: " << _pass.toLocal8Bit().constData() << endl;
    #endif

    //check credentials
    QString userRole = UserModel::authenticate( _user, _pass );
    if (userRole !="")
    {
        int userId = UserModel::getUserId(_user,_pass);
        mainWindow->switchRole(userRole,userId);
    }

    #ifdef DEBUGGING
    cout << "post authentication" << endl;
    #endif
}

void WindowController::logoutHack()
{
    mainWindow->close();
    QObject::disconnect( mainWindow, SIGNAL( loginSubmitted( QString, QString ) ),
                      this, SLOT( handle_login( QString, QString ) ) );
    QObject::disconnect( mainWindow, SIGNAL( logoutAction() ),
                      this, SLOT( logoutHack() ) );
    //delete mainWindow;

    mainWindow = new MainWindow;
    QObject::connect( mainWindow, SIGNAL( logoutAction() ),
                      this, SLOT( logoutHack() ) );
    mainWindow->show();
    QObject::connect( mainWindow, SIGNAL( loginSubmitted( QString, QString ) ),
                      this, SLOT( handle_login( QString, QString ) ) );
}
