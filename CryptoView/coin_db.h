#ifndef DATABASE_H
#define DATABASE_H
#pragma once

class DbManager
{
public:
    DbManager(const QString& path); //constructor

    ~DbManager(); //destructor

    bool addCoin(const QString& id, const Qstring& symbol, const Qstring& price_usd, const Qstrng & 24h, const Qstring& cap,
        const Qstring& availableSupply, const Qstring& totalSupply, const Qstring & 1h, const Qstring & 24h, const Qstring & 7d, const Qstring& lastUpdate); //add or update a specific coin type

    bool deleteCoin(const QString& coinType); //delete a specific type of coin

    bool PrintAllCoins() const;


private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
