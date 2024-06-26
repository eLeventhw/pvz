#include "footballzombie.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QDebug>
FootballZombie::FootballZombie()
{
    QSqlDatabase db = DatabaseManager::instance().database();
    if (db.open()) {
                qDebug() << "y";
                QSqlQuery query(db);
                query.exec("SELECT * FROM zombie where name=\"FootballZombie\"");
                query.next();
                hp = query.value(1).toInt();
                atk = query.value(2).toDouble();
                speed = query.value(3).toDouble();
                qDebug() << "Zombie hp:" <<  hp << ", atk:" << atk << ", Speed:" << speed;
                setMovie(":/images/FootballZombieWalk.gif");
            }
            else {
                qDebug() << "gg";
            }
//    hp = 1670;
//    atk = 100 * 33 / 1000;
//    speed = 80.0 * 33 / 1000 / 2.5;
//    setMovie(":/images/FootballZombieWalk.gif");
}

void FootballZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2;
            setMovie(":/images/FootballZombieDie.gif");
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
            setMovie(":/images/FootballZombieAttack.gif");
        }
        return;
    }
    if (state)
    {
        state = 0;
        setMovie(":/images/FootballZombieWalk.gif");
    }
    setX(x() - speed);
}
