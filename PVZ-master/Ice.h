#ifndef ICE_H
#define ICE_H
#include "plant.h"
class Ice : public Plant
{
public:
    Ice();
    void advance(int phase) override;
    QPointF pos;//记录随机生成的位置
    int status;
    void IceSimple(QPointF position,QGraphicsScene *scenePtr);
//    void GiftBoxBetter(QPointF position,QGraphicsScene *scenePtr);
};
#endif
