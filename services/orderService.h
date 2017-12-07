#ifndef orderservice_h
#define orderservice_h
#include "fileOperations.h"
#include "UIFunctions.h"
#include "Order.h"
#include "pizzaService.h"
#include <iostream>

using namespace std;

class orderService {

public:
  void createNewOrder();
  int generatePrice(Pizza pizza);

private:
  fileOperations fo;
  UIFunctions uf;

  pizzaService pizza_service;
};

#endif
