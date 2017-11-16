#ifndef COIN_H
#define COIN_H

#include <QWidget>

class coin : public QWidget
{
    Q_OBJECT
public:
    explicit coin(QWidget *parent = nullptr);

    coin();
    coin(string, string, string, int, float, float, float,
         float, float, float, float, float, float, float, int);


    string getId() const;
    void setId(const string &value);

    string getName() const;
    void setName(const string &value);

    string getSymbol() const;
    void setSymbol(const string &value);

    int getRank() const;
    void setRank(int value);

    float getPrice_usd() const;
    void setPrice_usd(float value);

    float getPrice_btc() const;
    void setPrice_btc(float value);

    float getTwentyfour_hour_volume_usd() const;
    void setTwentyfour_hour_volume_usd(float value);

    float getMarket_cap_usd() const;
    void setMarket_cap_usd(float value);

    float getAvailable_supply() const;
    void setAvailable_supply(float value);

    float getTotal_supply() const;
    void setTotal_supply(float value);

    float getMax_supply() const;
    void setMax_supply(const flaot &value);

    float getPercent_change_1h() const;
    void setPercent_change_1h(float value);

    float getPercent_change_24h() const;
    void setPercent_change_24h(float value);

    float getPercent_change_7d() const;
    void setPercent_change_7d(float value);

    int getLast_updated() const;
    void setLast_updated(int value);

protected:
    string id;
    string name;
    string symbol;
    int rank;
    float price_usd;
    float price_btc;
    float twentyfour_hour_volume_usd;
    float market_cap_usd;
    float available_supply;
    float total_supply;
    float max_supply;
    float percent_change_1h;
    float percent_change_24h;
    float percent_change_7d;
    int last_updated;

signals:

public slots:
};

#endif // COIN_H
