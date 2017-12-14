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
#include <limits>

class pizzaService {
public:
  Pizza convertActivePizzaVector(vector<string> pizzaWords);
  void createAndAppendMenuPizza();
  void listMenuPizzas();
  void listActivePizzas();
  void listMenuPizzasWithIndices();
  void listActiveWithIndicesForBakeryAndLocation(bool baked, int locationID);
  int adjustBakerIndexForBaked(bool baked, int locationID, int pseudoIndex);
  void deleteMenuPizza();
  int howManyPizzasOnMenu();
  int howManyActivePizzas();
  Pizza getMenuPizza(int index);
  void storeOrderPizza(Pizza pizza);
  void setActivePizzaStatus(int index, string field, bool truthValue);
  bool isDelivered(int index);
  void listFromLocationActivePizzas(int locationID);
  void saveCustomToppings(Pizza pizza);
  vector<Topping> getCustomToppings(int orderID);
  void deletePizzas(vector<Pizza> pizzas);
  void markPizzaAsBakedByOrderIDAndLocation(int orderID, int locationID);
  void markPizzaAsUNBakedByOrderIDAndLocation(int orderID, int locationID);
  int getOrderIDForPizza(int index);
  void deleteActivePizzasWithOrderID(int orderID);


private:
  fileOperations fo;
  UIFunctions uf;
  stringFunctions stringfunc;

  toppingService topping_service;
};

#endif
