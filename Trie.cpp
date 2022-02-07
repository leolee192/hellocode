
template <
    class charT,
    charT StartAlpha,
    int AlphaNum
>
class BasicTrie {
public:
    class TrieNode {
    public:
        TrieNode() {
            flag = false;
            for (int i = 0; i < AlphaNum; i++) {
                next[i] = nullptr;
            }
        }

#ifndef MY_NO_DETOR
        ~TrieNode() {
            for (int i = 0; i < AlphaNum; i++) {
                if (next[i] != nullptr) {
                    delete next[i];
                }
            }
        }
#endif // MY_NO_DETOR

        bool flag;
        TrieNode *next[AlphaNum];
    };

    BasicTrie() {
        root = new TrieNode();
    }

#ifndef MY_NO_DETOR
    ~BasicTrie() {
        if (root != nullptr) {
            delete root;
        }
    }
#endif // MY_NO_DETOR

    void insert(basic_string<charT> word) {
        TrieNode *p = root;
        for (int i=0; i<word.length(); ++i) {
            char e = word[i];
            int index = e - StartAlpha;
            if (p->next[index] == nullptr) p->next[index] = new TrieNode();
            p = p->next[index];
        }
        p->flag = true;
    }

    bool search(basic_string<charT> word) {
        TrieNode *p = root;
        for (int i=0; i<word.length(); ++i) {
            char e = word[i];
            int index = e - StartAlpha;
            if (p->next[index] == nullptr) return false;
            p = p->next[index];
        }
        return p->flag;
    }

    bool startsWith(basic_string<charT> prefix) {
        TrieNode *p = root;
        for (int i=0; i<prefix.length(); ++i) {
            char e = prefix[i];
            int index = e - StartAlpha;
            if (p->next[index] == nullptr) return false;
            p = p->next[index];
        }
        return true;
    }

private:
    TrieNode *root;
};

typedef BasicTrie<char, 'a', 26> Trie;
