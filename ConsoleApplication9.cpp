#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int ALPHABET_SIZE = 26; // Предполагаем, что используются только строчные английские буквы

class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

    void collectWords(TrieNode* node, string current, vector<string>& result) {
        if (node->isEndOfWord) {
            result.push_back(current);
        }
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i]) {
                char c = 'a' + i;
                collectWords(node->children[i], current + c, result);
            }
        }
    }

    void deleteSubtree(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i]) {
                deleteSubtree(node->children[i]);
            }
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
            int index = c - 'a';
            if (index < 0 || index >= ALPHABET_SIZE) continue; // Пропускаем недопустимые символы
            if (!current->children[index]) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
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

    cout << "\nTrie из обратных слов:" << endl;
    reversedTrie.printAllWords();

    return 0;
}