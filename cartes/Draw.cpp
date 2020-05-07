#include<iostream>
#include <stdlib.h>
#include <algorithm>
#include<vector>
#include <algorithm>
#include "Draw.h"
#include "Deck.h"

Draw::Draw() {
	for (int i = 0; i < 108; i++)
		draw_.push_back(i);
}

int Draw::drawCard() {
	//Dec var
	int rd;
	list<int>::iterator it;

	//Def var

	rd = rand() % draw_.size();
	it = find(draw_.begin(), draw_.end(), rd);
	draw_.erase(it);
	return rd;
}

bool Draw::pullOutCard(int IdCard) {
	list<int>::iterator it;
	for (it = draw_.begin(); it != draw_.end(); it++) {
		if (*it == IdCard) {
			draw_.erase(it);
			return true;
		}
	}

	return false;
}