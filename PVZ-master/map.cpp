#include "map.h"

// Map 类的构造函数，初始化并设置接受拖放
Map::Map()
{
    dragOver = false; // 初始化拖拽标志
    setAcceptDrops(true); // 设置接受拖放事件
}

// 返回 Map 的边界矩形
QRectF Map::boundingRect() const
{
    return QRectF(-369, -235, 738, 470); // 返回地图的边界矩形
}

// 绘制 Map
void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
    // 在此处可以添加绘制代码
}

// 处理拖拽进入事件
void Map::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->setAccepted(true); // 接受拖拽事件
        dragOver = true; // 设置拖拽标志
        update(); // 更新显示
    }
    else
        event->setAccepted(false); // 不接受拖拽事件
}

// 处理拖拽离开事件
void Map::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    dragOver = false; // 重置拖拽标志
    update(); // 更新显示
}

// 处理放下事件
void Map::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false; // 重置拖拽标志
    if (event->mimeData()->hasText())
    {
        QString s = event->mimeData()->text(); // 获取拖拽的文本
        QPointF pos = mapToScene(event->pos()); // 将事件位置转换为场景位置
        pos.setX((int(pos.x()) - 249) / 82 * 82 + 290); // 调整 X 轴位置
        pos.setY((int(pos.y()) - 81) / 98 * 98 + 130); // 调整 Y 轴位置
        if (s == "Shovel")
        {
            // 如果拖拽的是铲子，则移除植物
            Shovel *shovel = qgraphicsitem_cast<Shovel *>(scene()->items(QPointF(830, 15))[0]);
            shovel->removePlant(pos);
        }
        else
        {
            // 如果拖拽的是其他植物，则添加植物
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(300, 15))[0]);
            shop->addPlant(s, pos);
        }
    }
    update(); // 更新显示
}
