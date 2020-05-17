#pragma once
#include "Menu.h"

class MenuSalon : public Menu {
public:
	MenuSalon(string nom);
	bool setAction(string nomMenu);
};