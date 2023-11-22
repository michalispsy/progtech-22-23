#include <iostream>  

using namespace std;  


int main() {  

    int N, M, u, v; 
    int per=0;   

    cin>>N;  
    cin>>M;  

    int korifes[N];  

    for (int i=0; i<N; i++) 
    {  
        korifes[i]=0;  
    }  

    for(int i=0; i<M; i++)
    {
        cin >> u >> v;
        korifes[u]++;
        korifes[v]++;
    }

    for (int i=0; i<N; i++) 
    {  
        if(korifes[i]%2 != 0)
        {
            u = v;
            v = i;
            per++;  
        }
    }  

    if(per == 0) 
    {
        cout << "CYCLE" << endl; 
        return 0;
    }

    if(per != 2) 
    {
        cout << "IMPOSSIBLE" << endl; 
        return 0;
    }
    
    cout << "PATH ";

    if(u < v) cout << u << ' ' << v << endl;
    else cout << v << ' ' << u << endl;
    return 0;
}
