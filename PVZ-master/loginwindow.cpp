#include "loginwindow.h"
#include <QFormLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "mainwindow.h"
#include <iostream>  // 包含输入输出库

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    usernameLabel(new QLabel("用户名:", this)),
    passwordLabel(new QLabel("密码:", this)),
    usernameLineEdit(new QLineEdit(this)),
    passwordLineEdit(new QLineEdit(this)),
    loginButton(new QPushButton(tr("Login"), this)),
    registerButton(new QPushButton(tr("Register"), this))
{
    // 创建一个窗口
    this->setFixedSize(800, 600);

    // 设置背景图片
    QPixmap pixmap(":/images/Login.png");
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(pixmap));
    this->setPalette(palette);

    // 设置字体
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(10);
    font.setBold(true);

    usernameLabel->setFont(font);
    passwordLabel->setFont(font);
    usernameLineEdit->setFont(font);
    passwordLineEdit->setFont(font);
    loginButton->setFont(font);
    registerButton->setFont(font);

    // 移动用户名和密码标签
    usernameLabel->move(250, 200);
    passwordLabel->move(250, 250);

    // 移动用户名和密码输入框
    usernameLineEdit->move(350, 200);
    passwordLineEdit->move(350, 250);

    // 移动登录和注册按钮
    loginButton->move(290, 300);
    registerButton->move(440, 300);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("pvz");
    db.setUserName("root");
    db.setPassword("1234");

    if (!db.open()) {
        QMessageBox::critical(this, tr("Database Error"), db.lastError().text());
    }

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterButtonClicked);  // 添加这一行
}
int LoginWindow::getAccount()
{
    qDebug()<<user;
    return usernameLineEdit->text().toInt();
}
void LoginWindow::onLoginButtonClicked()
{
    int username = usernameLineEdit->text().toInt();
    QString password = passwordLineEdit->text();
    user=username;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE account = :username AND keyword = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();

    if (query.next()) {
        mainWindow = new MainWindow;  // 创建一个新的MainWindow对象
        mainWindow->username = usernameLineEdit->text().toInt();  // 设置MainWindow的username
        mainWindow->recover();
        mainWindow->remove_date();
        mainWindow->setFixedSize(900, 600);
        mainWindow->setWindowTitle("植物大战僵尸");
        mainWindow->show();
        this->close();

    } else {
        QMessageBox::warning(this, tr("Login Failed"), tr("Invalid username or password."));
    }
}
void LoginWindow::onRegisterButtonClicked()
{
    int username = usernameLineEdit->text().toInt();
    QString password = passwordLineEdit->text();

    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE account = :username");
    query.bindValue(":username", username);
    query.exec();

    if (query.next()) {
        QMessageBox::warning(this, tr("Registration Failed"), tr("Username already exists. Please choose a different username."));
    }else if(password.size() == 0 || username == 0){
        QMessageBox::warning(this, tr("Registration Failed"), tr("You didn't input your account or password, please check it."));
    }
    else {
        query.prepare("INSERT INTO users (account, keyword, sunshine,car1,car2,car3,car4,car5) VALUES (:username, :password,200,1,1,1,1,1)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        query.exec();
        QMessageBox::information(this, tr("Registration Successful"), tr("You have successfully registered. You can now log in."));
    }
}
LoginWindow::~LoginWindow()
{
//    int sunshine = mainWindow->saveSunshine();  // 添加这一行
//    int username = mainWindow->username;
//    QSqlQuery query(db);
//    query.prepare("UPDATE users SET sunshine = :sunshine WHERE account = :username");
//    query.bindValue(":sunshine", sunshine);
//    query.bindValue(":username", username);  // 使用MainWindow的username
//    query.exec();
    delete mainWindow;
}
