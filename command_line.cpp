//please enter these on the command line




//$ sqlite3 coin.db
//sqlite> CREATE TABLE Coin(
//id                 STRING(5) PRIMARY KEY
//NOT NULL,
//symbol             STRING(5) NOT NULL
//UNIQUE,
//price_usd          FLOAT(5)  NOT NULL,
//[24h_volume_usd]   FLOAT(5)  NOT NULL,
//market_cap_usd     FLOAT(5)  NOT NULL,
//available_supply   FLOAT(5)  NOT NULL,
//total_supply       FLOAT(5)  NOT NULL,
//percent_change_1h  STRING(5) NOT NULL,
//percent_change_24h STRING(5) NOT NULL,
//percent_change_7d  STRING(5) NOT NULL,
//last_updated       FLOAT(5)  NOT NULL);
//sqlite> .quit