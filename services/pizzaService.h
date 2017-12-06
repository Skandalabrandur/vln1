#ifndef pizzaservice_h
#define pizzaservice_h
#include "fileOperations.h"
#include "UIFunctions.h"
#include "stringFunctions.h"
#include "Topping.h"
#include "Pizza.h"
#include "toppingService.h"
#include <string>
#include <fstream>
#include <vector>

class pizzaService {
public:
  void createAndAppendMenuPizza();
  void listMenuPizzas();
  void listMenuPizzasWithIndices();
  void deleteMenuPizza();
  
  int howManyPizzasOnMenu();
  Pizza getMenuPizza(int index);
  void storeOrderPizza(Pizza pizza);

private:
  fileOperations fo;
  UIFunctions uf;
  stringFunctions stringfunc;

  toppingService topping_service;
};

#endif
