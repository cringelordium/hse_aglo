#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

enum Color { RED, BLACK };

struct TreeNode {
    int key;
    Color color;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k, Color c) : key(k), color(c), left(nullptr), right(nullptr) {}
};

int main() {
    int N, rootIndex;
    cin >> N >> rootIndex;

    if (N == 0) {
        cout << "YES" << endl;
        return 0;
    }

    unordered_map<int, pair<int, string>> nodes_input; // Pair: (key, "left right color")
    unordered_map<int, TreeNode*> nodes;

    for (int i = 0; i < N; ++i) {
        int number, key;
        string left, right, color;
        cin >> number >> key >> left >> right >> color;
        nodes_input[number] = make_pair(key, left + " " + right + " " + color);
    }

    // Build tree structure
    for (auto& [number, data] : nodes_input) {
        int key;
        string left, right, color;
        tie(key, left, right, color) = data;

        if (left != "null") nodes[number]->left = nodes[stoi(left)];
        if (right != "null") nodes[number]->right = nodes[stoi(right)];
    }

    // Construct tree nodes
    for (auto& [number, data] : nodes_input) {
        int key;
        string left, right, color;
        tie(key, left, right, color) = data;
        nodes[number] = new TreeNode(key, (color == "B" ? BLACK : RED));
    }

    return 0;
}