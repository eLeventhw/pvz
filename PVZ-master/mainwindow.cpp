#include "mainwindow.h"
#include "QSqlDatabase"
#include "shop.h"
#include "sun.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlError> // 包含这个头文件以访问数据库错误信息
#include <QDebug>
#include "DatabaseManager.h"
#include <iostream>  // 包含输入输出库
// MainWindow 的构造函数，初始化主窗口和游戏场景
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime()))); // 初始化随机数生成器
    sound = new QSound("Grazy Dave.wav"); // 初始化音效
    sound->setLoops(QSound::Infinite); // 设置音效循环播放
    timer = new QTimer; // 初始化定时器
    scene = new QGraphicsScene(this); // 初始化场景
    scene->setSceneRect(150, 0, 900, 600); // 设置场景矩形
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // 设置不使用索引
    // 添加商店到场景中
    shop = new Shop;
    shop->setPos(520, 45);
    scene->addItem(shop);

    // 添加铲子到场景中
    Shovel *shovel = new Shovel;
    shovel->setPos(830, 40);
    scene->addItem(shovel);

    // 添加按钮到场景中
    Button *button = new Button(sound, timer);
    button->setPos(970, 20);
    scene->addItem(button);

    // 添加地图到场景中
    Map *map = new Map;
    map->setPos(618, 326);
    scene->addItem(map);

    // 添加割草机到场景中
    for (int i = 0; i < 5; ++i)
    {
        mower[i] = new Mower;
        mower[i]->setPos(210, 130 + 98 * i);
        shop->mower[i] = mower[i];
        scene->addItem(mower[i]);
    }
//    // 初始化小推车状态
//    for (int i = 0; i < 5; ++i) {
//        mowerStatus[i] = 1;
//    }

    // 初始化视图
    view = new QGraphicsView(scene, this);
    view->resize(902, 602); // 设置视图大小
    view->setRenderHint(QPainter::Antialiasing); // 设置抗锯齿
    view->setBackgroundBrush(QPixmap(":/images/Background.jpg")); // 设置背景图片
    view->setCacheMode(QGraphicsView::CacheBackground); // 设置背景缓存模式
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate); // 设置视口更新模式

    // 连接定时器信号与槽函数
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);
    connect(timer, &QTimer::timeout, this, &MainWindow::check);

    sound->play(); // 播放音效
    timer->start(33); // 启动定时器，每33毫秒触发一次
    view->show(); // 显示视图
//    qDebug() << shop->sun;
}

// MainWindow 的析构函数，清理资源
MainWindow::~MainWindow()
{
    saveSunshine();
//    CarStatus();
    saveZombie();
    saveplant();
    savepea();
//    saveSunshine();  // 添加这一行
//    CarStatus();
    qDebug() << "你好";
    delete sound;
    delete timer;
    delete scene;
    delete view;
}

// 添加僵尸到场景中
void MainWindow::addZombie()
{
//    qDebug() << shop->sun;
    static int low = 4;
    static int high = 8;
    static int maxtime = 20 * 1000 / 33;
    static int time = maxtime / 2;
    static int counter = 0;
    if (++counter >= time)
    {
        if (++low > high)
        {
            maxtime /= 1.3; // 减少最大时间间隔
            high *= 2; // 增加高值
        }
        counter = 0;
        time = qrand() % (2 * maxtime / 3) + maxtime / 3; // 重新计算时间间隔
        int type = qrand() % 100;
        int i = qrand() % 5;
        Zombie *zombie;
        if (type < 40)
            zombie = new BasicZombie; // 添加普通僵尸
        else if (type < 70)
            zombie = new ConeZombie; // 添加路障僵尸
        else if (type < 80)
            zombie = new BucketZombie; // 添加铁桶僵尸
//        else if (type < 90)
//            zombie = new ScreenZombie; // 添加门板僵尸
        else
            zombie = new FootballZombie; // 添加橄榄球僵尸
        zombie->setPos(1028, 130 + 98 * i); // 设置僵尸位置
        scene->addItem(zombie); // 将僵尸添加到场景中
    }
}

// 检查游戏状态
void MainWindow::check()
{
    for(int i=0;i<5;++i){
        mower[i]=shop->mower[i];
    }
    static int time = 1 * 1000 / 33;
    static int counter = 0;
    if (++counter >= time)
    {
        counter = 0;
        const QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items)
            if (item->type() == Zombie::Type && item->x() < 200)
            {
                scene->addPixmap(QPixmap(":/images/ZombiesWon.png"))->setPos(336, 92); // 显示僵尸获胜图片
                scene->advance(); // 更新场景
                timer->stop(); // 停止定时器
                return;
            }
    }
}
void MainWindow::remove_date(){
    QSqlQuery query(db);
    query.prepare("DELETE FROM plant_recover WHERE account = :name");
    query.bindValue(":name", username);
    query.exec();
    query.prepare("DELETE FROM zombie_recover WHERE account = :name");
    query.bindValue(":name", username);
    query.exec();
    query.prepare("DELETE FROM bullet_recover WHERE account = :name");
    query.bindValue(":name", username);
    query.exec();
}
void MainWindow::recover(){
    //阳光恢复
    QSqlDatabase db = DatabaseManager::instance().database();
    if (db.open()) {
        QSqlQuery query(db);
        query.prepare("SELECT sunshine FROM users where account = :name");
        query.bindValue(":name", username);
        if (!query.exec()) {
            qDebug()<<"ggggg";
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
        query.exec();
        query.next();
        shop->sun=query.value(0).toInt();
    }
    //车恢复
//    for (int i = 0; i < 5; ++i)
//    {
//        QSqlQuery query(db);
//        query.prepare("SELECT car:num from users where account=:name");
//        query.bindValue(":name",username);
//        query.bindValue(":num", i+1);
//        query.exec();
//        query.next();
//        qDebug()<<query.value(0);
//        if(!query.value(0).toInt()){
//            scene->removeItem(mower[i]);
//            mower[i]=nullptr;
//        }
//    }
    //僵尸恢复
    QSqlQuery query(db);
    query.prepare("SELECT x_index,y_index,name,blood from zombie_recover where account=:name");
    query.bindValue(":name",username);
    query.exec();
    while (query.next()) {
        double x=query.value(0).toDouble();
        double y=query.value(1).toDouble();
        QString name=query.value(2).toString();
        Zombie *zombie;
        int blood=query.value(3).toInt();
        if(name=="BasicZombie"){
            zombie = new BasicZombie;
        }
        if(name=="BucketheadZombie"){
            zombie=new BucketZombie;
        }
        if(name=="ConeheadZombie"){
            zombie=new ConeZombie;
        }
        if(name=="FootballZombie"){
            zombie=new FootballZombie;
        }
        if(name=="ScreenZombie"){
            zombie=new ScreenZombie;
        }
        zombie->setPos(x, y); // 设置僵尸位置
        scene->addItem(zombie); // 将僵尸添加到场景中
        zombie->hp=blood;
    }
    //植物恢复
    query.prepare("SELECT x_index,y_index,name,blood from plant_recover where account=:name");
    query.bindValue(":name",username);
    query.exec();
    qDebug()<<"recover plant";
    while (query.next()) {
        double x=query.value(0).toDouble();
        double y=query.value(1).toDouble();
        QString name=query.value(2).toString();
        Plant *plant;
        int blood=query.value(3).toInt();
        if(name=="Peashooter"){
            plant = new Peashooter;
            plant->hp=blood;
        }
        if(name=="Sunflower"){
            plant=new SunFlower;
            plant->hp=blood;
        }
        if(name=="Cherrybomb"){
            plant=new CherryBomb;
             plant->hp=blood;
        }
        if(name=="Potatomine"){
            plant=new PotatoMine;
             plant->hp=blood;
        }
        if(name=="Repeater"){
            plant=new Repeater;
             plant->hp=blood;
        }
        if(name=="Snowpea"){
            plant=new SnowPea;
             plant->hp=blood;
        }
        if(name=="Wallnut"){
            plant=new WallNut;
             plant->hp=blood;
        }
        plant->setPos(x, y); // 设置僵尸位置
        scene->addItem(plant); // 将僵尸添加到场景中
        plant->hp=blood;
    }
    //子弹恢复
    query.prepare("SELECT x_index,y_index,name from bullet_recover where account=:name");
    query.bindValue(":name",username);
    query.exec();
    qDebug()<<"recover bullet";
    while (query.next()) {
        double x=query.value(0).toDouble();
        double y=query.value(1).toDouble();
        QString name=query.value(2).toString();
        Other *shot;
//        int blood=query.value(3).toInt();
        if(name=="Pea"){
            shot = new Pea(25,0);
        }
        if(name=="Snowpea"){
            shot = new Pea(25,1);
        }
        shot->setPos(x, y); // 设置僵尸位置
        scene->addItem(shot); // 将僵尸添加到场景中
    }
}

int MainWindow::saveSunshine()
{
    int sunshine = shop->sun;  // 获取阳光数
    // 将阳光数存储到数据库中...
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("pvz");
    db.setUserName("root");
    db.setPassword("1234");

    if (!db.open()) {
        QMessageBox::critical(this, tr("Database Error"), db.lastError().text());
    }

    QSqlQuery query(db);
    query.prepare("UPDATE users SET sunshine = :sunshine WHERE account = :username");
    query.bindValue(":sunshine", sunshine);
    qDebug() << username;
    query.bindValue(":username", username);  // 使用MainWindow的username
    query.exec();
    return shop->sun;  // 获取阳光数
}
void MainWindow::CarStatus()
{
    for (int i = 0; i < 5; ++i) {
//        mowerStatus[i] = mower[i]->status;
        qDebug()<<"save car";
        if(mower[i]==nullptr){
            qDebug()<<"null";
            mowerStatus[i]=0;
            }else{
            if(mower[i]->x() <= 1069&&mower[i]->x()>210){
                mowerStatus[i]=0;
                qDebug()<<mower[i]->x();
            }else{
                mowerStatus[i]=1;
                qDebug()<<mower[i]->x();
            }
        }
    }
    QSqlQuery query(db);
    query.prepare("UPDATE users SET car1 = :status1, car2 = :status2, car3 = :status3,"
                  "car4 = :status4, car5 = :status5 WHERE account = :username");
    query.bindValue(":status1", mowerStatus[0]);
    query.bindValue(":status2", mowerStatus[1]);
    query.bindValue(":status3", mowerStatus[2]);
    query.bindValue(":status4", mowerStatus[3]);
    query.bindValue(":status5", mowerStatus[4]);
    query.bindValue(":username", username);  // 使用MainWindow的username
    query.exec();
    return;
}
void MainWindow::saveZombie(){
//    qDebug()<<"in";
//    if (scene->items().isEmpty()) {
//        qDebug() << "The scene is empty.";
//    } else {
//        qDebug() << "The scene is not empty.";
//    }
    foreach (QGraphicsItem *item, scene->items()){
//        qDebug()<<"show";
//        qDebug()<<item->type();
        if (item->type() == Zombie::Type)
        {
//            qDebug()<<"save zombie";
            QSqlQuery query(db);
            query.prepare("INSERT INTO zombie_recover (x_index, y_index, account, name , blood) VALUES (:x,:y,:acc,:name,:blood)");
            query.bindValue(":x", item->x());
            query.bindValue(":y",item->y());
            query.bindValue(":acc",username);
            BasicZombie* p = dynamic_cast<BasicZombie*>(item);
            if (p) {
//                qDebug()<<"basiczombie";
                query.bindValue(":name","BasicZombie");
                query.bindValue(":blood",p->hp);
            }
            BucketZombie* p1 = dynamic_cast<BucketZombie*>(item);
            if (p1) {
//                qDebug()<<"hucketzombie";
                query.bindValue(":name","BucketheadZombie");
                query.bindValue(":blood",p1->hp);
            }
            ConeZombie* p2 = dynamic_cast<ConeZombie*>(item);
            if (p2) {
//                qDebug()<<"conezombie";
                query.bindValue(":name","ConeheadZombie");
                query.bindValue(":blood",p2->hp);
            }
            FootballZombie* p3 = dynamic_cast<FootballZombie*>(item);
            if (p3) {
//                qDebug()<<"footballzombie";
                query.bindValue(":name","FootballZombie");
                query.bindValue(":blood",p3->hp);
            }
            ScreenZombie* p4 = dynamic_cast<ScreenZombie*>(item);
            if (p4) {
//                qDebug()<<"screenzombie";
                query.bindValue(":name","ScreenZombie");
                query.bindValue(":blood",p4->hp);
            }
//                query.bindValue(":name")
            query.exec();
        }
    }
}

void MainWindow::saveplant(){
    qDebug()<<"saver";
    foreach (QGraphicsItem *item, scene->items()){
//        qDebug()<<item->type();
        if (item->type() == Plant::Type)
        {
            qDebug()<<"save plant";
            QSqlQuery query(db);
            query.prepare("INSERT INTO plant_recover (x_index, y_index, account, name , blood) VALUES (:x,:y,:acc,:name,:blood)");
            query.bindValue(":x", item->x());
            query.bindValue(":y",item->y());
            query.bindValue(":acc",username);
            SunFlower* p = dynamic_cast<SunFlower*>(item);
            if (p) {
                query.bindValue(":name","Sunflower");
                query.bindValue(":blood",p->hp);
            }
            Peashooter* p1 = dynamic_cast<Peashooter*>(item);
            if (p1) {
                query.bindValue(":name","Peashooter");
                query.bindValue(":blood",p1->hp);
            }
            CherryBomb* p2 = dynamic_cast<CherryBomb*>(item);
            if (p2) {
                query.bindValue(":name","Cherrybomb");
                query.bindValue(":blood",p2->hp);
            }
            PotatoMine* p3 = dynamic_cast<PotatoMine*>(item);
            if (p3) {
                query.bindValue(":name","Potatomine");
                query.bindValue(":blood",p3->hp);
            }
            Repeater* p4 = dynamic_cast<Repeater*>(item);
            if (p4) {
                query.bindValue(":name","Repeater");
                query.bindValue(":blood",p4->hp);
            }
            SnowPea* p5 = dynamic_cast<SnowPea*>(item);
            if (p5) {
                query.bindValue(":name","Snowpea");
                query.bindValue(":blood",p5->hp);
            }
            WallNut* p6 = dynamic_cast<WallNut*>(item);
            if (p6) {
                query.bindValue(":name","Wallnut");
                query.bindValue(":blood",p6->hp);
            }
            bool success = query.exec();
            if (success) {
                qDebug() << "Query executed successfully.";
            } else {
                qDebug() << "Query failed: " << query.lastError().text();
            }
        }
    }
}
void MainWindow::savepea(){
    foreach (QGraphicsItem *item, scene->items()){
        if (item->type() == Other::Type)
        {
//            qDebug()<<"save bullet";
            QSqlQuery query(db);
            query.prepare("INSERT INTO bullet_recover (x_index, y_index, account, name) VALUES (:x,:y,:acc,:name)");
            query.bindValue(":x", item->x());
            query.bindValue(":y",item->y());
            query.bindValue(":acc",username);
            Pea* p = dynamic_cast<Pea*>(item);
            if (p) {
                if(p->snow){
                    query.bindValue(":name","Snowpea");
                }else{
                    query.bindValue(":name","Pea");
                }
                bool success = query.exec();
                if (success) {
                    qDebug() << "Query executed successfully.";
                } else {
                    qDebug() << "Query failed: " << query.lastError().text();
                }
            }

        }
    }
}


