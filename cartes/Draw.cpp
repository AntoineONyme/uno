#include "Draw.h"

Draw::Draw() {
	genDraw();
}

// Permet de piocher al�atoirement une carte dans la pioche
int Draw::drawCard() {
	srand(time(NULL)); // on utilise la package random et time pour g�n�rer continuellement et al�atoirement 
	int rd;
	int valCard;
	list<int>::iterator it = draw_.begin();

	

	rd = rand() % draw_.size(); //on g�n�re un entier al�atoire compris entre 0 et la taille de la pioche
	advance(it, rd);
	valCard = *it;
	pullOutCard(valCard,0);
	return valCard;
}

// Permet de retirer une carte de la main ou de la pioche en fonction d'un indicateur. 
bool Draw::pullOutCard(int IdCard, int listChoice) {

		if (listChoice == 0) // ici on parcours la pioche pour supprimer la valeur de la carte d�sir�e
		{
			list<int>::iterator it1;
			for (it1 = draw_.begin(); it1 != draw_.end(); it1++) {
				if (*it1 == IdCard) {
					draw_.erase(it1);
					return true;
				}
			}
		}

		else // ici on parcours lamain  pour supprimer la valeur de la carte d�sir�e
		{
			list<int>::iterator it2;
			for (it2 = hand_.begin(); it2 != hand_.end(); it2++) {
				if (*it2 == IdCard) {
					hand_.erase(it2);
					return true;
				}
			}
		}

		return false;
	
}

// genere la main de d�part du joueur 
void Draw::generateHand()
{
	
	while(hand_.size() < 7) //Tant que la main ne fait pas 7 cartes on en ajoute 
		hand_.push_back(drawCard());
}

// Getter de la main du joueur
list<int> Draw::getHand()
{
	return hand_;
}

//Methode permettant d'ajouter une unique carte dans la main et de retourner son id
int Draw::DrawCardtoHand()
{
	int drawnCard = drawCard();
	hand_.push_back(drawnCard);
	return drawnCard;
}

// permet de g�n�rer la liste de carte piochable (les 107 premi�res cartes du Deck)
void Draw::genDraw()
{
	for (int i = 0; i < 108; i++)
		draw_.push_back(i);
}