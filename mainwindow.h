#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QString>
#include <QTextEdit>
#include "usermodel.h"
#include "subjectmodel.h"
#include "coursemodel.h"
#include "xmlfileparser.h"
#include <QFileDialog>
#include "holdmodel.h"
#include "termcoursemodel.h"
#include "termsubjectmodel.h"
#include "messagemodel.h"
#include "eventmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showLoginWindow();
    void setRegularWindowSize();
    void switchRole(QString _userRole, int userId);
    void updateAdminUserTable();
    void updateAdminSubjectTable();
    void updateAdminCourseTable();
    void updateCalendar();

    void populateAdminUserModel();
    void populateAdminSubjectModel();
    void populateAdminCourseModel();
    void populateTermCourseModel();
    void populateTermSubjectModel();
    void populateEventModel();

    void populateHolds();
    void showStates(QComboBox* _box);
    void showMajor(QComboBox* _box);
    void showRole(QComboBox* _box);
    void updateSubjects(QComboBox* _box, int nID);
    void clearLineEdit(QLineEdit* _lineEdit);
    void clearTextEdit(QTextEdit* _textEdit);

    // used for teacher
    void populateInstructorUserModel(int user_id);
    void populateInstructorCourse(int user_id);

    // used for ta
    void populateTAUserModel(int userId);
    void populateTACourse(int userId);
    //used for student
    void showTermYear(QComboBox* _box);
    void showTermSemester(QComboBox* _box);
    void showSubjects(QComboBox* _box);

    //message
    void populateMessageModel(int userId);
    void showAllUsers(QComboBox* _box, int userId);
    void repopulateAllUsers(QComboBox* _box);

signals:
    void loginSubmitted( QString _user, QString _pass );
    void logoutAction();

private slots:
    void deleteUser();
    void deleteHolds();
    void fillHold();
    void updateHolds();
    void selectXMLFile();
    void changeUserRoleForm(int _index);
    void showStatusMessage(QString _message);
    void clearAdminFrom();
    void on_pushButton_login_clicked();
    void on_lineEdit_password_returnPressed();
    void clearHoldForm();

    void on_lineEdit_login_returnPressed();

    void on_pushButton_compose_admin_clicked();

    void on_pushButton_compose_teacher_clicked();

    void on_pushButton_compose_ta_clicked();

    //void on_userinfo_pushButton_clicked();

    void on_tableWidget_adminUsersTable_cellClicked(int row, int column);

    void on_pushButton_adminSave_clicked();

    void createNewCourse();
    void createNewSubject();
    void on_pushButton_adminImport_clicked();
    void on_pushButton_RSearch_clicked();

    void on_save_instructor_clicked();

    void on_tableWidget_teacher_courses_cellClicked(int row, int column);

    void on_pushButton_adminSubjectDelete_clicked();

    void on_tableWidget_adminSubjects_cellClicked(int row, int column);

    void on_pushButton_adminSubjectNew_clicked();

    void on_pushButton_adminSubjectSave_clicked();

    void on_tableWidget_adminCourses_cellClicked(int row, int column);

    void on_pushButton_adminCourseSave_clicked();

    void on_pushButton_adminCourseDelete_clicked();

    void on_pushButton_adminCourseNew_clicked();

    void on_pushButton_ta_save_clicked();

    void on_tableWidget_ta_courses_cellClicked(int row, int column);

    void logout();

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_compose_clicked();

    void on_pushButton_CalendarSave_clicked();

    void on_pushButton_CalendarDelete_clicked();

    void on_pushButton_all_clicked();

    void on_pushButton_admin_clicked();

    void on_pushButton_teacher_clicked();

    void on_pushButton_ta_clicked();

    void on_pushButton_adviser_clicked();

    void on_pushButton_student_clicked();

private:
    Ui::MainWindow *ui;
    QMap< int, UserModel* >* userModels;
    UserModel * currentUserSelected;
    SubjectModel* currentSubjectSelected;
    CourseModel* currentCourseSelected;
    QMap< int, SubjectModel*>* subjectModels;
    QMap< int, CourseModel*> *courseModels;
    QMap< int, HoldModel*> *holdModels;
    QMap< int, TermCourseModel*> *termCourseModels;
    QMap< int, TermSubjectModel*> *termSubjectModels;
    QMap<int, MessageModel*> *messageModels;
    QMap<int, EventModel*>* eventModels;
    HoldModel* currentHold;
    int curUserID;
    EventModel* currentEventSelected;

    int globalSelectredRole;
};
#endif // MAINWINDOW_H
