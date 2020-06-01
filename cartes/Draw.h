#pragma once

#include<list>
#include<iostream>
//#include <stdlib.h>
#include <algorithm>
#include<time.h>


/*==================================
Classe permettant de gérer la pioche des cartes dans la main du joueur et leur suppression après au cours du jeu
====================================*/
using namespace std;
class Draw {
    list<int> draw_;
    list<int> hand_;

public:
    Draw();
    int drawCard(); // permet de piocher une carte aléatoirement dans la pioche en vérifiant si cette carte a été piochée ou non et retourne son identifiant.
    void generateHand(); // permet de générer la main de départ de 7 cartes.
    list<int> getHand(); // getter de la pioche.
    bool pullOutCard(int idCard, int listChoice );
    int DrawCardtoHand(); // permet de piocher une carte aléatoirement et l'ajoute dans la main du joueur et retourne son identifiant.
    void genDraw(); // méthode appelée par le constructeur pour générer la pioche.
    void clearHand() { hand_.clear(); }; // permet de vider la main de toutes ses cartes. 
    list<int>getDraw() { return draw_; } // getter de la main du joueur.
   
};