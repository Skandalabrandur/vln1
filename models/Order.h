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
  Order(string customer, int orderID, int locationID, bool pickUp);
  string getCustomer();
  void setCustomer(string customer);
  int getOrderID();
  void setOrderID(int orderID);
  void setLocationID(int locationID);
  int getLocationID();
  string getLocation();
  void setLocation(string place);
  void addPizza(Pizza pizza);
  string toString();

private:
  string _customer;
  int _orderID;
  int _locationID;
  string _location;
  bool _pickUp;
  vector<Pizza> _pizzas;

  stringFunctions stringfunc;
};

#endif
