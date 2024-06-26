#include "shop.h"  // 包含头文件
#include "DatabaseManager.h"
#include <QSqlQuery>
#include "loginwindow.h"
#include <QDebug>
#include "GiftBoxBetter.h"
#include "mainwindow.h"
Shop::Shop()
{
    sun = 200;  // 初始阳光数量
    counter = 0;  // 计数器初始化
    time = int(7.0 * 1000 / 33);  // 触发时间
    Card *card = nullptr;  // 卡片对象指针初始化为nullptr
    for (int i = 0; i < Card::name.size(); ++i)  // 遍历卡片名称列表
    {
        card = new Card(Card::name[i]);  // 创建卡片对象
        card->setParentItem(this);  // 将卡片设置为当前对象的子项
        card->setPos(-157 + 65 * i, -2);  // 设置卡片在场景中的位置
    }
}

QRectF Shop::boundingRect() const
{
    return QRectF(-270, -45, 540, 90);  // 返回边界矩形
}

void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-270, -45, 540, 90), QPixmap(":/images/Shop.png"));  // 绘制商店背景图片
    QFont font;  // 创建字体对象
    font.setPointSizeF(15);  // 设置字体大小
    painter->setFont(font);  // 应用字体到画笔
    painter->drawText(QRectF(-255, 18, 65, 22), Qt::AlignCenter, QString::number(sun));  // 绘制阳光数量文本
    painter->drawPoint(-220, 0);  // 绘制一个点（暂时不明确用途）
}

void Shop::advance(int phase)
{
    if (!phase)  // 如果不是更新阶段，直接返回
        return;
    update();  // 更新图形状态

    if (++counter >= time)  // 每过time时间间隔，执行一次
    {
        counter = 0;  // 计数器归零
        scene()->addItem(new Sun);  // 向场景中添加太阳对象
    }
}

void Shop::addPlant(QString s, QPointF pos)
{
    QList<QGraphicsItem *> items = scene()->items(pos);  // 获取指定位置的所有图形项
    foreach (QGraphicsItem *item, items)  // 遍历每一个图形项
        if (item->type() == Plant::Type)  // 如果是植物类对象
            return;  // 直接返回，不添加植物

    sun -= Card::cost[Card::map[s]];  // 减去选中植物的成本
    Plant *plant = nullptr;  // 植物对象指针初始化为nullptr
    switch (Card::map[s])  // 根据卡片映射表选择植物类型
    {
//    case 0:
//        plant = new SunFlower; break;  // 创建向日葵对象
//    case 1:
//        plant = new Peashooter; break;  // 创建豌豆射手对象
    case 0:{
        GiftBox *gf = new GiftBox;
        gf->pos = pos;
        plant = gf;
        break;
    }
    case 1:{
        GiftBoxBetter *gf = new GiftBoxBetter;
        gf->pos = pos;
        plant = gf;
        break;
    }
    case 2:{
//        Mower *gf = new Mower;
//        gf->setPos(pos);
//        scene()->addItem(gf);
        for (int i = 0; i < 5; ++i)
        {

            if(mower[i]!=nullptr){
                mower[i]->status = 2;
                mower[i]->advance(1);
            }
        }
        // 添加割草机到场景中
        for (int i = 0; i < 5; ++i)
        {
            mower[i] = new Mower;
            mower[i]->setPos(210, 130 + 98 * i);
            scene()->addItem(mower[i]);
        }
        break;
    }
    case 3:{
        foreach (QGraphicsItem *item, scene()->items()){
            if (item->type() == Zombie::Type){
                Zombie* p = dynamic_cast<Zombie*>(item);
                if(p->speed > 0.55)
                  p->speed=p->speed/2;
            }
        }
    }
    }
    if(plant != nullptr){
        plant->setPos(pos);  // 设置植物的位置
        scene()->addItem(plant);  // 将植物添加到场景中
    }
    QList<QGraphicsItem *> child = childItems();  // 获取所有子项
    foreach (QGraphicsItem *item, child)  // 遍历每一个子项
    {
        Card *card = qgraphicsitem_cast<Card *>(item);  // 尝试转换为卡片对象
        if (card->text == s)  // 如果卡片文本与选中的植物相同
            card->counter = 0;  // 计数器归零
    }
    counter = 0;  // 计数器归零
}
