#include "include\StockMarket.hpp"
#include<assert.h>

namespace StockMarket
{
//===================================================================
// METHOD      : DividendYieldCommon
// DESCRIPTION : Calculate the dividend yield for common stock
//               TEA, POP, ALE and JOE
//INPUT        : traded price and the value of last dividend
// RETURN      : double
// DATE        : 
//===================================================================
double DividendYieldCommon(double price, double last_dividend) noexcept
{
    assert(price > 0.0);
    assert(last_dividend >= 0.0);
    return last_dividend / price;
}
//=====================================================================
// METHOD      : DividendYieldPreferred
// DESCRIPTION : Calculates the dividend yield for preferred stock GIN
// INPUT       : The traded price of a share, fraction of the par value 
//                as fixed dividend and par_value          
// RETURN      : double
// DATE        : 
//=====================================================================
double DividendYieldPreferred(double price, double fixed_dividend_fraction,
                                double par_value) noexcept
{
    assert(price > 0.0);
    assert(fixed_dividend_fraction >= 0.0);
    assert(par_value >= 0.0);
    return fixed_dividend_fraction * par_value / price;
}
//===================================================================
// METHOD      : PERatio
// DESCRIPTION : Calculate the ratio of the price to the dividend
// INPUT       : traded price and the dividend paid
// RETURN      : 
// DATE        : 
//===================================================================
double PERatio(double price, double dividend) noexcept
{
    assert(price > 0.0);
    assert(dividend >= 0.0);
    return price / dividend;
}
//===================================================================
// METHOD      : Constructor of TradeRecord class
// DESCRIPTION : Initialises member variables
//INPUT        : Initial val
// RETURN      : None
// DATE        : 
//===================================================================
CTradeRecord::CTradeRecord (timestamp_t const &timestamp, int numberOfShares, buysellindex buy_sell,
             double tradedPrice) noexcept
    : m_timestamp{timestamp}, m_NumberOfShares{numberOfShares}, m_BuySell{buy_sell},
      m_TradedPrice{tradedPrice}
{
    assert(numberOfShares > 0);
    assert(tradedPrice > 0.0);
}

int CTradeRecord::numberOfShares() const noexcept
{
    return m_NumberOfShares;
}

CTradeRecord::timestamp_t CTradeRecord::timestamp() const noexcept
{
    return m_timestamp;
}

buysellindex CTradeRecord::buy_sell() const noexcept
{
    return m_BuySell;
}

double CTradeRecord::tradedPrice() const noexcept
{
    return m_TradedPrice;
}
} // namespace stocks