#pragma once

#include<list>
#include<iostream>
//#include <stdlib.h>
#include <algorithm>
#include<time.h>



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
    void clearHand() { hand_.clear(); };
   
};