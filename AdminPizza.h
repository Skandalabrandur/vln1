#ifndef pizza_h
#define pizza_h

#include <iostream>
#include <string>
#include "Topping.h"

using namespace std;


class AdminPizza {

public:
  AdminPizza();                                  //empty constructor
  AdminPizza(int numberOfToppings);              //non-empty constructor
  void initialize(int numberOfToppings);
  void resetToppingCount(int numberOfToppings);
  void addTopping(Topping newTopping);
  void setPizzaName(string name);
  void setPlaceName(string name);
  void setVerbose(bool set);
  virtual ~AdminPizza();

  friend ostream& operator << (ostream& out, const AdminPizza& pizza);
  friend istream& operator >> (istream& in, AdminPizza& pizza);
    
    string pizzaName;     //What is the name of the pizza?

private:
  Topping *toppings;    //A pointer for the dynamic array of toppings
  int toppingsCount;    //How many toppings will be on the pizza?
  int toppingCounter;   //How many toppings have we added so far?
  bool vbose;           //Will the pizza creation be verbose?
  string placeName;     //Name of place the pizza is made/sold in
};


#endif
