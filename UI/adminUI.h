#ifndef adminui_h
#define adminui_h
#include "UIFunctions.h"
#include "pizzaService.h"
#include "toppingService.h"

class adminUI {
public:
  void displayAdminMenu();
  void displayPizzaMenu();
  void displayToppingMenu();

private:
  UIFunctions uf;
  pizzaService pizza_service;
  toppingService topping_service;
};

#endif
