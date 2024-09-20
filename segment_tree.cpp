#include <iostream>
#include <vector>
#include <climits>

class SegmentTree {
private:
    std::vector<long long> tree;
    long long n;

public:
    SegmentTree(const std::vector<long long>& elements) {
        n = elements.size();
        tree.resize(2 * n);
        
        for (long long i = 0; i < n; ++i) {
            tree[n + i] = elements[i];
        }
    
        for (long long i = n - 1; i > 0; --i) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    void Update(long long pos, long long value) {

        pos += n;
        tree[pos] = value % 2 == 0 ? 1 : 0;

        for (pos /= 2; pos > 0; pos /= 2) {
            tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
        }
    }

long long RangeEvenQuery(long long left, long long right) {
    long long cur_res = 0;
    long long result = 0;
    left += n;
    right += n;

    while (left <= right) {
        if (left % 2 == 1) {
            if (tree[left] == 0) {
                ++cur_res;
                result = std::max(cur_res, result);
            } else {
                cur_res = 0;
            }
            left++;
        }
        if (right % 2 == 0) {
            if (tree[right] == 0) {
                ++cur_res;
                result = std::max(cur_res, result);
            } else {
                cur_res = 0;
            }
            right--;
        }
        left /= 2;
        right /= 2;
    }

    return result;
}

    void ShowTree() {
        for (const auto& elem : tree) {
            std::cout << elem << " "; 
        }
    }
};

long long next_power_of_2(long long n) {
    if (n == 0) return 1;
    if ((n & (n - 1)) == 0) return n;
    long long power = 1;
    while (power < n) {
        power *= 2;
    }
    return power;
}

int main() {

    long long n;
    std::cin >> n;
    std::vector<long long> elements(n);
    for (long long i = 0; i < n; ++i) {
        long long element;
        std::cin >> element;
        elements[i] = element % 2 == 0 ? 1 : 0;
    }

    long long resize = next_power_of_2(n);

    for (long long i = 0; i < resize - n; ++i) {
        elements.push_back(0);
    }

    SegmentTree tree(elements);

    long long queries;
    std::cin >> queries;

    for (long long i = 0; i < queries; ++i) {
        long long query;
        std::cin >> query;
        if (query == 1) {
            long long left, right;
            std::cin >> left >> right;
            std::cout << tree.RangeEvenQuery(left, right) << std::endl;
        } else if (query == 2) {
            long long index, new_element;
            std::cin >> index >> new_element;
            tree.Update(index, new_element); 
        }
    }

    return 0;
}
