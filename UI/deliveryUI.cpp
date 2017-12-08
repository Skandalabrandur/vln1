#include "deliveryUI.h"

void deliveryUI::displayDeliveryMenu(){
    //DO DO: choose location
    uf.clearScreen();
    chooseLocation();

    char userInput;
    while (userInput != 'b') {
        do {
            uf.clearScreen();
            cout << "L - LIST ORDERS" << endl;
            cout << "P - MARK ORDER AS PAID" << endl;
            cout << "D - MARK ORDER AS DELIVERED" << endl;
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

void deliveryUI::chooseLocation(){
    //lists locations from file, user inputs their location
    location_service.listLocationsWithIndex();
    int numLocations = location_service.howManyLocations();
    int choice;
    do{
        cout << "Select your location: ";
        cin >> choice;
    }while(choice <= 0 || choice > numLocations);
    //TO DO: how to keep location info, private variable?
}

void deliveryUI::viewOrders(){
    uf.clearScreen();
    int id = 1;
    do{
        order_service.listOrderOverviewWithIndices();
        cout << "Select an order for more info (0 to quit): ";
        if(id != 0){
            cin >> id;
            uf.clearScreen();
            order_service.listSpecificOrderWithInfo(id);
            uf.pressEnter();
            uf.clearScreen();
        }
    }while(id != 0);
}

void deliveryUI::selectAndMarkOrderAsPaid(){

    uf.pressEnter();
}

void deliveryUI::selectAndMarkOrderAsDelivered(){

    uf.pressEnter();
}
