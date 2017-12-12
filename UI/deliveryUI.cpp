#include "deliveryUI.h"

void deliveryUI::displayDeliveryMenu(){
    //TO DO: choose location
    uf.clearScreen();
    chooseLocation();

    char userInput;
    while (userInput != 'b') {
        do {
            uf.clearScreen();
            cout << "HOME/DELIVERY" << endl;
            cout << "L - LIST ALL ORDERS FOR YOUR PLACE" << endl;
            cout << "R - LIST READY ORDERS FOR YOUR PLACE" << endl;
            cout << "P - MARK ORDER AS PAID" << endl;
            cout << "D - MARK ORDER AS DELIVERED" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "pbldr"));

        userInput = tolower(userInput);

        if(userInput == 'l') {
          if(vs.ordersExistForLocationID(_locationID)){
              uf.clearScreen();
              cout << "HOME/DELIVERY/LIST ALL ORDERS" << endl;
              //False to show all orders not just ready orders
              viewOrders(false);
          } else {
              cout << "No orders exist for your location!" << endl;
              uf.pressEnter();
          }
        }

        else if(userInput == 'r') {
          if(vs.ordersExistForLocationID(_locationID)){
              uf.clearScreen();
              cout << "HOME/DELIVERY/LIST READY ORDERS" << endl;
              //True to show only ready orders
              viewOrders(true);
          } else{
              cout << "No orders exist for your location!" << endl;
              uf.pressEnter();
          }
        }

        else if(userInput == 'p') {
            if(vs.ordersExistForLocationID(_locationID)){
              uf.clearScreen();
              cout << "HOME/DELIVERY/MARK PAID" << endl;
              selectAndMarkOrderAsPaid();
            } else{
              cout << "No orders exist for your location!" << endl;
            }
            uf.pressEnter();
        }

        else if(userInput == 'd') {
            if(vs.ordersExistForLocationID(_locationID)){
              uf.clearScreen();
              cout << "HOME/DELIVERY/MARK DELIVERED" << endl;
              selectAndMarkOrderAsDelivered();
            } else{
              cout << "No orders exist for your location!" << endl;
            }
            uf.pressEnter();
        }
    }

}

void deliveryUI::chooseLocation(){
    _locationID = 0;
    //Lists locations from file, user inputs their location
    location_service.listLocationsWithIndex();
    int numLocations = location_service.howManyLocations();
    int choice;
    do{
        cout << "Select your location: ";
        cin >> choice;

        if(cin.fail()) {
          cin.clear();    //reset error flags
          cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
          choice = 0;     //set choice to continue loop
        }
    }while(choice <= 0 || choice > numLocations);
    //If changed so admin can delete locations then this does probably not work
    //Could make a function getLocationID(choice)
    _locationID = choice;
}

int deliveryUI::getLocationID(){
    return _locationID;
}

void deliveryUI::viewOrders(bool isReady){
    int choice = 1; //So the value is not 0
    do{
        order_service.listOrderFromLocationWithID(_locationID, isReady);
        cout << "Select an order for more info (0 to quit): ";
        if(choice != 0){
            cin >> choice;
            uf.clearScreen();
            order_service.listSpecificOrderFromLocationWithInfo(choice, _locationID);
            uf.pressEnter();
            uf.clearScreen();
        }
    }while(choice != 0);
}

void deliveryUI::selectAndMarkOrderAsPaid(){
    int index = -1;
    while(index < 0 || index > order_service.howManyOrders()) {
        //TO FIX: If user inputs a number that is not on the location list
        //but is an order in the file it will get changed

        //False to show all orders not just ready orders
        order_service.listOrderFromLocationWithID(_locationID, false);
        cout << "Please select a order to mark as PAID (0 to quit): ";
        cin >> index;
    }
    int orderID = order_service.getOrderID(index);
    order_service.markPizzaAsPaidByOrderIDAndLocation(orderID, _locationID);
}

void deliveryUI::selectAndMarkOrderAsDelivered(){
    int index = -1;
    while(index < 0 || index > order_service.howManyOrders()) {
        //TO FIX: If user inputs a number that is not on the location list
        //but is an order in the file it will get changed

        //False to show all orders not just ready orders
        order_service.listOrderFromLocationWithID(_locationID, false);
        cout << "Please select a order to mark as DELIVERED (0 to quit): ";
        cin >> index;
    }
    int orderID = order_service.getOrderID(index);
    order_service.markPizzaAsDeliveredByOrderIDAndLocation(orderID, _locationID);
    //move to legacy file
}
