#include "conezombie.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QDebug>
ConeZombie::ConeZombie()
{
    QSqlDatabase db = DatabaseManager::instance().database();
    if (db.open()) {
                qDebug() << "y";
                QSqlQuery query(db);
                query.exec("SELECT * FROM zombie where name=\"ConeheadZombie\"");
                query.next();
                hp = query.value(1).toInt();
                atk = query.value(2).toDouble();
                speed = query.value(3).toDouble();
                qDebug() << "Zombie hp:" <<  hp << ", atk:" << atk << ", Speed:" << speed;                
                setMovie(":/images/ConeZombieWalk.gif");
            }
            else {
                qDebug() << "gg";
            }
//    hp = 640;
//    atk = 100 * 33 / 1000;
//    speed = 80.0 * 33 / 1000 / 4.7;
}

void ConeZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2;
            setMovie(":/images/ZombieDie.gif");
            setHead(":/images/ZombieHead.gif");
        }
        else if (movie->currentFrameNumber() == movie->frameCount() - 1)
            delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        Plant *plant = qgraphicsitem_cast<Plant *>(items[0]);
        plant->hp -= atk;
        if (state != 1)
        {
            state = 1;
            setMovie(":/images/ConeZombieAttack.gif");
        }
        return;
    }
    if (state)
    {
        state = 0;
        setMovie(":/images/ConeZombieWalk.gif");
    }
    setX(x() - speed);
}
