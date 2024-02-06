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


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:

    void run();

    void processScript(const string& script);

    void splitByLast(const string& str, const string& sep, string& a, string& b);

    string completeTab(const string& script, const string& init, size_t& tabFileIndex,
                       string& start, string& base, string& startsWith);

    void runLoop();

    QTimer *logTimer;

private slots:
   void updateLog();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
