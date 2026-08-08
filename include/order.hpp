#pragma once
#include <cstdint>

enum class Side { Buy, Sell };

struct Order {
    uint64_t id;
    Side side;
    uint64_t price_ticks;
    uint32_t quantity;
};
