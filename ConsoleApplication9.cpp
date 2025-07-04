#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Функции для работы с регистром
bool is_alpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char to_lower(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        return ch + ('a' - 'A');
    return ch;
}

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }

    ~TrieNode() {
        for (int i = 0; i < 26; ++i) {
            if (children[i]) {
                delete children[i];
            }
        }
    }
};

class Trie {
private:
    TrieNode* root;

    // Рекурсивный сбор всех слов
    void collectAllWords(TrieNode* node, string current, vector<string>& words) {
        if (!node) return;

        if (node->isEndOfWord) {
            words.push_back(current);
        }

        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                collectAllWords(node->children[i], current + char('a' + i), words);
            }
        }
    }

public:
    Trie() : root(new TrieNode()) {}
    ~Trie() { delete root; }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (!is_alpha(ch)) continue;

            int index = to_lower(ch) - 'a';
            if (index < 0 || index >= 26) continue;

            if (!current->children[index]) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    // Получение всех слов из дерева
    vector<string> getAllWords() {
        vector<string> words;
        collectAllWords(root, "", words);
        return words;
    }

    // Построение дерева с обратными словами (нестатический метод)
    Trie buildReversedTrie() {
        Trie reversedTrie;
        vector<string> words = this->getAllWords();

        for (string word : words) {
            reverse(word.begin(), word.end());
            reversedTrie.insert(word);
        }

        return reversedTrie;
    }

    // Вывод всех слов
    void printAllWords() {
        vector<string> words;
        collectAllWords(root, "", words);

        cout << "Слова в дереве (" << words.size() << "):\n";
        for (const string& word : words) {
            cout << word << endl;
        }
        cout << "-------------------------\n";
    }
};

int main() {
    Trie originalTrie;
    const int wordCount = 5;

    cout << "Введите " << wordCount << " слов для исходного дерева:\n";
    for (int i = 0; i < wordCount; ++i) {
        string word;
        cin >> word;
        originalTrie.insert(word);
    }

    cout << "\nИсходное дерево:\n";
    originalTrie.printAllWords();

    // Строим дерево с обратными словами
    Trie reversedTrie = originalTrie.buildReversedTrie();

    cout << "\nДерево с обратными словами:\n";
    reversedTrie.printAllWords();

    return 0;
}