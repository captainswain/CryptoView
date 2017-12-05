#ifndef DATABASE_H
#define DATABASE_H
#pragma once


#include "coin.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include <QSqlRecord>


class DbManager
{
public:

    // Constructor
    DbManager(const QString& path);

    // Deconstructor
    ~DbManager();

    // Create Database Structure
    bool createTable();

    // Add coin to database.
    bool addCoin(coin coin);

    // Delete coin from database (using coin object)
    bool deleteCoin(coin coin);

    // Delete a coin based off name
    bool deleteCoin(const QString& name);

    // Delete all coins
    bool deleteAllCoins();

    // Check If coin exists in database.
    bool coinExists(const QString& name);

    // Print all coins in database
    bool printAllCoins() const;

    // check if DB connection is open
    bool isOpen() const;

    // Execute query
    bool query(const QString &query);

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
