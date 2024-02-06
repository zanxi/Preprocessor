#include "mainwindow.h"
#include <QApplication>

#include <QApplication>
#include <QtCore/QTextCodec>
#include <QFile>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    //***************** Установка шрифта ****************************//

//    QTranslator qtTranslator;
//    qtTranslator.load("qt_" + QLocale::system().name(),
//                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
//    a.installTranslator(&qtTranslator);

//    QTranslator myappTranslator;
//    myappTranslator.load("VIM_" + QLocale::system().name());
//    a.installTranslator(&myappTranslator);

//    //***************** END Установка шрифта ****************************//



    MainWindow w;
    w.show();

    return a.exec();
}
