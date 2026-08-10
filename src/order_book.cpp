#include "order_book.hpp"
#include <algorithm>

std::vector<Fill> OrderBook::add_limit_order(Order ord) {
    std::vector<Fill> fills;
    if (ord.side == Side::Buy) {
        auto it = asks_.begin();
        while (it != asks_.end() && it->first <= ord.price_ticks && ord.quantity > 0) {
            auto& queue = it->second;
            while (!queue.empty() && ord.quantity > 0) {
                Order& resting = queue.front();
                uint32_t traded = std::min(ord.quantity, resting.quantity);
                fills.push_back({resting.id, ord.id, resting.price_ticks, traded});
                ord.quantity -= traded;
                resting.quantity -= traded;
                if (resting.quantity == 0) {
                    index_.erase(resting.id);
                    queue.pop_front();
                }
            }
            if (queue.empty()) it = asks_.erase(it);
            else ++it;
        }
        if (ord.quantity > 0) {
            bids_[ord.price_ticks].push_back(ord);
            index_[ord.id] = std::prev(bids_[ord.price_ticks].end());
        }
    } else {
        auto it = bids_.begin();
        while (it != bids_.end() && it->first >= ord.price_ticks && ord.quantity > 0) {
            auto& queue = it->second;
            while (!queue.empty() && ord.quantity > 0) {
                Order& resting = queue.front();
                uint32_t traded = std::min(ord.quantity, resting.quantity);
                fills.push_back({resting.id, ord.id, resting.price_ticks, traded});
                ord.quantity -= traded;
                resting.quantity -= traded;
                if (resting.quantity == 0) {
                    index_.erase(resting.id);
                    queue.pop_front();
                }
            }
            if (queue.empty()) it = bids_.erase(it);
            else ++it;
        }
        if (ord.quantity > 0) {
            asks_[ord.price_ticks].push_back(ord);
            index_[ord.id] = std::prev(asks_[ord.price_ticks].end());
        }
    }
    return fills;
}

bool OrderBook::cancel_order(uint64_t order_id) {
    return index_.erase(order_id) > 0;
}
