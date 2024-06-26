#include "potatomine.h"  // 包含头文件

PotatoMine::PotatoMine()
{
    atk = 1800;  // 攻击力
    hp = 300;    // 生命值
    time = int(15.0 * 1000 / 33);  // 触发时间
    setMovie(":/images/PotatoMine1.gif");  // 设置初始化状态的动画
}

QRectF PotatoMine::boundingRect() const
{
    // 如果状态为2，返回一个固定大小的矩形，否则调用父类的boundingRect()
    return state == 2 ? QRectF(-75, -75, 150, 150) : Plant::boundingRect();
}

void PotatoMine::advance(int phase)
{
    if (!phase)  // 如果不是更新阶段，直接返回
        return;
    update();  // 更新图形状态

    if (hp <= 0)  // 如果生命值小于等于0，销毁当前对象
        delete this;
    else if (state == 0 && ++counter >= time)  // 如果状态为0且计数器超过时间
    {
        state = 1;  // 状态变为1
        counter = 0;  // 计数器归零
        time = int(1.0 * 1000 / 33);  // 更新时间
        setMovie(":/images/PotatoMine.gif");  // 设置新的动画
    }
    else if (state == 1 && ++counter >= time)  // 如果状态为1且计数器超过时间
    {
        counter = 0;  // 计数器归零
        QList<QGraphicsItem *> items = collidingItems();  // 获取与之碰撞的所有图形项
        if (!items.isEmpty())  // 如果碰撞项不为空
        {
            state = 2;  // 状态变为2
            setMovie(":/images/PotatoMineBomb.gif");  // 设置爆炸动画
            foreach (QGraphicsItem *item, items)  // 遍历碰撞项
            {
                Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);  // 尝试转换为僵尸类对象
                zombie->hp -= atk;  // 减少僵尸的生命值
                if (zombie->hp <= 0)  // 如果僵尸生命值小于等于0
                    delete zombie;  // 销毁僵尸对象
            }
        }
    }
    else if (state == 2 && movie->currentFrameNumber() == movie->frameCount() - 1)
        delete this;  // 如果状态为2且当前帧数等于总帧数减1，销毁当前对象
}

bool PotatoMine::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);  // 不使用mode参数
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 50;
    // 如果碰撞的对象是僵尸类，并且在y轴上很接近，并且在x轴上的距离小于50，返回true
}
