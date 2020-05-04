#include "SpecialCard.h"
SpecialCard::SpecialCard(int id, int color, int number,int sp) : ColoredCard(id, color, number) {
	specialType_ = sp;
}