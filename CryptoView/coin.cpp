#include "coin.h"

coin::coin(QWidget *parent) : QWidget(parent)
{

}

QString coin::getId() const
{
    return id;
}

void coin::setId(const QString &value)
{
    id = value;
}

QString coin::getName() const
{
    return name;
}

void coin::setName(const QString &value)
{
    name = value;
}

QString coin::getSymbol() const
{
    return symbol;
}

void coin::setSymbol(const QString &value)
{
    symbol = value;
}

int coin::getRank() const
{
    return rank;
}

void coin::setRank(int value)
{
    rank = value;
}

float coin::getPrice_usd() const
{
    return price_usd;
}

void coin::setPrice_usd(float value)
{
    price_usd = value;
}

float coin::getPrice_btc() const
{
    return price_btc;
}

void coin::setPrice_btc(float value)
{
    price_btc = value;
}

float coin::getTwentyfour_hour_volume_usd() const
{
    return twentyfour_hour_volume_usd;
}

void coin::setTwentyfour_hour_volume_usd(float value)
{
    twentyfour_hour_volume_usd = value;
}

float coin::getMarket_cap_usd() const
{
    return market_cap_usd;
}

void coin::setMarket_cap_usd(float value)
{
    market_cap_usd = value;
}

float coin::getAvailable_supply() const
{
    return available_supply;
}

void coin::setAvailable_supply(float value)
{
    available_supply = value;
}

float coin::getTotal_supply() const
{
    return total_supply;
}

void coin::setTotal_supply(float value)
{
    total_supply = value;
}

float coin::getMax_supply() const
{
    return max_supply;
}

void coin::setMax_supply(const float &value)
{
    max_supply = value;
}

float coin::getPercent_change_1h() const
{
    return percent_change_1h;
}

void coin::setPercent_change_1h(float value)
{
    percent_change_1h = value;
}

float coin::getPercent_change_24h() const
{
    return percent_change_24h;
}

void coin::setPercent_change_24h(float value)
{
    percent_change_24h = value;
}

float coin::getPercent_change_7d() const
{
    return percent_change_7d;
}

void coin::setPercent_change_7d(float value)
{
    percent_change_7d = value;
}

void coin::setLast_updated(int value)
{
    last_updated = value;
}

int coin::getChannelID() const
{
    return channelID;
}

void coin::setChannelID(int value)
{
    channelID = value;
}

int coin::getLast_updated() const
{
    return last_updated;
}
