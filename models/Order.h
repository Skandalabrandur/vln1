#ifndef order_h
#define order_h
#include <string>
#include <vector>
#include "stringFunctions.h"
#include "Pizza.h"
using namespace std;

class Order {

public:
  Order(string customer, int orderID);
  void addPizza(Pizza pizza);
  string toString();

  string getCustomerName();
  string getPlace();
  int getOrderID();

private:
  string _customer;
  int _orderID;
  string _place;
  vector<Pizza> _pizzas;

  stringFunctions stringfunc;

};

#endif
