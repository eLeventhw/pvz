#ifndef GIFTBOXBETTER_H
#define GIFTBOXBETTER_H

#include "plant.h"

class GiftBoxBetter: public Plant
{
public:
    GiftBoxBetter();
    void advance(int phase) override;
    QPointF pos;//记录随机生成的位置
    int status;
    void GiftBoxBetterr(QPointF position,QGraphicsScene *scenePtr);
};

#endif // GIFTBOX_H
