#ifndef _DICE_H_
#define _DICE_H_

#include <iostream>

class Dice
{
public:

	Dice();
	int roll();
	int operator()() const;
	void hold();
	bool held() const;
	void pass();
	void display( std::ostream& ) const;

	bool operator==( const Dice& ) const;
	bool operator!=( const Dice& ) const;
	bool operator<( const Dice& ) const;
	bool operator>( const Dice& ) const;
	bool operator<=( const Dice& ) const;
	bool operator>=( const Dice& ) const;

private:

	bool hold_;
	int value_;
};

std::ostream& operator<<( std::ostream&, const Dice& );

#endif