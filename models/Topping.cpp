#include "Topping.h"

Topping::Topping() {
  _name  = "Unnamed";
  _price = 0;
}

Topping::Topping(string name, int price) {
  _name  = name;
  _price = price;
}

string Topping::getName() {
  return _name;
}

int Topping::getPrice() {
  return _price;
}

void Topping::setName(string name) {
  _name = name;
}

void Topping::setPrice(int price) {
  _price = price;
}

//Most if not all toString() methods are the ones who will ultimately get written
//out to a file
string Topping::toString() {
  return _name + " " + stringfunc.intToString(_price);
}
