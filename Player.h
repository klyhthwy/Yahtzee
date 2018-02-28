#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Yahtzee.h"
#include "Score.h"
#include <iostream>

class Player
{
public:

    enum Contants
    {
        CHANCE = 0,
        ACE = 1,
        THREE_KIND = 7,
        FOUR_KIND = 8,
        FULL_HOUSE = 9,
        SM_STRAIGHT = 10,
        LG_STRAIGHT = 11,
        YAHTZEE = 12,
        NUM_SCORES = 13,
        NAME_SIZE = 25
    };

    Player(char *);
    virtual ~Player();

    virtual void turn(Yahtzee &) = 0;
    int score() const;
    bool done() const;
    const char *name() const;
    void display(std::ostream &) const;

protected:

    Player(const Player &);
    Player &operator=(const Player &);

    bool set_score(const Yahtzee &, char);
    bool set_score(Score &, int);
    bool invalid() const;
    int upper() const;
    int bonus() const;
    int lower() const;
    char *copy_name(char *) const;
    void upper(std::ostream &) const;
    void lower(std::ostream &) const;

    char *name_;
    Score scores_[NUM_SCORES];
    int yahtzee_bonuses_;
};

std::ostream &operator<<(std::ostream &, Player *);

#endif