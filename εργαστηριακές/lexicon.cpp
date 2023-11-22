#include <set>
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    map<int,set<string>> lexico;
    map<string, int> numbering;
    int N, D;
    int location;
    string word;
    cin >> N >> D;
    
    for(int i=0; i < N; i++)
    {
        cin >> location >> word;
   
        map<int,set<string>>::iterator p;
        p = lexico.find(location);

        if(p != lexico.end() && p->second.find(word) != p->second.end()) continue;

        lexico[location].insert(word);
        numbering[word]++;
    }

    int max_size = 0;
    int max_lex = 0;
    for(const auto & lex:lexico)
    {
        if(lex.second.size() > max_size) 
        {
            max_size = lex.second.size();
            max_lex = lex.first;
        }
    }
    
    cout << "largest dictionary is " << max_lex << " with " << max_size << " word(s)" << endl;
    set<string> everyware_words;
    for(const auto & num_words:numbering)
    {
        if(num_words.second == D) everyware_words.insert(num_words.first);
    }

    for(const auto & i:everyware_words)
    {
        cout << i << endl;
    }

    cout << everyware_words.size() << " word(s) appear in all dictionaries" << endl;

}
