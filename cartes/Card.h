#pragma once
#include<iostream>
using namespace std;
class Card
{
	int id_;
public :
	Card( int id = -1 );
	int getId() { return id_; }
	virtual string getType() { string no = "no"; return no; }
	virtual int getColor()const { return-1; }
	virtual int getNumber() const { return-1; }
	virtual int getSpecialType() const { return-1; }
	virtual void show()const { cout << "Identifiant carte : " << id_ << endl; }

};

