#include "order_book.hpp"
#include <chrono>
#include <iostream>

int main() {
    OrderBook lob;
    const uint64_t N = 150000;
    auto t0 = std::chrono::high_resolution_clock::now();
    for (uint64_t i = 1; i <= N; ++i) {
        Side s = (i % 2 == 0) ? Side::Buy : Side::Sell;
        uint64_t px = 10000 + (i % 50);
        lob.add_limit_order({i, s, px, 10});
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    double sec = std::chrono::duration<double>(t1 - t0).count();
    std::cout << "[bench] processed " << N << " orders in " << sec << "s (" << (uint64_t)(N / sec) << " orders/sec)\n";
    return 0;
}
