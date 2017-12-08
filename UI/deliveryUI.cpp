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
    //If it is possible to delete locations then this does not work
    _locationID = choice;
}

void deliveryUI::viewOrders(){
    uf.clearScreen();
    int choice = 1; //So the value is not 0
    do{
        //TO DO: list orders from chosen location
        order_service.listOrderOverviewWithIndices();
        cout << "Select an order for more info (0 to quit): ";
        if(choice != 0){
            cin >> choice;
            uf.clearScreen();
            order_service.listSpecificOrderWithInfo(choice);
            uf.pressEnter();
            uf.clearScreen();
        }
    }while(choice != 0);
}

void deliveryUI::selectAndMarkOrderAsPaid(){
    int index = -1;
    while(index < 1 || index > order_service.howManyOrders()) {
        uf.clearScreen();
        order_service.listOrderOverviewWithIndices();
        cout << "Please select a order to mark as PAID: ";
        cin >> index;
    }
    int orderID = order_service.getOrderID(index);
    order_service.MarkPizzaAsPaidByOrderID(orderID);
    uf.pressEnter();
}

void deliveryUI::selectAndMarkOrderAsDelivered(){
    int index = -1;
    while(index < 1 || index > order_service.howManyOrders()) {
        uf.clearScreen();
        order_service.listOrderOverviewWithIndices();
        cout << "Please select a order to mark as DELIVERED: ";
        cin >> index;
    }
    int orderID = order_service.getOrderID(index);
    order_service.MarkPizzaAsDeliveredByOrderID(orderID);
    uf.pressEnter();
}
