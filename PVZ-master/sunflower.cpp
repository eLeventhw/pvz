#include "sunflower.h"  // 包含头文件
#include <QDebug>  // 包含调试头文件
#include "DatabaseManager.h"
#include <QSqlQuery>
SunFlower::SunFlower()
{
    QSqlDatabase db = DatabaseManager::instance().database();
    if (db.open()) {
                qDebug() << "y";
                QSqlQuery query(db);
                query.exec("SELECT blood FROM plant where name=\"Sunflower\"");
                query.next();
                hp = query.value(0).toInt();
                qDebug() << "flower hp:" <<  hp ;
            }
            else {
                qDebug() << "gg";
            }
//    hp = 300;  // 设置生命值
    time = int(10.0 * 1000 / 33);  // 设置生成阳光的时间间隔
    setMovie(":/images/SunFlower.gif");  // 设置动画
}

void SunFlower::advance(int phase)
{
    if (!phase)  // 如果不是更新阶段，直接返回
        return;
    update();  // 更新图形状态

    if (hp <= 0)  // 如果生命值小于等于0，销毁当前对象
        delete this;
    else if (++counter >= time)  // 每过time时间间隔，执行一次
    {
        counter = 0;  // 计数器归零
        scene()->addItem(new Sun(pos()));  // 在当前向日葵的位置生成一个新的阳光对象
    }
}
