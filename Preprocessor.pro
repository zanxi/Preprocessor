#-------------------------------------------------
#
# Project created by QtCreator 2024-02-03T19:47:14
#
#-------------------------------------------------

QT       += core gui sql xml network printsupport script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Preprocessor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scripting/Constants.cpp \
    scripting/Functions.cpp \
    scripting/Interpreter.cpp \
    scripting/Parser.cpp \
    scripting/ParserFunction.cpp \
    scripting/ParsingScript.cpp \
    scripting/Translation.cpp \
    scripting/Utils.cpp \
    scripting/UtilsOS.cpp \
    scripting/Variable.cpp \
    csv/csvfile.cpp \
    db/database.cpp \
    db/GenerateDB.cpp \
    db/SqlDataBase.cpp \
    json/json_w.cpp \
    Debug/data.cpp \
    Debug/datetime.cpp \
    Debug/logger.cpp \
    utils/imageview.cpp \
    utils/qcustomplot.cpp \
    utils/UtilsT.cpp \
    dataanimals.cpp \
    utils/highlighter.cpp \
    utils/searchhightlight.cpp

HEADERS += \
        mainwindow.h \
    scripting/Constants.h \
    scripting/Functions.h \
    scripting/Interpreter.h \
    scripting/Parser.h \
    scripting/ParserFunction.h \
    scripting/ParsingScript.h \
    scripting/Translation.h \
    scripting/Utils.h \
    scripting/UtilsOS.h \
    scripting/Variable.h \
    csv/csvfile.h \
    db/database.h \
    db/GenerateDB.h \
    db/SqlDataBase.h \
    json/json_w.h \
    Debug/data.h \
    Debug/datetime.h \
    Debug/logger.h \
    utils/imageview.h \
    utils/qcustomplot.h \
    utils/UtilsT.h \
    dataanimals.h \
    utils/highlighter.h \
    utils/searchhightlight.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
