#ifndef orderservice_h
#define orderservice_h
#include "fileOperations.h"
#include "UIFunctions.h"
#include "stringFunctions.h"
#include "Pizza.h"
#include "Order.h"
#include "pizzaService.h"
#include "locationService.h"
#include "commentService.h"
#include "additionalProductService.h"
#include "validationService.h"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class orderService {

public:

  public:
  Order convertVector(vector<string> input);
  Order getOrderAt(int index);
  void createNewOrder();
  void listOrderOverviewWithIndices();
  void listOrderOverviewWithIndicesForLocation(int locationID);
  int getOrderIdFromIndexSelection(int index);
  int getOrderIdFromIndexSelectionForLocation(int index, int locationID);
  vector<Pizza> getPizzasFromOrderId(int order_id);
  void listSpecificOrderWithInfo(int order_id);
  int generatePizzaPrice(Pizza pizza, bool isMenuPizza);
  int howManyOrders();
  int getOrderID(int index);
  int getOrderLocationID(int index);
  int getOrderPrice(int orderID);
  int countOrdersFromLocationWithID(int locationID);

  void markPizzaAsPaidByOrderID(int orderID);
  void markPizzaAsPaidByOrderIDAndLocation(int OrderID, int locationID);
  void markPizzaAsDeliveredByOrderIDAndLocation(int orderID, int locationID);
  void listOrderFromLocationWithID(int locationID, bool isReady);
  void listSpecificOrderFromLocationWithInfo(int order_id, int location_ID);
  void deliveryListSpecificOrderFromLocationWithInfo(int order_id, int location_ID);
  void deleteOrderWithOrderID(int orderID);
  void moveToLegacyFile(int orderID);

private:
  fileOperations fo;
  UIFunctions uf;
  stringFunctions stringfunc;
  validationService vs;

  pizzaService pizza_service;
  locationService location_service;
  commentService comment_service;
  additionalProductService additionalProduct_service;
};

#endif
