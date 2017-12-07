#ifndef order_h
#define order_h
#include <string>
#include <vector>
#include "stringFunctions.h"
#include "Pizza.h"
using namespace std;

class Order {

public:
  Order();
  Order(string customer, int orderID);
  string getCustomer();
  void setCustomer(string customer);
  int getOrderID();
  void setOrderID(int orderID);
  string getPlace();
  void setPlace(string place);
  void addPizza(Pizza pizza);
  string toString();

private:
  string _customer;
  int _orderID;
  string _place;
  vector<Pizza> _pizzas;

  stringFunctions stringfunc;
};

#endif
