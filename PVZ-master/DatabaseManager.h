//#ifndef MYDATABASE_H
//#define MYDATABASE_H

//#endif // MYDATABASE_H
//#include <QtSql>
//#include <QtDebug>
//class MyDatabase {
//public:
//    static QSqlDatabase& getDatabase() {
//        static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//        db.setHostName("127.0.0.1");
//        db.setUserName("root");
//        db.setPassword("1234");
//        db.setDatabaseName("pvz");
//        if (db.open()) {
//        qDebug()<<'y';
//        QSqlQuery query(db);
//        query.exec("SELECT * FROM zombie");
//        QString column1 = query.value(0).toString();
//        qDebug() << column1;
//        QString column2 = query.value(1).toString();
//        qDebug() << column2;
//        }
//        return db;
//    }
//};


// DatabaseManager.h
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>

class DatabaseManager {
public:
    static DatabaseManager& instance();
    QSqlDatabase& database();

private:
    QSqlDatabase db;
    DatabaseManager();
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
};

#endif // DATABASEMANAGER_H
