#include <iostream>
#include <utility>
#include <climits>
#include <algorithm>
#include <deque>

struct Node {
    int key, priority, value;
    int max_value; 
    Node* left;
    Node* right;

    Node(int key) : key(key), priority(rand()), value(value), max_value(value), left(nullptr), right(nullptr) {}
};

class Treap {
private:
    Node* root;

    int get_max_value(Node* node) {
        return node ? node->max_value : -1;
    }

    void updateSize(Node* node) {
        if (node) {
            node->max_value = std::max(std::max(node->value, get_max_value(node->left)), get_max_value(node->right));
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
        if (node->key < key) {
            auto splitPair = split(node->right, key);
            node->right = splitPair.first;
            updateSize(node);
            return {node, splitPair.second};
        } else {
            auto splitPair = split(node->left, key);
            node->left = splitPair.second;
            updateSize(node);
            return {splitPair.first, node};
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

    Node* erase(Node* node, int key) {
        if (!node) return node;
        if (node->key == key) {
            Node* merged = merge(node->left, node->right);
            delete node;
            return merged;
        }
        if (key < node->key) {
            node->left = erase(node->left, key);
        } else {
            node->right = erase(node->right, key);
        }
        updateSize(node);
        return node;
    }

    void range_flip(Node* node, int left, int right) {
        auto splitted1 = split(node, left - 1);
        auto splitted2 = split(splitted1.second, right - left + 1);
        root = merge(splitted2.first, merge(splitted1.first, splitted2.second));
    }

    void InorderTraverse3(Node* node) {
        if (node == nullptr) {
            return;
        }
        InorderTraverse3(node->left);
        std::cout << node->key << " ";
        InorderTraverse3(node->right);      
    }

public:
    Treap() : root(nullptr) {
        srand(static_cast<unsigned int>(time(0)));
    }

    void insert(int key) {
        root = insert(root, new Node(key));
    }

    void erase(int key) {
        root = erase(root, key);   
    }

    void split(int key, Treap& leftTreap, Treap& rightTreap) {
        auto splitPair = split(root, key);
        leftTreap.root = splitPair.first;
        rightTreap.root = splitPair.second;
    }

    void merge(Treap& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }

    void flip(int left, int right) {
        range_flip(root, left, right);
    }

    void traverse() {
        InorderTraverse3(root);
    }

};

int main() {
    Treap treap;

    int soldiers, orders;
    std::cin >> soldiers >> orders;

    for (int i = 1; i <= soldiers; ++i) {
        
        treap.insert(i);
    }

    for (int i = 0; i < orders; ++i) {
        int left, right;
        std::cin >> left >> right;
        treap.flip(left, right);
        treap.traverse();
        std::cout << std::endl;
    }

    treap.traverse();

    return 0;
}
