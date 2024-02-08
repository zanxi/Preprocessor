#include "dialog_namefile.h"
#include "ui_dialog_namefile.h"

#include "dataanimals.h"

Dialog_NameFile::Dialog_NameFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_NameFile)
{
    ui->setupUi(this);
}

Dialog_NameFile::Dialog_NameFile(QString namFile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_NameFile)
{
    ui->setupUi(this);

    //***************** Установка белого цвета приложения и размеров ****************************//
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::white);
    //pal.setColor(QPalette::Window, QRgb(89, 153, 181));
    this->setPalette(pal);
    //setStyleSheet("background-color:"+DataSystems::Instance().settings___color_header+";");
    setGeometry(QRect(200, 100, 1600, 800));
    //***************** End Установка белого цвета приложения и размеров ****************************//

    ui->groupBox->setStyleSheet("QGroupBox {"
                                "background-color: white;"
                                "}"
                                "QGroupBox::title {"
                                "color: white;"
                                "background-color:"+DataSystems::Instance().settings___color_header_dialog+";"
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

    ui->lineEdit->setText(namFile);

}

Dialog_NameFile::~Dialog_NameFile()
{
    delete ui;
}

void Dialog_NameFile::on_pushButton_2_clicked()
{
    ui->lineEdit->update();
    NameFile=ui->lineEdit->text();
    this->close();
}


void Dialog_NameFile::on_pushButton_clicked()
{
    ui->lineEdit->update();
    NameFile=ui->lineEdit->text();
    this->close();
}

