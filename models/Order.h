#ifndef order_h
#define order_h
#include <string>
#include <vector>
#include "stringFunctions.h"
#include "Pizza.h"
#include "Comment.h"
#include "AdditionalProduct.h"
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
  void setComment(string comment);
  Comment getComment();
  string toString();

private:
  string _customer;
  int _orderID;
  int _locationID;
  string _location;
  bool _pickUp;
  vector<Pizza> _pizzas;
  Comment _comment;
  vector<AdditionalProduct> _additionalProducts;

  stringFunctions stringfunc;
};

#endif
