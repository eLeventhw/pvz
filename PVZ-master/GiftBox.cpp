#include "giftbox.h"
#include <QPainter>
#include <QDebug>
#include "peashooter.h"
#include "sunflower.h"
#include "wallnut.h"
#include "snowpea.h"
#include "GiftBox.h"
#include "potatomine.h"
#include "repeater.h"
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"
#include "cherrybomb.h"
#include "mower.h"
// GiftBox 类的构造函数，初始化礼物盒子
GiftBox::GiftBox()
{
    // 初始化礼物盒子的属性，如动画、攻击力、计数器、状态、时间等
    setMovie(":/images/GiftBoxSimple.gif");  // 设置动画
    time = int(10*100 / 33);
}
void GiftBox::advance(int phase)//到时间更新
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
            GiftBoxSimple(position,scenePtr);
        }
}
void GiftBox::GiftBoxSimple(QPointF position,QGraphicsScene *scenePtr){
    int randomNum = qrand() % 12;

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
            BasicZombie *wn = new BasicZombie;
            wn->setPos(position);
            scenePtr->addItem(wn);
            break;
        }
        case 6:{
            ConeZombie *wn = new ConeZombie;
            wn->setPos(position);
            scenePtr->addItem(wn);
            break;
        }
        case 7:{
            BucketZombie *wn = new BucketZombie;
            wn->setPos(position);
            scenePtr->addItem(wn);
            break;
        }
        case 8:{
            ScreenZombie *wn = new ScreenZombie;
            wn->setPos(position);
            scenePtr->addItem(wn);
            break;
        }
        case 9:{
            FootballZombie *wn = new FootballZombie;
            wn->setPos(position);
            scenePtr->addItem(wn);
            break;
        }
        case 10:{
            CherryBomb *wn = new CherryBomb;
            wn->setPos(position);
            scenePtr->addItem(wn);
            break;
        }
        case 11:{
            CherryBomb *wn = new CherryBomb;
            wn->setPos(position);
            scenePtr->addItem(wn);
            break;
        }
    }
}
//void GiftBox::GiftBoxBetter(QPointF position,QGraphicsScene *scenePtr){
//    int randomNum = qrand() % 6;
//    switch (randomNum)
//    {
//        case 0:{
//            Peashooter *ps = new Peashooter;
//            ps->setPos(position);
//            scenePtr->addItem(ps);
//            break;
//        }
//        case 1:{
//            SunFlower *sf = new SunFlower;
//            sf->setPos(position);
//            scenePtr->addItem(sf);
//            break;
//        }
//        case 2:{
//            WallNut *wn = new WallNut;
//            wn->setPos(position);
//            scenePtr->addItem(wn);
//            break;
//        }
//        case 3:{
//            Repeater *sf = new Repeater;
//            sf->setPos(position);
//            scenePtr->addItem(sf);
//            break;
//        }
//        case 4:{
//            SnowPea *sf = new SnowPea;
//            sf->setPos(position);
//            scenePtr->addItem(sf);
//            break;
//        }
//        case 5:{
//            Mower *wn = new Mower;
//            wn->setX(position.x() - 10);
//            wn->setY(position.y());
//            scenePtr->addItem(wn);
//            break;
//        }
//    }
//}
//                case 3:{
//                    PotatoMine *sf = new PotatoMine;
//                    sf->setPos(position);
//                    scenePtr->addItem(sf);
//                    break;
//                }
//                case 4:{
//                    Repeater *sf = new Repeater;
//                    sf->setPos(position);
//                    scenePtr->addItem(sf);
//                    break;
//                }
//                case 5:{
//                    SnowPea *sf = new SnowPea;
//                    sf->setPos(position);
//                    scenePtr->addItem(sf);
//                    break;
//                }
//            }
//            if (!collidingItems().isEmpty()) // 如果有碰撞的物品
//            {
//                Pea *pea = new Pea(atk); // 创建一个新的豌豆
//                pea->setX(x() + 32); // 设置豌豆的 X 坐标
//                pea->setY(y()); // 设置豌豆的 Y 坐标
//                scene()->addItem(pea); // 将豌豆添加到场景中
//                return;
//            }
//            delete this;
//            qDebug() << "x:" << pos.x() << ", y:" << pos.y();
//            Peashooter * ps = new Peashooter;
//            ps->setPos(pos);
//            scene()->addItem(ps);
