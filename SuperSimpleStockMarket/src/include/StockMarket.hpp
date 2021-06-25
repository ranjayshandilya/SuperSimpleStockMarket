#ifndef STOCKMARKET_HPP
#define STOCKMARKET_HPP
#include <chrono>
#include <assert.h>
#include <set>
#include <numeric>
#include<vector>

// Namespace for stock market
// unless otherwise stated all values are in pennies
namespace StockMarket{

/*Emum to track if a trade was a buy or a sell */
enum class buysellindex { buy, sell };

/*CTradeRecord class stores the details of a trade */
class CTradeRecord{

private:
    int m_NumberOfShares;
    double m_TradedPrice;
    buysellindex m_BuySell;

public:
    using timestamp_t = std::chrono::time_point<std::chrono::system_clock>;
    CTradeRecord(timestamp_t const &timestamp, int numberOfShares, buysellindex buy_sell, double tradedPrice) noexcept;
    timestamp_t timestamp() const noexcept;
    int numberOfShares() const noexcept;
    buysellindex buy_sell() const noexcept;
    double tradedPrice() const noexcept;

private:
    timestamp_t m_timestamp;
};

double DividendYieldCommon(double price, double last_dividend) noexcept;
double DividendYieldPreferred(double price, double fixed_dividend_fraction, double par_value) noexcept;
double PERatio(double price, double dividend) noexcept;

/*Functor to sort trades by timestamp*/
struct SortByTimestamp
{
    /** Requires c++14, allows comparison of CTradeRecord to timestamp */
    using is_transparent = void;

    bool operator()(CTradeRecord const &lv, CTradeRecord const &rv) const noexcept
    {
        return lv.timestamp() < rv.timestamp();
    }

    bool operator()(CTradeRecord::timestamp_t const &lv, CTradeRecord const &rv) const noexcept
    {
        return lv < rv.timestamp();
    }

    bool operator()(CTradeRecord const &lv, CTradeRecord::timestamp_t const &rv) const noexcept
    {
        return lv.timestamp() < rv;
    }
};

/*recordTrade class is a container of trades indexed by timestamp.
this would be implemented using https://github.com/rbock/sqlpp11)*/
using recordTrade = std::multiset<CTradeRecord, SortByTimestamp>;


//===================================================================
// METHOD      : VolumeWeightedStockPrice
// DESCRIPTION :Template method to Calculate the volume weighted stock price, 
//               assume this includes all shares traded (buy or sell)
// RETURN      : begin and end iterator TradeRecord container
// DATE        : 
//===================================================================

template <typename Iterator>double VolumeWeightedStockPrice(Iterator begin, Iterator end) noexcept
{
    auto m_weightedTradedPrice = std::decay_t<decltype(begin->tradedPrice() * begin->numberOfShares())>{};

    auto m_TotalSharesBought = std::decay_t<decltype(begin->numberOfShares())>{};

    while(begin!=end)
    {
        m_weightedTradedPrice += begin->tradedPrice() * begin->numberOfShares();
        m_TotalSharesBought += begin->numberOfShares();
        ++begin;
    }

    return m_weightedTradedPrice / m_TotalSharesBought;
}

//===================================================================
// METHOD      : GbceAllShareIndex
// DESCRIPTION : geometric mean of prices for all stocks
// RETURN      : begin and end iterator TradeRecord container
// DATE        : 
//===================================================================
 template <typename Iterator> double GbceAllShareIndex(Iterator begin, Iterator end) noexcept
{
    for (auto it = begin; it != end; ++it)
    {
        assert(*it > 0.0);
    }
    auto product = std::accumulate(begin, end, 0.0, [](auto a, auto b) { return a + std::log(b); });
    return std::exp(product / std::distance(begin, end));
}

}

#endif /*STOCKMARKET_HPP*/