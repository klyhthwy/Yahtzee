#ifndef _YAHTZEE_H_
#define _YAHTZEE_H_

#include "Dice.h"

#include <iostream>

class Yahtzee
{
public:
	
	enum Constants
	{
		BONUS = 63,
		BONUS_SCORE = 35,
		FULL_HOUSE = 25,
		SM_STRAIGHT = 30,
		LG_STRAIGHT = 40,
		YAHTZEE = 50
	};

	Yahtzee();
	int total( int=0 ) const;
	int kind( int ) const;
	int full_house() const;
	int straight( int ) const;
	int yahtzee() const;
	void roll();
	void hold( char* );
	void pass();
	void display( std::ostream& ) const;

private:
	
	void sort_dice();

	Dice dice_[5];
};

std::ostream& operator<<( std::ostream&, const Yahtzee& );

#endif