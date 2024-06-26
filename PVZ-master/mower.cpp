#include "mower.h"

// Mower 类的构造函数，初始化割草机
Mower::Mower()
{
    flag = false; // 割草机启动标志
    speed = 270.0 * 33 / 1000; // 割草机速度
    status = 1; //非特殊移动
    final=1;
}

// 返回 Mower 的边界矩形
QRectF Mower::boundingRect() const
{
    return QRectF(-30, -30, 60, 60); // 割草机的边界矩形
}

// 绘制 Mower
void Mower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-30, -30, 60, 60), QPixmap(":/images/Mower.png")); // 绘制割草机图片
}

// 检查 Mower 是否与其他物品碰撞
bool Mower::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15; // 判断是否与僵尸碰撞
}

// 更新 Mower 的状态
void Mower::advance(int phase)
{
    if (!phase)
        return;
    update(); // 更新割草机
    QList<QGraphicsItem *> items = collidingItems(); // 获取碰撞的物品列表
    if (!items.empty() || status == 2)
    {
        flag = true; // 设置割草机启动标志
        foreach (QGraphicsItem *item, items)
        {
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item); // 将物品转换为 Zombie
            zombie->hp = 0; // 将僵尸的生命值设为 0
        }
    }
    if (flag)
        setX(x() + speed); // 如果启动标志为真，移动割草机
    if (x() > 1069)
        delete this; // 如果割草机移出屏幕，删除割草机
}
