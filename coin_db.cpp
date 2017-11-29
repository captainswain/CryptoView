DbManager::DbManager(const QString& path)
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName(path);

	if (!m_db.open())
	{
		qDebug() << "Error: connection with database fail";
	}
	else
	{
		qDebug() << "Database: connection ok";
	}
}

DbManager::~DbManager()
{
	if (m_db.isOpen())
	{
		m_db.close();
	}
}

bool DbManager::addCoin(const QString& id, const Qstring& symbol, const Qstring& price_usd, const Qstrng & 24h, const Qstring& cap,
	const Qstring& availableSupply, const Qstring& totalSupply, const Qstring & 1h, const Qstring & 24h, const Qstring & 7d, const Qstring& lastUpdate)

{
	bool success = false;

	QSqlQuery query;
	query.prepare("INSERT INTO Coin (id, symbol, price_usd, [24h_volume_usd], market_cap_usd, available_supply, total_supply, percent_change_1h, percent_change_24h, percent_change_7d, last_updated)"
		"VALUES (:id, :symbol, :price_usd, :24h, :cap, :availableSupply, :totalSupply, :1h, :24h, :7d, :lastUpdate)");
	query.bindValue(":id", id);
	query.bindValue(":symbol", symbol);
	query.bindValue(":price_usd", price_usd);
	query.bindValue(":24h", [24h_volume_usd]);
	query.bindValue(":cap", market_cap_usd);
	query.bindValue(":availableSupply", available_supply, );
	query.bindValue(":total_supply", totalSupply);
	query.bindValue(":1h", percent_change_1h);
	query.bindValue(":24h", percent_change_24h);
	query.bindValue(":7d", percent_change_7d);
	query.bindValue("lastUpdate", last_updated);
	if (query.exec())
	{
		success = true;
	}
	else
	{
		qDebug() << "addCoin error:  "
			<< query.lastError();
	}

	return success;
}
bool DbManager::DeleteCoin(const QString& coinType)
{
	if (personExists(cointType))
	{
		QSqlQuery query;
		query.prepare("DELETE FROM Coin WHERE coinType = (:id)");
		query.bindValue(":id", coinType);
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

bool DbManager::PrintAllCoins() const
{
	QSqlQuery query("SELECT * FROM Coin");
	int idName = query.record().indexOf("id");
	while (query.next())
	{
		QString name = query.value(idName).toString();
		qDebug() << name;
	}
}
