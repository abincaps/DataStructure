#include <bits/types/clock_t.h>

#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "bst.h"

std::string rand_lower_str(std::mt19937& rand) {
    std::string res;
    for (int i = 0; i < 4; i++) {
        res += 'a' + rand() % 26;
    }
    return res;
}
int main() {
    const int size = 2e6;

    std::mt19937 rand;
    std::vector<std::string> test_data;

    for (int i = 0; i < size; i++) {
        test_data.push_back(rand_lower_str(rand));
    }

    ds::bst<std::string> a;

    clock_t start = clock();
    for (const auto& x : test_data) {
        a.insert(x);
    }

    for (int i = 0; i < size / 3; i++) {
        a.erase(test_data[i]);
    }

    clock_t end = clock();
    double duration = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    std::cout << duration << "ms" << "\n";

    std::map<std::string, int> b;

    start = clock();
    for (const auto& x : test_data) {
        b[x]++;
    }

    for (int i = 0; i < size / 3; i++) {
        b.erase(test_data[i]);
    }
    end = clock();

    duration = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    std::cout << duration << "ms" << "\n";

    for (int i = 0; i < size; i++) {
        if (a.count(test_data[i]) != b.count(test_data[i]) && a.count(test_data[i]) != b[test_data[i]]) {
            std::cout << a.count(test_data[i]) << " " << b[test_data[i]] << "\n";
            std::cerr << "error"
                      << "\n";
            break;
        }
    }

    if (a.size() != b.size()) {
        std::cout << a.size() << " " << b.size() << "\n";
        std::cout << "a.size() != b.size()"
                  << "\n";
    }

    std::cerr << "stop"
              << "\n";

    return 0;
}