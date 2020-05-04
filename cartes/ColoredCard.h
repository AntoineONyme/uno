#pragma once
#include"OpalCard.h"
class ColoredCard : public Card
{
	int color_;
	int number_;
public :
	ColoredCard(int id, int color, int number);
	int getColor() const { return color_ ; }
	int getNumber() const { return number_; }
	void show() const { Card::show(); cout << " Couleur de la carte : " << color_ << " " << " Valeur de la carte : "<< number_ <<endl;}
};

