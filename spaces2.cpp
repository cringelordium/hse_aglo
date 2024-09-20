#include <iostream>
#include <numeric>
#include <vector>
#include <cstdint>

int64_t MinPresses(const std::vector<int64_t>& spaces, const int64_t& lines) {
    int64_t press = 0;

    for (const auto& space : spaces) {
        if (!(space % 4)) {
            press += space / 4;
        } else if (space % 4 == 1) {
            press += (space / 4) + 1;
        } else if (space % 4 == 2) {
            press += (space / 4) + 2;
        } else if (space % 4 == 3) {
            press += ((space + 1) / 4) + 1; // Добавляем 4 пробела и один Backspace
        }
    }

    return press;
}

int main() {
    
    int64_t lines;

    std::cin >> lines;

    std::vector<int64_t> spaces(lines);

    for (auto& space : spaces) {
        
        int64_t input;

        std::cin >> input;

        space = input;
    }

    int64_t min_presses = 0;
    min_presses += MinPresses(spaces, lines);

    std::cout << min_presses << std::endl;

    return 0;
}
