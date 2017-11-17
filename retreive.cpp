#include <stdio.h>
#include <sqlite3.h> 

static int callback(void *data, int numResults, char **values, char **colNames) {
	for (int i = 0; i < numResults; i++) {
		printf("%s : %s\n", colNames[i], values[i]);
	}
	return 0;
}

int main(int argc, char* argv[]) {
	sqlite3 *db;

	sqlite3_open("test.db", &db);
	char* sql =  "CREATE TABLE Coin("
		"id                 STRING(5) PRIMARY KEY"
		"NOT NULL,"
		"symbol             STRING(5) NOT NULL"
		"UNIQUE,"
		"price_usd          FLOAT(5)  NOT NULL,"
		"[24h_volume_usd]   FLOAT(5)  NOT NULL,"
		"market_cap_usd     FLOAT(5)  NOT NULL,"
		"available_supply   FLOAT(5)  NOT NULL,"
		"total_supply       FLOAT(5)  NOT NULL,"
		"percent_change_1h  STRING(5) NOT NULL,"
		"percent_change_24h STRING(5) NOT NULL,"
		"percent_change_7d  STRING(5) NOT NULL,"
		"last_updated       FLOAT(5)  NOT NULL"
		");";
	sqlite3_exec(db, sql, NULL, 0, NULL);

	sql =  "INSERT INTO Coin (ID, Symbol)"
		"VALUES(" + a + "," + s + ")";;

	sqlite3_exec(db, sql, NULL, 0, NULL);

	sql = "SELECT * FROM POSTS";

	sqlite3_exec(db, sql, callback, 0, NULL);

	sqlite3_close(db);
}