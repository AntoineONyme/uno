#pragma once
#include<iostream>
#include"Card.h"

/*==================================
header de la classe fille de carte des cartes sans couleur gérant la génération de leurs propriétés
====================================*/

class OpalCard : public Card
{
	string type_;
public :
	OpalCard(int id , const string& type);
	string getType() const { return type_; } //methode virtuelle spécifique à ce type de carte permettant de renvoyer la propriété +4 ou jokerS
	void show() const { Card::show(); cout << " Type de la carte : " << type_ << " " << endl; }
	
};

