#ifndef toppingservice_h
#define toppingservice_h
#include "Topping.h"
#include "UIFunctions.h"
#include "fileOperations.h"
#include "stringFunctions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

class toppingService {
public:
  Topping getToppingAt(int index);
  void listToppings();
  void listToppingsWithIndex();
  void createNewTopping();
  Topping lookupTopping(string name);
  int howManyToppings();
  void deleteTopping();

private:
  fileOperations fo;
  stringFunctions stringfunc;
  UIFunctions uf;
};

#endif
