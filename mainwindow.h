#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <cmath>
#include <cstdio>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <locale>
#include <map>
#include <string>
#include <vector>

#include "scripting/Interpreter.h"
#include "scripting/Parser.h"
#include "scripting/Translation.h"
#include "scripting/Utils.h"
#include "scripting/UtilsOS.h"

#include <QTimer>

#include "utils/highlighter.h"
#include "utils/searchhightlight.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent * event);

private slots:
    void on_pushButton_clicked();
    void OpenFileScript();
    void OpenFileScript(QString fileScript);

private:

    void run();
    void processScript(const string& script);
    void splitByLast(const string& str, const string& sep, string& a, string& b);
    string completeTab(const string& script, const string& init, size_t& tabFileIndex,
                       string& start, string& base, string& startsWith);
    void runLoop();

    QTimer *logTimer;

    Highlighter *highlighter_code;
    Highlighter *highlighter_execution;
    Highlighter *highlighter_log;

    SearchHighLight *searchHighLight_execution;
    SearchHighLight *searchHighLight_log;


    int on_lineEdit_log_search_cursorPosition_arg1;
    int on_lineEdit_log_search_cursorPosition_arg2;

    int on_lineEdit_execution_search_cursorPosition_arg1;
    int on_lineEdit_execution_search_cursorPosition_arg2;


    //QString fileName;

private slots:
   void updateLog();
    void on_pushButton_open_script_clicked();
   void on_pushButton_savescript_clicked();
    void on_pushButton_exe_search_clicked();
   void on_pushButton_log_search_clicked();
    void on_lineEdit_log_search_cursorPositionChanged(int arg1, int arg2);
   void on_lineEdit_execution_search_cursorPositionChanged(int arg1, int arg2);

   private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
