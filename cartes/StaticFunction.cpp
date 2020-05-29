#include "StaticFunction.h"

//Méthode permettant de changer la couleur d'affichage du texte console
void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}



// Tableau de valeur char ou string à afficher dans la console 
char colorsText[4] = { 'R','B','J','V' };
int colors[4] = {12,11,14,10};
vector<string> actions = { "+2", "InvSens", "PasseTour" };



// Methode permettant de convertir les id des cartes jouées / affichées en nom compréhensible par le joueur
void showCardName(int cardId)
{	
	Deck d("d");
	d.generateOpalCards();
	d.generateColoredCards(); // on génère un deck 
	char color;
	string action;
	
	vector<Card*> deck = d.getDeck();
	int num = deck.size();
	if (deck[cardId]->getType() != "no") // s'il s'agit d'un joker ou d'un +4 on ne rentre pas dans la boucle.
		cout << deck[cardId]->getType();
	else
	{
		if (cardId < deck.size() - 8) // taille - 8 correspond au n cartes du jeu initial
		{
			if (deck[cardId]->getNumber() < 10) // si la valeur d'une carte est inférieur à 10 on sait qu'elle n'aura pas d'effet
			{
				color = colorsText[deck[cardId]->getColor() - 1];
				num = deck[cardId]->getNumber();
				Color(colors[deck[cardId]->getColor() - 1]);
				cout << color;
				Color(7);
				cout << num;
				
			}
			else // sinon on sait qu'elle a une faculté spéciale.
			{
				color = colorsText[deck[cardId]->getColor() - 1];
				Color(colors[deck[cardId]->getColor() - 1]);
				cout << color; 
				Color(7);
				cout << actions[deck[cardId]->getSpecialType()];
				
			}
		}
		else // si on touche au cartes supérieur à n - 8 on affiche les subsituts de couleur des cartes +4 et joker 
		{
			if (cardId == deck.size() - 1)
			{
				cout << "+4 ";
				Color(10);
				cout << "vert";
			}
			if (cardId == deck.size() - 2) 
			{
				cout << "+4 ";
				Color(14);
				cout<<"jaune";
			}
				
			if (cardId == deck.size() - 3) 
			{
				cout << "+4 ";
				Color(3);
				cout << "bleu";
			}
				
			if (cardId == deck.size() - 4)
			{
				cout << "+4 ";
				Color(12);
				cout<<"rouge";
			}
			if (cardId == deck.size() - 5)
			{
				cout << "joker ";
				Color(10);
				cout << "vert";
			}
			if (cardId == deck.size() - 6)
			{
				cout << "joker "; 
				Color(14);
				cout << "jaune";
			}
			if (cardId == deck.size() - 7)
			{
				cout << "joker ";
				Color(11);
				cout << "bleu";
			}
			if (cardId == deck.size() - 8)
			{
				cout << "joker ";
				Color(12);
				cout << "rouge";
			}
			
			Color(7);
		}
	}
}



