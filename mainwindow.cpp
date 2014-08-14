#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "windowcontroller.h"
#include "globals.h"

///test
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_adminNew,SIGNAL(clicked()),this,SLOT(clearAdminFrom()));
    connect(ui->pushButton_deleteUser,SIGNAL(clicked()),this,SLOT(deleteUser()));
    connect(ui->comboBox_adminRole,SIGNAL(currentIndexChanged(int)),this,SLOT(changeUserRoleForm(int)));
    connect(ui->toolButton_XML,SIGNAL(clicked()),this,SLOT(selectXMLFile()));
    connect(ui->pushButton_adminDeleteHolds,SIGNAL(clicked()),this,SLOT(deleteHolds()));
    connect(ui->pushButton_adminSavHolds,SIGNAL(clicked()),this,SLOT(updateHolds()));
    showLoginWindow();
    globalSelectredRole = 0;
    userModels = new QMap < int, UserModel* >;
    currentUserSelected = NULL;
    currentSubjectSelected = NULL;
    subjectModels = new QMap < int, SubjectModel*>;
    courseModels = new QMap <int, CourseModel*>;
    termCourseModels = new QMap <int, TermCourseModel*>;
    termSubjectModels = new QMap <int, TermSubjectModel*>;
    messageModels = new QMap <int, MessageModel*>;

    holdModels = new QMap <int, HoldModel*>;
    currentHold = NULL;

}

//resizes main window to login size and displays login gorupbox
void MainWindow::showLoginWindow()
{
    ui->actionLogout->setDisabled(true);
    int margin = 5;
    int mainWindowXsize = ui->groupBox_login->width()+2*margin;
    int mainWindowYsize = ui->groupBox_login->height()+2*margin+10;
    ui->label_passwordError->setVisible(false);

    ui->statusbar->showMessage("Please login to the system.");

    this->setMinimumSize(mainWindowXsize,mainWindowYsize);
    this->setMaximumSize(mainWindowXsize,mainWindowYsize);
    //reposition login info
    ui->groupBox_login->setGeometry(margin,margin,270,170);

    //hide tabs
    ui->tabWidget_role->setVisible(false);
}

void MainWindow::clearLineEdit(QLineEdit *_lineEdit){
    _lineEdit->setText("");
}

void MainWindow::clearTextEdit(QTextEdit *_textEdit){
    _textEdit->setText("");
}

void MainWindow::selectXMLFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open XML file"), "", tr("XML Files (*.xml)"));
    ui->lineEdit_XML->setText(fileName);
}

void MainWindow::clearAdminFrom(){

    clearLineEdit(ui->lineEdit_adminFirstName);
    clearLineEdit(ui->lineEdit_adminLastName);
    clearLineEdit(ui->lineEdit_adminLogin);
    clearLineEdit(ui->lineEdit_adminDOB);
    clearLineEdit(ui->lineEdit_adminUIN);
    clearLineEdit(ui->lineEdit_adminAddress1);
    clearLineEdit(ui->lineEdit_adminAddress2);
    clearLineEdit(ui->lineEdit_adminCity);
    clearLineEdit(ui->lineEdit_adminZIP);
    clearLineEdit(ui->lineEdit_adminCountry);
    clearLineEdit(ui->lineEdit_adminSS);
    clearLineEdit(ui->lineEdit_adminPassword);
    ui->comboBox_adminMajor->setCurrentIndex(0);
    ui->comboBox_adminRole->setCurrentIndex(0);
    ui->comboBox_adminState->setCurrentIndex(0);
    ui->label_adminID->setText("");
    currentUserSelected = NULL;
}
void MainWindow::changeUserRoleForm(int _index)
{

    int roleID = ui->comboBox_adminRole->itemData(_index).toInt();

    cout<<"switched id: "<<_index <<" "<<roleID<<endl;
    switch(roleID){
    //admin
    case(1):
        // teacher
    case(2):

        //ta
    case(3):
        //adviser
    case(4):

        ui->label_adminUIN->setVisible(false);
        ui->lineEdit_adminUIN->setVisible(false);

        ui->label_adminMajor->setVisible(false);
        ui->comboBox_adminMajor->setVisible(false);
        ui->tabWidget_adminEditUser->removeTab(1);

        break;

        //student
    case(5):
        ui->tabWidget_adminEditUser->addTab(ui->tab_adminHold,"Manage Holds");
        ui->label_adminUIN->setVisible(true);
        ui->lineEdit_adminUIN->setVisible(true);

        ui->label_adminMajor->setVisible(true);
        ui->comboBox_adminMajor->setVisible(true);

        break;
        //student

    }

}


void MainWindow::setRegularWindowSize()
{
    int margin = 5;
    int mainWindowXsize = ui->tabWidget_role->width()+2*margin;
    int mainWindowYsize = ui->tabWidget_role->height()+2*margin+10;

    this->setMinimumSize(mainWindowXsize,mainWindowYsize);
    this->setMaximumSize(mainWindowXsize,mainWindowYsize);
    ui->groupBox_login->setVisible(false);
}


void MainWindow::switchRole(QString _userRole, int userId)
{
    curUserID = userId;
    int countTabs =ui->tabWidget_role->count();
    for (int i=0;i<countTabs;i++){
        //removes all tabs
        //start-----------------------------------------------------------------comment this line if you wan to see all tabs
        ui->tabWidget_role->removeTab(0);
        //end--------------------------------------------------------------------------------------------------------------
    }

        populateAdminUserModel();
        showMajor(ui->comboBox_profMajor);
    if(_userRole == "Administrator"){
        ui->tabWidget_role->addTab(ui->tab_admin,_userRole);
        showStates(ui->comboBox_adminState);
        showMajor(ui->comboBox_adminMajor);
        showRole(ui->comboBox_adminRole);
        showSubjects(ui->comboBox_adminCourseSubject);

        populateAdminUserModel();
        updateAdminUserTable();
        populateAdminSubjectModel();
        populateAdminCourseModel();
        populateHolds();

    }else if(_userRole == "Teacher"){
        showStates(ui->comboBox_professorState);
        ui->tabWidget_role->addTab(ui->tab_teacher,_userRole);
        ui->tabWidget_prof->insertTab(4,ui->tab_6,"Message");
        ui->tabWidget_prof->insertTab(3,ui->tab_5,"Calendar");
        populateInstructorUserModel(userId);
        populateInstructorCourse(userId);
    }else if(_userRole == "Student"){
        ui->tabWidget_role->addTab(ui->tab_student,_userRole);
        //ui->tabWidget_student->addTab(ui->tab_5,"Calendar");
        ui->tabWidget_student->insertTab(4,ui->tab_6,"Message");
        ui->tabWidget_student->insertTab(3,ui->tab_5,"Calendar");
        showTermYear(ui->comboBox_RYear);
        showTermSemester(ui->comboBox_RTerm);
        showSubjects(ui->comboBox_RSubject);
        populateAdminCourseModel(); //populated

        showStates(ui->comboBox_professorState);
        ui->tabWidget_student->insertTab(0,ui->User,"User Account");
        populateInstructorUserModel(curUserID);
        populateInstructorCourse(curUserID);

    }
    else if(_userRole == "Teacher Assistant")
    {
        showStates(ui->comboBox_ta_state);
        ui->tabWidget_role->addTab(ui->tab_ta,_userRole);
        ui->tabWidget_ta->insertTab(4,ui->tab_6,"Message");
        ui->tabWidget_ta->insertTab(3,ui->tab_5,"Calendar");
        populateTAUserModel(userId);
        populateTACourse(userId);
    }else if(_userRole == "Adviser")
    {
        ui->tabWidget_role->addTab(ui->tab_adviser,_userRole);
        ui->tabWidget_adviser->insertTab(4,ui->tab_6,"Message");
        ui->tabWidget_adviser->insertTab(3,ui->tab_5,"Calendar");
        showStates(ui->comboBox_professorState);
        ui->tabWidget_adviser->insertTab(0,ui->User,"User Account");
        ui->tabWidget_adviser->insertTab(1,ui->tab_courses,"Courses");
        populateInstructorUserModel(curUserID);
        populateInstructorCourse(curUserID);
    }
    populateTermSubjectModel();
    populateTermCourseModel();
    populateEventModel();
    //to-do add more cases for other users


    // this is for message. All Users! So This will not go under any specific case.
    showAllUsers(ui->comboBox_allusers,userId);
    showAllUsers(ui->comboBox_allusers_2,userId);

    populateMessageModel(userId);

    //just make sure has a proper size
    this->setRegularWindowSize();

    ui->actionLogout->setEnabled(true);


    //ui->tabWidget_role->setCurrentIndex(0); // 0- admin


    ui->tabWidget_role->setVisible(true);
}

void MainWindow::repopulateAllUsers(QComboBox* _box)
{
    int userId = ui->lineEdit_sender_id->text().toInt();
    db.mysql_query("select * from user where id_user <> "+QString::number(userId));
    db.firstQuery();
    int count = db.count();

    for (int i = 0; i < count; i++)
    {
        QString name = (db.getField("firstname",i)+" "+db.getField("lastname",i));
        _box->removeItem(i);
        _box->addItem(name,QVariant(db.getField("id_user",i)));
    }

}

void MainWindow::showAllUsers(QComboBox* _box, int userId)
{
    ui->lineEdit_sender_id->setHidden(true);
    ui->lineEdit_sender_id->setText(QString::number(userId));

    db.mysql_query("select * from user where id_user <> "+QString::number(userId));
    db.firstQuery();
    int count = db.count();

    for (int i = 0; i < count; i++)
    {
        QString name = (db.getField("firstname",i)+" "+db.getField("lastname",i));
        _box->addItem(name,QVariant(db.getField("id_user",i)));
    }

}

void MainWindow::showStates(QComboBox* _box){
    db.mysql_query("Select * from state;");

    db.firstQuery();
    int count=db.count();
    for(int i=0;i<count;i++){
        _box->addItem(db.getField("name",i), QVariant(db.getField("id_state",i)));
    }
}

void MainWindow::showRole(QComboBox* _box){
    db.mysql_query("Select * from user_role;");

    db.firstQuery();
    int count=db.count();
    for(int i=0;i<count;i++){
        _box->addItem(db.getField("name",i), QVariant(db.getField("id_user_role",i)));
    }
}

void MainWindow::showMajor(QComboBox* _box){
    db.mysql_query("Select * from major;");

    //_box->addItem("2323", QVariant(344));

    db.firstQuery();
    int count=db.count();
    for(int i=0;i<count;i++){
        _box->addItem(db.getField("name",i), QVariant(db.getField("id_major",i)));
    }
}

void MainWindow::showTermYear(QComboBox* _box){
    db.mysql_query("Select * from term;");

    //get years from database
    db.firstQuery();
    int count=db.count();
    for(int i=0;i<count;i++){
        _box->addItem(db.getField("year",i), QVariant(db.getField("id_term",i)));
    }
}

void MainWindow::showTermSemester(QComboBox* _box){
    db.mysql_query("Select * from term;");

    //get semesters from database
    db.firstQuery();
    int count=db.count();
    for(int i=0;i<count;i++){
        _box->addItem(db.getField("semester",i), QVariant(db.getField("id_term",i)));
    }
}

void MainWindow::showSubjects(QComboBox* _box){
    db.mysql_query("Select * from subject;");

    //get subjects from database
    db.firstQuery();
    int count=db.count();
    for(int i=0;i<count;i++){
        _box->addItem(db.getField("name",i), QVariant(db.getField("id_subject",i)));
    }
}

void MainWindow::updateSubjects(QComboBox* _box, int nID){
    SubjectModel* tempSubjectModel = subjectModels->value(nID);
    _box->addItem( tempSubjectModel->name, QVariant(tempSubjectModel->nID));
}



MainWindow::~MainWindow()
{
    delete ui;
    delete userModels;
    delete subjectModels;
    delete courseModels;
    delete termSubjectModels;
    delete termCourseModels;
    delete holdModels;
    disconnect(ui->pushButton_adminNew,SIGNAL(clicked()),this,SLOT(clearAdminFrom()));
    disconnect(ui->pushButton_deleteUser,SIGNAL(clicked()),this,SLOT(deleteUser()));
    disconnect(ui->comboBox_adminRole,SIGNAL(currentIndexChanged(int)),this,SLOT(changeUserRoleForm(int)));
    disconnect(ui->toolButton_XML,SIGNAL(clicked()),this,SLOT(selectXMLFile()));
    disconnect(ui->pushButton_adminDeleteHolds,SIGNAL(clicked()),this,SLOT(deleteHolds()));
    disconnect(ui->pushButton_adminSavHolds,SIGNAL(clicked()),this,SLOT(updateHolds()));
}

//if enter is pressed, it submit the login form
void MainWindow::on_lineEdit_password_returnPressed()
{
    on_pushButton_login_clicked();
}


void MainWindow::on_pushButton_login_clicked()
{
#ifdef DEBUGGING
    cout << "login pushed" << endl;
#endif

    //ui->login_pushButton->setDisabled(true);
    ui->label_passwordError->setVisible(true);
    emit loginSubmitted( ui->lineEdit_login->text(), ui->lineEdit_password->text() );
}

void MainWindow::on_lineEdit_login_returnPressed()
{
    ui->lineEdit_password->setFocus();
}


// all the 3 functions below might be needed to combined soon
void MainWindow::on_pushButton_compose_admin_clicked()
{
#ifdef DEBUGGING
    cout << "compose message pushed" << endl;
#endif
}

void MainWindow::on_pushButton_compose_teacher_clicked()
{
#ifdef DEBUGGING
    cout << "compose message pushed" << endl;
#endif
}

void MainWindow::on_pushButton_compose_ta_clicked()
{
#ifdef DEBUGGING
    cout << "compose message pushed" << endl;
#endif
}

//void MainWindow::on_userinfo_pushButton_clicked()
//{
//    //emit

//}

void MainWindow::populateAdminUserModel(){
    db.mysql_query("Select * from user WHERE 1;");
    QSqlRecord rec;
    UserModel* userModelPtr;

    while( db.nextQuery() )
    {
        rec = db.getRecord();
        userModelPtr = new UserModel( rec );
        userModels->insert( userModelPtr->nID, userModelPtr );
    }
}

void MainWindow::populateAdminCourseModel(){
    db.mysql_query("Select * from course WHERE 1;");
    QSqlRecord rec;
    CourseModel* courseModelPtr;

    while( db.nextQuery() )
    {
        rec = db.getRecord();
        courseModelPtr = new CourseModel( rec );
        courseModels->insert( courseModelPtr->nID, courseModelPtr );
    }
    updateAdminCourseTable();
}


void MainWindow::updateHolds(){
    int id = curUserID;
    if (currentHold){
//---------------------------------------
     //this has to be changed to reflect current user login

        currentHold->updateHold(id,"",id,ui->lineEdit_adminHoldBalance->text(),id,id,ui->checkBox_adminImmunization->isChecked(),ui->checkBox_adminInsurance->isChecked());
        currentHold->placeHold();
    }else{
        int id = 1;
        currentHold = new HoldModel(currentUserSelected->nID);
        currentHold->updateHold(1,"",id,ui->lineEdit_adminHoldBalance->text(),id,id,ui->checkBox_adminImmunization->isChecked(),ui->checkBox_adminInsurance->isChecked());
        currentHold->placeHold();
        holdModels->insert(currentHold->id_student,currentHold);
    }
}



void MainWindow::populateTermCourseModel(){
    db.mysql_query("Select * from termcourse WHERE 1;");
    QSqlRecord rec;
    TermCourseModel* termCourseModelPtr;

    while( db.nextQuery() )
    {
        rec = db.getRecord();
        termCourseModelPtr = new TermCourseModel( rec );
        termCourseModels->insert( termCourseModelPtr->nID, termCourseModelPtr );
    }
    //updateAdminTermCourseTable();
}

void MainWindow::populateTermSubjectModel(){
    db.mysql_query("Select * from termsubject WHERE 1;");
    QSqlRecord rec;
    TermSubjectModel* termSubjectModelPtr;

    while( db.nextQuery() )
    {
        rec = db.getRecord();
        termSubjectModelPtr = new TermSubjectModel( rec );
        termSubjectModels->insert( termSubjectModelPtr->nID, termSubjectModelPtr );
    }
    //updateAdminTermCourseTable();
}

void MainWindow::populateEventModel(){
    db.mysql_query( "Select * from event WHERE id_user = " + curUserID );
    QSqlRecord rec;
    EventModel* eventModelPtr;

    while( db.nextQuery() )
    {
        rec = db.getRecord();
        eventModelPtr = new EventModel( rec );
        eventModels->insert( eventModelPtr->nID, eventModelPtr );
    }
}

void MainWindow::populateHolds(){
    db.mysql_query("Select * from hold WHERE 1;");
    QSqlRecord rec;
    HoldModel* holdModelPtr;

    while( db.nextQuery() )
    {
        rec = db.getRecord();
        holdModelPtr = new HoldModel( rec );
        holdModels->insert( holdModelPtr->id_student, holdModelPtr );
    }
}

void MainWindow::updateAdminUserTable(){


    int count = userModels->size();


    ui->tableWidget_adminUsersTable->setRowCount(count);
    ui->tableWidget_adminUsersTable->setColumnCount(4);

    UserModel* userModelPtr;
    int i=0;
    QMap<int, UserModel*>::iterator c;

    for (c = userModels->begin(); c != userModels->end(); ++c){
        userModelPtr = c.value();
        if (globalSelectredRole == 0){
        ui->tableWidget_adminUsersTable->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(userModelPtr->nID)));
        ui->tableWidget_adminUsersTable->setItem(i,0,new QTableWidgetItem(userModelPtr->firstname));
        ui->tableWidget_adminUsersTable->setItem(i,1,new QTableWidgetItem(userModelPtr->lastname));
        ui->tableWidget_adminUsersTable->setItem(i,2,new QTableWidgetItem(userModelPtr->login));
        ui->tableWidget_adminUsersTable->setItem(i++,3,new QTableWidgetItem(QString::number(userModelPtr->nSS)));
        }else if(globalSelectredRole == userModelPtr->nRole){

            ui->tableWidget_adminUsersTable->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(userModelPtr->nID)));
            ui->tableWidget_adminUsersTable->setItem(i,0,new QTableWidgetItem(userModelPtr->firstname));
            ui->tableWidget_adminUsersTable->setItem(i,1,new QTableWidgetItem(userModelPtr->lastname));
            ui->tableWidget_adminUsersTable->setItem(i,2,new QTableWidgetItem(userModelPtr->login));
            ui->tableWidget_adminUsersTable->setItem(i++,3,new QTableWidgetItem(QString::number(userModelPtr->nSS)));

        }
        }
ui->tableWidget_adminUsersTable->setRowCount(i);
    repopulateAllUsers(ui->comboBox_allusers);

    /*
    int i=0;
    while( db.nextQuery() )
    {
        //rec = db.getRecord();
        userModelPtr = new UserModel( rec );
        userModels->insert( userModelPtr->nID, userModelPtr );
        ui->tableWidget_adminUsersTable->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(userModelPtr->nID)));
        ui->tableWidget_adminUsersTable->setItem(i,0,new QTableWidgetItem(userModelPtr->firstname));
        ui->tableWidget_adminUsersTable->setItem(i,1,new QTableWidgetItem(userModelPtr->lastname));
        ui->tableWidget_adminUsersTable->setItem(i,2,new QTableWidgetItem(userModelPtr->login));
        ui->tableWidget_adminUsersTable->setItem(i,3,new QTableWidgetItem(QString::number(userModelPtr->nSS)));
        ++i;
        // ui->tableWidget_adminUsersTable->setItem(i,4,new QTableWidgetItem(db.getField("major",i)));
#ifdef DEBUGGING
        cout << "id: " << userModelPtr->nID << endl; //.toLocal8Bit().constData()
#endif
*/


    //for(int i=0;i<count;i++){
    //    ui->tableWidget_adminUsersTable->setVerticalHeaderItem(i,new QTableWidgetItem(db.getField("id_user",i)));
    //    ui->tableWidget_adminUsersTable->setItem(i,0,new QTableWidgetItem(db.getField("firstname",i)));
    //    ui->tableWidget_adminUsersTable->setItem(i,1,new QTableWidgetItem(db.getField("lastname",i)));
    //    ui->tableWidget_adminUsersTable->setItem(i,2,new QTableWidgetItem(db.getField("login",i)));
    //    ui->tableWidget_adminUsersTable->setItem(i,3,new QTableWidgetItem(db.getField("ss",i)));
    // ui->tableWidget_adminUsersTable->setItem(i,4,new QTableWidgetItem(db.getField("major",i)));

    //}

}

void MainWindow::on_tableWidget_adminUsersTable_cellClicked(int row, int column)
{
    int id = ui->tableWidget_adminUsersTable->verticalHeaderItem(row)->text().toInt();
    UserModel* editUser;
    editUser = userModels->value(id);

    currentUserSelected = userModels->value(id);
    if (editUser->nRole ==5)
        fillHold();
    ui->label_adminID->setText(QString::number(editUser->nID));
    ui->lineEdit_adminLogin->setText(editUser->login);
    ui->comboBox_adminRole->setCurrentIndex( ui->comboBox_adminRole->findData(editUser->nRole));
    changeUserRoleForm(editUser->nRole);
    ui->lineEdit_adminFirstName->setText(editUser->firstname);
        ui->lineEdit_adminPassword->setText(editUser->password);
    ui->lineEdit_adminLastName->setText(editUser->lastname);
    ui->lineEdit_adminAddress1->setText(editUser->address1);
    ui->lineEdit_adminAddress2->setText(editUser->address2);
    ui->lineEdit_adminCity->setText(editUser->city);
    ui->lineEdit_adminZIP->setText(QString::number(editUser->nZip));
    ui->comboBox_adminState->setCurrentIndex( ui->comboBox_adminState->findData(editUser->nState));
    ui->lineEdit_adminDOB->setText(editUser->dob);
    ui->lineEdit_adminSS->setText(QString::number(editUser->nSS));
    ui->lineEdit_adminPassword->setText(editUser->password);
    ui->lineEdit_adminTelephone->setText(QString::number(editUser->nTelephone));
    ui->comboBox_adminMajor->setCurrentIndex( ui->comboBox_adminMajor->findData(QString::number(editUser->nMajor)));
    //ui->name_lineEdit->setText(ui->tableWidget_adminUsersTable->verticalHeaderItem(row)->text());


}

void MainWindow::showStatusMessage(QString _message){
    ui->statusbar->showMessage(_message);
}


void MainWindow::clearHoldForm()
{
    ui->checkBox_adminAcademic->setChecked(false);
    ui->checkBox_adminAdvising->setChecked(false);
    ui->checkBox_adminImmunization->setChecked(false);
    ui->checkBox_adminInsurance->setChecked(false);
    ui->checkBox_adminMedical->setChecked(false);
    ui->checkBox_adminTuition->setChecked(false);
    ui->label_adminAcademic->setText("n/a");
    ui->label_adminAdvising->setText("n/a");
    ui->label_adminMedical->setText("n/a");
    ui->label_adminTuition->setText("n/a");
}


void MainWindow::fillHold(){


    if (holdModels->contains(currentUserSelected->nID)){

        UserModel * tempUser;
        QString name ="";

        currentHold = holdModels->value(currentUserSelected->nID);


        if (currentHold->id_user_academic > 0){
            tempUser = userModels->value(currentHold->id_user_academic);
            if (tempUser){
                name =QString(tempUser->firstname+" "+tempUser->lastname);
                       }else{
                name ="User was removed.";
            }
            ui->checkBox_adminAcademic->setChecked(true);
            ui->label_adminAcademic->setText(name);
            ui->plainTextEdit_adminHold->setPlainText(currentHold->description);
        }

        if (currentHold->id_user_advising > 0){
            tempUser = userModels->value(currentHold->id_user_advising);
            if (tempUser){
                name =tempUser->firstname+" "+tempUser->lastname;
                       }else{
                name ="User was removed.";
            }
            ui->checkBox_adminAdvising->setChecked(true);
            ui->label_adminAdvising->setText(name);
        }

        if (currentHold->id_user_tuition > 0){
            tempUser = userModels->value(currentHold->id_user_tuition);
            ui->checkBox_adminTuition->setChecked(true);
            if (tempUser){
                name =tempUser->firstname+" "+tempUser->lastname;
                       }else{
                name ="User was removed.";
            }
            ui->label_adminTuition->setText(name);
            ui->lineEdit_adminHoldBalance->setText(currentHold->balance);
        }

        if (currentHold->id_user_medical > 0){
            tempUser = userModels->value(currentHold->id_user_medical);
            if (tempUser){
                name =tempUser->firstname+" "+tempUser->lastname;
                       }else{
                name ="User was removed.";
            }
            ui->label_adminMedical->setText(name);
            ui->checkBox_adminMedical->setChecked(true);

            ui->checkBox_adminImmunization->setChecked(currentHold->immunization);
            ui->checkBox_adminInsurance->setChecked(currentHold->insurance);
        }

   }else{

        clearHoldForm();

    }

}

void MainWindow::deleteUser(){
    if (currentUserSelected){
        connect(currentUserSelected, SIGNAL(sendMessage(QString)),
                this, SLOT(showStatusMessage(QString)));
        int id = currentUserSelected->nID;

        currentUserSelected= userModels->value(id);
        delete(currentUserSelected);

        userModels->remove(id);
        currentUserSelected= NULL;
        clearAdminFrom();
        updateAdminUserTable();
        //editUser = userModels->value(id);
#ifdef DEBUGGING
        cout << "Delete user clicked." << endl;
#endif

    }else{
#ifdef DEBUGGING
        cout << "User not selected for deletion." << endl;
#endif

    }
}





void MainWindow::deleteHolds(){
    if (currentHold){
        connect(currentHold, SIGNAL(sendMessage(QString)),
                this, SLOT(showStatusMessage(QString)));
        int id = currentHold->id_student;

        delete(currentHold);

        holdModels->remove(id);
        clearHoldForm();
        currentHold = NULL;
        //editUser = userModels->value(id);
#ifdef DEBUGGING
        cout << "Delete hold clicked." << endl;
#endif

    }
}








/* working code
void MainWindow::deleteUser(){
    if (currentUserSelected != NULL){
        UserModel* editUser;
        editUser= userModels->value(currentUserSelected);
        delete(editUser);
        userModels->remove(currentUserSelected);
        updateAdminUserTable();
        //editUser = userModels->value(id);
#ifdef DEBUGGING
        cout << "Delete user clicked." << endl;
#endif

    }else{
#ifdef DEBUGGING
        cout << "User not selected for deletion." << endl;
#endif

    }
}

*/







//check SS, doesn't send to DB

void MainWindow::on_pushButton_adminSave_clicked()
{
    #ifdef DEBUGGING
    cout <<"clicked admin save" << endl;
    #endif
    int ss= QString(ui->lineEdit_adminSS->text()).replace("-","").toInt();

    if( currentUserSelected == NULL )
    {
       UserModel* newUser;
        newUser = new UserModel( ui->lineEdit_adminLogin->text(),
                                 ui->lineEdit_adminPassword->text(),
                                 ui->lineEdit_adminFirstName->text(),
                                 ui->lineEdit_adminLastName->text(),
                                 ui->lineEdit_adminAddress1->text(),
                                 ui->lineEdit_adminAddress2->text(),
                                 ui->lineEdit_adminCity->text(),
                                 ui->lineEdit_adminDOB->text(),
                                 ui->lineEdit_adminZIP->text().toInt(),
                                 ui->comboBox_adminRole->itemData(ui->comboBox_adminRole->currentIndex()).toInt(),
                                 ui->comboBox_adminState->itemData(ui->comboBox_adminState->currentIndex()).toInt(),

                                 ss,
                                 ui->lineEdit_adminTelephone->text().toInt(),
                                 ui->comboBox_adminMajor->itemData(ui->comboBox_adminMajor->currentIndex()).toInt());
        userModels->insert(newUser->nID,newUser);
    }
    else
    {
        currentUserSelected->login = ui->lineEdit_adminLogin->text();
        currentUserSelected->password = ui->lineEdit_adminPassword->text();
        currentUserSelected->firstname = ui->lineEdit_adminFirstName->text();
        currentUserSelected->lastname = ui->lineEdit_adminLastName->text();
        currentUserSelected->address1 = ui->lineEdit_adminAddress1->text();
        currentUserSelected->address2 = ui->lineEdit_adminAddress2->text();
        currentUserSelected->city = ui->lineEdit_adminCity->text();
        currentUserSelected->dob = ui->lineEdit_adminDOB->text();
        currentUserSelected->nZip = ui->lineEdit_adminZIP->text().toInt();
        currentUserSelected->nRole = ui->comboBox_adminRole->itemData(ui->comboBox_adminRole->currentIndex()).toInt();
        currentUserSelected->nState = ui->comboBox_adminState->itemData(ui->comboBox_adminState->currentIndex()).toInt();
        currentUserSelected->nSS = ss;
        currentUserSelected->nTelephone = ui->lineEdit_adminTelephone->text().toInt();
        currentUserSelected->nMajor = ui->comboBox_adminMajor->itemData(ui->comboBox_adminMajor->currentIndex()).toInt();
        currentUserSelected->updateUser();
    }
    updateAdminUserTable();
}

void MainWindow::createNewCourse()
{
    CourseModel *newCourse = new CourseModel("Chemistry I",1,"CHEM 101",4);
    courseModels->insert(newCourse->getID(),newCourse);
    newCourse->updateCourse();
}

void MainWindow::createNewSubject()
{
    SubjectModel *newSubject = new SubjectModel("Mechininal Engineering", "College of Engineering");
    subjectModels->insert(newSubject->getID(),newSubject);
    newSubject->updateSubject();
}

void MainWindow::populateAdminSubjectModel(){
    db.mysql_query("Select * from subject WHERE 1;");  //select all from subject table

    ui->tableWidget_adminSubjects->setRowCount(db.count());
    ui->tableWidget_adminSubjects->setColumnCount(2);
    QSqlRecord rec;
    SubjectModel* subjectModelPtr;

    int i=0;
    while( db.nextQuery() )
    {
        rec = db.getRecord();
        subjectModelPtr = new SubjectModel( rec );
        subjectModels->insert( subjectModelPtr->nID, subjectModelPtr); //create a new userModel pointer to object
        ui->tableWidget_adminSubjects->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(subjectModelPtr->nID)));
        ui->tableWidget_adminSubjects->setItem(i,0,new QTableWidgetItem(subjectModelPtr->name));
        ui->tableWidget_adminSubjects->setItem(i,1,new QTableWidgetItem(subjectModelPtr->college));
        ++i;
#ifdef DEBUGGING
        cout << "id: " << subjectModelPtr->nID << endl;
#endif
    }



}

/* Kamran's code */

void MainWindow::populateMessageModel(int user_id)
{
        #ifdef DEBUGGING
        cout << "in message model user id: " << user_id<< endl;
        #endif


    db.mysql_query("Select * from message where receiver = "+QString::number(user_id));
    QSqlRecord rec;
    MessageModel *msgPtr;

    while(db.nextQuery())
    {
        rec = db.getRecord();
        msgPtr = new MessageModel(rec);
        messageModels->insert(msgPtr->nID, msgPtr);
    }

    int count = messageModels->count();

    ui->tableWidget_messages->setRowCount(count);
    ui->tableWidget_messages->setColumnCount(3);

    MessageModel* msgModelPtr;
    int i=0;
    QMap<int, MessageModel*>::iterator c;

    for(c = messageModels->begin(); c != messageModels->end(); c++)
    {
        msgModelPtr = c.value();
        //ui->tableWidget_messages->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(msgModelPtr->nID)));
        db.mysql_query("select * from user where id_user = "+QString::number(msgModelPtr->nFrom));

        QString senderName = db.getField("firstname",0)+" "+db.getField("lastname",0);

        //cout<<"name of sender "<<msgModelPtr->nFrom<<endl;
        ui->tableWidget_messages->setItem(i,0,new QTableWidgetItem(senderName));
        ui->tableWidget_messages->setItem(i,1,new QTableWidgetItem(msgModelPtr->subject));
        ui->tableWidget_messages->setItem(i++,2,new QTableWidgetItem(msgModelPtr->content));

    }
}

void MainWindow::on_pushButton_compose_clicked()
{
    MessageModel* newMessage;
    newMessage = new MessageModel(ui->lineEdit_message_subject->text(),
                                  ui->lineEdit_message_body->text(),
                                  ui->comboBox_allusers->itemData(ui->comboBox_allusers->currentIndex()).toInt(),
                                  ui->lineEdit_sender_id->text().toInt());

    messageModels->insert(newMessage->nID,newMessage);
    clearLineEdit(ui->lineEdit_message_body);
    clearLineEdit(ui->lineEdit_message_subject);
}


void MainWindow::populateInstructorUserModel(int user_id)
{
    db.mysql_query("Select * from user where id_user = "+QString::number(user_id));//+user_id);
    QSqlRecord rec;
    UserModel *userModelPtr;

    while( db.nextQuery() )
    {
            rec = db.getRecord();
            userModelPtr = new UserModel( rec );
            userModels->insert( userModelPtr->nID, userModelPtr );
            //ui->iDLabel->setHidden(true);
            ui->lineEdit_profFirstName->setText(userModelPtr->firstname);
            ui->lineEdit_profLastName->setText(userModelPtr->lastname);
            ui->lineEdit_Profaddress1->setText(userModelPtr->address1);
            ui->lineEdit_profAddress2->setText(userModelPtr->address2);
            ui->lineEdit_Profcity->setText(userModelPtr->city);
            ui->lineEdit_profzipcode->setText(QString::number(userModelPtr->nZip));
            //ui->comboBox_professorState->setDisabled(true);
            ui->comboBox_professorState->setCurrentIndex( ui->comboBox_professorState->findData(userModelPtr->nState));
            ui->lineEdit_profDOB->setText(userModelPtr->dob);
            ui->lineEdit_profssn->setText(QString::number(userModelPtr->nSS));
            //ui->LineEdit_id->setText(QString::number(userModelPtr->nID));
            //ui->LineEdit_id->setHidden(true);
                //ui->lineEdit_professorEmail>setText(QString::number(userModelPtr->nTelephone));

    }
}

void MainWindow::populateInstructorCourse(int user_id)
{
    ui->tableWidget_studentsList->setHidden(true);
    db.mysql_query("SELECT * FROM  course WHERE id_course IN (SELECT id_course FROM termcourse WHERE id_instructor = "+QString::number(user_id)+")");
    QSqlRecord rec;
    CourseModel *course;
    while( db.nextQuery() )
    {
        rec = db.getRecord();
        course = new CourseModel(rec);
        courseModels->insert(course->nID,course);
    }

    int count = courseModels->size();

    ui->tableWidget_teacher_courses->setRowCount(count);
    ui->tableWidget_teacher_courses->setColumnCount(2);

    CourseModel* courseModelPtr;
    int i=0;
    QMap<int, CourseModel*>::iterator c;

    for (c = courseModels->begin(); c != courseModels->end(); ++c)
    {
        courseModelPtr = c.value();
#ifdef DEBUGGING
        cout << "name: " << courseModelPtr->nID<< endl;
        //cout <<"name "<<courseModelPtr->name<<endl;
#endif
        ui->tableWidget_teacher_courses->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(courseModelPtr->nID)));
        ui->tableWidget_teacher_courses->setItem(i++,1,new QTableWidgetItem(courseModelPtr->name));
    }

    db.mysql_query("SELECT * FROM term WHERE id_term IN ( SELECT id_term FROM termsubject WHERE id_termsubject IN (SELECT id_termsubject FROM termcourse WHERE id_instructor ="+QString::number(user_id)+"))");

    i = 0;

    while(db.nextQuery() && i < count)
    {
        rec = db.getRecord();
        QString semester_year = rec.value("semester").toString()+" "+rec.value("year").toString();
        ui->tableWidget_teacher_courses->setItem(i++,0,new QTableWidgetItem(semester_year));
    }
}

void MainWindow::on_tableWidget_teacher_courses_cellClicked(int row, int column)
{
    int id = ui->tableWidget_teacher_courses->verticalHeaderItem(row)->text().toInt();
    ui->tableWidget_studentsList->setHidden(false);
    db.mysql_query("select * from user where role = 5 and id_user in (select id_student from student_progress where id_course = "+QString::number(id)+")");

    QSqlRecord rec;
    UserModel* student;
    QMap< int, UserModel* >* studentModels = new QMap < int, UserModel* >;

    while(db.nextQuery())
    {

        rec = db.getRecord();
        #ifdef DEBUGGING
        cout << "fname: " << rec.value("id_user").toInt() << endl;
        #endif

        student = new UserModel(rec);
        studentModels->insert(student->nID,student);

        //ui->tableWidget_studentsList->setItem(i++,0,new QTableWidgetItem(semester_year));
        //ui->tableWidget_studentsList->setItem(i,0,new QTableWidgetItem(fname));
        //ui->tableWidget_studentsList->setItem(i++,1,new QTableWidgetItem(lname));
    }

    int count  = studentModels->count();

    ui->tableWidget_studentsList->setRowCount(count);
    ui->tableWidget_studentsList->setColumnCount(2);

    int i = 0;
    QMap<int, UserModel*>::iterator c;
    UserModel* iterator;
    for (c = studentModels->begin(); c != studentModels->end(); ++c)
    {
        iterator = c.value();
        //ui->tableWidget_studentsList->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(iterator->nID)));
        ui->tableWidget_studentsList->setItem(i,0,new QTableWidgetItem(iterator->firstname));
        ui->tableWidget_studentsList->setItem(i++,1,new QTableWidgetItem(iterator->lastname));
    }

    if(i==0)
    {
        ui->tableWidget_studentsList->setItem(i,0,new QTableWidgetItem("No Students registered"));
    }
}

void MainWindow::on_save_instructor_clicked()
{
    int ss= QString(ui->lineEdit_profssn->text()).replace("-","").toInt();

    UserModel *changeUser =  userModels->value(curUserID);
    changeUser->address1 = ui->lineEdit_Profaddress1->text();
    changeUser->password = ui->lineEdit_profPass->text();
    changeUser->address2 = ui->lineEdit_profAddress2->text();
    changeUser->firstname = ui->lineEdit_profFirstName->text();
    changeUser->lastname = ui->lineEdit_profLastName->text();
    changeUser->city = ui->lineEdit_Profcity->text();
    changeUser->nState = ui->comboBox_professorState->itemData(ui->comboBox_professorState->currentIndex()).toInt();
    changeUser->nZip = ui->lineEdit_profzipcode->text().toInt();
    changeUser->dob = ui->lineEdit_profDOB->text();
    changeUser->nSS = ss;
    changeUser->nTelephone = ui->lineEdit_professorEmail->text().toInt();
    changeUser->nMajor = ui->comboBox_adminMajor->itemData(ui->comboBox_adminMajor->currentIndex()).toInt();



    changeUser->updateUser();

}

void MainWindow::populateTAUserModel(int user_id)
{
    db.mysql_query("Select * from user where id_user = "+QString::number(user_id));//+user_id);
    QSqlRecord rec;
    UserModel *userModelPtr;

    while( db.nextQuery() )
    {
            rec = db.getRecord();
            userModelPtr = new UserModel( rec );
            userModels->insert( userModelPtr->nID, userModelPtr );
           // ui->iDLabel->setHidden(true);
            ui->lineEdit_ta_firstname->setText(userModelPtr->firstname);
            ui->lineEdit_ta_lastname->setText(userModelPtr->lastname);
            ui->lineEdit_ta_address1->setText(userModelPtr->address1);
            ui->lineEdit_ta_address2->setText(userModelPtr->address2);
            ui->lineEdit_ta_city->setText(userModelPtr->city);
            ui->lineEdit_ta_zipcode->setText(QString::number(userModelPtr->nZip));
            //ui->comboBox_professorState->setDisabled(true);
            ui->comboBox_ta_state->setCurrentIndex( ui->comboBox_ta_state->findData(userModelPtr->nState));
            ui->lineEdit_ta_DOB->setText(userModelPtr->dob);
            ui->lineEdit_ta_ssn->setText(QString::number(userModelPtr->nSS));
            //ui->LineEdit_id->setText(QString::number(userModelPtr->nID));
            //ui->lineEdit_ta_UIN->setText(QString::number(userModelPtr->nUIN));
            //ui->LineEdit_id->setHidden(true);
    }
}


void MainWindow::on_pushButton_ta_save_clicked()
{
    UserModel *changeUser =  userModels->value(curUserID);
    changeUser->address1 = ui->lineEdit_ta_address1->text();
    changeUser->address2 = ui->lineEdit_ta_address2->text();
    changeUser->firstname = ui->lineEdit_ta_firstname->text();
    changeUser->lastname = ui->lineEdit_ta_lastname->text();
    changeUser->city = ui->lineEdit_ta_city->text();
    changeUser->nState = ui->comboBox_ta_state->itemData(ui->comboBox_ta_state->currentIndex()).toInt();
    changeUser->nZip = ui->lineEdit_ta_zipcode->text().toInt();
    changeUser->dob = ui->lineEdit_ta_DOB->text();
    changeUser->nSS = ui->lineEdit_ta_ssn->text().toInt();
    changeUser->nTelephone = ui->lineEdit_ta_email->text().toInt();

    changeUser->updateUser();

}

void MainWindow::populateTACourse(int user_id)
{
    ui->tableWidget_ta_studentsList->setHidden(true);
    db.mysql_query("SELECT * FROM  course WHERE id_course IN (SELECT id_course FROM termcourse WHERE id_ta = "+QString::number(user_id)+")");
    QSqlRecord rec;
    CourseModel *course;
    while( db.nextQuery() )
    {
        rec = db.getRecord();
        course = new CourseModel(rec);
        courseModels->insert(course->nID,course);
    }

    int count = courseModels->size();

    ui->tableWidget_ta_courses->setRowCount(count);
    ui->tableWidget_ta_courses->setColumnCount(2);

    CourseModel* courseModelPtr;
    int i=0;
    QMap<int, CourseModel*>::iterator c;

    for (c = courseModels->begin(); c != courseModels->end(); ++c)
    {
        courseModelPtr = c.value();
#ifdef DEBUGGING
        cout << "name: " << courseModelPtr->nID<< endl;
        //cout <<"name "<<courseModelPtr->name<<endl;
#endif
        ui->tableWidget_ta_courses->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(courseModelPtr->nID)));
        ui->tableWidget_ta_courses->setItem(i++,1,new QTableWidgetItem(courseModelPtr->name));
    }

    db.mysql_query("SELECT * FROM term WHERE id_term IN ( SELECT id_term FROM termsubject WHERE id_termsubject IN (SELECT id_termsubject FROM termcourse WHERE id_ta ="+QString::number(user_id)+"))");

    i = 0;

    while(db.nextQuery() && i < count)
    {
        rec = db.getRecord();
        QString semester_year = rec.value("semester").toString()+" "+rec.value("year").toString();
        ui->tableWidget_ta_courses->setItem(i++,0,new QTableWidgetItem(semester_year));
    }
}

void MainWindow::on_tableWidget_ta_courses_cellClicked(int row, int column)
{
    int id = ui->tableWidget_ta_courses->verticalHeaderItem(row)->text().toInt();
    ui->tableWidget_ta_studentsList->setHidden(false);
    db.mysql_query("select * from user where role = 5 and id_user in (select id_student from student_progress where id_course = "+QString::number(id)+")");

    QSqlRecord rec;
    UserModel* student;
    QMap< int, UserModel* >* studentModels = new QMap < int, UserModel* >;

    while(db.nextQuery())
    {

        rec = db.getRecord();
        #ifdef DEBUGGING
        //cout << "fname: " << rec.value("id_user").toInt() << endl;
        #endif

        student = new UserModel(rec);
        studentModels->insert(student->nID,student);
    }

    int count  = studentModels->count();

    ui->tableWidget_ta_studentsList->setRowCount(count);
    ui->tableWidget_ta_studentsList->setColumnCount(2);

    int i = 0;
    QMap<int, UserModel*>::iterator c;
    UserModel* iterator;
    for (c = studentModels->begin(); c != studentModels->end(); ++c)
    {
        iterator = c.value();
        //ui->tableWidget_ta_studentsList->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(iterator->nID)));
        ui->tableWidget_ta_studentsList->setItem(i,0,new QTableWidgetItem(iterator->firstname));
        ui->tableWidget_ta_studentsList->setItem(i++,1,new QTableWidgetItem(iterator->lastname));
    }

    if(i==0)
    {
        ui->tableWidget_ta_studentsList->setItem(i,0,new QTableWidgetItem("No Students registered"));
    }
}
// changes end

void MainWindow::on_pushButton_adminImport_clicked()
{
    QString fileName = ui->lineEdit_XML->text();
#ifdef DEBUGGING
    cout << "xml file name: " << fileName.toLocal8Bit().constData() << endl;
#endif
    XmlFileParser* myXmlParser = new XmlFileParser();
    myXmlParser->parseXML( fileName );
    QList< QMap<QString,QString> >* importedUsers = myXmlParser->users;
    QList< QMap<QString,QString> >* importedSubjects = myXmlParser->subjects;
    QList< QMap<QString,QString> >* importedCourses = myXmlParser->courses;

#ifdef DEBUGGING
    cout << "importing " << importedUsers->size() << " users" << endl;
    cout << "importing " << importedSubjects->size() << " subjects" << endl;
    cout << "importing " << importedCourses->size() << " courses" << endl;
#endif


    for( int i=0; i<importedUsers->size(); ++i )
    {
        QMap<QString,QString> curUser = (*importedUsers)[i];
        UserModel* tmpUserModel = new UserModel( curUser["login"], curUser["password"], curUser["firstname"], curUser["lastname"], curUser["address1"], curUser["address2"], curUser["city"], curUser["dob"], curUser["nZip"].toInt(), curUser["nRole"].toInt(), curUser["nState"].toInt(), curUser["nSS"].toInt(), curUser["nTelephone"].toInt(), curUser["nMajor"].toInt() );
        userModels->insert( tmpUserModel->nID, tmpUserModel );
#ifdef DEBUGGING
        cout << "added user with id: " << tmpUserModel->nID << endl;
#endif
    }

    for( int i=0; i<importedSubjects->size(); ++i )
    {
        QMap<QString,QString> curSubject = (*importedSubjects)[i];
        SubjectModel* tmpSubjectModel = new SubjectModel( curSubject["name"], curSubject["college"] );
        subjectModels->insert( tmpSubjectModel->nID, tmpSubjectModel );
#ifdef DEBUGGING
        cout << "added subject with id: " << tmpSubjectModel->nID << endl;
#endif
    }

    for( int i=0; i<importedCourses->size(); ++i )
    {
        QMap<QString,QString> curCourse = (*importedCourses)[i];
        CourseModel* tmpCourseModel = new CourseModel( curCourse["name"], curCourse["nSubject"].toInt(), curCourse["description"], curCourse["nCreditHours"].toInt() );
        courseModels->insert( tmpCourseModel->nID, tmpCourseModel );
#ifdef DEBUGGING
        cout << "added course with id: " << tmpCourseModel->nID << endl;
#endif
    }

    updateAdminUserTable();
    updateAdminSubjectTable();
    updateAdminCourseTable();

    delete myXmlParser;
}

void MainWindow::on_pushButton_RSearch_clicked()
{
    //get values from comboboxes to form query
    QString rYear = ui->comboBox_RYear->currentText();
    QString rTerm = ui->comboBox_RTerm->currentText();
    QString rSubject = ui->comboBox_RSubject->currentText();

    //populate registration tab

    //select the term based on the user input
    db.mysql_query("Select id_term FROM term WHERE year = '" + rYear + "' AND semester = '" + rTerm + "';");
    QString termID = db.getField("id_term", 0);
    //cout << "query run"<< endl;

    //get all the subjects taught in the semester
    TermSubjectModel* termSubjectModelPtr;
    QMap<int, TermSubjectModel*>::iterator i;
    //int cnt = 0; //counter for subjects map
    QMap<int, int> subjects; //stores IDs of subjects
    cout << "subject Model Size: " << termSubjectModels->size()<< endl;

    //iterate through the subject models
    for( i = termSubjectModels->begin(); i != termSubjectModels->end(); ++i)
    {
        //cout <<" inside for loop"<<endl;
        termSubjectModelPtr = i.value();
        //find termsubject.id_subject based on id_term
        if( termSubjectModelPtr->nTermID == termID.toInt()){
            cout << "nTermID: " << termSubjectModelPtr->nTermID;
            cout << " nSubjectID: " << termSubjectModelPtr->nSubjectId<<endl;
            subjects.insert(termSubjectModelPtr->nSubjectId, termSubjectModelPtr->nSubjectId);
            //cnt++;
            cout << "subjects map zise: " << subjects.size() <<endl;
        }

    }

    //now iterate through and find the courses taught in that year/semester
    CourseModel* courseModelPtr;
    QMap<int, CourseModel*>::iterator n;
    cout << "CourseModel size: " << courseModels->size() <<endl;
    for( n = courseModels->begin(); n != courseModels->end(); ++n)
    {
        courseModelPtr = n.value();
        if(subjects.contains(courseModelPtr->nSubject))
        {
            cout << "course: " << courseModelPtr->name.toStdString() <<endl;
        }
    }
    //QMap< int, TermCourseModel*> *termCourseModels;

    //QMap< int, TermSubjectModel*> *termSubjectModels;

#ifdef DEBUGGING

    cout << "year: " << rYear.toAscii().data() << endl;
    cout << "term: " << rTerm.toAscii().data() << endl;
    cout << "subject: " << rSubject.toAscii().data() << endl;


    cout << "db count: " << db.count() << endl;
    cout << "db idTerm: " << db.getField("id_term", 0).toStdString() <<endl;
    cout << "QString termID: " << termID.toStdString() << endl;
#endif
}

void MainWindow::updateAdminSubjectTable(){

    int count = subjectModels->size();


    ui->tableWidget_adminSubjects->setRowCount(count);
    ui->tableWidget_adminSubjects->setColumnCount(2);

    SubjectModel* subjectModelPtr;
    int i=0;
    QMap<int, SubjectModel*>::iterator c;

    for (c = subjectModels->begin(); c != subjectModels->end(); ++c){
        subjectModelPtr = c.value();
        ui->tableWidget_adminSubjects->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(subjectModelPtr->nID)));
        ui->tableWidget_adminSubjects->setItem(i,0,new QTableWidgetItem(subjectModelPtr->name));
        ui->tableWidget_adminSubjects->setItem(i++,1,new QTableWidgetItem(subjectModelPtr->college));
    }
}

void MainWindow::updateAdminCourseTable(){

    int count = courseModels->size();


    ui->tableWidget_adminCourses->setRowCount(count);
    ui->tableWidget_adminCourses->setColumnCount(4);

    CourseModel* courseModelPtr;
    int i=0;
    QMap<int, CourseModel*>::iterator c;

    for (c = courseModels->begin(); c != courseModels->end(); ++c){
        courseModelPtr = c.value();
        ui->tableWidget_adminCourses->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(courseModelPtr->nID)));
        ui->tableWidget_adminCourses->setItem(i,0,new QTableWidgetItem(courseModelPtr->name));
        ui->tableWidget_adminCourses->setItem(i,1,new QTableWidgetItem(QString::number(courseModelPtr->nSubject)));
        ui->tableWidget_adminCourses->setItem(i,2,new QTableWidgetItem(courseModelPtr->description));
        ui->tableWidget_adminCourses->setItem(i++,3,new QTableWidgetItem(QString::number(courseModelPtr->nCreditHours)));
    }
}

void MainWindow::updateCalendar(){

    int count = eventModels->size();

    EventModel* eventModelPtr;
    int i=0;
    QMap<int, EventModel*>::iterator c;

    QTextCharFormat format;

    format.setForeground(qvariant_cast<QColor>(tr("Green")));

    for (c = eventModels->begin(); c != eventModels->end(); ++c){
        eventModelPtr = c.value();
        ui->calendarWidget->setDateTextFormat( eventModelPtr->date, format );
    }
}

void MainWindow::on_pushButton_adminSubjectDelete_clicked()
{
    #ifdef DEBUGGING
            cout << "Delete subject clicked." << endl;
    #endif
    if (currentSubjectSelected){
        connect(currentSubjectSelected, SIGNAL(sendMessage(QString)),
                this, SLOT(showStatusMessage(QString)));
        int id = currentSubjectSelected->nID;

        currentSubjectSelected = subjectModels->value(id);
        delete(currentSubjectSelected);

        subjectModels->remove(id);
        updateAdminSubjectTable();
    }else{
        #ifdef DEBUGGING
                cout << "Subject not selected for deletion." << endl;
        #endif
    }
}

void MainWindow::on_tableWidget_adminSubjects_cellClicked(int row, int column)
{
    int id = ui->tableWidget_adminSubjects->verticalHeaderItem(row)->text().toInt();
    SubjectModel* editSubject;
    editSubject = subjectModels->value(id);

    currentSubjectSelected = subjectModels->value(id);
    ui->label_SubjectID->setText(QString::number(editSubject->nID));
    ui->lineEdit_adminSubjectName->setText(editSubject->name);
    ui->lineEdit_adminSubjectCollege->setText(editSubject->college);
}

void MainWindow::on_pushButton_adminSubjectNew_clicked()
{
    clearLineEdit(ui->lineEdit_adminSubjectName);
    clearLineEdit(ui->lineEdit_adminSubjectCollege);
    currentSubjectSelected = NULL;
}

void MainWindow::on_pushButton_adminSubjectSave_clicked()
{
    if( currentSubjectSelected == NULL )
    {
        SubjectModel* newSubject;
        newSubject = new SubjectModel( ui->lineEdit_adminSubjectName->text(),
                                 ui->lineEdit_adminSubjectCollege->text());
         subjectModels->insert(newSubject->nID, newSubject);
         updateSubjects(ui->comboBox_adminCourseSubject, newSubject->nID);
    }
    else
    {
        currentSubjectSelected->name = ui->lineEdit_adminSubjectName->text();
        currentSubjectSelected->college = ui->lineEdit_adminSubjectCollege->text();
        currentSubjectSelected->updateSubject();
    }
    updateAdminSubjectTable();
}

void MainWindow::on_tableWidget_adminCourses_cellClicked(int row, int column)
{
    int id = ui->tableWidget_adminCourses->verticalHeaderItem(row)->text().toInt();
    CourseModel* editCourse;
    editCourse = courseModels->value(id);

    currentCourseSelected = courseModels->value(id);
    ui->label_CourseID->setText(QString::number(editCourse->nID));
    ui->lineEdit_adminCourseName->setText(editCourse->name);
    //ui->lineEdit_adminCourseSubject->setText(QString::number(editCourse->nSubject));
    ui->comboBox_adminCourseSubject->setCurrentIndex( ui->comboBox_adminCourseSubject->findData(editCourse->nSubject));
    ui->lineEdit_adminCourseDescription->setText(editCourse->description);
    ui->lineEdit_adminCourseCreditHours->setText(QString::number(editCourse->nCreditHours));
}

void MainWindow::on_pushButton_adminCourseSave_clicked()
{
    if( currentCourseSelected == NULL )
    {
        CourseModel* newCourse;
        newCourse = new CourseModel( ui->lineEdit_adminCourseName->text(), ui->comboBox_adminCourseSubject->itemData(ui->comboBox_adminCourseSubject->currentIndex()).toInt(), ui->lineEdit_adminCourseDescription->text(), ui->lineEdit_adminCourseCreditHours->text().toInt() );
        courseModels->insert(newCourse->nID, newCourse);
    }
    else
    {
        currentCourseSelected->name = ui->lineEdit_adminCourseName->text();
        //currentCourseSelected->nSubject = ui->lineEdit_adminCourseSubject->text().toInt();
        currentCourseSelected->nSubject = ui->comboBox_adminCourseSubject->itemData(ui->comboBox_adminCourseSubject->currentIndex()).toInt();
        currentCourseSelected->description = ui->lineEdit_adminCourseDescription->text();
        currentCourseSelected->nCreditHours = ui->lineEdit_adminCourseCreditHours->text().toInt();
        currentCourseSelected->updateCourse();
    }
    updateAdminCourseTable();
}

void MainWindow::on_pushButton_adminCourseDelete_clicked()
{
    #ifdef DEBUGGING
            cout << "Delete course clicked." << endl;
    #endif
    if (currentSubjectSelected){
        connect(currentCourseSelected, SIGNAL(sendMessage(QString)),
                this, SLOT(showStatusMessage(QString)));
        int id = currentCourseSelected->nID;

        currentCourseSelected = courseModels->value(id);
        delete(currentCourseSelected);

        courseModels->remove(id);
        updateAdminCourseTable();
    }else{
        #ifdef DEBUGGING
                cout << "Course not selected for deletion." << endl;
        #endif
    }
}

void MainWindow::on_pushButton_adminCourseNew_clicked()
{
    clearLineEdit(ui->lineEdit_adminCourseName);
    ui->comboBox_adminCourseSubject->setCurrentIndex(0);
    clearLineEdit(ui->lineEdit_adminCourseDescription);
    clearLineEdit(ui->lineEdit_adminCourseCreditHours);
    currentCourseSelected = NULL;
}

void MainWindow::logout(){
    emit(logoutAction());
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QTextCharFormat format;

    format.setForeground(qvariant_cast<QColor>(tr("Green")));
    ui->calendarWidget->setDateTextFormat ( date, format );
}

void MainWindow::on_pushButton_CalendarSave_clicked()
{
    if( currentEventSelected == NULL )
    {
        EventModel* newEvent;
        newEvent = new EventModel( ui->lineEdit_CalendarEventName->text(), ui->textEdit_CalendarEventDescription->toPlainText(), curUserID, ui->calendarWidget->selectedDate() );
        eventModels->insert(newEvent->nID, newEvent);
    }
    else
    {
        currentEventSelected->name = ui->lineEdit_CalendarEventName->text();
        currentEventSelected->description = ui->textEdit_CalendarEventDescription->toPlainText();
        currentEventSelected->nIDUser = curUserID;
        currentEventSelected->date = ui->calendarWidget->selectedDate();
        currentEventSelected->updateEvent();
    }
    updateCalendar();
}

void MainWindow::on_pushButton_CalendarDelete_clicked()
{
#ifdef DEBUGGING
        cout << "Delete event clicked." << endl;
#endif
if (currentEventSelected){
    connect(currentEventSelected, SIGNAL(sendMessage(QString)),
            this, SLOT(showStatusMessage(QString)));
    int id = currentEventSelected->nID;

    currentEventSelected = eventModels->value(id);
    delete(currentEventSelected);

    eventModels->remove(id);
    QTextCharFormat format;

    format.setForeground(qvariant_cast<QColor>(tr("Black")));
    ui->calendarWidget->setDateTextFormat ( ui->calendarWidget->selectedDate(), format );
}else{
    #ifdef DEBUGGING
            cout << "Event not selected for deletion." << endl;
    #endif
}

    clearLineEdit(ui->lineEdit_CalendarEventName);
    clearTextEdit(ui->textEdit_CalendarEventDescription);
    currentEventSelected = NULL;
}

void MainWindow::on_pushButton_all_clicked()
{
    globalSelectredRole =0;
    updateAdminUserTable();
}

void MainWindow::on_pushButton_admin_clicked()
{
    globalSelectredRole =1;
    updateAdminUserTable();
}

void MainWindow::on_pushButton_teacher_clicked()
{
    globalSelectredRole =2;
    updateAdminUserTable();
}

void MainWindow::on_pushButton_ta_clicked()
{
    globalSelectredRole =3;
    updateAdminUserTable();
}

void MainWindow::on_pushButton_adviser_clicked()
{
    globalSelectredRole =4;
    updateAdminUserTable();
}

void MainWindow::on_pushButton_student_clicked()
{
    globalSelectredRole =5;
    updateAdminUserTable();
}
