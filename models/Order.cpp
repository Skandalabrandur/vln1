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

string Order::getCustomerName(){
    return _customer;
}

string Order::getPlace(){
    return _place;
}

int Order::getOrderID(){
    return _orderID;
}
