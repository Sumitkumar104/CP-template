#include <iostream>
#include <string>
using namespace std;

class trieNode
{
public:
    trieNode *child[26];
    bool complete = false;

    trieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            child[i] = NULL;
        }
    }
};

class trie
{
    trieNode *root;

public:
    trie()
    {
        root = new trieNode();
    }

    void insert(string str)
    {
        trieNode *node = root;
        for (auto a : str)
        {
            if (node->child[a - 'a'] == NULL)
            {
                node->child[a - 'a'] = new trieNode();
            }
            node = node->child[a - 'a'];
        }
        node->complete = true;
    }

    // Check for the exact word in string, not prefix
    bool search(string str)
    {
        trieNode *node = root;
        for (auto a : str)
        {
            if (node->child[a - 'a'] != NULL)
            {
                node = node->child[a - 'a'];
            }
            else
            {
                return false;
            }
        }
        return node->complete;
    }

    // Check if the given string is a prefix of any word in the trie
    bool isprefix(string str)
    {
        trieNode *node = root;
        for (auto a : str)
        {
            if (node->child[a - 'a'] != NULL)
            {
                node = node->child[a - 'a'];
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};

int checkTemplete()
{
    trie t;
    t.insert("hello");
    t.insert("hell");
    t.insert("heaven");
    t.insert("goodbye");

    cout << boolalpha;
    cout << "Search for 'hello': " << t.search("hello") << endl;
    cout << "Search for 'hell': " << t.search("hell") << endl;
    cout << "Search for 'heaven': " << t.search("heaven") << endl;
    cout << "Search for 'goodbye': " << t.search("goodbye") << endl;
    cout << "Search for 'good': " << t.search("good") << endl;
    cout << "Prefix check for 'he': " << t.isprefix("he") << endl;
    cout << "Prefix check for 'good': " << t.isprefix("good") << endl;
    return 0;
}
