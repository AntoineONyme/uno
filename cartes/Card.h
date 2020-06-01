#pragma once
#include<iostream>
using namespace std;

/*==================================
header de la classe m�re carte  permet g�rant la construction g�n�rique d'une carte
====================================*/

class Card
{
	int id_;

public :
	Card( int id = -1 );
	int getId() { return id_; }
	virtual string getType() const { string no = "no"; return no; } // m�thode virtuelle renvoyant la "joker" et "+4"  de la carte si elle l'est, "no" sinon.
	virtual int getColor()const { return 0; } // m�thode virtuelle renvoyant la couleur de la carte si elle en a une, 0 sinon.
	virtual int getNumber() const { return-1; } // m�thode virtuelle renvoyant la valeur de la carte si elle en a une, -1 sinon.
	virtual int getSpecialType() const { return-1; } // m�thode virtuelle renvoyant le type d'action de la carte si elle en a une 0 sinon.
	virtual void show()const { cout << "Identifiant carte : " << id_ << endl; } // m�thode virtuelle renvoyant toutes les caract�ristiques d'une carte.

};

