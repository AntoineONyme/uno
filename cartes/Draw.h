#pragma once

#include<list>
#include<iostream>
#include <stdlib.h>
#include <algorithm>



using namespace std;
class Draw {
    list<int> draw_;
    list<int> hand_;
    
public:
    Draw();
    int drawCard();
    void generateHand();
    list<int> getHand();
    bool pullOutCard(int idCard);
    void DrawCardtoHand() { hand_.push_back(drawCard()); }
};