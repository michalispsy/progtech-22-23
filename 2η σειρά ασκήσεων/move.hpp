#include <iostream>
#include <stdexcept>

using namespace std;


class Move {
public:
// Take sc coins from heap sh and put tc coins to heap th.
    Move(int sh, int sc, int th, int tc);

    int getSource() const;
    int getSourceCoins() const;
    int getTarget() const;
    int getTargetCoins() const;

    friend ostream & operator << (ostream &out, const Move &move);

private:
    int s_h = 0, s_c = 0, 
        t_h = 0, t_c = 0;

};

Move::Move(int sh, int sc, int th, int tc) : s_h(sh), s_c(sc),
                                             t_h(th), t_c(tc) {}

int Move::getSource() const 
{
    return s_h;
}


int Move::getSourceCoins() const
{
    return s_c;
}

int Move::getTarget() const
{
    return t_h;
}

int Move::getTargetCoins() const
{
    return t_c;
}

ostream& operator<<(ostream &out, const Move &move) 
{
    cout << "takes " << move.s_c << " coins from heap "
         << move.s_h <<  " and puts ";
    if(move.t_c == 0) cout << "nothing";
    else cout << move.t_c << " coins to heap " << move.t_h;
    return out;
}

class State {
public:
// State with h heaps, where the i-th heap starts with c[i] coins.
// A total of n players are in the game, numbered from 0 to n-1,
// and player 0 is the first to play.
    State(int h, const int c[], int n);
    ~State();

    void next(const Move &move); //throw(logic_error);
    bool winning() const;

    int getHeaps() const;
    int getCoins(int h) const; //throw(logic_error);

    int getPlayers() const;
    int getPlaying() const;

    friend ostream & operator << (ostream &out, const State &state);

    private:
    int heaps = 0, players = 0, *coins = nullptr;
    static int cur_player;
    int s_h = 0, s_c = 0, 
        t_h = 0, t_c = 0;
};

int State::cur_player = 0;

State::State(int h, const int c[], int n)  
{
    heaps = h;
    players = n;
    coins = new int[heaps];

    for(int i=0; i < heaps; i++)
    {
        coins[i] = c[i];
    }
}

State::~State() 
{
    delete [] coins;
}

void State::next(const Move &move) // throw(logic_error) 
{   
    s_h = move.getSource();
    s_c = move.getSourceCoins();
    t_h = move.getTarget();
    t_c = move.getTargetCoins();
    
    //logic errors
    if ( s_h < 0 || s_h >= heaps) throw logic_error("invalid source heap");
    if ( t_h < 0 || t_h >= heaps) throw logic_error("invalid target heap");
    if (coins[s_h] < s_c) throw logic_error("not enough coins");
    if ( t_c >= s_c) throw logic_error("wrong coins");


    cur_player = (cur_player + 1) % players; 
    coins[s_h] -= s_c;
    coins[t_h] += t_c;
}

bool State::winning() const 
{
    bool won = true;
    for(int i = 0; i < heaps; i++)
    {
        if(coins[i] != 0) won = false;
    }
    return won;
}

int State::getHeaps() const 
{
    return heaps;
}

int State::getCoins(int h) const // throw(logic_error) 
{
    if ( h < 0 || h >= heaps) throw logic_error("invalid heap");
    return coins[h];
}

int State::getPlayers() const 
{
    return players;
}

int State::getPlaying() const 
{
    return cur_player;
}

ostream & operator << (ostream &out, const State &state) 
{
    for(int i=0; i < state.heaps - 1; i++)
    {
        cout << state.coins[i] << ", ";
    }
    cout << state.coins[state.heaps - 1] << " with " << state.cur_player
         << '/' << state.players << " playing next";
    return out;
}

/*
int main() {
    Move t(1,3,2,1);
    Move s(0,10,0,0);
    Move r(1,6,2,2);
    Move z(2,8,2,3);
    Move x(2,3,0,0);
    cout << t << endl << s << endl;
    
    int test[3] = {10, 9 , 5};
    State first(3, test, 4);
    cout << first << endl;
    first.next(t);
    cout << first << endl;
    first.next(s);
    cout << first << endl << first.winning() << endl;
    first.next(r);
    cout << first << endl << first.winning() << endl;
    first.next(z);
    cout << first << endl << first.winning() << endl;
    first.next(x);
    cout << first << endl << first.winning() << endl;

    cout << "-----------------" << endl 

    << first.getHeaps() << endl << first.getCoins(1);
}
*/
