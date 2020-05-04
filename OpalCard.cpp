#include "OpalCard.h"
#pragma once
OpalCard::OpalCard(int id, const string& type) : Card(id)
{
	type_ = type;
}