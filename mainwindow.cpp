#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QObject>
#include <QFileDialog>
#include <QRgb>

#include "Debug/logger.h"
#include "csv/csvfile.h"
#include "dataanimals.h"
#include "dialog_viewphoto.h"
#include "dialog_namefile.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DataSystems::Instance().clear();
    logger::ClearLog();

    //***************** Установка белого цвета приложения и размеров ****************************//
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::gray);
    //pal.setColor(QPalette::Window, QRgb(89, 153, 181));
    //this->setPalette(pal);
    //setStyleSheet("background-color:"+DataSystems::Instance().settings___color_header+";");
    setGeometry(QRect(200, 100, 1600, 800));
    //***************** End Установка белого цвета приложения и размеров ****************************//

    //setStyleSheet("background-color:"+DataSystems::Instance().settings___color_header+";");






    //this->maximumSize();
    //run();
    //script = "a=357/113;c=a;";

    setWindowTitle("Preprocessor cscs");

    //ui->textEdit_code->setStyleSheet("background-color: rgb(197, 249, 136)");


    highlighter_code = new Highlighter(ui->textEdit_code->document());
    //highlighter_execution = new Highlighter(ui->textEdit_execution->document());
    //highlighter_log = new Highlighter(ui->textEdit_log->document());

    searchHighLight_execution = new SearchHighLight(ui->textEdit_execution->document());
    searchHighLight_log = new SearchHighLight(ui->textEdit_log->document());



    ThisStyle(DataSystems::Instance().settings___color_header);

    ui->textEdit_code->setText(
                "a=357/113;"
                "\ni = 0;"
                      "\nwhile (++i < 3) {"
                                     "\nj=i+1; "
                                     "\nprint(3245);"
                                 "\n}");
                                //"print(a);");
                //"\nc=a;"); //QString::fromStdString(script));

    OpenFileScript(DataSystems::Instance().savePath+"/"+"script_cscs_13-02-2024 10-58-29.58S_.txt");

    //ui->textEdit_code->append("print(\"******************** #SetSyle ****************\");");
    //ui->textEdit_code->append("setstyle(\"#2222FF\");");
//    ui->textEdit_code->append("setstyle(\"#2222FF\", \"(208, 255, 208)\");");
//    ui->textEdit_code->append("setstyle(\"#2222FF\", \"(57, 58, 5)\");");
//    ui->textEdit_code->append("setstyle(\"#2222FF\", \"(17, 39, 47)\");");
//    ui->textEdit_code->append("setstyle(\"#2222FF\", \"(37, 32, 27)\");");
//    ui->textEdit_code->append("setstyle(\"#2222FF\", \"(192,192, 192)\");");

//    ui->textEdit_code->append("setstyle(\"#2222FF\", \"(0, 128, 192)\");");
//    ui->textEdit_code->append("setstyle(\"#2222FF\", \"(208, 255, 208)\");");
    //    ui->textEdit_code->append("setstyle(\"#2222FF\", \"(208, 255, 208)\");");
        //ui->textEdit_code->append("setstyle(\"#2222FF\", \"(81, 134, 129)\");");


    on_pushButton_clicked();

    logTimer = new QTimer(this);
    connect(logTimer, SIGNAL(timeout()),this,SLOT(updateLog()));
    logTimer->start(1000);

    connect(ui->actionOpen_2 , SIGNAL(triggered()), SLOT(OpenFileScript()));

    update_ImageLoad();

}

void MainWindow::ThisStyle(QString color_h)
{

    setStyleSheet(QString()+"background-color:"+"white"+";");
    ui->textEdit_code->setStyleSheet("background-color: rgb" + DataSystems::Instance().settings___color_header_textedit_code);
    ui->textEdit_execution->setStyleSheet("background-color: rgb" + DataSystems::Instance().settings___color_header_textedit_code);
    ui->textEdit_log->setStyleSheet("background-color: rgb"+DataSystems::Instance().settings___color_header_textedit_code);

    ui->textEdit_code->setForegroundRole(QPalette::ColorRole::Window); //Foreground(QColor("#b973ff"));
    ui->textEdit_code->setTextColor( QColor( "white" ) );
    ui->textEdit_execution->setForegroundRole(QPalette::ColorRole::Window); //Foreground(QColor("#b973ff"));
    ui->textEdit_execution->setTextColor( QColor( "white" ) );
    ui->textEdit_log->setForegroundRole(QPalette::ColorRole::Window); //Foreground(QColor("#b973ff"));
    ui->textEdit_log->setTextColor( QColor( "white" ) );
    //ui->textEdit->setTextColor( QColor( "red" ) );


    QList<QPushButton*> allButton = findChildren<QPushButton*>();
    for(int i=0;i<allButton.size();i++)
    {
        allButton[i]->setStyleSheet(
            "background-color:"+color_h+";"
                                                                                    "color: white;"
                                                                                    "padding: 4 50 4 10;");
    }

    QList<QGroupBox*> allGroup = findChildren<QGroupBox*>();
    for(int i=0;i<allGroup.size();i++)
    {
        allGroup[i]->setStyleSheet(
            "QGroupBox {"
            "background-color: white;"
            "}"
            "QGroupBox::title {"
            "color: white;"
            "background-color:"+color_h+";"
                                                                "padding: 4 20000 4 10;"
                                                                "}"
            );
    }

}

void MainWindow::update_ImageLoad()
{
    QString folder = DataSystems::Instance().savePath + "/";
    //folder = "d:/img2/";

    std::vector<std::string> vec = csvfile::ReadFiles(folder.toStdString().c_str());
    ui->comboBox_scripts->clear();
    for(int k=0; k<vec.size();k++)
    {
        if(QString::fromStdString(vec[k]).toLower().contains("txt"))
        {
            //logger::WriteLog(folder + QString::fromStdString(vec[k]));
            ui->comboBox_scripts->addItem(folder + QString::fromStdString(vec[k]));
        }
    }
}

void MainWindow::Addshow()
{
    //OutputLog(QString::number(row));

    QString fileNamePicture = DataSystems::Instance().savePath + "/" + "mylene_farmer.jpg";
    //fileNamePicture = "https://demotivatorium.ru/sstorage/3/2014/09/13001529222202/demotivatorium_ru_a_chto_eto_vi_tut_delaete_a_58272.jpg";
    Dialog_ViewPhoto dvf2(fileNamePicture, this);

    if(!(dvf2.exec()==QDialog::Accepted))
    {
        //QMessageBox::information(this,"Спасибо","Сухостойность");
    }

    return;

    logger::WriteMsg("Add action");
    if(DataSystems::Instance().robot_paramfile1==nullptr)return;
    Dialog_ViewPhoto dvf(DataSystems::Instance().robot_paramfile1);
    if(!(dvf.exec()==QDialog::Accepted))
    {
        //QMessageBox::information(this,"Спасибо","Сухостойность");
    }
}



void MainWindow::updateLog()
{

    ThisStyle(DataSystems::Instance().settings___color_header);

    if(DataSystems::Instance().log__lists.size()==0 && DataSystems::Instance().log_execution_result__lists.size()==0)return;

    //ui->textEdit_log->clear();
    if(DataSystems::Instance().log__lists.size()!=0)logger::WriteMsg("Log actions");
    for(const QString str_val: DataSystems::Instance().log__lists)
    {
        ui->textEdit_log->append(str_val);
        logger::WriteMsg(str_val.toStdString());
    }
    DataSystems::Instance().log__lists.clear();

    //ui->textEdit_execution->clear();
    if(DataSystems::Instance().log_execution_result__lists.size()!=0)logger::WriteMsg("Log compilation & executions");
    for(const QString str_val: DataSystems::Instance().log_execution_result__lists)
    {
        ui->textEdit_execution->append(str_val);
        logger::WriteMsg(str_val.toStdString());
    }
    DataSystems::Instance().log_execution_result__lists.clear();

   QTextCursor cursor_log = ui->textEdit_log->textCursor();
   cursor_log.movePosition(QTextCursor::End);
   ui->textEdit_log->setTextCursor(cursor_log);

   QTextCursor cursor_execution = ui->textEdit_execution->textCursor();
   cursor_execution.movePosition(QTextCursor::End);
   ui->textEdit_execution->setTextCursor(cursor_execution);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Enter) {
        qDebug() << ("keyPressEvent: Enter received");
    }
    else if (keyEvent->key() == Qt::Key_A)
    {
        qDebug() << ("keyPressEvent: A received");
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Enter) {
        qDebug() << ("keyReleaseEvent: Enter received");
    }
    else if (keyEvent->key() == Qt::Key_A)
    {
        qDebug() << ("keyReleaseEvent: A received");
    }
    else if (keyEvent->key() == Qt::Key_Escape)
    {
        qDebug() << ("keyReleaseEvent: Escape received");
        QMessageBox::information(this,"Спасибо","Вы вышли из программы");
        QApplication::closeAllWindows();
        QApplication::quit();
    }
}


void MainWindow::OpenFileScript()
{

    //QString fileName = QFileDialog::getOpenFileName(this,  tr("Open Directory"), DataSystems::Instance().savePath, filter=audioFormats);
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Scripts (*.h *.txt *.cpp)"));
    dialog.setDirectory(DataSystems::Instance().savePath);
    dialog.setViewMode(QFileDialog::Detail);

    QString fileScript = dialog.getOpenFileName();
    if(fileScript.isEmpty())
    {
        logger::WriteLog("No file name ");
        QMessageBox::information(this,"файл не выбран","Повторите операцию");
        return;
    }
    logger::WriteLog("File script: [" + fileScript + "]");
    //updateLog();

    QFile *localFile = new QFile(fileScript);
    localFile->open(QFile::ReadOnly);
    QTextStream in(localFile);
    ui->textEdit_code->setText(in.readAll());
    localFile->close();


}

void MainWindow::OpenFileScript(QString fileScript)
{
    logger::WriteLog("File script: [" + fileScript + "]");
    //updateLog();

    QFileInfo f_info(fileScript);
    if(fileScript.isEmpty())
    {
        logger::WriteLog("No file name ");
        return;
    }
    if(!f_info.exists())
    {
        logger::WriteLog("File not exists: "+fileScript);
        return;
    }

    QFile *localFile = new QFile(fileScript);
    localFile->open(QFile::ReadOnly);
    QTextStream in(localFile);
    ui->textEdit_code->setText(in.readAll());
    localFile->close();
}


void MainWindow::run()
{
    on_pushButton_clear_log_exec_clicked();

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

        ui->textEdit_code->update();
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
    //updateLog();
}

void MainWindow::on_pushButton_open_script_clicked()
{
    OpenFileScript();
}


void MainWindow::on_pushButton_savescript_clicked()
{    
    ui->textEdit_code->update();
    QString NameFile = QString("script_cscs") + QString::fromStdString(logger::CreateLogName2());
    //fileNamePicture = "https://demotivatorium.ru/sstorage/3/2014/09/13001529222202/demotivatorium_ru_a_chto_eto_vi_tut_delaete_a_58272.jpg";
    Dialog_NameFile dvf(NameFile, this);

    if(!(dvf.exec()==QDialog::Accepted))
    {
        //QMessageBox::information(this,"Спасибо","Сухостойность");

    NameFile = dvf.NameFile;

    QString fileScript = DataSystems::Instance().savePath+"/"+ NameFile+".txt";
    QFile *localFile = new QFile(fileScript);
    localFile->open(QFile::WriteOnly);
    QTextStream out(localFile);
    out<<ui->textEdit_code->toPlainText();
    localFile->close();

    QMessageBox::information(this,"Скрипт сохранен в файл",fileScript);
    logger::WriteLog("Скрипт сохранен в файл"+fileScript);

    update_ImageLoad();
    //updateLog();

        //return;
    }




}


void MainWindow::on_pushButton_exe_search_clicked()
{
    searchHighLight_execution->searchText(ui->lineEdit_execution_search->text().toLower());

    QTextCursor cursor=ui->textEdit_execution->textCursor();
    cursor.setPosition(cursor.position());
    cursor.setPosition(cursor.position()+ui->lineEdit_execution_search->text().toLower().size(),QTextCursor::KeepAnchor);
    QTextCharFormat charFormat = cursor.charFormat();
    charFormat.setBackground(QColor(150, 200, 250));
    cursor.setCharFormat(charFormat);
    ui->textEdit_execution->setTextCursor(cursor);


//    QTextCursor cursor_execution = ui->textEdit_execution->textCursor();
//    cursor_execution.movePosition(QTextCursor::End);
//    ui->textEdit_execution->setTextCursor(cursor_execution);
//    ui->textEdit_execution->selectAll();

    //logger::WriteLog(ui->lineEdit_execution_search->text().toLower());
    //updateLog();
}


void MainWindow::on_pushButton_log_search_clicked()
{
    searchHighLight_log->searchText(ui->lineEdit_log_search->text().toLower());

    return;


    //QTextEdit *aEdit = activeEdit();
    QString select = ui->textEdit_log->textCursor().selectedText();
    int sEnd = ui->textEdit_log->textCursor().selectionEnd();

    QTextCursor tx = ui->textEdit_log->textCursor();
    tx.setPosition(sEnd);
    ui->textEdit_log->setTextCursor(tx);

    if(ui->textEdit_log->find(select, QTextDocument::FindBackward))
    {
    ui->textEdit_log->setTextBackgroundColor(Qt::yellow);
    }


    return;

    ui->textEdit_log->moveCursor(QTextCursor::End);
    if(ui->textEdit_log->find(ui->lineEdit_log_search->text().toLower(), QTextDocument::FindBackward))
        ui->textEdit_log->setTextBackgroundColor(Qt::yellow);
    ui->textEdit_log->moveCursor(QTextCursor::End);

    return;

    //поиск строки по времени
    QTextCursor cur = ui->textEdit_log->document()->find(ui->lineEdit_log_search->text());
    ui->textEdit_log->setTextCursor(cur);
    int numLine = cur.blockNumber();

    int line = ui->textEdit_log->document()->find(ui->lineEdit_log_search->text(), numLine, QTextDocument::FindBackward).blockNumber();

    if (line > 0){
    QString str = ui->textEdit_log->document()->findBlockByLineNumber(line).text();

    int k = str.indexOf(ui->lineEdit_log_search->text());
    if (k!=-1){
      int ii = str.indexOf(QRegExp("[0-9]"),0);
      str.remove(0,ii);
      ui->textEdit_log->setText(str);
    }
    }

//    QTextCursor cursor=ui->textEdit_log->textCursor();
//    cursor.setPosition(cursor.position());
//    cursor.setPosition(cursor.position()+ui->lineEdit_log_search->text().toLower().size(),QTextCursor::KeepAnchor);
//    QTextCharFormat charFormat = cursor.charFormat();
//    charFormat.setBackground(QColor(150, 200, 250));
//    cursor.setCharFormat(charFormat);
//    ui->textEdit_log->setTextCursor(cursor);

    //highlighter_log->searchText(ui->lineEdit_log_search->text().toLower());
    //logger::WriteLog(ui->lineEdit_log_search->text().toLower());
    //updateLog();
}


void MainWindow::on_lineEdit_log_search_cursorPositionChanged(int arg1, int arg2)
{
    on_lineEdit_log_search_cursorPosition_arg1 = arg1;
    on_lineEdit_log_search_cursorPosition_arg2 = arg2;

}


void MainWindow::on_lineEdit_execution_search_cursorPositionChanged(int arg1, int arg2)
{
    on_lineEdit_execution_search_cursorPosition_arg1 = arg1;
    on_lineEdit_execution_search_cursorPosition_arg2 = arg2;


}


void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit_log->clear();
    ui->textEdit_execution->clear();

}


void MainWindow::on_pushButton_clear_log_exec_clicked()
{
    ui->textEdit_log->clear();
    ui->textEdit_execution->clear();
}


void MainWindow::on_comboBox_scripts_activated(int index)
{
    OpenFileScript(ui->comboBox_scripts->currentText());
}

