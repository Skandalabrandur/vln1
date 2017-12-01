#include <string>
#include <iostream>
#include "WRtopping.h"
#include "MainUI.h"
#include "SalesPizza.h"
#include "Topping.h"

SalesPizza::SalesPizza(){
    toppings = 0; //pointer
    bottomType = ' ';
    toppingsCount = 0;
    toppingCounter = 0;
    pizzaName = "";
    placeName = "";
    vbose = true;
}

void SalesPizza::resetToppingCount(int numberOfToppings) {
    if(toppings != 0) {
        delete[] toppings;
    }

    toppings = new Topping[numberOfToppings];
    toppingsCount = numberOfToppings;
    toppingCounter = 0;
}

void SalesPizza::addTopping(Topping newTopping) {
    //If we still have room for toppings
    if(toppingCounter < toppingsCount) {
        toppings[toppingCounter] = newTopping;  //add the topping
        toppingCounter++;                       //increment the counter
    }
}

ostream& operator << (ostream& out, const SalesPizza& pizza) {
    out << pizza.pizzaName << " " << pizza.bottomType << " ";
    out << pizza.toppingsCount << " ";

    for(int i = 0; i < pizza.toppingsCount; i++) {
        out << pizza.toppings[i] << " ";
    }
    out << endl;

    return out;
}

istream& operator >> (istream& in, SalesPizza& pizza) {
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

    if(pizza.vbose) {
        cout << "Type of pizza bottom: ";
    }
    in >> pizza.bottomType;


    return in;
}
