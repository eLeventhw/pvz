#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSound>
#include <QTimer>
#include "shop.h"
#include "card.h"
#include "shovel.h"
#include "button.h"
#include "map.h"
#include "mower.h"
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"
#include <QSqlDatabase>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void remove_date();
    void addZombie();
    void saveplant();
    void savepea();
    void recover();
    void saveZombie();
    void check();
    int saveSunshine();  // 添加这一行
    void CarStatus();
    int username;  // 添加这一行
    int mowerStatus[5];  // 添加这一行
    Mower *mower[5];
    QSqlDatabase db;
//    Mower *mower[5];
    void start();
private:
    QSound *sound;
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsView *view;
    Shop *shop;  // 添加这一行
};

#endif // MAINWINDOW_H
