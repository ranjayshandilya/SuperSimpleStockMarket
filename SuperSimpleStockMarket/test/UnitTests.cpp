#include<StockMarket.hpp>
#include<cmath>
#include<gtest/gtest.h>

TEST(Dividend_Yeild, TEA)
{
    const double result = 0.0/100.0;
    EXPECT_DOUBLE_EQ(StockMarket::DividendYieldCommon(100.0, 0.0),result)<<"Dividend yeild of TEA is not as expected";
}
TEST(Dividend_Yeild, POP)
{
    const double result = 8.0/100.0;
    EXPECT_DOUBLE_EQ(StockMarket::DividendYieldCommon(100.0, 8.0),result)<<"Dividend yeild of POP is not as expected";
}
TEST(Dividend_Yeild, ALE)
{
    const double result = 23.0/60.0;
    EXPECT_DOUBLE_EQ(StockMarket::DividendYieldCommon(60.0, 23.0),result)<<"Dividend yeild of ALE is not as expected";
}
TEST(Dividend_Yeild, GIN)
{
    const double result = 2.0/100.0;
    EXPECT_DOUBLE_EQ(StockMarket::DividendYieldPreferred(100.0,0.02, 100.0),result)<<"Dividend yeild of GIN is not as expected";
}
TEST(Dividend_Yeild, JOE)
{
    const double result = 13.0/250.0;
    EXPECT_DOUBLE_EQ(StockMarket::DividendYieldCommon(250.0, 13.0),result)<<"Dividend yeild of JOE is not as expected";
}


TEST(Prcice_To_Earning_Ratio, TEA)
{
    EXPECT_TRUE(isinf(StockMarket::PERatio(100.0, 0.0)))<<"P/E of TEA is not as expected";
}
TEST(Prcice_To_Earning_Ratio, POP)
{
    const double result = 100.0/8.0;
    EXPECT_DOUBLE_EQ(StockMarket::PERatio(100.0, 8.0),result)<<"P/E of POP is not as expected";
}
TEST(Prcice_To_Earning_Ratio, ALE)
{
    const double result = 60.0/23.0;
    EXPECT_DOUBLE_EQ(StockMarket::PERatio(60.0, 23.0),result)<<"P/E of ALE is not as expected";
}
TEST(Prcice_To_Earning_Ratio, GIN)
{
    const double result = 100.0/2.0;
    EXPECT_DOUBLE_EQ(StockMarket::PERatio(100.0,2.0),result)<<"P/E of GIN is not as expected";
}
TEST(Prcice_To_Earning_Ratio, JOE)
{
    const double result = 250.0/13.0;
    EXPECT_DOUBLE_EQ(StockMarket::PERatio(250.0, 13.0),result)<<"P/E of JOE is not as expected";
}

TEST(Trade_Record, Record_Trade_with_timestamp_quantity_of_shares_buy_or_sell_indicator_and_traded_price)
{
    auto const timestamp1 = std::chrono::system_clock::now();
    auto trade1 = StockMarket::CTradeRecord{timestamp1, 100, StockMarket::buysellindex::buy, 50.0};

    EXPECT_EQ(trade1.buy_sell(), StockMarket::buysellindex::buy);
    EXPECT_EQ(trade1.numberOfShares(), 100);
    EXPECT_EQ(trade1.timestamp(), timestamp1);
    EXPECT_EQ(trade1.tradedPrice(), 50.0);

    auto const timestamp2 = std::chrono::system_clock::now();
    auto trade2 = StockMarket::CTradeRecord{timestamp2, 100, StockMarket::buysellindex::buy, 50.0};

    EXPECT_EQ(trade2.buy_sell(), StockMarket::buysellindex::buy);
    EXPECT_EQ(trade2.numberOfShares(), 100);
    EXPECT_EQ(trade2.timestamp(), timestamp2);
    EXPECT_EQ(trade2.tradedPrice(), 50.0);

    auto const timestamp = std::chrono::system_clock::now();
    auto trade = StockMarket::CTradeRecord{timestamp, 10, StockMarket::buysellindex::sell, 5.0};

    auto recordTrade = StockMarket::recordTrade{};
    recordTrade.emplace(trade);

    EXPECT_EQ(recordTrade.size(),1u);
}

TEST(Calculate_Trade_Volume, Calculate_Volume_Weighted_Stock_Price_based_on_trades_in_past_15_minutes)
{
     auto const now = std::chrono::system_clock::now();

    // Create some trades over the last 30 minutes
    auto trades = StockMarket::recordTrade{};
    for (int i = 0; i < 30; ++i)
    {
        trades.emplace_hint(trades.begin(),
                            StockMarket::CTradeRecord{now - std::chrono::minutes{i}, i + 1,
                                          StockMarket::buysellindex::sell, (i + 1) * 2.0});
    }
    // Select any trades that occurred in the last 15 minutes (inclusive)
    auto recent_trades = trades.lower_bound(now - std::chrono::minutes{15});

    EXPECT_EQ(StockMarket::VolumeWeightedStockPrice(recent_trades, trades.end()),22.0);
}

TEST(Calculate_GBCE, Calculate_the_GBCE_All_Share_Index_using_the_geometric_mean_of_prices_for_all_stocks)
{
    auto prices = std::vector<double>{1.0, 3.0, 9.0, 27.0, 81.0};
   EXPECT_DOUBLE_EQ(StockMarket::GbceAllShareIndex(prices.begin(),prices.end()), 9.0)<<"Calculated GBCE is not right" ;
}
