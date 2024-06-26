#include "pea.h"
#include "zombie.h"

// Pea 类的构造函数，初始化豌豆
Pea::Pea(int attack, bool flag)
{
    snow = flag; // 是否为冰豌豆
    atk = attack; // 攻击力
    speed = 360.0 * 33 / 1000; // 豌豆速度
}

// 返回 Pea 的边界矩形
QRectF Pea::boundingRect() const
{
    return QRectF(-12, -28, 24, 24); // 豌豆的边界矩形
}

// 绘制 Pea
void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-12, -28, 24, 24), QPixmap(snow ? ":/images/PeaSnow.png" : ":/images/Pea.png")); // 绘制豌豆图片
}

// 检查 Pea 是否与其他物品碰撞
bool Pea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15; // 判断是否与僵尸碰撞
}

// 更新 Pea 的状态
void Pea::advance(int phase)
{
    if (!phase)
        return;
    update(); // 更新豌豆
    QList<QGraphicsItem *> items = collidingItems(); // 获取碰撞的物品列表
    if (!items.isEmpty())
    {
        // 随机选择一个碰撞的僵尸，并减少其生命值
        Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[qrand() % items.size()]);
        zombie->hp -= atk; // 减少僵尸的生命值
        if (snow && zombie->speed > 0.55)
            zombie->speed /= 2; // 如果是冰豌豆，减少僵尸速度
        delete this; // 删除豌豆
        return;
    }
    setX(x() + speed); // 移动豌豆
    if (x() > 1069)
        delete this; // 如果豌豆移出屏幕，删除豌豆
}
