#include "shovel.h"  // 包含头文件

Shovel::Shovel()
{
    // 默认构造函数，不做额外初始化
}

QRectF Shovel::boundingRect() const
{
    return QRectF(-40, -40, 80, 80);  // 返回边界矩形
}

void Shovel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-40, -40, 80, 80), QPixmap(":/images/ShovelBank.png"));  // 绘制铲子的背景图片
    painter->drawPixmap(QRect(-35, -35, 70, 70), QPixmap(":/images/Shovel.png"));  // 绘制铲子的图片
}

void Shovel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);  // 设置鼠标光标为箭头形状
}

void Shovel::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
            < QApplication::startDragDistance())
        return;  // 如果移动距离小于启动拖动的距离，直接返回

    QDrag *drag = new QDrag(event->widget());  // 创建拖动对象
    QMimeData *mime = new QMimeData;  // 创建MIME数据对象
    QImage image(":/images/Shovel.png");  // 加载铲子的图片
    mime->setText("Shovel");  // 设置MIME数据的文本类型
    mime->setImageData(image);  // 设置MIME数据的图像数据
    drag->setMimeData(mime);  // 设置拖动操作的MIME数据
    drag->setPixmap(QPixmap::fromImage(image).scaled(70, 70));  // 设置拖动时显示的图片
    drag->setHotSpot(QPoint(35, 35));  // 设置拖动的热点位置
    drag->exec();  // 执行拖动操作
    setCursor(Qt::ArrowCursor);  // 拖动结束后设置鼠标光标为箭头形状
}

void Shovel::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);  // 设置鼠标光标为箭头形状
}

void Shovel::removePlant(QPointF pos)
{
    QList<QGraphicsItem *> items = scene()->items(pos);  // 获取指定位置的所有图形项
    foreach (QGraphicsItem *item, items)  // 遍历每一个图形项
        if (item->type() == Plant::Type)  // 如果是植物类对象
        {
            delete item;  // 删除该植物对象
            return;  // 结束函数执行
        }
}
