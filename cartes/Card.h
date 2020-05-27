#pragma once
#include<iostream>
using namespace std;

/*==================================
header de la classe mère carte  permet gérant la construction générique d'une carte
====================================*/

class Card
{
	int id_;

public :
	Card( int id = -1 );
	int getId() { return id_; }
	virtual string getType() const { string no = "no"; return no; } //le type correspond ici à si la carte est un +4 ou un joker.  
	virtual int getColor()const { return 0; }
	virtual int getNumber() const { return-1; }
	virtual int getSpecialType() const { return-1; }
	virtual void show()const { cout << "Identifiant carte : " << id_ << endl; }

};

