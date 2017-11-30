#include <string>
#include <iostream>
#include "AdminPizza.h"
#include "WRtopping.h"
#include "MainUI.h"

using namespace std;

//Empty constructor. Initializes AdminPizza to 0 toppings
AdminPizza::AdminPizza() {
  toppings = 0;   //avoids segmentation fault
  initialize(0);
}

AdminPizza::AdminPizza(int numberOfToppings) {
  toppings = 0;   //avoids segmentation fault
  initialize(numberOfToppings);
}

void AdminPizza::initialize(int numberOfToppings) {
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
  placeName = "";
  vbose = true;
}

void AdminPizza::resetToppingCount(int numberOfToppings) {
  if(toppings != 0) {
    delete[] toppings;
  }

  toppings = new Topping[numberOfToppings];
  toppingsCount = numberOfToppings;
  toppingCounter = 0;
}

void AdminPizza::addTopping(Topping newTopping) {
  //If we still have room for toppings
  if(toppingCounter < toppingsCount) {
    toppings[toppingCounter] = newTopping;  //add the topping
    toppingCounter++;                       //increment the counter
  }
}

void AdminPizza::setPizzaName(string name) {
  pizzaName = name;
}

void AdminPizza::setVerbose(bool set) {
  vbose = set;
}

AdminPizza::~AdminPizza() {
  //destructor

  //let's avoid the nullpointer exception
  if (toppings != 0) {
    delete[] toppings;
  }
}


//friend functions

//AdminPizza data is on the form
//pizzaName bottomType
//or if pizzaName is literally "custom" then
//pizzaName bottomType numberOfToppings <list of toppings>

ostream& operator << (ostream& out, const AdminPizza& pizza) {
  out << pizza.pizzaName << " " << pizza.bottomType << " ";
  out << pizza.toppingsCount << " ";

  for(int i = 0; i < pizza.toppingsCount; i++) {
    out << pizza.toppings[i] << " ";
  }
  out << endl;

  return out;
}

istream& operator >> (istream& in, AdminPizza& pizza) {

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
  MainUI clearFunction;

  for(int i = 0; i < numberOfToppings; i++) {
    clearFunction.clearScreen();
    Topping newTopping;
    int numberOfAvailableToppings = wrtopping.listAndCountToppings();
    int selection;

    if(pizza.vbose) {
      cout << "Select ingredient " << (i+1) << " of " << numberOfToppings << endl;
    }

    cin >> selection;
    wrtopping.selectTopping(selection, newTopping);
    pizza.addTopping(newTopping);
  }

  return in;
}