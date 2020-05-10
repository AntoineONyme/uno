#include "Draw.h"

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

void Draw::generateHand()
{
	while(hand_.size() < 7)
		hand_.push_back(drawCard());
	
}

list<int> Draw::getHand()
{
	return hand_;
}

