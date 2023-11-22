#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <set>
#include <utility>

using namespace std;

struct poi_info
{
    double x = 0;
    double y = 0;
};

double distance (const poi_info & point, double loc_x, double loc_y)
{
    return sqrt((point.x - loc_x)*(point.x - loc_x) + (point.y - loc_y)*(point.y - loc_y));
}

int main() 
{
    int N, K;
    map<string , vector<poi_info>> database;

    cin >> N;
    for(int i = 0; i < N; i++)
    {
        poi_info temp;
        string c;
        cin >> temp.x >> temp.y >> c;
        database[c].push_back(temp);
    }
    
    cin >> K;
    vector<pair<double, double>> positions;

    for(int i = 0; i<K; i++)
    {
        double locx, locy;
        cin >> locx >> locy;
        positions.push_back(make_pair(locx, locy));
    }

    for(const auto & set_position:positions)
    {
        map<string, set<double>> sorted_distances;
        
        cout << fixed << setprecision(0) << set_position.first << ' ' << set_position.second << endl;
        for(const auto & type:database)
        {
            for(const auto & poi:type.second)
            {
                double dist = distance(poi, set_position.first, set_position.second);
                sorted_distances[type.first].insert(dist);
            }

            cout << "  " << type.first << ' ' << fixed << setprecision(3) << *(sorted_distances[type.first].begin()) << endl;
        }
    }
}