#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>

struct Node {

    int key;
    Node* parent;
    Node* left;
    Node* right; 
    
    Node() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        key = -1;
    }

    Node(int x) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        key = x;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

class AVL {

private:

    Node* root_ = nullptr;

    void RotateLeft(Node* v) {
        Node* p = v->parent;
        Node* gp = nullptr;
        if (p != nullptr) {
            gp = p->parent;
        }
        Node* v_left = v->left;
        if (gp != nullptr) {
            if (gp->left == p) {
                gp->left = v;
            } else {
                gp->right = v;
            }
        }
        v->parent = p->parent;
        p->parent = v;
        v->left = p;
        p->right = v_left;
        if (v_left != nullptr) {
            v_left->parent = p;
        }
        if (root_ == p) {
            root_ = v;
        }
    }

    void RotateRight(Node* v) {
        Node* p = v->parent;
        Node* gp = nullptr;
        if (p != nullptr) {
            gp = p->parent;
        }
        Node* v_right = v->right;
        if (gp != nullptr) {
            if (gp->left == p) {
                gp->left = v;
            } else {
                gp->right = v;
            }
        }
        v->parent = p->parent;
        p->parent = v;
        v->right = p;
        p->left = v_right;
        if (v_right != nullptr) {
            v_right->parent = p;
        }
        if (root_ == p) {
            root_ = v;
        }
    }

    void Splay(Node* v) {
        while (v->parent != nullptr) {
            if (v->parent->left == v) {
                if (v->parent->parent == nullptr) {
                    RotateRight(v);
                } else if (v->parent->parent->left == v->parent) {
                    RotateRight(v->parent);
                    RotateRight(v);
                } else {
                    RotateRight(v);
                    RotateLeft(v);
                }
            } else {
                if (v->parent->parent == nullptr) {
                    RotateLeft(v);
                } else if (v->parent->parent->right == v->parent) {
                    RotateLeft(v->parent);
                    RotateLeft(v);
                } else {
                    RotateLeft(v);
                    RotateRight(v);
                }
            }
        }
        root_ = v;
    }

public:

    AVL() : root_(nullptr) {}

    ~AVL() {
        delete root_;
    }

    Node* GetRoot() { return root_; };

    void InorderTraverse(Node* node) {
        if (node == nullptr) {
            return;
        }
        InorderTraverse(node->left);
        if (node->left != nullptr || node->right != nullptr) {
            std::cout << node->key << std::endl;
        }
        InorderTraverse(node->right);      
    }

    Node* Find(int x) {

        Node* result = nullptr;
        Node* current = root_;
        Node* previous = nullptr;

        while (current != nullptr) {

            previous = current;

            if (x < current->key) {
                current = current->left;
            } else if (x > current->key) {
                current = current->right; 
            } else {
                result = current;
                break;
            }
        }
    return ThresholdFind(result, previous, x);
    }

    Node* ThresholdFind(Node* res, Node* prev, int x) {
        if (res != nullptr) {
            Splay(res);
        } else if (prev != nullptr) {
            if (prev->key > x) {
                res = prev;
            }
            if (prev->key < x) {
                while (prev != nullptr) {
                    if (prev->key > x) {
                        res = prev;
                        break;
                    }
                res = nullptr;
                prev = prev->parent;
                }
            }
            if (res != nullptr) {
                Splay(res);
            }
        }
        return res;
    }

    void Insert(int element) {
    
        if (!root_) {
            root_ = new Node(element);
            return;
        }
        
        Node* current = root_;

        while (current != nullptr) {
            if (element < current->key) {
                if (current->left == nullptr) {
                    Node* new_node = new Node(element);
                    current->left = new_node; 
                    new_node->parent = current;
                    Splay(current);
                    return;
                }
                current = current->left;
            } else if (element > current->key) {
                if (current->right == nullptr) {
                    Node* new_node = new Node(element);
                    current->right = new_node;
                    new_node->parent = current;
                    Splay(current);
                    return;
                }
                current = current->right;
            } else {
                Splay(current);
                return;
            } 
        }
        
    }

    int FindHeight(Node* root_) {

        if (root_ == nullptr) {
            return 0;
        } else {
            int left_tree_height = FindHeight(root_->left);
            int right_tree_height = FindHeight(root_->right);

            return std::max(left_tree_height, right_tree_height) + 1;
        }
    }

    int FindSecondMax() {

        Node* current = root_;

        while (current->right != nullptr) {
            current = current->right;
        }

        if (current->left != nullptr) {
            current = current->left;
            while (current->right != nullptr) {
                current = current->right;
            }
            return current->key;
        }
        return current->parent->key;
    }
};

int main() {

    AVL tree;

    while (true) {
        
        int element;
        std::cin >> element;

        if (!element) {
            break;
        }
        
        tree.Insert(element);
    }

    Node* root = tree.GetRoot();    
    int height_one = tree.FindHeight(root);

}
