#ifndef GIFTBOX_H
#define GIFTBOX_H

#include "plant.h"

class GiftBox : public Plant
{
public:
    GiftBox();
    void advance(int phase) override;
    QPointF pos;//记录随机生成的位置
    int status;
    void GiftBoxSimple(QPointF position,QGraphicsScene *scenePtr);
//    void GiftBoxBetter(QPointF position,QGraphicsScene *scenePtr);
};

#endif // GIFTBOX_H
