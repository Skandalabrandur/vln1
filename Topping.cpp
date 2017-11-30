#include <iostream>
#include <string>
#include "Topping.h"

Topping::Topping() {
  _name  = "Topping";
  _price = 1337;
  vbose = true;
}

Topping::Topping(string name) {
  _name = name;
  _price = 1337;
  vbose = true;
}

Topping::Topping(string name, int price) {
  _name  = name;
  _price = price;
  vbose = true;
}

void Topping::setVerbose(bool set) {
  vbose = set;
}

void Topping::setName(string name) {
  _name = name;
}

void Topping::setPrice(int price) {
  _price = price;
}

//empty destructor
Topping::~Topping() {

}


ostream& operator << (ostream& out, const Topping& topping) {
  out << topping._name << " ";
  out << topping._price;

  return out;
}

istream& operator >> (istream& in, Topping& topping) {

  if(topping.vbose) {
    cout << "Input topping name: ";
  }
  in >> topping._name;

  if(topping.vbose) {
    cout << "Input topping price (integer): ";
  }
  in >> topping._price;

  return in;
}
