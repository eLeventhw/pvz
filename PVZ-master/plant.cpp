#include "plant.h"
#include "zombie.h"

// Plant 类的构造函数，初始化植物
Plant::Plant()
{
    movie = nullptr; // 动画指针初始化为空
    atk = counter = state = time = 0; // 攻击力、计时器、状态、时间初始化为 0
}

// Plant 类的析构函数，删除动画对象
Plant::~Plant()
{
    delete movie; // 删除动画对象
}

// 返回 Plant 的边界矩形
QRectF Plant::boundingRect() const
{
    return QRectF(-35, -35, 70, 70); // 植物的边界矩形
}

// 绘制 Plant
void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage()); // 绘制当前动画帧
}

// 检查 Plant 是否与其他物品碰撞
bool Plant::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 30; // 判断是否与僵尸碰撞
}

// 返回 Plant 的类型
int Plant::type() const
{
    return Type; // 返回植物的类型
}

// 设置 Plant 的动画
void Plant::setMovie(QString path)
{
    if (movie) // 如果动画对象已存在，删除它
        delete movie;
    movie = new QMovie(path); // 创建新的动画对象
    movie->start(); // 启动动画
}
