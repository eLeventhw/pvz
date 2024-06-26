#include "DatabaseManager.h"

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("1234");
    db.setDatabaseName("pvz");
    db.open();
}

DatabaseManager::~DatabaseManager() {
    db.close();
}

QSqlDatabase& DatabaseManager::database() {
    return db;
}
