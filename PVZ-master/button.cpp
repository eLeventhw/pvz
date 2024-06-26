#include "button.h"

// Button 类的构造函数，初始化按钮并设置音效和计时器
Button::Button(QSound *s, QTimer *t)
{
    sound = s; // 设置音效
    timer = t; // 设置计时器
}

// 返回按钮的边界矩形
QRectF Button::boundingRect() const
{
    return QRectF(-80, -20, 160, 40); // 返回按钮的边界矩形
}

// 绘制按钮
void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-80, -20, 160, 40), QPixmap(":/images/Button.png")); // 绘制按钮背景
    painter->setPen(Qt::green); // 设置字体颜色
    QFont font("Calibri", 18, QFont::Bold, true); // 设置字体
    painter->setFont(font);
    if (timer->isActive())
        painter->drawText(boundingRect(), Qt::AlignCenter, "PAUSE"); // 绘制 "PAUSE" 文本
    else
        painter->drawText(boundingRect(), Qt::AlignCenter, "CONTINUE"); // 绘制 "CONTINUE" 文本
}

// 处理鼠标按下事件
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (timer->isActive())
        {
            sound->stop(); // 停止音效
            timer->stop(); // 停止计时器
        }
        else
        {
            sound->play(); // 播放音效
            timer->start(); // 启动计时器
        }
    }
    update(); // 更新按钮状态
}
