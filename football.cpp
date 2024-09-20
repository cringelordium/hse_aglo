#include <iostream>
#include <numeric>
#include <vector>

int GoalsToWinCounter(const std::vector<int>& first_match, const std::vector<int>& second_match, const int& guest_info) {

    int goals = 0;

    if (first_match[0] + second_match[0] > first_match[1] + second_match[1]) {

        return goals;
    } else if (first_match[0] + second_match[0] == first_match[1] + second_match[1]) {

        if (first_match[0] == second_match[0] == first_match[1] == second_match[1]) {

            ++goals;
        }

        if ((first_match[0] == second_match[0]) && (guest_info == 1 && second_match[0] > first_match[1])) {
            
            return goals;
        }

        if ((first_match[0] == second_match[0]) && (guest_info == 2 && first_match[0] > second_match[1])) {
            
            return goals;
        }

        if (guest_info == 1) {

            if (second_match[0] < second_match[1]) {

                ++goals;
            }

        } else {

            if (first_match[0] < first_match[1]) {

                ++goals;
            }
        }
    } else if (first_match[0] + second_match[0] < first_match[1] + second_match[1]) {
        
        if (guest_info == 1) {

            goals += first_match[1] + second_match[1] - first_match[0] + second_match[0];
            
        } else {

            if (first_match[0] <= first_match[1]) {

                goals += first_match[1] + second_match[1] - first_match[0] + second_match[0] + 1;
            } else {

                goals += first_match[1] + second_match[1] - first_match[0] + second_match[0];
            }
        }
    }

    return goals;
}

int main() {
    
    int guest_info;

    std::vector<int> first_match(2);
    std::vector<int> second_match(2);

    int match_1_goals_1;
    int match_1_goals_2;

    int match_2_goals_1;
    int match_2_goals_2;

    char dots = ':';

    std::cin >> match_1_goals_1 >> dots >> match_1_goals_2;
    std::cin >> match_2_goals_1 >> dots >> match_2_goals_2;
    std::cin >> guest_info;

    first_match[0] = match_1_goals_1;
    first_match[1] = match_1_goals_2;

    second_match[0] = match_2_goals_1;
    second_match[1] = match_2_goals_2;

    int goals_to_win = 0;

    goals_to_win += GoalsToWinCounter(first_match, second_match, guest_info);

    std::cout << goals_to_win << std::endl;

    return 0;
}
