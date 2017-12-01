#ifndef SalesPizza_h
#define SalesPizza_h

#include <stdio.h>
#include <string>
#include "Topping.h"

class SalesPizza {

public:
    SalesPizza();
    void resetToppingCount(int numberOfToppings);
    void addTopping(Topping newTopping);
    friend ostream& operator << (ostream& out, const SalesPizza& pizza);
    friend istream& operator >> (istream& in, SalesPizza& pizza);

private:
    Topping *toppings;    //A pointer for the dynamic array of toppings
    char bottomType;      //Type of pizza bottom (classic, italian, etc)
    int toppingsCount;    //How many toppings will be on the pizza?
    int toppingCounter;   //How many toppings have we added so far?
    string pizzaName;     //What is the name of the pizza?
    string placeName;     //Name of the place where the pizza is made and sold
    bool vbose;           //Will the pizza creation be verbose?
};

#endif /* SalesPizza_h */
