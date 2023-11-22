#include <iostream>
#include <string>

using namespace std;

class lexicon {
    
private:

    struct node{
    node *left = nullptr;
    node *right = nullptr;
    string word = {};
    int cnt = 0;
    };
    node *root = nullptr;

    node find(const string &s);

    static void inorder(ostream &out, const node &p)
    {
        if(p.left != nullptr)
        {
            inorder(out, *p.left);
        } 

        cout << p.word << " " << p.cnt << endl;

        if(p.right != nullptr)
        {
            inorder(out, *p.right);
        }

        return;
    }

    void remove(const string & s)  
    {  
        root = remove(root,s);
    }  

    node* minVal(node* root)  
    {  
        node* temp = root;  
        while(temp->left != nullptr)  
            temp = temp->left;  
        return temp;  
    } 

    node* remove(node* root, const string &s)  
    {  
        if(root==nullptr)  
            return root;  

        if(s<root->word)  
            root->left = remove(root->left,s);  
        
        else if(s>root->word)  
            root->right = remove(root->right,s);  
        
        else   
        {  
            if(root->left==nullptr)  
            {  
                node* temp= root->right;  
                delete root;  
                return temp;  
            }  
            if(root->right==nullptr)  
            {  
                node* temp = root->left;  
                delete root;  
                return temp;  
            }  

        node* temp = minVal(root->left);  
        root->word=temp->word;  
        root->cnt=temp->cnt;  
        root->left=remove(root->left,temp->word);  
        }

        return root;  
    }


public:
    lexicon() {};
    ~lexicon() {};

    void insert(const string &s, int num = 1);
    int lookup(const string &s) const;
    int depth(const string &s);
    void replace(const string &s1, const string &s2);

    friend ostream & operator << (ostream &out, const lexicon &l)
    {
        inorder(out, *l.root);
        return out;
    };
};

void lexicon::insert(const string &s,int num)
{
    if(root == nullptr)
    {
        root = new node;
        root->left = nullptr;
        root->right = nullptr;
        root->word = s;
        root->cnt = num;
        return;
    }
    
    node *p = root;
    node *q = nullptr;

    while(true)
    {
        q = p;

        if(p->word == s) 
        {
            p->cnt = p->cnt + num;
            return;
        }

        if(p->word > s) 
        {   
            p = p->left;
            if(p == nullptr)
            {
                p = new node;
                p->word = s;
                p->cnt = num;
                p->left = nullptr;
                p->right = nullptr;

                q->left = p;
                return;
            }
        }
        else if(p->word < s) 
        {
            p = p->right;
            if(p == nullptr)
            {
                p = new node;
                p->word = s;
                p->cnt = num;
                p->left = nullptr;
                p->right = nullptr;

                q->right = p;
                return;
            }
        }
    }
}

int lexicon::lookup(const string &s) const
{
    node *q = root;
    while(q != nullptr)
    {
        if(q->word == s) return q->cnt;

        if(q->word > s)
        {
            q = q->left;
        }
        else if
        (q->word < s)
        {
            q = q->right;
        }
    }

    return 0;
}

int lexicon::depth(const string &s)
{
    node *l = root;
    int dep = 0;

    while(l != nullptr)
    {
        if(l->word == s) return dep;

        if(l->word > s)
        {
            l = l->left;
            dep++;
        }
        else if(l->word < s)
        {
            l = l->right;
            dep++;
        }
    }
    
    return -1;
}

void lexicon::replace(const string &s1, const string &s2)
{
    node *q = root;
    node *p = nullptr;
    bool left = false;

    while(true)
    {
        if(q == nullptr) 
        {
            return;
        }

        p = q;
        
        if(q->word == s1) break;

        if(q->word > s1)
        {
            q = q->left;
            left = true;
        }

        if(q->word < s1)
        {
            q = q->right;
            left = false;
        }
    }

    insert(s2, q->cnt);
    remove(s1);
    return;
}

/*
int main() 
{
    lexicon l;
    string word;
    string pastword = "a";
    while(cin >> word)
    {
        l.insert(word);
        cout << word << " has been inserted at depth " << l.depth(word) << " this many times " << l.lookup(word) << endl;
        cout << "replace " << word << "with "<< pastword << endl;
        l.replace(word, pastword);
        cout << "noproblem";
        pastword = word;
    }
    cout << l;
}
*/