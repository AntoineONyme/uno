#pragma once
#include<iostream>
using namespace std;
class Card
{
	int id_;
public :
	Card( int id = -1 );
	int getId() { return id_; }
	virtual const string& getType()const { return "no"; }
	virtual int getColor() { return-1; }
	virtual int getNumber() { return-1; }
	virtual int getSpecialType() const { return-1; }
	virtual void show()const { cout << "Identifiant carte : " << id_ << endl; }

};

