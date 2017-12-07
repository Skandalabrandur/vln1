#ifndef bakerUI_h
#define bakerUI_h
#include "UIFunctions.h"
#include "pizzaService.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class bakerUI {

public:
    void displayBakerMenu();
    void viewPizzas();
    void selectAndMarkPizzaAsBaked();
    void selectAndMarkPizzaAsUnbaked();

private:
  UIFunctions uf;
  pizzaService pizza_service;

};
#endif /* bakerUI_h */
