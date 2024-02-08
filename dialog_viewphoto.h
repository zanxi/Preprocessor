#ifndef DIALOG_VIEWPHOTO_H
#define DIALOG_VIEWPHOTO_H

#include <QDialog>

namespace Ui {
class Dialog_ViewPhoto;
}

class Dialog_ViewPhoto : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ViewPhoto(QString fileNamePicture, QWidget *parent = nullptr);
    explicit Dialog_ViewPhoto(QByteArray ba, QWidget *parent = nullptr);
    ~Dialog_ViewPhoto();

    void PhotoView(QString fileNamePicture);
    void PhotoView(QByteArray ba);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent * event);


public slots:
     void CloseDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_ViewPhoto *ui;

    QTimer *mTimer;
};

#endif // DIALOG_VIEWPHOTO_H
