#pragma once
#include<iostream>
#include"Card.h"

class OpalCard : public Card
{
	string type_;
public :
	OpalCard(int id, const string& type);
	const string& getType()const { return type_; }
	void show() const { Card::show(); cout << " Type de la carte : " << type_ << " " << endl; }
};

