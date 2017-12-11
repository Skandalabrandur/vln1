#ifndef orderservice_h
#define orderservice_h
#include "fileOperations.h"
#include "UIFunctions.h"
#include "stringFunctions.h"
#include "Pizza.h"
#include "Order.h"
#include "pizzaService.h"
#include "locationService.h"
#include <iostream>
#include <vector>

using namespace std;

class orderService {

public:

  public:
  Order convertVector(vector<string> input);
  void createNewOrder();
  void listOrderOverviewWithIndices();
  int getOrderIdFromIndexSelection(int index);
  vector<Pizza> getPizzasFromOrderId(int order_id);
  void listSpecificOrderWithInfo(int order_id);
  int generatePrice(Pizza pizza, bool isMenuPizza);
  int howManyOrders();
  int getOrderID(int index);

  void markPizzaAsPaidByOrderID(int OrderID);
  void markPizzaAsDeliveredByOrderID(int orderID);
  void listOrderFromLocationWithID(int locationID);
  void listSpecificOrderFromLocationWithInfo(int order_id, int location_ID);

private:
  fileOperations fo;
  UIFunctions uf;
  stringFunctions stringfunc;

  pizzaService pizza_service;
    locationService location_service;
};

#endif
