#include "userinformation.h"
#include "ui_userinformation.h"

UserInformation::UserInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserInformation)
{
    ui->setupUi(this);

    ui->name_lineEdit->setText("Testing Testing");
    ui->name_lineEdit->setDisabled(true);
    ui->DOB_lineEdit->setText("09/06/1987");
    ui->DOB_lineEdit->setDisabled(true);
    ui->lineEdit_address1->setText("University of Illinois");
    ui->lineEdit_address1->setDisabled(true);
    ui->lineEdit_address2->setText("");
    ui->lineEdit_address2->setDisabled(true);
    ui->lineEdit_city->setText("Chicago");
    ui->lineEdit_city->setDisabled(true);
    ui->lineEdit_country->setText("United States");
    ui->lineEdit_country->setDisabled(true);
    ui->lineEdit_state->setText("Alaska");
    ui->lineEdit_state->setDisabled(true);
    ui->lineEdit_email->setText("abc@uic.edu");
    ui->lineEdit_email->setDisabled(true);
    ui->lineEdit_Major->setText("Computer Science");
    ui->lineEdit_Major->setDisabled(true);
    ui->lineEdit_zipcode->setText("60000");
    ui->lineEdit_zipcode->setDisabled(true);
    ui->lineEdit_ssn->setText("123-23-3454");
    ui->lineEdit_ssn->setDisabled(true);
    ui->lineEdit_UIN->setText("1233453454");
    ui->lineEdit_UIN->setDisabled(true);
}

UserInformation::~UserInformation()
{
    delete ui;
}

void UserInformation::on_pushButton_addr1_clicked()
{
     ui->lineEdit_address1->setDisabled(false);
     ui->lineEdit_address2->setDisabled(false);
     ui->lineEdit_city->setDisabled(false);
     ui->lineEdit_country->setDisabled(false);
     ui->lineEdit_state->setDisabled(false);
     ui->DOB_lineEdit->setDisabled(false);
     ui->name_lineEdit->setDisabled(false);
     ui->lineEdit_email->setDisabled(false);
     ui->lineEdit_zipcode->setDisabled(false);
}

void UserInformation::on_userinfo_pushButton_clicked()
{
    ui->lineEdit_address1->setDisabled(true);
    ui->lineEdit_address2->setDisabled(true);
    ui->lineEdit_city->setDisabled(true);
    ui->lineEdit_country->setDisabled(true);
    ui->lineEdit_state->setDisabled(true);
    ui->DOB_lineEdit->setDisabled(true);
    ui->name_lineEdit->setDisabled(true);
    ui->lineEdit_email->setDisabled(true);
    ui->lineEdit_zipcode->setDisabled(true);
}
