#-------------------------------------------------
#
# Project created by QtCreator 2012-04-16T11:45:49
#
#-------------------------------------------------

QT       += core gui sql

CONFIG  += qt

TARGET = course-registration-cs440
TEMPLATE = app


SOURCES += main.cpp\
    windowcontroller.cpp \
    utils.cpp \
    userinformation.cpp \
    loginview.cpp \
    usermodel.cpp \
    db.cpp \
    globals.cpp \
    mainwindow.cpp \
    subjectmodel.cpp \
    coursemodel.cpp \
    termcoursemodel.cpp \
    termsubjectmodel.cpp \
    xmlfileparser.cpp \
    holdmodel.cpp \
    messagemodel.cpp \
    eventmodel.cpp

HEADERS  += \
    utils.h \
    userinformation.h \
    windowcontroller.h \
    loginview.h \
    usermodel.h \
    db.h \
    globals.h \
    mainwindow.h \
    subjectmodel.h \
    coursemodel.h \
    termcoursemodel.h \
    termsubjectmodel.h \
    xmlfileparser.h \
    holdmodel.h \
    messagemodel.h \
    eventmodel.h

FORMS    += \
    userinformation.ui \
    loginview.ui \
    mainwindow.ui

OTHER_FILES += \
    lib/qsqlmysqld4.dll \
    lib/qsqlmysql4.dll \
    lib/libqsqlmysqld4.a \
    lib/libqsqlmysql4.a \
    lib/libmysql.dll \
    import.xml

RESOURCES += \
    res.qrc
