#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>

struct Node {
    int key, priority;
    int size;
    Node* left;
    Node* right;

    Node(int key, int value) : key(key), priority(rand()), size(1), left(nullptr), right(nullptr) {}
};

class Treap {
private:
    Node* root;

    int getSize(Node* node) {
        return node ? node->size : 0;
    }

    void updateSize(Node* node) {
        if (node) {
            node->size = 1 + getSize(node->left) + getSize(node->right);
        }
    }

    Node* merge(Node* left, Node* right) {
        if (!left || !right) return left ? left : right;
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            updateSize(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            updateSize(right);
            return right;
        }
    }

    std::pair<Node*, Node*> split(Node* node, int key) {
        if (!node) return {nullptr, nullptr};
        if (key < node->key) {
            auto splitPair = split(node->left, key);
            node->left = splitPair.second;
            updateSize(node);
            return {splitPair.first, node};
        } else {
            auto splitPair = split(node->right, key);
            node->right = splitPair.first;
            updateSize(node);
            return {node, splitPair.second};
        }
    }

    Node* insert(Node* node, Node* item) {
        if (!node) return item;
        if (item->priority > node->priority) {
            auto splitPair = split(node, item->key);
            item->left = splitPair.first;
            item->right = splitPair.second;
            updateSize(item);
            return item;
        }
        if (item->key < node->key) {
            node->left = insert(node->left, item);
        } else {
            node->right = insert(node->right, item);
        }
        updateSize(node);
        return node;
    }

    void range_flip(Node* &root, int left, int right) {
        auto leftSplit = split(root, left - 1);
        auto midSplit = split(leftSplit.second, right - left + 1);
        root = merge(midSplit.first, merge(leftSplit.first, midSplit.second));
    }

    void inorderTraversal(Node* node) {
        if (!node) return;
        inorderTraversal(node->left);
        std::cout << node->key << " ";
        inorderTraversal(node->right);
    }

public:
    Treap() : root(nullptr) {
        srand(static_cast<unsigned int>(time(0)));
    }

    void insert(int key, int value) {
        root = insert(root, new Node(key, value));
    }

    void flip(int left, int right) {
        range_flip(root, left, right);
    }

    void traverse() {
        inorderTraversal(root);
    }
};

int main() {
    Treap treap;

    int soldiers, orders;
    std::cin >> soldiers >> orders;

    for (int i = 1; i <= soldiers; ++i) {
        treap.insert(i, i);
    }

    for (int i = 0; i < orders; ++i) {
        int left, right;
        std::cin >> left >> right;
        treap.flip(left, right);
    }

    treap.traverse();

    return 0;
}
