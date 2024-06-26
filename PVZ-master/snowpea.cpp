#include "snowpea.h"  // 包含头文件

SnowPea::SnowPea()
{
    atk = 25;  // 攻击力
    hp = 300;  // 生命值
    time = int(1.4 * 1000 / 33);  // 触发时间
    setMovie(":/images/SnowPea.gif");  // 设置动画
}

void SnowPea::advance(int phase)
{
    if (!phase)  // 如果不是更新阶段，直接返回
        return;
    update();  // 更新图形状态

    if (hp <= 0)  // 如果生命值小于等于0，销毁当前对象
        delete this;
    else if (++counter >= time)  // 每过time时间间隔，执行一次
    {
        counter = 0;  // 计数器归零
        if (!collidingItems().isEmpty())  // 如果有碰撞的对象
        {
            Pea *pea = new Pea(atk, true);  // 创建寒冰豌豆对象，第二个参数表示是否是寒冰类型
            pea->setX(x() + 32);  // 设置豌豆的位置（向右偏移32个像素）
            pea->setY(y());  // 设置豌豆的y坐标与当前对象相同
            scene()->addItem(pea);  // 将豌豆添加到场景中
            return;  // 结束函数执行
        }
    }
}

bool SnowPea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);  // 不使用mode参数
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y());
    // 如果碰撞的对象是僵尸类，并且在y轴上很接近，返回true
}
