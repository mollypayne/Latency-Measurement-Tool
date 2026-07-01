#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <fstream>

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
    long long zero_count = 0;
    std::map<long long, int> frequency;
    for (long long latency: latencies) {
        total += latency;
        frequency[latency]++;
        if(latency < min_latency) {
            min_latency=latency;
        }
        if(latency > max_latencies) {
            max_latencies=latency;
        }
        if(latency == 0) {
            zero_count++;
        }
    }
    double average = static_cast<double>(total)/runs;
    std::cout << "Runs: " << runs << "\n";
    std::cout << "Minimum latency: " <<min_latency << " ns\n";
    std::cout << "Maximum latency: " <<max_latencies << " ns\n";
    std::cout << "Average latency: " <<average << "ns\n";
    double zero_percentage = static_cast<double>(zero_count) / runs * 100;
    std::cout << "Zero readings percentage: " << zero_percentage << "%\n";
    std::cout << "Zero readings: " << zero_count << "\n";
    std::cout << "Latency Distribution:\n";
    for (const auto& pair : frequency) {
        if (pair.second > 1) {
            std::cout
            <<pair.first
            <<"ns: "
            <<pair.second 
            <<"\n";
        }
    }
    std::ofstream outputFile("Latency_Distribution.txt");
    outputFile << "Latency_ns, Frequency\n";
    for (const auto& pair : frequency) {
        outputFile << pair.first <<"," << pair.second <<"\n";
    }
    outputFile.close();
    return 0;
}