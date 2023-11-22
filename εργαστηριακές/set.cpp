#include <set>
#include <map>
#include <iostream>

using namespace std;

struct offer {
string supplier;
double price;
};

typedef map<string, set<offer>> bids;

bool operator< (const offer & o1, const offer & o2) {
return (o1.price < o2.price);
}

int main ()
{   
    bids receivedOffers = {};
    offer currentOffer = {"sofia_ae", 100};
    receivedOffers["potatoes"].insert(currentOffer);
    receivedOffers["potatoes"].insert({"mixalis_ae", 30});
    receivedOffers["dildos"].insert({"sofia_ae", 125});
    
    bids::iterator p;
    p = receivedOffers.find("potatoes");

    for (const auto & iitem:receivedOffers) {
        cout << iitem.first << ":" << endl;
        for (const auto & sofia : iitem.second)
            cout << " " << sofia.supplier << " " << sofia.price << endl;
    }

    map<string, set<string>> supps = {};   
    
    for (const auto & iitem:receivedOffers) {
        for (const auto & companies : iitem.second)
            supps[companies.supplier].insert(iitem.first); 
    }

    for(const auto & companies:supps)
    {
        cout << companies.first << ":" << endl;
        for(const auto & products: companies.second)
        {
            cout << ' ' << products << endl;
        }
    }
}