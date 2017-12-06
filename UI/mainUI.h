#ifndef mainui_h
#define mainui_h
#include "UIFunctions.h"

#include "adminUI.h"
#include "salesUI.h"
#include "bakerUI.h"
#include <iostream>

class mainUI {
public:
  void displayMainMenu();

//Classes as member variables for
//quick and easy function access in mainUI.cpp
private:
  UIFunctions uf;

  adminUI admin_ui;
  salesUI sales_ui;
  bakerUI baker_ui;
};

#endif
