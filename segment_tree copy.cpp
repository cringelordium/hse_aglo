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
            tree[n + i] = elements[i] % 2 == 0 ? 1 : 0;
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
        long long result = 0;
        left += n;
        right += n;

        while (left <= right) {
            if (left % 2 == 1) {
                result += tree[left];
                left++;
            }
            if (right % 2 == 0) {
                result += tree[right];
                right--;
            }
            left /= 2;
            right /= 2;
        }

        return result;
    }

    long long find_kth_even(long long left, long long right, long long k) {
        left += n;
        right += n;
        long long root = 1;
        long long l = 0, r = n - 1;

        while (l < r) {
            long long mid = (l + r) / 2;
            if (right <= mid) {
                root = 2 * root;
                r = mid;
            } else if (left > mid) {
                root = 2 * root + 1;
                l = mid + 1;
            } else {
                break;
            }
        }

        if (k > tree[root]) {
            return -1;  // If k is greater than the number of even numbers in the range
        }

        while (left != right) {
            long long mid = (left + right) / 2;
            if (tree[2 * root] >= k) {
                root = 2 * root;
                right = mid;
            } else {
                k -= tree[2 * root];
                root = 2 * root + 1;
                left = mid + 1;
            }
        }
        return left - n;  // Return the 0-based index in the original array
    }

    void ShowTree() {
        for (const auto& elem : tree) {
            std::cout << elem << " "; 
        }
        std::cout << std::endl;
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
        elements[i] = element;
    }

    long long resize = next_power_of_2(n);

    for (long long i = 0; i < resize - n; ++i) {
        elements.push_back(1);
    }

    SegmentTree tree(elements);

    long long queries;
    std::cin >> queries;

    for (long long i = 0; i < queries; ++i) {
        long long query;
        std::cin >> query;
        if (query == 1) {
            long long left, right, index;
            std::cin >> left >> right >> index;
            long long answer = tree.find_kth_even(left, right, index);
            if (answer == -1) {
                std::cout << "NONE" << std::endl; 
            } else {
                std::cout << elements[answer] << std::endl;
            }
        } else if (query == 2) {
            long long index, new_element;
            std::cin >> index >> new_element;
            tree.Update(index, new_element);
            elements[index] = new_element;
        }
    }

    return 0;
}
