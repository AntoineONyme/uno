#pragma once
#include "Deck.h"
#include<list>

using namespace std;
class Draw {
    list<int> draw_;
public:
    Draw();
    int drawCard();
    bool pullOutCard(int idCard);
};