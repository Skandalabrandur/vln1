#ifndef bakerUI_h
#define bakerUI_h
#include "UIFunctions.h"
#include "pizzaService.h"
#include "locationService.h"
#include "orderService.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class bakerUI {

public:
    void displayBakerMenu();
    void chooseLocation();
    void viewPizzas();
    void selectAndMarkPizzaAsBaked();
    void selectAndMarkPizzaAsUnbaked();

private:
  int _locationID;
  UIFunctions uf;
  pizzaService pizza_service;
  locationService location_service;
  orderService order_service;
  //orderService order_service;

};
#endif /* bakerUI_h */
