#include "sun.h"  // 包含头文件
#include "shop.h"  // 包含头文件

Sun::Sun()
{
    // 随机生成目标位置
    dest = QPointF(290 + qrand() % (82 * 7), 130 + qrand() % (98 * 5));
    setPos(QPointF(dest.x(), 70));  // 设置初始位置
    speed = 60.0 * 50 / 1000;  // 设置下降速度
    counter = 0;  // 计数器初始化
    time = int(10.0 * 1000 / 33);  // 触发时间
    movie = new QMovie(":/images/Sun.gif");  // 加载动画
    movie->start();  // 启动动画
    setAcceptedMouseButtons(Qt::LeftButton);  // 设置接受左键点击
}

Sun::Sun(QPointF pos)
{
    // 根据传入的位置生成目标位置
    dest = QPointF(pos.x() + qrand() % 30 - 15, pos.y() + qrand() % 30 + 15);
    setPos(QPointF(dest.x(), pos.y()));  // 设置初始位置
    speed = 60 * 50 / 1000;  // 设置下降速度
    counter = 0;  // 计数器初始化
    time = int(10.0 * 1000 / 33);  // 触发时间
    movie = new QMovie(":/images/Sun.gif");  // 加载动画
    movie->start();  // 启动动画
    setAcceptedMouseButtons(Qt::LeftButton);  // 设置接受左键点击
}

Sun::~Sun()
{
    if (movie)
        delete movie;  // 删除动画对象
}

QRectF Sun::boundingRect() const
{
    return QRectF(-35, -35, 70, 70);  // 返回边界矩形
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());  // 绘制当前帧的图像
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(300, 15))[0]);  // 获取商店对象
    shop->sun += 25;  // 增加商店中的阳光数量
    counter = time;  // 计数器设置为最大值，以触发删除
    event->setAccepted(true);  // 接受事件
}

void Sun::advance(int phase)
{
    if (!phase)  // 如果不是更新阶段，直接返回
        return;
    update();  // 更新图形状态

    if (++counter >= time)  // 如果计数器达到或超过时间阈值
        delete this;  // 删除当前对象
    else if (y() < dest.y())  // 如果当前y坐标小于目标y坐标
        setY(y() + speed);  // 向下移动
}
