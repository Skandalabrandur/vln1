#ifndef topping_h
#define topping_h
#include <iostream>
#include <string>
#include "stringFunctions.h"
using namespace std;

class Topping {

public:
  Topping();
  Topping(string name, int price);
  string getName();
  int getPrice();
  void setName(string name);
  void setPrice(int price);
  string toString();
private:
  string _name;
  int _price;

  stringFunctions stringfunc;
};

#endif
