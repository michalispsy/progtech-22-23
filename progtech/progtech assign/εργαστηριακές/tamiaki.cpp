#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class purchase
{
public:
    purchase() {};
    ~purchase() {};

    void add(string prod, int price) 
    {
        tamio[prod].push_back(price);
        return;
    };

    void make_apodixi () 
    {
        for(const auto & prod : tamio) 
        {
            int sum = 0;
            int size = prod.second.size();
            for(int i=0; i<prod.second.size(); i++)
            {
                sum += prod.second[i];
            }

            apodixi[prod.first].push_back(size);
            apodixi[prod.first].push_back(sum);
        }
    };

    friend ostream& operator << (ostream &out, const purchase &l)
    {
        for(const auto & prod : l.apodixi)
        {
            cout << prod.first << ' ' << prod.second[0] << " x " << prod.second[1] / prod.second[0]
                 << " = " << prod.second[1] << endl; 
        }
        return out;
    };

private:
    unordered_map<string,vector<int>> tamio;
    unordered_map<string,vector<int>> apodixi;
};

int main() 
{
    string c = {};
    int price = 0;
    purchase t;
    while(cin >> c >> price) {t.add(c,price);}
    t.make_apodixi();
    cout << t;
}
