#pragma once
#include "ColoredCard.h"

/*==================================
header de la classe fille de carte colorées des cartes colorées ayant des effets gérant la génération de leurs propriétés
====================================*/
class SpecialCard : public ColoredCard
{
	int specialType_;
public :
	SpecialCard(int id, int color, int number, int sp);
	int getSpecialType() const { return specialType_ ; } // renvoie ici une valeur entre 0 et 2 atribué à un effet.
	void show() const { ColoredCard::show(); cout <<  " Action de la carte : " << specialType_ << endl; }
};

