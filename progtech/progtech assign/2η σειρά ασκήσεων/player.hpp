#include <iostream>
#include <stdexcept>
//#include "move.hpp"

using namespace std;


class Player {
public:
    Player() {};
    Player(const string &n) : name(n) {};
    virtual ~Player() {};

    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player) 
    {
        cout << player.getType() << " player " << player.name;
        return out;
    }

    friend int findmax(int coins[], int indx);
    friend int findmin(int coins[], int indx);

protected:
    string name;
};

int findmax(int coins[], int indx)
{
    int cur_max = coins[0];
    int pos = 0;
    for(int i = 1; i < indx; i++)
    {
        if(coins[i] > cur_max)
        { 
            cur_max = coins[i]; 
            pos = i;
        }
    }
    return pos;
}

int findmin(int coins[], int indx)
{
    int cur_min = 2100000000;
    int pos = 0;
    for(int i = 0; i < indx; i++)
    {
        if(coins[i] < cur_min && coins[i] != 0) 
        {
            cur_min = coins[i];
            pos = i;
        }
    }
    return pos;
}

class GreedyPlayer:
    public Player {
    public:
        //constructor
        GreedyPlayer(const string &n) {
            name = n;
            type = "Greedy";
        }

        ~GreedyPlayer() {};

        const string & getType() const override 
        {
            return type;
        }

        Move play(const State &s) override 
        {
            int sze = s.getHeaps();
            int coins[sze];
            for(int i=0; i<sze; i++)
            {
                coins[i] = s.getCoins(i);
            }

            int pos = findmax(coins, sze);
            Move next_move(pos, s.getCoins(pos), 0 , 0);
            return next_move;
        }
    private: 
        string type;
};

class SpartanPlayer:
    public Player {
    public:
        //constructor
        SpartanPlayer(const string &n) {
            name = n;
            type = "Spartan";
        }

        ~SpartanPlayer() {};

        const string & getType() const override 
        {
            return type;
        }

        Move play(const State &s) override 
        {
            int sze = s.getHeaps();
            int coins[sze];
            for(int i=0; i<sze; i++)
            {
                coins[i] = s.getCoins(i);
            }

            int pos = findmax(coins , sze);
            Move next_move(pos, 1, 0 , 0);
            return next_move;
        }
    private:
        string type;
};

class SneakyPlayer:
    public Player {
    public:
        //constructor
        SneakyPlayer(const string &n) {
            name = n;
            type = "Sneaky";
        }

        ~SneakyPlayer() {};

        const string & getType() const override 
        {
            return type;
        }

        Move play(const State &s) override 
        {
            int sze = s.getHeaps();
            int coins[sze];
            for(int i=0; i<sze; i++)
            {
                coins[i] = s.getCoins(i);
            }

            int pos = findmin(coins, sze);
            Move next_move(pos, s.getCoins(pos), 0 , 0);
            return next_move;
        }
    private: 
        string type;
};

class RighteousPlayer:
    public Player {
    public:
        //constructor
        RighteousPlayer(const string &n) {
            name = n;
            type = "Righteous";
        }

        ~RighteousPlayer() {};

        const string & getType() const override 
        {
            return type;
        }

        Move play(const State &s) override 
        {
            int sze = s.getHeaps();
            int temp = sze;
            int coins[sze];
            for(int i=0; i<sze; i++)
            {
                coins[i] = s.getCoins(i);
                if(coins[i] == 0 && temp > i) temp = i;
            }

            int posmax = findmax(coins, sze);
            int posmin = findmin(coins, sze);
            if(temp < sze) posmin = temp;
            int c = s.getCoins(posmax);
            Move next_move(posmax, c / 2 + c % 2 , posmin , (c / 2 + c % 2) - 1);
            return next_move;
        }
    private:
        string type;
};

