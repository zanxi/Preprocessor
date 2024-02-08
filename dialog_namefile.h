#ifndef DIALOG_NAMEFILE_H
#define DIALOG_NAMEFILE_H

#include <QDialog>

namespace Ui {
class Dialog_NameFile;
}

class Dialog_NameFile : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_NameFile(QWidget *parent = nullptr);
    explicit Dialog_NameFile(QString NameFile, QWidget *parent = nullptr);
    ~Dialog_NameFile();
    QString NameFile;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dialog_NameFile *ui;
};

#endif // DIALOG_NAMEFILE_H
