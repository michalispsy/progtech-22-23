#include <stack>
#include <queue>
#include <iostream>

using namespace std;

int main () 
{
    int N = 0;
    cin >> N;

    stack<int> s = {};
    queue<int> q = {};

    for(int i = 0; i < N; i++)
    {
        int num;
        cin >> num;
        q.push(num); 
    }

    char c = getchar();
    while(c != EOF)
    {
        if(c == 'S')
        {
            if(s.empty())
            {
                cout << "error" << endl;
                return 0;
            }

            q.push(s.top());
            s.pop();
        }

        if(c == 'Q')
        {
            if(q.empty())
            {
                cout << "error" << endl;
                return 0;
            }
             
            s.push(q.front());
            q.pop();
        }

        if(c == 'P')
        {
            queue<int> temp = q;
            for(int i=0; i<q.size(); i++)
            {
                if (i == q.size() - 1)
                {
                    cout << temp.front() << endl;
                    break;
                }
                
                cout << temp.front() << ' ' ;
                temp.pop();
            }
        }
        c = getchar();
    }
}