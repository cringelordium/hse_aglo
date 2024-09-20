#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
#include <string>

enum Opeation {
    INSERT, ERASE, CONTAINS
};

struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;
    Node(int key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr) {}
};

std::pair<Node*, int> Find(Node* root_, int x) {

    int edges = 0;
    Node* result = nullptr;
    Node* current = root_;
    Node* previous = nullptr;

    while (current != nullptr) {

        previous = current;

        if (x < current->key) {
            current = current->left;
            ++edges;
        } else if (x > current->key) {
            current = current->right;
            ++edges; 
        } else {
            result = current;
            break;
        }
    }
    return {result, edges};
}

std::pair<Node*, Node*> Split(Node* root, int key) {
    if (root == nullptr)
        return {nullptr, nullptr};
    std::pair<Node*, Node*> result;
    if (root->key <= key) {
        result = Split(root->right, key);
        root->right = result.first;
        return {root, result.second};
    } else {
        result = Split(root->left, key);
        root->left = result.second;
        return {result.first, root};
    }
}

Node* Merge(Node* treap1, Node* treap2) {
    if (treap1 == nullptr)
        return treap2;
    if (treap2 == nullptr)
        return treap1;
    if (treap1->priority < treap2->priority) {
        treap1->right = Merge(treap1->right, treap2);
        return treap1;
    } else {
        treap2->left = Merge(treap1, treap2->left);
        return treap2;
    }
}

// 2*logN, N*logN tree build 
Node* Insert(Node* root, int key, int priority) {
    if (root == nullptr) {
        return new Node(key, priority);
    } else {
        auto splitted = Split(root, key);
        Node* new_node = new Node(key, priority);
        return Merge(splitted.first, Merge(new_node, splitted.second));
    }
    return root;
}

// logN (2022 proved)
Node* Erase(Node* root, int key) {
    if (root == nullptr)
        return nullptr;
    if (Find(root, key).first == nullptr) {
        return root;
    } else {
        Node* temp = Find(root, key).first;
        root = Merge(temp->left, temp->right);
        delete temp;
    }
    return root;
}

int main() {

    int amount_of_operations;
    std::cin >> amount_of_operations;

    Node* root = nullptr;

    for (int i = 0; i < amount_of_operations; ++i) {

        std::string operation;
        std::cin >> operation;
        if (operation == "INSERT") {
            int key, priority;
            std::cin >> key >> priority;
            root = Insert(root, key, priority);
        } else if (operation == "ERASE") {
            int key;
            std::cin >> key;
            root = Erase(root, key);
        } else if (operation == "CONTAINS") {
            int key;
            std::cin >> key;
            if (Find(root, key).first != nullptr) {
                std::cout << Find(root, key).second << std::endl;
            } else {
                std::cout << -1 << std::endl;
            }
        }
    }

    return 0;
}
