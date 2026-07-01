#include <iostream>
#include <chrono>
#include <vector>

int main() {
    const int runs = 1000000;
    const int warmup_runs = 10000;
    for (int i=0; i < warmup_runs; i++){
        volatile int x= i + 1;
    }
    std::vector<long long> latencies;
    latencies.reserve(runs);
    for (int i=0; i<runs; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        volatile int x= i + 1;
        auto end = std::chrono::high_resolution_clock::now();
        auto latency = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
        latencies.push_back(latency.count());
    }
    long long total = 0;
    long long min_latency = latencies[0];
    long long max_latencies = latencies[0];
    for (long long latency: latencies) {
        total += latency;
        if(latency < min_latency) {
            min_latency=latency;
        }
        if(latency > max_latencies) {
            max_latencies=latency;
        }
    }
    double average = static_cast<double>(total)/runs;
    std::cout << "Runs: " << runs << "\n";
    std::cout << "Minimum latency: " <<min_latency << " ns\n";
    std::cout << "Maximum latency: " <<max_latencies << " ns\n";
    std::cout << "Average latency: " <<average << "ns\n";

    return 0;
}