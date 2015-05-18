#include "HumanPlayer.h"

#include <iomanip>

HumanPlayer::HumanPlayer( char* name ):
Player( name )
{}

void HumanPlayer::turn( Yahtzee& dice )
{
	char holds[6];
	bool roll = true;
	std::cout << "\n\nPress Enter to Roll";
	std::cin.get(holds[0]);
	while( holds[0] != '\n' )
		std::cin.get(holds[0]);

	for( int i=0; i<3 && roll; i++ )
	{
		dice.roll();
		std::cout << dice << '\n';
		if( dice.yahtzee() )
		{
			std::cout << "YAHTZEE!!!\n";
			if( scores_[YAHTZEE]() )
			{
				yahtzee_bonuses_++;
				return;
			}
		}
		if( i!=2 )
		{
			roll = get_holds( holds );
			dice.hold( holds );
		}
	}
	while( !set_score( dice, options( dice )));
}

char HumanPlayer::options( const Yahtzee& dice ) const
{
	char c;
	if( !scores_[ACE] )
		std::cout << "\n    (1) Aces          :" << std::setw(4) << dice.total(ACE);
	if( !scores_[2] )
		std::cout << "\n    (2) Twos          :" << std::setw(4) << dice.total(2);
	if( !scores_[3] )
		std::cout << "\n    (3) Threes        :" << std::setw(4) << dice.total(3);
	if( !scores_[4] )
		std::cout << "\n    (4) Fours         :" << std::setw(4) << dice.total(4);
	if( !scores_[5] )
		std::cout << "\n    (5) Fives         :" << std::setw(4) << dice.total(5);
	if( !scores_[6] )
		std::cout << "\n    (6) Sixes         :" << std::setw(4) << dice.total(6);
	if( !scores_[THREE_KIND] )
		std::cout << "\n    (T) 3 of a Kind   :" << std::setw(4) << dice.kind(3);
	if( !scores_[FOUR_KIND] )
		std::cout << "\n    (F) 4 of a Kind   :" << std::setw(4) << dice.kind(4);
	if( !scores_[FULL_HOUSE] )
		std::cout << "\n    (H) Full House    :" << std::setw(4) << dice.full_house();
	if( !scores_[SM_STRAIGHT] )
		std::cout << "\n    (S) Sm Straight   :" << std::setw(4) << dice.straight(Yahtzee::SM_STRAIGHT);
	if( !scores_[LG_STRAIGHT] )
		std::cout << "\n    (L) Lg Straight   :" << std::setw(4) << dice.straight(Yahtzee::LG_STRAIGHT);
	if( !scores_[YAHTZEE] )
		std::cout << "\n    (Y) YAHTZEE       :" << std::setw(4) << dice.yahtzee();
	if( !scores_[CHANCE] )
		std::cout << "\n    (C) Chance        :" << std::setw(4) << dice.total();
	std::cout << "\n\n        Enter Choice: ";
	std::cin >> c;
	std::cin.ignore(3,'\n');
	return c;
}

bool HumanPlayer::get_holds( char holds[] ) const
{
	std::cin.get( holds[0] );
	if( holds[0] == '0' )
	{
		std::cin.ignore(6,'\n');
		return false;
	}
	std::cin.unget();
	for( int i=0; i<6; i++ )
	{
		std::cin.get(holds[i]);
		if( holds[i] == '\n' )
		{
			holds[i] = '\0';
			return true;
		}
	}
	std::cin.ignore(6,'\n');
	return true;
}