#ifndef SHOP_H
#define SHOP_H

#include "plant.h"
#include "other.h"
#include "card.h"
#include "sun.h"
#include "sunflower.h"
#include "peashooter.h"
#include "cherrybomb.h"
#include "wallnut.h"
#include "snowpea.h"
#include "GiftBox.h"
#include "potatomine.h"
#include "repeater.h"
#include "mower.h"
#include "basiczombie.h"
class Shop : public Other
{
public:
    int sun;
    Shop();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void addPlant(QString s, QPointF pos);
    GiftBox* gifbox;
    Mower *mower[5]; //记录mainwindow的小推车并修改
private:
    int counter;
    int time;
};

#endif // SHOP_H
