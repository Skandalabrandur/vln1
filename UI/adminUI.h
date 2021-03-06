#ifndef adminui_h
#define adminui_h
#include "UIFunctions.h"
#include "pizzaService.h"
#include "toppingService.h"
#include "locationService.h"
#include "additionalProductService.h"
#include "validationService.h"
#include "orderService.h"

class adminUI {
public:
    bool requestPassword();
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
  additionalProductService additionalProduct_service;
  orderService order_service;
  validationService vs;
};

#endif
