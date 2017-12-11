#include "Order.h"
using namespace std;


Order::Order() {
  _customer = "";
  _orderID  = -1;
  _location = "";
}

Order::Order(string customer, int orderID, int locationID) {
  _customer = customer;
  _orderID = orderID;
  _locationID = locationID;
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

string Order::getLocation() {
  return _location;
}

void Order::setLocation(string location) {
  _location = location;
}

void Order::setLocationID(int locationID){
    _locationID = locationID;
}

int Order::getLocationID(){
    return _locationID;
}

void Order::setComment(string comment) {
  Comment newComment(comment, _orderID);
  _comment = newComment;
}

Comment Order::getComment() {
  return _comment;
}


string Order::toString() {
  return _customer + " " + stringfunc.intToString(_orderID) + " " + stringfunc.intToString(_locationID);
}

void Order::addPizza(Pizza pizza) {
  _pizzas.push_back(pizza);
}
