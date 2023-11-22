#include <iostream>
#include <vector>

using namespace std;

int main () 
{
    int c;
    vector<int> nums;
    while(cin >> c)
    {
        nums.push_back(c);
    }

    cout << "{ ";
    for(int i=0; i < nums.size(); i++)
    {
        cout << nums[i] << ", ";
    }

    cout << '}';
} 