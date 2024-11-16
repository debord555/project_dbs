#pragma once

#include <string>

class Trie {
    public:
        Trie();
        ~Trie();

        bool isEmpty() const;
        int insert(std::string word);
        int remove(std::string word);
        bool contains(std::string word);
        size_t getSize() const;

    private:

        struct TrieNode {
            TrieNode* children[256];
            bool is_end_of_word;
            TrieNode() {
                for (int i = 0; i < 256; i++)
                    children[i] = NULL;
                is_end_of_word = false;
            }
        };

        TrieNode* root;
        size_t size;
};