#include "coin_db.h"


/*
 * Creates instance of databaseManager
 * @param Path for databse
 *
 */
DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

/*
 * Deconstructor, closes database if currently open.
 * @param none
 *
 */
DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

/*
 * Create coin table
 * @param none
 *
 */
bool DbManager::createTable()
{

    QSqlQuery query;
    query.prepare("CREATE TABLE coin (id INTEGER PRIMARY KEY AUTOINCREMENT, symbol varchar(255), open double, close double, high double, low double, time int);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'coin': one might already exist.";
        return false;
    }

    return true;
}

/*
 * Check if DB connection is open.
 *
 */
bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::query(const QString &statement)
{
    QSqlQuery query(statement);

    if (query.exec())
    {
        return true;
    }
    else
    {
        qDebug() << "query error:  "  << query.lastError();
        return false;
    }
}

/*
 * Add Coin to databse
 * @param coin
 *
 */
bool DbManager::addCoin(coin coin)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Coin (id, symbol, price_usd, [24h_volume_usd], market_cap_usd, available_supply, total_supply, percent_change_1h, percent_change_24h, percent_change_7d, last_updated)"
        "VALUES (:id, :symbol, :price_usd, :24h, :cap, :availableSupply, :totalSupply, :1h, :24h, :7d, :lastUpdate)");
    query.bindValue(":id", coin.getId());
    query.bindValue(":symbol", coin.getSymbol());
    query.bindValue(":price_usd", coin.getPrice_usd());
    //query.bindValue(":24h", coin.24h_volume_usd);
    query.bindValue(":cap", coin.getMarket_cap_usd());
    query.bindValue(":availableSupply", coin.getAvailable_supply());
    //query.bindValue(":total_supply", coin.totalSupply);
    query.bindValue(":1h", coin.getPercent_change_1h());
    query.bindValue(":24h", coin.getPercent_change_24h());
    query.bindValue(":7d", coin.getPercent_change_7d());
    query.bindValue("lastUpdate", coin.getLast_updated());

    //try and run query.
    if (query.exec())
    {
        return true;
    }
    else
    {
        qDebug() << "addCoin error:  "
            << query.lastError();
        return false;
    }
}


/*
 * Check If coin exists in database
 * @param name type(string)
 *
 */
bool DbManager::coinExists(const QString& name){

    QSqlQuery query;
    query.prepare("SELECT name FROM Coin WHERE name = (:name)");
    query.bindValue(":name", name);

    if (query.exec())
    {
       if (query.next())
       {
          return true;
       }
    }

    return false;
}

/*
 * Delete coin from databse
 * @param coin type(string)
 *
 */
bool DbManager::deleteCoin(const QString& name)
{
    bool success = false;

    if (coinExists(name))
    {
        QSqlQuery query;
        query.prepare("DELETE FROM Coin WHERE name = (:name)");
        query.bindValue(":name", name);
        success = query.exec();

        if (!success)
        {
            qDebug() << "removeCoin error: "
                << query.lastError();
            return false;
        }
        else
            return true;
    }
}


/*
 * Print coins from database.
 * @param none
 *
 */
bool DbManager::printAllCoins() const
{
    QSqlQuery query("SELECT * FROM Coin");

    int idName = query.record().indexOf("id");

    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << name;
    }
}

/*
 * Delete All coins from database.
 * @param none
 *
 */
bool DbManager::deleteAllCoins()
{
    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM Coins");

    // Check if query was ran. If so return true.
    if(removeQuery.exec()){

        return true;
    }

   return false;

}

