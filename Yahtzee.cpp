#include "Yahtzee.h"
#include <cstdlib>

#include <ctime>

Yahtzee::Yahtzee()
{
    srand(time(NULL));
    for(int i = 0; i < rand() % 10 + 1; i++)
    {
        dice_[i].roll();
    }
}

int Yahtzee::total(int value) const
{
    int temp = 0;
    for(int i = 0; i < 5; i++)
        if(dice_[i]() == value || value == 0)
        {
            temp += dice_[i]();
        }
    return temp;
}

int Yahtzee::kind(int kind) const
{
    if(kind > 5)
    {
        return 0;
    }
    if(kind == 5)
    {
        return yahtzee();
    }
    for(int i = 0; i < 5; i++)
    {
        int matches = 0;
        for(int j = 0; j < 5; j++)
            if(dice_[i] == dice_[j])
            {
                matches++;
            }
        if(matches >= kind)
        {
            return total();
        }
    }
    return 0;
}

int Yahtzee::full_house() const
{
    Yahtzee temp(*this);
    temp.sort_dice();
    if(((temp.dice_[0] == temp.dice_[1]) &&
            (temp.dice_[1] == temp.dice_[2]) &&
            (temp.dice_[3] == temp.dice_[4])) ||
            ((temp.dice_[0] == temp.dice_[1]) &&
             (temp.dice_[2] == temp.dice_[3]) &&
             (temp.dice_[3] == temp.dice_[4])))
    {
        return FULL_HOUSE;
    }
    return 0;
}

int Yahtzee::straight(int score) const
{
    Yahtzee temp(*this);
    temp.sort_dice();
    int seq = 1;
    for(int i = 1; i < 5; i++)
        if(temp.dice_[i]() == (temp.dice_[i - 1]() + 1))
        {
            seq++;
        }
    if(seq > (score / 10))
    {
        return score;
    }
    return 0;
}

int Yahtzee::yahtzee() const
{
    for(int j = 1; j < 5; j++)
        if(dice_[0] != dice_[j])
        {
            return 0;
        }
    return YAHTZEE;
}

void Yahtzee::roll()
{
    for(int i = 0; i < 5; i++)
    {
        dice_[i].roll();
    }
}

void Yahtzee::sort_dice()
{
    int j;
    Dice insert;
    for(int i = 1; i < 5; i++)
    {
        insert = dice_[i];
        for(j = i - 1; j >= 0 && dice_[j] > insert; j--)
        {
            dice_[j + 1] = dice_[j];
        }
        dice_[j + 1] = insert;
    }
}

void Yahtzee::hold(char *c)
{
    char value[2];
    pass();
    for(int i = 0; i < 5 && c[i] != '\0'; i++)
    {
        value[0] = c[i];
        value[1] = '\0';
        for(int j = 0; j < 5; j++)
        {
            if(dice_[j]() == atoi(value) && !dice_[j].held())
            {
                dice_[j].hold();
                break;
            }
        }
    }
}

void Yahtzee::pass()
{
    for(int i = 0; i < 5; i++)
    {
        dice_[i].pass();
    }
}

void Yahtzee::display(std::ostream &out) const
{
    out << "________________________________________________\n";
    for(int i = 0; i < 5; i++)
    {
        out << dice_[i];
    }
}

std::ostream &operator<<(std::ostream &out, const Yahtzee &yahtzee)
{
    yahtzee.display(out);
    return out;
}
