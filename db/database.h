#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

#include <iostream>
#include <map>
#include <vector>
#include <list>


#include "../utils/UtilsT.h"

#define DB_NAME   "vim2"

class DataBase : public QObject
{
    Q_OBJECT    
public:
    //DataBase(QObject *parent = 0, QString connectionname = "vim3");
    DataBase(QObject *parent = 0);

    bool inserIntoTableSqlScript(QString table);          // публичный метод - вставить в таблицу
    void FillValue();
    bool inserIntoTable2(QString table, const QList<QString>  clumns, const QVariantList &data);          // публичный метод - вставить в таблицу

    ~DataBase();
    void createTables();                  //   создать таблицу
    bool Open();
    bool isOpen();
    bool CreateDataBase(QString table);
    void DropTables();
    void UpdateTables();
    void UpdateTable(QString file_sql);
    void DropTable(QString table);
    void DropDataBase(QString nameDB);
    void UseDataBase(QString nameDB);
    bool StatusOpen(){ return db_open; };
    QString GetLog();
    void WriteLog(QString msg);

    QSqlDatabase   db;                         // Сам объект базы данных
    bool sql_exec(QString nameDB, QString comment="");
    bool sql_exec(QString sql_script, QByteArray var1_qba, QByteArray var2_qba, QString comment);
    bool sql_prepare_exec(QString sql_script, QString vart1, QByteArray var1_qba, QString comment);
    bool sql_prepare_exec(QString sql_script, QByteArray var1_qba, QByteArray var2_qba, QString vart1, QString vart2,  QString comment);
    bool sql_prepare_exec(QString sql_script, QByteArray var1_qba, QByteArray var2_qba, QString vart1, QString vart2, QString vart3, QString vart4,  QString comment);
    bool sql_prepare_exec(QString sql_script, QByteArray var1_qba, QByteArray var2_qba,  QString robot_no,  QString coord_teat_lf, QString coord_teat_lr, QString coord_teat_rf, QString coord_teat_rr, QString param1, QString param2, QString param3, QString param4, QString paramtime1, QString paramtime2, QString paramtime3, QString paramtime4,  QString comment);
    bool sql_prepare_exec(QString sql_script, QByteArray var1_qba, QByteArray var2_qba, QString comment);

    bool sql_prepare_exec_update(QString sql_script, QByteArray var1_qba, QByteArray var2_qba, QString id,  QString comment);

    QSqlQuery* sql_exec2(QString nameDB, QString comment="");
    QSqlQuery* sql_exec_insert_bytea(QString sql_script, QByteArray by, QString comment);

    QString insert_add(QString tab, QString variable, QString val);
    QString insert_add_question(QString tab, QString var_type_add);
    QString update_add(QString tab, QString parameterId, QString valueId, QString variable, QString val);
    QString update_add(QString tab, QString parameterId, int valueId, QString variable, QString val);

    //std::string sql_insert;
    //std::string sql_update;


private:
    //QSqlDatabase   db;                         // Сам объект базы данных


    bool db_open = false;    
    void DropDB(QString nameDB);
    //bool sql_exec(QString nameDB, QString comment="");

    QString log="";
    QString connection_name="";

    std::string tab_fn;
    std::vector<std::string> columns_Name_insert_temp;
    std::vector<std::string> columns_value_insert_temp;


    //std::vector<key_value_t> columns_value_update;
    std::vector<std::string> columns_Name_update_temp;
    std::vector<std::string> columns_value_update_temp;


};

#endif   // DATABASE_H
