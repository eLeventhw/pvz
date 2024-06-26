#include "peashooter.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
// Peashooter 类的构造函数，初始化豌豆射手
Peashooter::Peashooter()
{

    atk = 25; // 攻击力
    hp = 300; // 生命值
    time = int(1.4 * 1000 / 33); // 攻击间隔时间
    setMovie(":/images/Peashooter.gif"); // 设置动画
}

// 更新 Peashooter 的状态
void Peashooter::advance(int phase)
{
    if (!phase)
        return;
    update(); // 更新豌豆射手
    if (hp <= 0) // 如果生命值小于等于 0，删除豌豆射手
        delete this;
    else if (++counter >= time) // 计时器增加，如果达到攻击间隔时间
    {
        counter = 0; // 重置计时器
        if (!collidingItems().isEmpty()) // 如果有碰撞的物品
        {
            Pea *pea = new Pea(atk); // 创建一个新的豌豆
            pea->setX(x() + 32); // 设置豌豆的 X 坐标
            pea->setY(y()); // 设置豌豆的 Y 坐标
            scene()->addItem(pea); // 将豌豆添加到场景中
            return;
        }
    }
}

// 检查 Peashooter 是否与其他物品碰撞
bool Peashooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()); // 判断是否与僵尸碰撞
}
