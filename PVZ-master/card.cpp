#include "card.h"
#include "shop.h"

// 初始化 Card 类的静态成员变量
const QMap<QString, int> Card::map = {{"GiftBoxSimple", 0},
                                      {"GiftBoxBetter", 1},
                                      {"Mower", 2},
                                      {"Ice",3}}; // 卡片名称到索引的映射
const QVector<QString> Card::name = {"GiftBoxSimple", "GiftBoxBetter", "Mower","Ice"}; // 卡片名称列表
const QVector<int> Card::cost = {10, 50, 0, 0}; // 卡片费用列表
const QVector<int> Card::cool = {22, 110, 22,22}; // 卡片冷却时间列表

// Card 类的构造函数，使用给定的名称初始化卡片，并将计数器设为 0
Card::Card(QString s)
{
    text = s; // 设置卡片名称
    counter = 0; // 初始化计数器
}

// 返回卡片的边界矩形
QRectF Card::boundingRect() const
{
    return QRectF(-50, -30, 100, 60); // 返回卡片的边界矩形
}

// 绘制卡片
void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->scale(0.6, 0.58); // 缩放绘图
    painter->drawPixmap(QRect(-50, -70, 100, 140), QPixmap(":/images/Card.png")); // 绘制卡片背景
    painter->drawPixmap(QRect(-35, -42, 70, 70), QPixmap(":/images/" + text + ".png")); // 绘制卡片图标
    QFont font;
    font.setPointSizeF(15); // 设置字体大小
    painter->setFont(font);
    painter->drawText(-30, 60, QString().sprintf("%3d", cost[map[text]])); // 绘制卡片费用
    if (counter < cool[map[text]])
    {
        QBrush brush(QColor(0, 0, 0, 200)); // 设置画刷颜色
        painter->setBrush(brush);
        painter->drawRect(QRectF(-48, -68, 98, 132 * (1 - qreal(counter) / cool[map[text]]))); // 绘制冷却遮罩
    }
}

// 更新卡片状态
void Card::advance(int phase)
{
    if (!phase)
        return;
    update(); // 更新卡片
    if (counter < cool[map[text]])
        ++counter; // 增加计数器
}

// 处理鼠标按下事件
void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (counter < cool[map[text]])
        event->setAccepted(false); // 如果卡片在冷却中，则不接受事件
    Shop *shop = qgraphicsitem_cast<Shop *>(parentItem());
    if (cost[map[text]] > shop->sun)
        event->setAccepted(false); // 如果阳光不足，则不接受事件
    setCursor(Qt::ArrowCursor); // 设置鼠标指针为箭头
}

// 处理鼠标移动事件
void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
            < QApplication::startDragDistance())
        return; // 如果鼠标移动距离小于拖动距离，则返回
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    QImage image(":/images/" + text + ".png");
    mime->setText(text); // 设置拖动数据的文本
    mime->setImageData(image); // 设置拖动数据的图像
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image)); // 设置拖动图像
    drag->setHotSpot(QPoint(35, 35)); // 设置拖动热点
    drag->exec(); // 执行拖动操作
    setCursor(Qt::ArrowCursor); // 设置鼠标指针为箭头
}

// 处理鼠标释放事件
void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor); // 设置鼠标指针为箭头
}
