#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <Windows.h>

using namespace std;
struct Node
{
    bool isend;
    Node* m[36];
    Node()
    {
        isend = false;
        for (int i = 0;i < 36;i++)
        {
            m[i] = nullptr;
        }
    }
    ~Node()
    {
        for (int i = 0;i < 36;i++)
            if (m[i] != nullptr)
                delete m[i];
    }
};
class Trie
{
    Node* root;
public:
    Trie()
    {
        root = new Node();
    }
    void Insert(string s)
    {
        Node* p = root;
        for (int i = 0;i < s.size();i++)
        {
            int c;
            if (isalpha(s[i]))
                c = (int)s[i] - 'a';
            else
                c = (int)s[i] - '0' + 26;
            if (p->m[c] == nullptr)
                p->m[c] = new Node();
            p = p->m[c];
            if (i == s.size() - 1)
                p->isend = true;
        }
    }
    void Delete(string s)
    {
        Delete_True(s, 0, root);
    }
    bool Delete_True(string s,int k,Node * p)
    {
        if (k < s.size())
        {
            int c;
            if (isalpha(s[k]))
                c = (int)s[k] - 'a';
            else
                c = (int)s[k] - '0' + 26;
            if (p->m[c] == nullptr || Delete_True(s, k + 1, p->m[c]) == false)
                return false;
            p->m[c] = nullptr;
            delete p->m[c];
        }

        for (int i = 0;i < 36;i++)
            if (p->m[i] != nullptr)
                return false;
        return p->isend == false || k == s.size();
    }
    void Sbor_slov(vector<string> & k,Node * p,string s)
    {
        for (int i = 0;i < 36;i++)
        {
            if (p->m[i] != nullptr)
            {
                char c;
                if (i < 26)
                    c = 'a' + i;
                else
                    c = '0' + i - 26;
                Sbor_slov(k, p->m[i], s + c);
            }
        }
        if (p->isend)
            k.emplace_back(s);
    }
    void print()
    {
        vector<string> k;
        Sbor_slov(k, root, "");
        for (auto i : k)
        {
            cout << i << endl;
        }
    }
    void Podstroki(Trie * t)
    {
        vector<string> k;
        Sbor_slov(k, root, "");
        for (auto l : k)
        {
            for (int i = 0;i < l.size();i++)
            {
                for (int j = 1;j <= l.size() - i;j++)
                {
                    t->Insert(l.substr(i, j));
                }
            }
        }
        
    }
    void Chered()
    {
        vector<string> k;
        Sbor_slov(k, root, "");
        for (auto i : k)
        {
            char c_1 = i[0];
            char c_2 = i[1];
            bool f = true;
            for (int j = 0;j < i.size();j++)
            {
                if (j % 2 == 0)
                {
                    if (i[j] != c_1)
                        f = false;
                }
                else
                {
                    if (i[j] != c_2)
                        f = false;
                }
            }
            if (f)
                Delete(i);
        }
    }
    void Suffiks(string s)
    {
        int z = 0;
        vector<string> k;
        Sbor_slov(k, root, "");
        for (auto i : k)
        {
            bool flag = true;
            for (int j = 0;j < s.size();j++)
            {
                if (i[i.size() - 1 - j] != s[s.size() - 1 - j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                cout << i << endl;
                z++;
            }
        }
        cout << z << endl;
        
    }
    ~Trie()
    {
        delete root;
    }
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    Trie t;
    t.Insert("start90");
    t.Insert("90");
    t.Insert("abababab");
    t.Insert("13131313");
    t.Insert("rake");
    t.Insert("puki");
    //Trie p;
    //t.Podstroki(&p);
    // p.print();
   // t.Chered();
   // t.print();
    t.Suffiks("90");
    
}

