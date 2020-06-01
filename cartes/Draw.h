#pragma once

#include<list>
#include<iostream>
//#include <stdlib.h>
#include <algorithm>
#include<time.h>


/*==================================
Classe permettant de g�rer la pioche des cartes dans la main du joueur et leur suppression apr�s au cours du jeu
====================================*/
using namespace std;
class Draw {
    list<int> draw_;
    list<int> hand_;

public:
    Draw();
    int drawCard(); // permet de piocher une carte al�atoirement dans la pioche en v�rifiant si cette carte a �t� pioch�e ou non et retourne son identifiant.
    void generateHand(); // permet de g�n�rer la main de d�part de 7 cartes.
    list<int> getHand(); // getter de la pioche.
    bool pullOutCard(int idCard, int listChoice );
    int DrawCardtoHand(); // permet de piocher une carte al�atoirement et l'ajoute dans la main du joueur et retourne son identifiant.
    void genDraw(); // m�thode appel�e par le constructeur pour g�n�rer la pioche.
    void clearHand() { hand_.clear(); }; // permet de vider la main de toutes ses cartes. 
    list<int>getDraw() { return draw_; } // getter de la main du joueur.
   
};