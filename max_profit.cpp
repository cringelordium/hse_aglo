#include <iostream>
#include <numeric>
#include <vector>
#include <cstdint>
#include <cmath>

int64_t CombineNumbers(int lenght, std::vector<int64_t> number) {

    int64_t num_digits = 1;

    return num_digits;
}

int64_t MaxProfit(int64_t& n, const int64_t& k, const int& d) {

    for (int i = 0; i < d; ++i) {
            
        int64_t max_profit = 0;
        int64_t curr_profit = 0;

        for (int j = 0; j < 10; ++j) {

            if (CombineNumbers(n, j) % k == 0) {

                curr_profit = CombineNumbers(n, j);

                if (curr_profit > max_profit) {
                    
                    max_profit = curr_profit;
                } 

            } else if (n == max_profit) {
                
                return -1;
            } 
        }
    
    n = max_profit;

    }

    return n;
}

int main() {
    
    int64_t n; // 21
    int64_t k; // 108
    int d; // 1

    std::cin >> n >> k >>d;

    std::cout << MaxProfit(n, k, d) << std::endl;
}