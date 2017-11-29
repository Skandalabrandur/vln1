#ifndef pizza_h
#define pizza_h

#include <iostream>
#include <string>
#include "Topping.cpp"

using namespace std;


class Pizza {

public:
  Pizza();                                  //empty constructor
  Pizza(int numberOfToppings);              //non-empty constructor
  void initialize(int numberOfToppings);
  void resetToppingCount(int numberOfToppings);
  void addTopping(Topping newTopping);
  void setPizzaName(string name);
  void setVerbose(bool set);
  virtual ~Pizza();

  friend ostream& operator << (ostream& out, const Pizza& pizza);
  friend istream& operator >> (istream& in, Pizza& pizza);

private:
  Topping *toppings;    //A pointer for the dynamic array of toppings
  char bottomType;      //Type of pizza bottom (classic, italian, etc)
  int toppingsCount;    //How many toppings will be on the pizza?
  int toppingCounter;   //How many toppings have we added so far?
  string pizzaName;     //What is the name of the pizza?
  bool vbose;           //Will the pizza creation be verbose?
};


#endif
