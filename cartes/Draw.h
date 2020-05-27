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
    int drawCard();
    void generateHand();
    list<int> getHand();
    bool pullOutCard(int idCard, int listChoice );
    int DrawCardtoHand();
    void genDraw();
   
};