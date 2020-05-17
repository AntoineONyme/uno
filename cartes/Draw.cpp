#include "Draw.h"

Draw::Draw() {
	genDraw();
}

int Draw::drawCard() {
	//Dec var
	int rd;
	int valCard;
	list<int>::iterator it = draw_.begin();

	//Def var

	rd = rand() % draw_.size();
	advance(it, rd);
	valCard = *it;
	pullOutCard(valCard,0);
	return valCard;
}

bool Draw::pullOutCard(int IdCard, int listChoice) {

		if (listChoice == 0)
		{
			list<int>::iterator it1;
			for (it1 = draw_.begin(); it1 != draw_.end(); it1++) {
				if (*it1 == IdCard) {
					draw_.erase(it1);
					return true;
				}
			}
		}

		else
		{
			list<int>::iterator it;
			for (it = hand_.begin(); it != hand_.end(); it++) {
				if (*it == IdCard) {
					hand_.erase(it);
					return true;
				}
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

void Draw::DrawCardtoHand()
{
	hand_.push_back(drawCard());
}

void Draw::genDraw()
{
	for (int i = 0; i < 108; i++)
		draw_.push_back(i);
}