#include "Dice.h"
#include <cstdlib>

Dice::Dice():
    hold_(false), value_(rand() % 6 + 1)
{}

int Dice::roll()
{
    if(!hold_)
    {
        value_ = rand() % 6 + 1;
        return value_;
    }
    return 0;
}

int Dice::operator()() const
{
    return value_;
}

void Dice::hold()
{
    hold_ = true;
}

bool Dice::held() const
{
    return hold_;
}

void Dice::pass()
{
    hold_ = false;
}

void Dice::display(std::ostream &out) const
{
    switch(value_)
    {
        case 1:
            out << "  _________ \n"
                << " |         |\n"
                << " |         |\n"
                << " |    O    |\n"
                << " |         |\n"
                << " |_________|\n";
            break;
        case 2:
            out << "  _________ \n"
                << " |         |\n"
                << " |  O      |\n"
                << " |         |\n"
                << " |      O  |\n"
                << " |_________|\n";
            break;
        case 3:
            out << "  _________ \n"
                << " |         |\n"
                << " |  O      |\n"
                << " |    O    |\n"
                << " |      O  |\n"
                << " |_________|\n";
            break;
        case 4:
            out << "  _________ \n"
                << " |         |\n"
                << " |  O   O  |\n"
                << " |         |\n"
                << " |  O   O  |\n"
                << " |_________|\n";
            break;
        case 5:
            out << "  _________ \n"
                << " |         |\n"
                << " |  O   O  |\n"
                << " |    O    |\n"
                << " |  O   O  |\n"
                << " |_________|\n";
            break;
        case 6:
            out << "  _________ \n"
                << " |         |\n"
                << " |  O   O  |\n"
                << " |  O   O  |\n"
                << " |  O   O  |\n"
                << " |_________|\n";
            break;
        default:
            break;
    }
}

bool Dice::operator==(const Dice &dice) const
{
    return (value_ == dice.value_);
}

bool Dice::operator!=(const Dice &dice) const
{
    return !operator==(dice);
}

bool Dice::operator<(const Dice &dice) const
{
    return (value_ < dice.value_);
}

bool Dice::operator>(const Dice &dice) const
{
    return (value_ > dice.value_);
}

bool Dice::operator<=(const Dice &dice) const
{
    return !operator>(dice);
}

bool Dice::operator>=(const Dice &dice) const
{
    return !operator<(dice);
}

std::ostream &operator<<(std::ostream &out, const Dice &dice)
{
    dice.display(out);
    return out;
}
