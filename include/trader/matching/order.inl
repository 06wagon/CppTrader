/*!
    \file order.inl
    \brief Order inline implementation
    \author Ivan Shynkarenka
    \date 31.07.2017
    \copyright MIT License
*/

namespace CppTrader {
namespace Matching {

inline std::ostream& operator<<(std::ostream& stream, OrderSide side)
{
    switch (side)
    {
        case OrderSide::BUY:
            return stream << "BUY";
        case OrderSide::SELL:
            return stream << "SELL";
        default:
            return stream << "<\?\?\?>";
    }
}

inline std::ostream& operator<<(std::ostream& stream, OrderType type)
{
    switch (type)
    {
        case OrderType::MARKET:
            return stream << "MARKET";
        case OrderType::LIMIT:
            return stream << "LIMIT";
        default:
            return stream << "<\?\?\?>";
    }
}

inline Order::Order(uint64_t id, uint32_t symbol, OrderType type, OrderSide side, uint64_t price, uint64_t quantity, uint64_t slippage) noexcept
    : Id(id),
      SymbolId(symbol),
      Type(type),
      Side(side),
      Price(price),
      Quantity(quantity),
      Slippage(slippage)
{
}

inline std::ostream& operator<<(std::ostream& stream, const Order& order)
{
    stream << "Order(Id=" << order.Id
        << "; SymbolId=" << order.SymbolId
        << "; Type=" << order.Type
        << "; Side=" << order.Side
        << "; Price=" << order.Price
        << "; Quantity=" << order.Quantity;
    if (order.Slippage < std::numeric_limits<uint64_t>::max())
        stream << "; Slippage=" << order.Slippage;
    return stream << ")";
}

inline Order Order::Limit(uint64_t id, uint32_t symbol, OrderSide side, uint64_t price, uint64_t quantity) noexcept
{
    return Order(id, symbol, OrderType::LIMIT, side, price, quantity, std::numeric_limits<uint64_t>::max());
}

inline Order Order::BuyLimit(uint64_t id, uint32_t symbol, uint64_t price, uint64_t quantity) noexcept
{
    return Order(id, symbol, OrderType::LIMIT, OrderSide::BUY, price, quantity, std::numeric_limits<uint64_t>::max());
}

inline Order Order::SellLimit(uint64_t id, uint32_t symbol, uint64_t price, uint64_t quantity) noexcept
{
    return Order(id, symbol, OrderType::LIMIT, OrderSide::SELL, price, quantity, std::numeric_limits<uint64_t>::max());
}

inline Order Order::Market(uint64_t id, uint32_t symbol, OrderSide side, uint64_t quantity, uint64_t slippage) noexcept
{
    return Order(id, symbol, OrderType::MARKET, side, 0, quantity, slippage);
}

inline Order Order::BuyMarket(uint64_t id, uint32_t symbol, uint64_t quantity, uint64_t slippage) noexcept
{
    return Order(id, symbol, OrderType::MARKET, OrderSide::BUY, 0, quantity, slippage);
}

inline Order Order::SellMarket(uint64_t id, uint32_t symbol, uint64_t quantity, uint64_t slippage) noexcept
{
    return Order(id, symbol, OrderType::MARKET, OrderSide::SELL, 0, quantity, slippage);
}

inline OrderNode::OrderNode(const Order& order) noexcept : Order(order), Level(nullptr)
{
}

} // namespace Matching
} // namespace CppTrader
