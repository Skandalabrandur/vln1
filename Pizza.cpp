#include <string>
#include <iostream>
#include "Pizza.h"
#include "WRtopping.h"


using namespace std;

//Empty constructor. Initializes Pizza to 0 toppings
Pizza::Pizza() {
  toppings = 0;   //avoids segmentation fault
  initialize(0);
}

Pizza::Pizza(int numberOfToppings) {
  toppings = 0;   //avoids segmentation fault
  initialize(numberOfToppings);
}

void Pizza::initialize(int numberOfToppings) {
  //If pizza toppings have been initalized then we have to
  //delete that dynamic array
  if(toppings != 0) {
    delete[] toppings;
  }
  toppings = new Topping[numberOfToppings];

  //Reset member variables
  bottomType = ' ';
  toppingsCount = numberOfToppings;
  toppingCounter = 0;
  pizzaName = "";
  vbose = true;
}

void Pizza::resetToppingCount(int numberOfToppings) {
  if(toppings != 0) {
    delete[] toppings;
  }

  toppings = new Topping[numberOfToppings];
  toppingsCount = numberOfToppings;
  toppingCounter = 0;
}

void Pizza::addTopping(Topping newTopping) {
  //If we still have room for toppings
  if(toppingCounter < toppingsCount) {
    toppings[toppingCounter] = newTopping;  //add the topping
    toppingCounter++;                       //increment the counter
  }
}

void Pizza::setPizzaName(string name) {
  pizzaName = name;
}

void Pizza::setVerbose(bool set) {
  vbose = set;
}

Pizza::~Pizza() {
  //destructor

  //let's avoid the nullpointer exception
  if (toppings != 0) {
    delete[] toppings;
  }
}


//friend functions

//Pizza data is on the form
//pizzaName bottomType
//or if pizzaName is literally "custom" then
//pizzaName bottomType numberOfToppings <list of toppings>

ostream& operator << (ostream& out, const Pizza& pizza) {
  out << pizza.pizzaName << " " << pizza.bottomType << " ";
  out << pizza.toppingsCount << " ";

  for(int i = 0; i < pizza.toppingsCount; i++) {
    out << pizza.toppings[i] << " ";
  }
  out << endl;

  return out;
}

istream& operator >> (istream& in, Pizza& pizza) {

  if(pizza.vbose) {
    cout << "Name of pizza: ";
  }
  in >> pizza.pizzaName;

  if(pizza.vbose) {
    cout << "Type of pizza bottom: ";
  }
  in >> pizza.bottomType;

  if(pizza.vbose) {
    cout << "Number of toppings on pizza: ";
  }
  int numberOfToppings;
  cin >> numberOfToppings;
  pizza.resetToppingCount(numberOfToppings);

  WRtopping wrtopping;

  for(int i = 0; i < numberOfToppings; i++) {
    Topping newTopping;
    int numberOfAvailableToppings = wrtopping.listAndCountToppings();
    int selection;
    cin >> selection;
    wrtopping.selectTopping(selection, newTopping);
    pizza.addTopping(newTopping);
  }

  return in;
}
