#include <iostream>
#include <string>

using namespace std;

class Trie {
private:
    struct Node {
        Node* children[26];
        bool isEndOfWord;
        Node() {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
            isEndOfWord = false;
        }
    };

    bool wordDelete(Node* curr, string word, int depth) {
        if (!curr) return false;

        if (depth == word.size()) {
            if (curr->isEndOfWord) {
                curr->isEndOfWord = false;
            }
            return isEmpty(curr);
        }

        int index = word[depth] - 'a';
        if (wordDelete(curr->children[index], word, depth + 1)) {
            delete curr->children[index];
            curr->children[index] = nullptr;
            return !curr->isEndOfWord && isEmpty(curr);
        }
        return false;
    }

    bool isEmpty(Node* node) {
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) return false;
        }
        return true;
    }

public:
    Node* root;

    Trie() {
        root = new Node();
    }

    void insert(string word) {
        Node* curr = root;
        for (char c : word) {
            int index = c - 'a';
            if (!curr->children[index]) {
                curr->children[index] = new Node();
            }
            curr = curr->children[index];
        }
        curr->isEndOfWord = true;
    }

    bool search(string word) {
        Node* curr = root;
        for (char c : word) {
            int index = c - 'a';
            if (!curr->children[index]) return false;
            curr = curr->children[index];
        }
        return curr->isEndOfWord;
    }

    void remove(string word) {
        if (!root) return;
        wordDelete(root, word, 0);
    }
};


int main() {
    Trie trie;

    trie.insert("car");
    trie.insert("cart");
    trie.insert("cartoon");
    trie.insert("can");
    trie.insert("candy");
    trie.insert("cannon");

    // search
    cout << "Search 'can': " << (trie.search("cartoon") ? "Found" : "Not Found") << endl;
    cout << "Search 'cannon': " << (trie.search("cannon") ? "Found" : "Not Found") << endl;
    
    // delete
    trie.remove("can");
    cout << "Deleted 'can'" << endl;

    // delete validation
    cout << "Search 'can': " << (trie.search("can") ? "Found" : "Not Found") << endl;
    cout << "Search 'cannon': " << (trie.search("cannon") ? "Found" : "Not Found") << endl;

    return 0;
}