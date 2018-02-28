#include "Yahtzee.h"
#include "Player.h"
#include "HumanPlayer.h"

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int get_num_players();
Player *get_player(int &);
void high_scores(Player **, int);

//	MAIN
int main()
{
    Yahtzee dice;
    int num_players = get_num_players();

    Player **players = new Player*[num_players];
    for(int i = 0; i < num_players; i++)
    {
        players[i] = get_player(i);
    }

    bool done = false;
    while(!done)
    {
        done = true;
        for(int i = 0; i < num_players; i++)
        {
            dice.pass();
            if(!players[i]->done())
            {
                done = false;
                cout << players[i];
                players[i]->turn(dice);
            }
        }
    }

    cout << "\n*******************************************************\n\n"
         << "  Final Scores:\n\n";
    for(int i = 0; i < num_players; i++)
        cout << setw(Player::NAME_SIZE) <<  players[i]->name()
             << ": " << players[i]->score() << "\n";
    cout << "\n*******************************************************\n\n";

    high_scores(players, num_players);

    for(int i = 0; i < num_players; i++)
    {
        delete players[i];
    }
    delete[] players;
}

int get_num_players()
{
    int num_players = 0;
    while(num_players < 1 || num_players > 6)
    {
        cout << "\nHow Many Players? ";
        cin >> num_players;
        if(num_players < 1)
        {
            cout << "\n\t** Not Enough **\n";
        }
        if(num_players > 6)
        {
            cout << "\n\t** Too Many **\n";
        }
    }
    return num_players;
}

Player *get_player(int &i)
{
    Player *player;
    char name[Player::NAME_SIZE];

    cout << "\nEnter a Name for Player " << i + 1
         << " (up to " << Player::NAME_SIZE - 1 << " letters): ";
    cin >> name;
    cin.ignore(6, '\n');

    player = new HumanPlayer(name);
    return player;
}

void high_scores(Player **players, int num_players)
{
    cout << "Score not saved...\n";
}
