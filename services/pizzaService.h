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
#include <iostream>

class pizzaService {
public:
  Pizza convertActivePizzaVector(vector<string> pizzaWords);
  void createAndAppendMenuPizza();
  void listMenuPizzas();
  void listActivePizzas();
  void listMenuPizzasWithIndices();
  void listActivePizzasWithIndicesForBakery(bool baked);
  int adjustBakerIndexForBaked(bool baked, int pseudoIndex);
  void deleteMenuPizza();
  int howManyPizzasOnMenu();
  int howManyActivePizzas();
  Pizza getMenuPizza(int index);
  void storeOrderPizza(Pizza pizza);
  void setActivePizzaStatus(int index, string field, bool truthValue);

private:
  fileOperations fo;
  UIFunctions uf;
  stringFunctions stringfunc;

  toppingService topping_service;
};

#endif
