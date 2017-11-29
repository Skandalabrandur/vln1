#ifndef pizza_h
#define pizza_h
#include <iostream>

class Pizza {

public:
  void addTopping(Topping topping);
  friend

private:
  Topping toppings[];

};


#endif
