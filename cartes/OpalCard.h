#pragma once
#include<iostream>
#include"Card.h"

/*==================================
header de la classe fille de carte des cartes sans couleur g�rant la g�n�ration de leurs propri�t�s
====================================*/

class OpalCard : public Card
{
	string type_;
public :
	OpalCard(int id , const string& type);
	string getType() const { return type_; } //methode virtuelle sp�cifique � ce type de carte permettant de renvoyer la propri�t� +4 ou jokerS
	void show() const { Card::show(); cout << " Type de la carte : " << type_ << " " << endl; }
	
};

