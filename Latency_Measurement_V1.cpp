#include <iostream>
#include <chrono>

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i =0; i <1000000; i++) {
        int x = i*i;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time Taken: \n" << duration.count() << " microseconds\n" << std::endl;
    return 0;
}