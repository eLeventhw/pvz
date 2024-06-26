#include "Ice.h"
#include <QPainter>
#include <QDebug>
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"
// GiftBox 类的构造函数，初始化礼物盒子
Ice::Ice()
{
    // 初始化礼物盒子的属性，如动画、攻击力、计数器、状态、时间等
    setMovie(":/images/GiftBoxSimple.gif");  // 设置动画
    time = int(10*100 / 33);
}
void Ice::advance(int phase)//到时间更新
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
            delete this; // 删除对象
            IceSimple(position,scenePtr);
        }
}
void Ice::IceSimple(QPointF position,QGraphicsScene *scenePtr){
      foreach (QGraphicsItem *item, scenePtr->items()){
          if (item->type() == Zombie::Type){
              Zombie* p = dynamic_cast<Zombie*>(item);
              if(p->speed > 0.55)
                p->speed=p->speed/2;
          }
      }
}
