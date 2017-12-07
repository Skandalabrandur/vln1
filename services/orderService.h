#ifndef orderservice_h
#define orderservice_h
#include "fileOperations.h"
#include "UIFunctions.h"
#include "stringFunctions.h"
#include "Pizza.h"
#include "Order.h"
#include "pizzaService.h"
#include <iostream>
#include <vector>

using namespace std;

class orderService {

public:
  Order convertVector(vector<string> input);
  void createNewOrder();
  void listOrderOverviewWithIndices();
  int getOrderIdFromIndexSelection(int index);
  vector<Pizza> getPizzasFromOrderId(int order_id);
  void listSpecificOrderWithInfo(int order_id);
  int generatePrice(Pizza pizza, bool isMenuPizza);

private:
  fileOperations fo;
  UIFunctions uf;
  stringFunctions stringfunc;

  pizzaService pizza_service;
};

#endif
