/**
 *  Author: Neeecu
 *  Data structure: Trie
 */
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    int wordCnt;

    TrieNode() : wordCnt(0) {}
};

struct Trie {
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string s) {
        TrieNode* curr = root;
        for (int i = 0; i < s.length(); i++) {
            if (curr->children.find(s[i]) == curr->children.end()) {
                curr->children[s[i]] = new TrieNode();
            }
            curr = curr->children[s[i]];
        }

        curr->wordCnt++;
    }

    void remove(string s) {
        _remove(s, 0, root);
    }

    bool _remove(string s, int i, TrieNode* curr) {
        if (i == s.length()) {
            curr->wordCnt--;
            return (curr->wordCnt == 0 and curr->children.size() == 0);
        }
        TrieNode* node = curr->children[s[i]];
        bool should_remove = _remove(s, i + 1, node);

        if (should_remove) {
            curr->children.erase(s[i]);
            return (curr->wordCnt == 0 and curr->children.size() == 0 and curr != root);
        }
        return false;
    }

    int count(string s) {
        TrieNode* curr = root;
        for (int i = 0; i < s.length(); i++) {
            if (curr->children.find(s[i]) == curr->children.end()) {
                return 0;
            }
            curr = curr->children[s[i]];
        }

        return curr->wordCnt;
    }

    int longest_prefix(string s) {
        TrieNode* curr = root;
        for (int i = 0; i < s.length(); i++) {
            if (curr->children.find(s[i]) == curr->children.end())
                return i;
            curr = curr->children[s[i]];
        }

        return s.length();
    }
};
