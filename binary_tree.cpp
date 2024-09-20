#include <iostream>
#include <vector>
#include <string>
#include <cctype>

bool canJump(std::vector<int>& nums) {
    int len = 0;
    int n = nums.size() - 1;
    int i = 0;
    while (len < n) {
        len += nums[i] - 1;
        if (len == 0) return false;
    }
    
    std::cout << len << std::endl;

    if (len != nums.size() - 1) {
        return false;
    }
    return true;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> nums(n);

    for (auto& k : nums) {
        std::cin >> k;
    }

    bool res = canJump(nums);

    std::cout << res << std::endl;

    return 0;
}
