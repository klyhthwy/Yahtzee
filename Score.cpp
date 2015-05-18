#include "Score.h"

#include <iomanip>

Score::Score():
score_(0), used_(false)
{}

Score::Score( int score ):
score_( score ), used_(true)
{}

int Score::operator()() const
{
	if( used_ )
		return score_;
	return 0;
}

bool Score::operator!() const
{
	return !used_;
}

void Score::display( std::ostream& out ) const
{
	if( used_ )
		out << std::setw(4) << score_ << " *";
	else
		out << std::setw(4) << 0;
}

std::ostream& operator<<( std::ostream& out, const Score& score )
{
	score.display( out );
	return out;
}