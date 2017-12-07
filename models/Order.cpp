#include "Order.h"
using namespace std;


Order::Order() {
  _customer = "";
  _orderID  = -1;
  _place = "";
}

Order::Order(string customer, int orderID) {
  _customer = customer;
  _orderID = orderID;
}

string Order::getCustomer() {
  return _customer;
}

void Order::setCustomer(string customer) {
  _customer = customer;
}

int Order::getOrderID() {
  return _orderID;
}

void Order::setOrderID(int orderID) {
  _orderID = orderID;
}

string Order::getPlace() {
  return _place;
}

void Order::setPlace(string place) {
  _place = place;
}




string Order::toString() {
  return _customer + " " + stringfunc.intToString(_orderID);
}

void Order::addPizza(Pizza pizza) {
  _pizzas.push_back(pizza);
}
