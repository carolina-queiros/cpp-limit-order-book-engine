#include "order_book.hpp"
#include <iostream>
#include <sstream>

int main() {
    OrderBook lob;
    lob.add_limit_order({1, Side::Sell, 10050, 25});
    auto fills = lob.add_limit_order({2, Side::Buy, 10050, 10});
    std::cout << "[lob-engine] executed " << fills.size() << " fills | active resting orders: " << lob.active_orders() << "\n";
    return 0;
}
