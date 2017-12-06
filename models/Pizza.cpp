#include "Pizza.h"

Pizza::Pizza(string name, vector<Topping> toppings, int price) {
  _name = name;
  _toppings = toppings;
  _price = price;

  _orderID = -1;
  _baked = false;
  _paid = false;
  _delivered = false;
}

string Pizza::getName() {
  return _name;
}

int Pizza::getOrderID() {
  return _orderID;
}

bool Pizza::isBaked() {
  return _baked;
}

bool Pizza::isPaid() {
  return _paid;
}

bool Pizza::isDelivered() {
  return _delivered;
}

void Pizza::setOrderID(int set) {
  _orderID = set;
}

void Pizza::setBaked(bool set) {
  _baked = set;
}

void Pizza::setPaid(bool set) {
  _paid = set;
}

void Pizza::setDelivered(bool set) {
  _delivered = set;
}

string Pizza::toString(bool showToppings) {
  string builder = "";
builder += stringfunc.intToString(_orderID) + " ";
  builder += _name + " ";

  if(showToppings) {
    for(int i = 0; i < _toppings.size(); i++) {
      builder += _toppings[i].getName() + " ";
    }
  }

  builder += stringfunc.intToString(_price) + " ";
  builder += stringfunc.boolToString(_baked) + " ";
  builder += stringfunc.boolToString(_paid) + " ";
  builder += stringfunc.boolToString(_delivered) + " ";

  return builder;
}
