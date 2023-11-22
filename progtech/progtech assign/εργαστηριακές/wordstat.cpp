#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;


bool cmp (string o1, string o2)  {
    if(o1.length() == o2.length()) return (o1 < o2);
    return (o1.length() < o2.length());
}

int main() 
{
    map<char, int> wordcount;
    map<char, vector<string>> dictionary;

    string c;

    while(cin >> c)
    {
        if( find(dictionary[c.front()].begin(), dictionary[c.front()].end() , c) 
        == dictionary[c.front()].end()) wordcount[c.front()]++;

        dictionary[c.front()].push_back(c);
    }
    
    for(auto letter:dictionary)
    {       
            sort(letter.second.begin(), letter.second.end(), cmp);

            cout << letter.first << ": " << letter.second.size() << " word(s), " << wordcount.find(letter.first)->second
                 <<  " unique word(s), longest '" << letter.second.back() << "' and shortest '" << letter.second.front()
                 << "'" << endl;
    }
}