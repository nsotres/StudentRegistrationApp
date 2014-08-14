#include "utils.h"
#include "loginview.h"
#include "ui_loginview.h"
#include "windowcontroller.h"

/* Previously MainWindow
* Please keep all gui classes
suffixed with View.
*/

LoginView::LoginView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginView)
{

    ui->setupUi(this);
    ui->passwordError_label->setVisible(false);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_login_pushButton_clicked()
{
    #ifdef DEBUGGING
    cout << "login pushed" << endl;
    #endif

    //ui->login_pushButton->setDisabled(true);
    ui->passwordError_label->setVisible(true);
    emit loginSubmitted( ui->login_lineEdit->text(), ui->password_lineEdit->text() );
}
