#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include "mainwindow.h"

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    int getAccount();

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();  // 添加这一行
private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;  // 添加这一行
    QSqlDatabase db;
    MainWindow *mainWindow;
    QWidget window;
    QGraphicsScene *scene;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    int user;

};

#endif // LOGINWINDOW_H
