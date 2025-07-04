#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
};

class Trie {
private:
    TrieNode* root;

    void collectWords(TrieNode* node, string current, vector<string>& result) {
        if (!node) return;
        if (node->isEndOfWord) {
            result.push_back(current);
        }
        for (auto& child : node->children) {
            collectWords(child.second, current + child.first, result);
        }
    }

    void deleteSubtree(TrieNode* node) {
        if (!node) return;
        for (auto& child : node->children) {
            deleteSubtree(child.second);
        }
        delete node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (!current->children[c])
                current->children[c] = new TrieNode();
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    vector<string> getAllWords() {
        vector<string> result;
        collectWords(root, "", result);
        return result;
    }

    void printAllWords() {
        vector<string> words = getAllWords();
        if (words.empty()) {
            cout << "Trie пуст." << endl;
        }
        else {
            cout << "Слова в Trie:" << endl;
            for (const string& word : words) {
                cout << word << endl;
            }
        }
    }

    ~Trie() {
        deleteSubtree(root);
    }
};

int main() {
    setlocale(LC_ALL, "Rus");

    // Исходные слова
    vector<string> words = {
        "level",   
        "hello",
        "radar",   
        "world",
        "kayak"    
    };

    Trie originalTrie;

    // Строим исходный trie
    for (const string& word : words) {
        originalTrie.insert(word);
    }

    cout << "Исходный trie:" << endl;
    originalTrie.printAllWords();

    // Собираем слова из исходного trie
    vector<string> allWords = originalTrie.getAllWords();

    Trie reversedTrie;

    for (const string& word : allWords) {
            string reversed = word;
            reverse(reversed.begin(), reversed.end());
            reversedTrie.insert(reversed);
    }

    cout << "\nTrie из обратных слов :" << endl;
    reversedTrie.printAllWords();

    return 0;
}
