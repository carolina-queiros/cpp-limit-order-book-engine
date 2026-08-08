#pragma once
#include "order.hpp"
#include <map>
#include <list>
#include <unordered_map>
#include <vector>

struct Fill {
    uint64_t maker_id;
    uint64_t taker_id;
    uint64_t price_ticks;
    uint32_t quantity;
};

class OrderBook {
public:
    std::vector<Fill> add_limit_order(Order ord);
    bool cancel_order(uint64_t order_id);
    size_t active_orders() const { return index_.size(); }
private:
    std::map<uint64_t, std::list<Order>, std::greater<uint64_t>> bids_;
    std::map<uint64_t, std::list<Order>> asks_;
    std::unordered_map<uint64_t, std::list<Order>::iterator> index_;
};
