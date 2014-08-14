#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QDialog>

namespace Ui {
class UserInformation;
}

class UserInformation : public QDialog
{
    Q_OBJECT
    
    public:
        explicit UserInformation(QWidget *parent = 0);
        ~UserInformation();

    private:
        Ui::UserInformation *ui;

    private slots:
        void on_pushButton_addr1_clicked();
        void on_userinfo_pushButton_clicked();
};

#endif // USERINFORMATION_H
