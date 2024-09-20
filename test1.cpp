#include <iostream>
#include <deque>
#include <numeric>

int CheckIntersection(const int& vasya_id, const int& vasya_bucket, const int& masha_id, const int& masha_bucket) {

    int difference = 0;

    if (std::max(vasya_id - vasya_bucket, masha_id - masha_bucket) > std::min(vasya_id + vasya_bucket, masha_id + masha_bucket)) {

        return difference;
    } else {

        difference += std::abs(std::max(vasya_id - vasya_bucket, masha_id - masha_bucket) - std::min(vasya_id + vasya_bucket, masha_id + masha_bucket)) + 1;
    }

    return difference;
}

int main() {
    
    int vasya_id;
    int vasya_bucket;

    int masha_id;
    int masha_bucket;

    std::cin >> vasya_id >> vasya_bucket;
    std::cin >> masha_id >> masha_bucket;

    int tree_sum = 0;

    tree_sum += 2*vasya_bucket + 1 + 2*masha_bucket + 1 - CheckIntersection(vasya_id, vasya_bucket, masha_id, masha_bucket);

    std::cout << tree_sum << std::endl;

    return 0;
}
