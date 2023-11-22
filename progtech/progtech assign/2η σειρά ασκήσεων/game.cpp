#include <iostream>
#include <stdexcept>
//#include "move.hpp"
//#include "player.hpp"

using namespace std;

class Game {
public:
    Game(int heaps, int players): total_heaps(heaps), total_players(players) 
    {
        all_heaps = new int [total_heaps];
        all_players = new Player *[total_players];
    };

    ~Game(){};

    void addHeap(int coins); //throw(logic_error);
    void addPlayer(Player *player); //throw(logic_error);
    void play(ostream &out); //throw(logic_error);

    int getPlayers() const;
    const Player *getPlayer(int p) const
    {
        if ( total_players <= p) throw logic_error("non existing player");
        return all_players[p];
    }

private:
    int total_heaps, total_players;
    int added_h = 0, added_p = 0;
    int *all_heaps;
    Player **all_players;
};

void Game::addHeap(int coins) 
{
    if ( coins < 0 ) throw logic_error("negative coins");
    if ( added_h >= total_heaps) throw logic_error("too many heaps");

    all_heaps[added_h++] = coins;
}

void Game::addPlayer(Player *player)
{
    if ( added_p >= total_players) throw logic_error("too many players");

    all_players[added_p++] = player;
}

int Game::getPlayers() const
{
    return total_players;
}

void Game::play(ostream &out)
{
    State game(total_heaps, all_heaps, total_players);
    int prev_player = 0;

    while(!game.winning())
    {
        prev_player = game.getPlaying();
        cout << "State: " << game << endl;
        cout << *all_players[game.getPlaying()] << ' '
             << all_players[game.getPlaying()]->play(game) << endl;
        game.next(all_players[game.getPlaying()]->play(game));

    }

    cout << "State: " << game << endl;
    cout << *all_players[prev_player] << " wins" << endl;

}

/*
int main() 
{
    Game specker(3, 4);
    specker.addHeap(10);
    specker.addHeap(20);
    specker.addHeap(17);
    specker.addPlayer(new SneakyPlayer("Tom"));
    specker.addPlayer(new SpartanPlayer("Mary"));
    specker.addPlayer(new GreedyPlayer("Alan"));
    specker.addPlayer(new RighteousPlayer("Robin"));
    specker.play(cout);
}
*/