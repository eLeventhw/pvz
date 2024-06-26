#include <QApplication>
#include "mainwindow.h"
#include "QSqlDatabase"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlError> // 包含这个头文件以访问数据库错误信息
#include <QDebug>
#include "loginwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
//    MainWindow w;
//    w.setFixedSize(900, 600);
//    w.setWindowTitle("植物大战僵尸");
//    w.show();
    return a.exec();
}
