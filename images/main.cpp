#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splashScreen=new QSplashScreen();
    splashScreen->setPixmap(QPixmap(":/Images/splashImage.png"));
    splashScreen->show();
    MainWindow w;
    QTimer::singleShot(3500,splashScreen,SLOT(close()));
    QTimer::singleShot(3500,&w,SLOT(show()));
    //w.show();
    return a.exec();
}
