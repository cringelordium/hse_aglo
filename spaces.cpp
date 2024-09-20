#include <iostream>
#include <numeric>
#include <vector>

int MinPresses(const std::vector<int>& spaces, const int& lines) {
    
    int press = 0;

    if (!lines) {

        return press;
    } 

    for (const auto& space : spaces) {
        
        if (!(space % 4)) {

            press += space / 4;
        } 
        
        if (space % 4 <= 2) {
            
            press += space / 4 + space % 4;
        } else {

            press += (space + 1) / 4 + 1; 
        }
    }

    return press;
}

int main() {
    
    int lines;

    std::cin >> lines;

    std::vector<int> spaces(lines);

    for (auto& space : spaces) {
        
        int input;

        std::cin >> input;

        space = input;
    }

    int min_presses = 0;
    min_presses += MinPresses(spaces, lines);

    std::cout << min_presses << std::endl;

    return 0;
}
