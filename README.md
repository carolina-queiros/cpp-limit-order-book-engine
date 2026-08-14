# Real-Time Financial Limit Order Book & Trade Matching Engine (C++17)

Ultra-low-latency in-memory **Limit Order Book (LOB)** and deterministic trade matching engine written in **C++17**, enforcing strict **price-time priority (FIFO)** without lock contention on the hot execution path.

## Architecture

- **Price-Time Ladders (`include/order_book.hpp`):** Maintains sorted Bid (`std::greater`) and Ask (`std::less`) price trees backed by doubly-linked FIFO queues (`std::list<Order>`) and `O(1)` order lookup indexing (`std::unordered_map`).
- **Deterministic Matching (`src/order_book.cpp`):** Matches crossing limit orders immediately against resting liquidity and prunes depleted price levels in-place.
- **Throughput Benchmark (`bench/throughput_bench.cpp`):** Simulates bursts of `150,000+` alternating buy/sell orders compiled with `-O3` to verify sub-microsecond matching latency.

## Build & Run Benchmark

```bash
mkdir build && cd build
cmake .. && make
./lob-bench
```
