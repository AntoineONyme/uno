#include "StaticFunction.h"


char colors[4] = { 'R','B','J','V' };
vector<string> actions = { "+2", "InvSens", "PasseTour" };

Deck d("d");

void showCardName(int cardId)
{	
	d.generateOpalCards();
	d.generateColoredCards();
	char color;
	string action;
	int num;
	vector<Card*> deck = d.getDeck();
	if (deck[cardId]->getType() != "no")
		cout << deck[cardId]->getType();
	else
	{

		if (deck[cardId]->getNumber() < 10)
		{
			color = colors[deck[cardId]->getColor() - 1];
			num = deck[cardId]->getNumber();
			cout << color << num;
		}
		else
		{
			color = colors[deck[cardId]->getColor() - 1];
			cout << color << actions[deck[cardId]->getSpecialType()];
		}

	}
}