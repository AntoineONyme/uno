#pragma once
#include "ColoredCard.h"
class SpecialCard : public ColoredCard
{
	int specialType_;
public :
	SpecialCard(int id, int color, int number, int sp);
	int getSpecialType() const { return specialType_ ; }
	const string& getType()const { return "no"; }
	void show() const { ColoredCard::show(); cout <<  " Action de la carte : " << specialType_ << endl; }
};

