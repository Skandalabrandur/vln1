#include "deliveryUI.h"

void deliveryUI::displayDeliveryMenu(){
    //choose place
    char userInput;
    while (userInput != 'b') {
        do {
            uf.clearScreen();
            cout << "L - LIST ORDERS" << endl;
            cout << "P - MARK ORDER AS PAID" << endl;
            cout << "D - MARK PIZZA AS DELIVERED" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "pbld"));

        userInput = tolower(userInput);

        if(userInput == 'l') {
          viewOrders();
        }

        if(userInput == 'p') {
          selectAndMarkOrderAsPaid();
        }

        if(userInput == 'd') {
          selectAndMarkOrderAsDelivered();
        }
    }

}

void deliveryUI::viewOrders(){
    uf.clearScreen();
    //list orders
    uf.pressEnter();
}

void deliveryUI::selectAndMarkOrderAsPaid(){

    uf.pressEnter();
}

void deliveryUI::selectAndMarkOrderAsDelivered(){

    uf.pressEnter();
}
