#include "Player.h"
#include "Yahtzee.h"
#include <iomanip>

Player::Player(char *name):
    name_(copy_name(name)), yahtzee_bonuses_(0)
{}

Player::~Player()
{
    delete name_;
}

int Player::score() const
{
    return upper() + bonus() + lower();
}

bool Player::done() const
{
    for(int i = 0; i < NUM_SCORES; i++)
        if(!scores_[i])
        {
            return false;
        }
    return true;
}

const char *Player::name() const
{
    return name_;
}

bool Player::set_score(const Yahtzee &dice, char c)
{
    switch(c)
    {
        case 'a':
        case 'A':
        case '1':
            return set_score(scores_[ACE], dice.total(ACE));
        case '2':
            return set_score(scores_[2], dice.total(2));
        case '3':
            return set_score(scores_[3], dice.total(3));
        case '4':
            return set_score(scores_[4], dice.total(4));
        case '5':
            return set_score(scores_[5], dice.total(5));
        case '6':
            return set_score(scores_[6], dice.total(6));
        case 't':
        case 'T':
            return set_score(scores_[THREE_KIND], dice.kind(3));
        case 'f':
        case 'F':
            return set_score(scores_[FOUR_KIND], dice.kind(4));
        case 'h':
        case 'H':
            return set_score(scores_[FULL_HOUSE], dice.full_house());
        case 's':
        case 'S':
            return set_score(scores_[SM_STRAIGHT], dice.straight(Yahtzee::SM_STRAIGHT));
        case 'l':
        case 'L':
            return set_score(scores_[LG_STRAIGHT], dice.straight(Yahtzee::LG_STRAIGHT));
        case 'y':
        case 'Y':
            return set_score(scores_[YAHTZEE], dice.yahtzee());
        case 'c':
        case 'C':
            return set_score(scores_[CHANCE], dice.total());
        default:
            return invalid();
    }
}

bool Player::set_score(Score &score, int value)
{
    if(!score)
    {
        score = Score(value);
        return true;
    }
    return invalid();
}

bool Player::invalid() const
{
    std::cout << "\n\t** Invalid Choice **\n";
    return false;
}

int Player::upper() const
{
    int score = 0;
    for(int i = ACE; i < THREE_KIND; i++)
    {
        score += scores_[i]();
    }
    return score;
}

int Player::bonus() const
{
    if(upper() >= Yahtzee::BONUS)
    {
        return Yahtzee::BONUS_SCORE;
    }
    return 0;
}

int Player::lower() const
{
    int score = 0;
    for(int i = THREE_KIND; i < NUM_SCORES; i++)
    {
        score += scores_[i]();
    }
    score += scores_[CHANCE]();
    score += yahtzee_bonuses_ * Yahtzee::YAHTZEE * 2;
    return score;
}

char *Player::copy_name(char *name) const
{
    char *temp = new char[NAME_SIZE];
    for(int i = 0; i < NAME_SIZE; i++)
    {
        temp[i] = name[i];
    }
    temp[NAME_SIZE - 1] = '\0';
    return temp;
}

void Player::display(std::ostream &out) const
{
    out << std::right << "________________________________________________\n"
        << "________________________________________________\n\n\t"
        << name_ << ":"
        << "\n\t\t___________________";

    upper(out);
    out << "\n\t\t              -----"
        << "\n\t\tSubtotal      :" << std::setw(4) << upper()
        << "\n\t\tBonus         :" << std::setw(4) << bonus()
        << "\n\t\t              -----"
        << "\n\t\tUpper Section :" << std::setw(4) << upper() + bonus()
        << "\n\t\t___________________";

    lower(out);
    out << "\n\t\tYAHTZEE BONUS :" << std::setw(4) << yahtzee_bonuses_ * Yahtzee::YAHTZEE * 2
        << "\n\t\t              -----"
        << "\n\t\tLower Section :" << std::setw(4) << lower()
        << "\n\t\tUpper Section :" << std::setw(4) << upper() + bonus()
        << "\n\t\t              -----"
        << "\n\t\tGrand Total   :" << std::setw(4) << score();
}

void Player::upper(std::ostream &out) const
{
    out << "\n\t\tAces          :" << scores_[ACE]
        << "\n\t\tTwos          :" << scores_[2]
        << "\n\t\tThrees        :" << scores_[3]
        << "\n\t\tFours         :" << scores_[4]
        << "\n\t\tFives         :" << scores_[5]
        << "\n\t\tSixes         :" << scores_[6];
}

void Player::lower(std::ostream &out) const
{
    out << "\n\t\t3 of a Kind   :" << scores_[THREE_KIND]
        << "\n\t\t4 of a Kind   :" << scores_[FOUR_KIND]
        << "\n\t\tFull House    :" << scores_[FULL_HOUSE]
        << "\n\t\tSm Straight   :" << scores_[SM_STRAIGHT]
        << "\n\t\tLg Straight   :" << scores_[LG_STRAIGHT]
        << "\n\t\tYAHTZEE       :" << scores_[YAHTZEE]
        << "\n\t\tChance        :" << scores_[CHANCE];
}

std::ostream &operator<<(std::ostream &out, Player *player)
{
    player->display(out);
    return out;
}