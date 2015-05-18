#ifndef _SCORE_H_
#define _SCORE_H_

#include <iostream>

class Score
{
public:
	Score();
	Score( int );
	int operator()() const;
	bool operator!() const;
	void display( std::ostream& ) const;
protected:
	int score_;
	bool used_;
};

std::ostream& operator<<( std::ostream&, const Score& );

#endif