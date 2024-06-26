#include "cherrybomb.h"

// CherryBomb 类的构造函数，初始化攻击力和生命值，并设置动画
CherryBomb::CherryBomb()
{
    atk = 1800; // 设置攻击力
    hp = 300; // 设置生命值
    setMovie(":/images/CherryBomb.gif"); // 设置初始动画
}

// 返回 CherryBomb 的边界矩形
QRectF CherryBomb::boundingRect() const
{
    return state ? QRectF(-150, -150, 300, 300) : Plant::boundingRect(); // 爆炸状态时扩大边界矩形
}

// 更新 CherryBomb 的状态
void CherryBomb::advance(int phase)
{
    if (!phase)
        return;
    update(); // 更新 CherryBomb
    if (hp <= 0)
    {
        delete this; // 如果生命值小于等于 0，删除 CherryBomb
    }
    else if (state == 0 && movie->currentFrameNumber() == movie->frameCount() - 1)
    {
        state = 1; // 切换到爆炸状态
        setMovie(":/images/Boom.gif"); // 设置爆炸动画
        QList<QGraphicsItem *> items = collidingItems(); // 获取碰撞的物品列表
        foreach (QGraphicsItem *item, items)
        {
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item); // 将物品转换为 Zombie
            zombie->hp -= atk; // 减少 Zombie 的生命值
            if (zombie->hp <= 0)
            {
                zombie->state = 3; // 将 Zombie 的状态设置为死亡
                zombie->setMovie(":/images/Burn.gif"); // 设置 Zombie 的死亡动画
            }
        }
    }
    else if (state == 1 && movie->currentFrameNumber() == movie->frameCount() - 1)
    {
        delete this; // 如果爆炸动画结束，删除 CherryBomb
    }
}

// 检查 CherryBomb 是否与其他物品碰撞
bool CherryBomb::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && QLineF(pos(), other->pos()).length() < 160; // 碰撞检测，距离小于 160 时视为碰撞
}
