#include "trie.hpp"
#include <queue>
#include <stack>

/**
 * Constructs an empty Trie.
 */
Trie::Trie() {
    root = new TrieNode();
    size = 0;
}

/**
 * Destroys the Trie and frees its memory.
 *
 * This function is needed to destroy the Trie when it is
 * no longer needed. It frees the memory of all TrieNodes
 * in the Trie by using a queue to visit all the
 * TrieNodes. This uses a Breadth-First Search (BFS)
 * algorithm, which ensures that all TrieNodes are
 * visited.
 */
Trie::~Trie() {
    std::queue<TrieNode*> q;
    if (root != nullptr)
        q.push(root);
    while (!q.empty()) {
        for (int i = 0; i < 256; i++) {
            if (q.front()->children[i] != nullptr) {
                q.push(q.front()->children[i]);
            }
        }
        delete q.front();
        q.pop();
    }
}

/**
 * Checks if the Trie is empty.
 *
 * \return \c true if the Trie is empty and \c false otherwise.
 */
bool Trie::isEmpty() const {
    return size == 0;
}

/**
 * Inserts a word into the Trie.
 *
 * \param word The word to be inserted.
 * \return \c 0 on success and a non-zero value on failure.
 *
 * This function inserts a word into the Trie. It starts at the root
 * TrieNode and traverses down the Trie, creating new TrieNodes
 * if necessary, until it reaches the end of the word. At the end
 * of the word, it sets the is_end_of_word flag to \c true and
 * increments the size of the Trie.
 */
int Trie::insert(std::string word) {
    TrieNode* node = root;
    for (size_t i = 0; i < word.size(); i++) {
        if (node->children[(unsigned char)word[i]] == nullptr)
            node->children[(unsigned char)word[i]] = new TrieNode();
        node = node->children[(unsigned char)word[i]];
    }
    node->is_end_of_word = true;
    size++;
    return 0;
}

/**
 * Removes a word from the Trie.
 *
 * \param word The word to be removed.
 * \return \c 0 on success and a non-zero value on failure.
 *
 * This function removes a word from the Trie. It starts at the root
 * TrieNode and traverses down the Trie, popping off the nodes of the
 * stack until it finds a node that has other children or is the end
 * of a word. It then deletes the nodes below that node and decrements
 * the size of the Trie.
 */
int Trie::remove(std::string word) {
    std::stack<TrieNode*> node_stack;
    TrieNode* node = root;
    for (size_t i = 0; i < word.size(); i++) {
        if (node->children[(unsigned char)word[i]] == nullptr)
            return -1;
        node = node->children[(unsigned char)word[i]];
        node_stack.push(node);
    }
    node->is_end_of_word = false;
    bool found = false;
    TrieNode *last = nullptr;
    while (!node_stack.empty() && !found) {
        TrieNode* temp = node_stack.top();
        node_stack.pop();
        for (int i = 0; i < 256; i++) {
            if (!(temp->children[i] == nullptr || temp->children[i] == last) || temp->is_end_of_word) {
                found = true;
                break;
            }
        }
        if (!found)
            delete temp;
        last = temp;
    }
    size--;
    return 0;
}

/**
 * Checks if a word is contained in the Trie.
 *
 * \param word The word to check.
 * \return \c true if the word is contained in the Trie and \c false otherwise.
 *
 * This function traverses down the Trie, following the path defined by
 * the characters of the word. If it reaches the end of the word and the
 * node is marked as the end of a word, then the word is contained in the
 * Trie. Otherwise, the word is not contained in the Trie.
 */
bool Trie::contains(std::string word) {
    TrieNode* node = root;
    for (size_t i = 0; i < word.size(); i++) {
        if (node->children[(unsigned char)word[i]] == nullptr)
            return false;
        node = node->children[(unsigned char)word[i]];
    }
    return node->is_end_of_word;
}

/**
 * Returns the size of the Trie.
 *
 * \return The number of words in the Trie.
 */
size_t Trie::getSize() const {
    return size;
}