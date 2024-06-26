#ifndef MOWER_H
#define MOWER_H

#include "other.h"
#include "zombie.h"

class Mower : public Other//图形项
{
public:
    Mower();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
    int status;
    int final;
private:
    bool flag;
    qreal speed;
};

#endif
