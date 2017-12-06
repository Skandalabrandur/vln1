#include "Order.h"
using namespace std;

Order::Order(string customer, int orderID) {
  _customer = customer;
  _orderID = orderID;
}

string Order::toString() {
  return _customer + " " + stringfunc.intToString(_orderID);
}

void Order::addPizza(Pizza pizza) {
  _pizzas.push_back(pizza);
}
