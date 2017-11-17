
#include <stdio.h>
#include "sqlite3.h"
#include <string>
using namespace std;


int main(int argc, char* argv[]) {
	sqlite3 *db;

	sqlite3_open("coin.db", &db);
	char* sql = "CREATE TABLE Coin("
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
	int a;
	string s;
	to_string(a);
		char* str1 = "INSERT INTO Coin (ID, Symbol)"
			"VALUES("+a+","+s+")";
		

		
		//sql = strcat(str1, str2);
	


	sqlite3_exec(db, sql, NULL, 0, NULL);

	sqlite3_close(db);
}