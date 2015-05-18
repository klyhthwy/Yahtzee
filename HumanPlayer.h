#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include "Player.h"

class HumanPlayer: public Player
{
public:
	HumanPlayer( char* );
	virtual void turn( Yahtzee& );
	char options( const Yahtzee& ) const;
private:
	bool get_holds( char[] ) const;
};

#endif