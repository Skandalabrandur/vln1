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

private:
  string _customer;
  int _orderID;
  vector<Pizza> _pizzas;

  stringFunctions stringfunc;

};

#endif
