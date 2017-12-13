#ifndef bakerUI_h
#define bakerUI_h
#include "UIFunctions.h"
#include "pizzaService.h"
#include "locationService.h"
#include "orderService.h"
#include "validationService.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class bakerUI {

public:
    void displayBakerMenu();
    void chooseLocation();
    void viewPizzas();
    void selectAndMarkPizzaAsBaked();
    void selectAndMarkPizzaAsUnbaked();
    void listByOrders(bool isReady);

private:
  int _locationID;
  UIFunctions uf;
  pizzaService pizza_service;
  locationService location_service;
  orderService order_service;
  validationService vs;

};
#endif /* bakerUI_h */
