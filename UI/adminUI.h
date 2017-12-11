#ifndef adminui_h
#define adminui_h
#include "UIFunctions.h"
#include "pizzaService.h"
#include "toppingService.h"
#include "locationService.h"

class adminUI {
public:
  void displayAdminMenu();
  void displayPizzaMenu();
  void displayToppingMenu();
  void displayLocationMenu();
  void displayAdditionalProductsMenu();

private:
  UIFunctions uf;
  pizzaService pizza_service;
  toppingService topping_service;
  locationService location_service;
};

#endif
