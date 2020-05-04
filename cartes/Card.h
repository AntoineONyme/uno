#pragma once
#include<iostream>
using namespace std;
class Card
{
	int id_;
public :
	Card( int id );
	int getId() { return id_; }
	virtual void show()const { cout << "Identifiant carte : " << id_ << endl; }

};

