#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QMainWindow>

/* Previously MainWindow
* Please keep all gui classes
suffixed with View.
*/

namespace Ui {
class LoginView;
}

class LoginView : public QMainWindow
{
    Q_OBJECT
    
    public:
        explicit LoginView(QWidget *parent = 0);
        ~LoginView();

    signals:
        void loginSubmitted( QString _user, QString _pass );

    private slots:
        void on_login_pushButton_clicked();

    private:
        Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
