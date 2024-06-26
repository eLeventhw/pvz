#include "giftbox.h"
#include <QPainter>
#include <QDebug>
#include "peashooter.h"
#include "sunflower.h"
#include "wallnut.h"
#include "snowpea.h"
#include "potatomine.h"
#include "repeater.h"
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"
#include "mower.h"
#include "GiftBoxBetter.h"
#include "cherrybomb.h"
GiftBoxBetter::GiftBoxBetter()
{
    // 初始化礼物盒子的属性，如动画、攻击力、计数器、状态、时间等
    setMovie(":/images/GiftBoxBetter.gif");
    time = int(10*100 / 33);
}
void GiftBoxBetter::advance(int phase)//到时间更新
{
    if (!phase)
        return;
    update(); // 更新盒子
//    delete this;
    if (++counter >= time) // 计时器增加
        {
            counter = 0; // 重置计时器
            QPointF position = pos; // 保存位置
            QGraphicsScene *scenePtr = scene(); // 保存场景指针
            int boxstatus = status;
            qDebug()<< "boxstatus :"<< boxstatus;
            delete this; // 删除对象
            GiftBoxBetterr(position,scenePtr);
        }
}
void GiftBoxBetter::GiftBoxBetterr(QPointF position,QGraphicsScene *scenePtr){
    int randomNum = qrand() % 7;
    switch (randomNum)
    {
        case 0:{
            Peashooter *ps = new Peashooter;
            ps->setPos(position);
            scenePtr->addItem(ps);
            break;
        }
        case 1:{
            SunFlower *sf = new SunFlower;
            sf->setPos(position);
            scenePtr->addItem(sf);
            break;
        }
        case 2:{
            WallNut *wn = new WallNut;
            wn->setPos(position);
            scenePtr->addItem(wn);
            break;
        }
        case 3:{
            Repeater *sf = new Repeater;
            sf->setPos(position);
            scenePtr->addItem(sf);
            break;
        }
        case 4:{
            SnowPea *sf = new SnowPea;
            sf->setPos(position);
            scenePtr->addItem(sf);
            break;
        }
        case 5:{
            CherryBomb *wn = new CherryBomb;
            wn->setPos(position);
            scenePtr->addItem(wn);
            break;
        }
        case 6:{
            CherryBomb *wn = new CherryBomb;
            wn->setPos(position);
            scenePtr->addItem(wn);
            break;
        }
    }
}
