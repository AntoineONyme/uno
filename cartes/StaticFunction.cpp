#include "StaticFunction.h"


char colors[4] = { 'R','B','J','V' };
vector<string> actions = { "+2", "InvSens", "PasseTour" };



void showCardName(int cardId)
{	
	Deck d("d");
	d.generateOpalCards();
	d.generateColoredCards();
	char color;
	string action;
	
	vector<Card*> deck = d.getDeck();
	int num = deck.size();
	if (deck[cardId]->getType() != "no")
		cout << deck[cardId]->getType();
	else
	{
		if (cardId < deck.size() - 8)
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
		else
		{
			if (cardId == deck.size()-1)
				cout << "+4 vert";
			if (cardId == deck.size()-2)
				cout << "+4 jaune";
			if (cardId == deck.size()-3)
				cout << "+4 bleu";
			if (cardId == deck.size()-4)
				cout << "+4 rouge";
			if (cardId == deck.size()-5)
				cout << "joker vert";
			if (cardId == deck.size()-6)
				cout << "joker jaune";
			if (cardId == deck.size()-7)
				cout << "joker bleu";
			if (cardId == deck.size()-8)
				cout << "joker rouge";
			

		}
	}
}