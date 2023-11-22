#include <iostream>
using namespace std;

template <typename T>
class stack {
public:
    stack (int size)
    { 
        array_size = size;
        head = new T[array_size];
    }

    stack (const stack &s) 
    {
        array_size = s.array_size;
        head = new T[array_size];
        cur_size = s.cur_size;
        for(int i=0; i<cur_size; i++)
        {
            head[i] = s.head[i];
        }
    }

    ~stack ()
    {
        delete [] head;
    }

    const stack & operator = (const stack &s) 
    {
        delete [] head;
        head = new T[s.array_size];

        for(int i=0; i<s.cur_size; i++)
        {
            head[i] = s.head[i];
        }
        cur_size = s.cur_size;

        return *this;
    }

    bool empty () const
    {
        if(cur_size == 0) return true;
        return false;
    }

    void push (const T &x) 
    {
        head[cur_size++] = x;
    }

    T pop () 
    {
        return head[--cur_size];
    }

    int size () 
    {
        return cur_size;
    }

    friend ostream & operator << (ostream &out, const stack &s) 
    {
        cout << '[';
        if(!s.empty())
        {   
            for(int i=0; i<s.cur_size-1; i++)
            {
                cout << s.head[i]<< ", ";
            }
            cout << s.head[s.cur_size-1];
        }
        cout << ']';
        return out;
    }

private:
    int array_size;
    int cur_size = 0;
    T *head = nullptr;
};


/*
#ifndef CONTEST
int main () {
// let’s play with integers...
stack<int> s(10);
cout << "s is empty: " << s << endl;
s.push(42);
cout << "s has one element: " << s << endl;
s.push(17);
s.push(34);
    cout << "s has more elements: " << s << endl;
    cout << "How many? " << s.size() << endl;
    stack<int> t(5);
    t.push(7);
    cout << "t: " << t << endl;
    t = s;
    cout << "popping from s: " << s.pop() << endl;

    s.push(8);
    stack<int> a(s);
    t.push(99);
    a.push(77);
    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    cout << "a: " << a << endl;
    // now with doubles...
    stack<double> c(4);
    c.push(3.14);
    c.push(1.414);
    cout << "c contains doubles " << c << endl;
    // and with characters...
    stack<char> k(4);
    k.push('$');
    cout << "k contains a character " << k << endl;
}
#endif
*/