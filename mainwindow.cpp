#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QObject>

#include "Debug/logger.h"
#include "dataanimals.h"
#include "utils/highlighter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DataSystems::Instance().clear();

    //***************** Установка белого цвета приложения и размеров ****************************//
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::gray);
    this->setPalette(pal);
    setGeometry(QRect(200, 100, 1600, 800));
    //***************** End Установка белого цвета приложения и размеров ****************************//

    ui->groupBox->setStyleSheet("QGroupBox {"
                                "background-color: white;"
                                "}"
                                "QGroupBox::title {"
                                "color: white;"
                                "background-color:"+DataSystems::Instance().settings___color_header+";"
                                "padding: 4 20000 4 10;"
                                "}");
    ui->groupBox_2->setStyleSheet("QGroupBox {"
                                "background-color: white;"
                                "}"
                                "QGroupBox::title {"
                                "color: white;"
                                "background-color:"+DataSystems::Instance().settings___color_header+";"
                                "padding: 4 20000 4 10;"
                                "}");
    ui->groupBox_3->setStyleSheet("QGroupBox {"
                                "background-color: white;"
                                "}"
                                "QGroupBox::title {"
                                "color: white;"
                                "background-color:"+DataSystems::Instance().settings___color_header+";"
                                "padding: 4 20000 4 10;"
                                "}");

    ui->pushButton->setStyleSheet(
        "background-color:"+DataSystems::Instance().settings___color_header+";"
        "color: white;"
        "padding: 4 50 4 10;"
        );
    ui->pushButton_2->setStyleSheet(
        "background-color:"+DataSystems::Instance().settings___color_header+";"
        "color: white;"
        "padding: 4 50 4 10;"
        );


    //this->maximumSize();
    //run();
    //script = "a=357/113;c=a;";

    setWindowTitle("Preprocessor cscs");

    //ui->textEdit_code->setStyleSheet("background-color: rgb(197, 249, 136)");
    ui->textEdit_code->setStyleSheet("background-color: rgb(208, 255, 208)");
    ui->textEdit_execution->setStyleSheet("background-color: rgb(208, 255, 208)");
    ui->textEdit_log->setStyleSheet("background-color: rgb(208, 255, 208)");

    Highlighter *highlighter = new Highlighter(ui->textEdit_code->document());
    Highlighter *highlighter2 = new Highlighter(ui->textEdit_execution->document());
    Highlighter *highlighter3 = new Highlighter(ui->textEdit_log->document());

    ui->textEdit_code->setText(
                "a=357/113;"
                "\ni = 0;"
                      "\nwhile (++i < 3) {"
                                     "\nj=i+1; "
                                     "\nprint(3245);"
                                 "\n}");
                                //"print(a);");
                //"\nc=a;"); //QString::fromStdString(script));



    logTimer = new QTimer(this);
    connect(logTimer, SIGNAL(timeout()),this,SLOT(updateLog()));
    //logTimer->start(250);

}

void MainWindow::updateLog()
{
   ui->textEdit_log->setText(DataSystems::Instance().log);
   ui->textEdit_execution->setText(DataSystems::Instance().log_execution_result);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run()
{
    int argc = 0;
    char **argv;
    argv = new char*[3] ();
    argv[0] = new char[10]();
    argv[1] = new char[10]();
    argv[2] = new char[10]();

    OS::init();

    try {
      Interpreter::init();
    }
    catch (ParsingException& exc) {
      OS::printError(exc.what(), true);
    }
    ParserFunction::allFunctions();

    processScript("include(\"/Users/vk/cscs/scripts/functions.cscs\");");
    string file;
    file = "/Users/vk/Documents/github/cscscpp/bin/Debug/scripts/temp.cscs";


          //string script = Utils::getFileContents("");
          //string result = Translation::translateScript(script, argv[1], argv[2]);

//    if (argc > 3 ) {
//      string script = Utils::getFileContents(argv[3]);
//      string result = Translation::translateScript(script, argv[1], argv[2]);
//      cout << result << endl;
//      return; //0;
//    }

//    string path = argv[0];
//    if (argc > 1 ) {
//      file = argv[1];
//    }

    if (!file.empty()) {
      string script;
      try {

        //script = Utils::getFileContents(file);

        //script = Utils::getFileContents("c:/_2024__/test.cscs");
        script = "a=1;"
                "//b=2;"
                "//c=3;"
                "//d=4;"
                "e=5;"
                "i = 0;"
                "while (++i < 10) {"
                    "print(\"i=\", i);    // GO AWAY"
                "    print(\"a/c=\", a/c);   "
                "}";

        script = "a=357/113; c=a;"
                 "i = 0;"
                 "while (++i < 3) {"
                     "j=i+1; "
                     "print(3245);"
                 "}";
                //"print(a);";

        script = ""
                 "i = 0;"
                 "while (++i < 10) {"
                     "j=i+1; "
                     "print(3245);"
                 "}";
                //"print(a);";

        script = "a=357/113;c=a;";

        script = ui->textEdit_code->toPlainText().toStdString();

        ui->textEdit_code->setText(QString::fromStdString(script));
        //ui->textEdit_code->setBack;



      }
      catch (exception& exc) {
        OS::printError(exc.what(), true);
        ui->textEdit_code->setText(exc.what()); //QString::fromStdString(script));
        return;// -1;
      }
      processScript(script);
      qDebug()<<"processScript(script);";
    } else {
      runLoop();
    }

}

void MainWindow::processScript(const string& script)
{
  Variable result;
  try {
    result = Interpreter::process(script);

    logger::WriteLog_result_execution(QString::fromStdString(result.toPrint()));
    //ui->textEdit_execution->setText(QString::fromStdString(result.toPrint()));
    //ui->textEdit_execution->setText(QString::fromStdString(result.toString()));

    if (result.type != Constants::NONE) {
      OS::print(result.toPrint(), true);
    }
  } catch(exception& exc) {
    OS::printError(exc.what(), true);
  }
}

void splitByLast(const string& str, const string& sep, string& a, string& b)
{
  size_t it = str.find_last_of(sep);
  a = it == string::npos ? "" : str.substr(0, it + 1);
  b = it == string::npos ? str : str.substr(it + 1);
}

string MainWindow::completeTab(const string& script, const string& init, size_t& tabFileIndex,
                   string& start, string& base, string& startsWith)
{
  if (tabFileIndex > 0 && script.compare(init) != 0) {
    // The user has changed something in the input field
    tabFileIndex = 0;
  }
  if (tabFileIndex == 0 ||
      (!script.empty() && script.back() == OS::DIR_SEP[0])) {
    // The user pressed tab first time or pressed it on a directory
    string path;
    //splitByLast(script.c_str(), " ", start, path);
    //splitByLast(path, "/\\", base, startsWith);
  }

  tabFileIndex++;
  string result = OS::getFileEntry(base, tabFileIndex, startsWith);
  result = result.empty() ? startsWith : result;
  return start + base  + result;
}

void MainWindow::runLoop()
{
  vector<string> commands;
  string init;
  int cmdPtr = 0;
  size_t tabFileIndex = 0;
  bool arrowMode = false;
  string start, base, startsWith;
  string script;
  bool newStatement = true;

  while (true) {
    OS::NEXT_CMD nextCmd = OS::NEXT_CMD::NONE;
    if (newStatement) {
      script.clear();
    }
    script += OS::getConsoleLine(nextCmd, init,
             true /*enhancedMode*/, newStatement);
    script = Utils::trim(script);

    if (nextCmd == OS::NEXT_CMD::TAB) {
      init = completeTab(script, init, tabFileIndex, start, base, startsWith);
      continue;
    } else if (nextCmd == OS::NEXT_CMD::PREV || nextCmd == OS::NEXT_CMD::NEXT) {
      if (arrowMode || nextCmd == OS::NEXT_CMD::NEXT) {
        cmdPtr += (int)nextCmd;
      }
      if (!commands.empty()) {
        cmdPtr = cmdPtr < 0 ? cmdPtr + (int)commands.size() :
        cmdPtr % (int)commands.size();
      }
      init = commands.empty() ? script : commands[cmdPtr];
      arrowMode = true;
      continue;
    }

    init.clear();
    tabFileIndex = 0;
    arrowMode = false;

    if (script.empty()) {
      continue;
    }

    if (script.back() == Constants::NEXT_LINE) {
      script.pop_back();
      newStatement = false;
      continue;
    }
    if (commands.empty() || commands.back().compare(script)) {
      commands.push_back(script);
    }
    if (script.back() != Constants::END_STATEMENT) {
      script += Constants::END_STATEMENT;
    }

    processScript(script);
    newStatement = true;
    cmdPtr = (int)commands.size() - 1;
  }
}

void MainWindow::on_pushButton_clicked()
{    
    DataSystems::Instance().clear();
    logger::WriteLog("<<<<<<Start compilation>>>>>>>");
    logger::WriteLog_result_execution("<<<<<<Execution result>>>>>>>");
    run();
    updateLog();
}
