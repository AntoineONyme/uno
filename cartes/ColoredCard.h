#pragma once
#include"OpalCard.h"

/*==================================
header de la classe fille de carte des cartes colorées gérant la génération de leurs propriétés
====================================*/

class ColoredCard : public Card
{
	int color_;
	int number_;
public :
	ColoredCard(int id, int color, int number);
	int getColor() const { return color_ ; } // renvoie une valeur entre 1 et 4
	int getNumber() const { return number_; } // renvoie la valeur d'une carte entre 0 et 9
	int getSpecialType() const { return -1; }
	void show() const { Card::show(); cout << " Couleur de la carte : " << color_ << " " << " Valeur de la carte : "<< number_ <<endl;}
};

