#pragma once
#include "ColoredCard.h"

/*==================================
header de la classe fille de carte color�es des cartes color�es ayant des effets g�rant la g�n�ration de leurs propri�t�s
====================================*/
class SpecialCard : public ColoredCard
{
	int specialType_;
public :
	SpecialCard(int id, int color, int number, int sp);
	int getSpecialType() const { return specialType_ ; } // renvoie ici une valeur entre 0 et 2 atribu� � un effet.
	void show() const { ColoredCard::show(); cout <<  " Action de la carte : " << specialType_ << endl; }
};

