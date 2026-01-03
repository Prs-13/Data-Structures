#include <iostream>
using namespace std;

class AVL {
private:
    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;
    };

    int height(Node* n) {
        if (n == nullptr)
            return 0;
        return n->height;
    }

    int balanceFactor(Node* n) {
        if (n == nullptr)
            return 0;
        return height(n->right) - height(n->left);
    }

    int max(int a, int b) {
        return (a > b) ? a : b; // if
    }

    Node* newNode(int key) {
        Node* node = new Node();
        node->key = key;
        node->left = node->right = nullptr;
        node->height = 1;
        return node;
    }

    // right rotation
    Node* rightRotate(Node* x) {
        Node* y = x->left;
        Node* beta = y->right;
        y->right = x;
        x->left = beta;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    // left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* beta = y->left;
        y->left = x;
        x->right = beta;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* successor(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    Node* insert(Node* node, int key) {
        if (!node)
            return newNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        
        int balance = balanceFactor(node);

        if (balance < -1 && key < node->left->key)
            return rightRotate(node);

        if (balance > 1 && key > node->right->key)
            return leftRotate(node);

        if (balance < -1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance > 1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = successor(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));
        
        int balance = balanceFactor(root);

        if (balance < -1 && balanceFactor(root->left) <= 0)
            return rightRotate(root);

        if (balance < -1 && balanceFactor(root->left) > 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance > 1 && balanceFactor(root->right) >= 0)
            return leftRotate(root);

        if (balance > 1 && balanceFactor(root->right) < 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }

public:
    Node* root;

    AVL() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    void display() {
        inorder(root);
        cout << endl;
    }
};




int main() {
    AVL tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30); 
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    tree.insert(55);
    tree.insert(35);
    cout << "Inorder traversal of the AVL tree is: ";
    tree.display();
    tree.remove(30); 
    cout << "Inorder traversal after deletion of 30 (root): ";
    tree.display();
    return 0;
}



