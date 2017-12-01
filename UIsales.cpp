//
//  UIsales.cpp
//
//
//  Created by Hlynur Hólm Hauksson on 30/11/2017.
//

#include "UIsales.h"
#include "SalesPizza.h"
using namespace std;

void UIsales::salesUI(){
    char choice;
    do {
        ui.clearScreen();
        cout << "What do?" << endl << endl;
        cout << "N - New Order" << endl;
        cout << "C - Change Order" << endl;
        cout << "L - List Orders" << endl;
        cout << "Q - Quit" << endl;
        cin >> choice;
      } while ( !ui.good_choice(choice, "nNqQcClL"));
      cout << "Not yet implemented. " << endl;
        ui.pressEnter();
}

void UIsales::orderPizza(){
    SalesPizza pizza;
    cin >> pizza;
}

void UIsales::orderPizzaMenu(){

}
