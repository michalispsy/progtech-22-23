#include <map>
#include <set>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

struct classcomp {
  bool operator() (const string & o1, const string & o2)  {
    if(o1.length() == o2.length()) return (o1 < o2);
    return (o1.length() < o2.length());
}
};

int main() 
{
    map<char, int> wordcount;
    map<char, set<string, classcomp>> dictionary;

    string c;

    while(cin >> c)
    {
        wordcount[c.front()]++;
        dictionary[c.front()].insert(c);
    }
    
    for(auto letter:dictionary)
    {       
            //sort(letter.second.begin(), letter.second.end(), cmp);

            cout << letter.first << ": " << wordcount[letter.first] << " word(s), " << letter.second.size()
                 <<  " unique word(s), longest '" << *letter.second.rbegin() << "' and shortest '" << *letter.second.begin()
                 << "'" << endl;
    }
}