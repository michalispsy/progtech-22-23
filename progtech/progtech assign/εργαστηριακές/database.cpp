#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


struct worker
{
  int id = 0;
  string name;
  string surname;
  int birthday = 0;
  int salary = 0;
};

bool asc = true;

bool comp_id (const worker & o1, const worker & o2 )
{
  return (o1.id < o2.id);
}

bool comp_name (const worker & o1, const worker & o2 )
{
  if((o1.surname + o1.name) == (o2.surname + o2.name))
  {
    if(asc) return (o1.id < o2.id);
            return (o1.id > o2.id);
  }
  return ((o1.surname + o1.name) < (o2.surname + o2.name));
}

bool comp_birthday (const worker & o1, const worker & o2 )
{
  if(o1.birthday == o2.birthday){
    if(asc) return (o1.id < o2.id);
            return (o1.id > o2.id);
  }
  return (o1.birthday < o2.birthday);
}

bool comp_salary (const worker & o1, const worker & o2 )
{
  if(o1.salary == o2.salary){
    if(asc) return (o1.id < o2.id);
            return (o1.id > o2.id);
  }
  return (o1.salary < o2.salary);
}

int main()
{
  vector<worker> database;
  int N, M;
  cin >> N;

  for(int i=0; i<N; i++)
  {
    worker temp;
    cin >> temp.id >> temp.name >> temp.surname >> temp.birthday >> temp.salary;
    database.push_back(temp);
  }

  cin >> M;
  for(int i=0; i<M; i++)
  {
    string type = {};
    string order = {};
    int num = 0;
    cin >> type >> order >> num;

    if(order == "asc") asc = true;
    else asc = false;

    if(type == "id") sort(database.begin(), database.end(), comp_id);
    if(type == "name") sort(database.begin(), database.end(), comp_name);
    if(type == "year") sort(database.begin(), database.end(), comp_birthday);
    if(type == "salary") sort(database.begin(), database.end(), comp_salary);

    cout << "Query: " << type << ' ' << order << ' ' << num << endl;

    if(order == "asc")
    {
       for(int m=0; m<num; m++)
       {
         cout << database[m].id << ' ' << database[m].name << ' ' << database[m].surname << ' '
              << database[m].birthday << ' ' << database[m].salary << endl;
       }

    }

     if(order == "desc")
     {
        for(int m=database.size()-1; m > database.size() -1 - num; m--)
        {
          cout << database[m].id << ' ' << database[m].name << ' ' << database[m].surname << ' '
               << database[m].birthday << ' ' << database[m].salary << endl;
        }

     }
  }
}


