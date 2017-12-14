#include "deliveryUI.h"

void deliveryUI::displayDeliveryMenu(){
    //TO DO: choose location
    uf.clearScreen();
    chooseLocation();

    char userInput;
    while (userInput != 'b') {
        do {
            uf.clearScreen();
            cout << "HOME/DELIVERY" << endl << endl;
            cout << "1 - LIST ALL ORDERS FOR YOUR PLACE" << endl;
            cout << "2 - LIST READY ORDERS FOR YOUR PLACE" << endl;
            cout << "3 - MARK ORDER AS PAID" << endl;
            cout << "4 - MARK ORDER AS DELIVERED" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "1234b"));

        userInput = tolower(userInput);

        if(userInput == '1') {
          if(vs.ordersExistForLocationID(_locationID)){
              uf.clearScreen();
              cout << "HOME/DELIVERY/LIST ALL ORDERS" << endl << endl;
              //False to show all orders not just ready orders
              viewOrders(false);
          } else {
              cout << "No orders exist for your location!" << endl;
              uf.pressEnter();
          }
        }

        else if(userInput == '2') {
          if(vs.readyOrdersExistForLocationID(_locationID)){
              uf.clearScreen();
              cout << "HOME/DELIVERY/LIST READY ORDERS" << endl << endl;
              //True to show only ready orders
              viewOrders(true);
          } else{
              cout << "No ready orders exist for your location!" << endl;
              uf.pressEnter();
          }
        }

        else if(userInput == '3') {
            if(vs.ordersExistForLocationID(_locationID)){
              uf.clearScreen();
              cout << "HOME/DELIVERY/MARK PAID" << endl << endl;
              selectAndMarkOrderAsPaid();
            } else{
              cout << "No orders exist for your location!" << endl;
            }
            uf.pressEnter();
        }

        else if(userInput == '4') {
            if(vs.readyOrdersExistForLocationID(_locationID)){
              uf.clearScreen();
              cout << "HOME/DELIVERY/MARK DELIVERED" << endl << endl;
              selectAndMarkOrderAsDelivered();
            } else{
              cout << "No ready orders exist for your location!" << endl;
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
    int choice = -1; //So the value is not 0
    int numOrders = order_service.howManyOrdersForLocation(_locationID);
    do{
        uf.clearScreen();
        order_service.listOrderFromLocationWithID(_locationID, isReady);
        cout << "Select an order for more info (c to cancel): ";
        cin >> choice;

        if(cin.fail()) {
            cin.clear(); //clear error flags
            choice = 0;  //appropriate quit condition
        }
        if(choice >= 1 && choice <= numOrders){
            uf.clearScreen();
            int orderID = order_service.getOrderIdFromIndexSelectionForLocation(choice, _locationID);
            order_service.deliveryListSpecificOrderFromLocationWithInfo(orderID, _locationID);
            uf.pressEnter();
            uf.clearScreen();
        }
    }while((choice < 0) || (choice > numOrders));
}

void deliveryUI::selectAndMarkOrderAsPaid(){
    int index = -1;
    while(index < 0 || index > order_service.howManyOrdersForLocation(_locationID)) {
        uf.clearScreen();
        //False to show all orders not just ready orders
        order_service.listOrderFromLocationWithID(_locationID, false);
        cout << "Please select an order to mark as PAID (c to cancel): ";
        cin >> index;
        if(cin.fail()) {
            cin.clear();  //clear error flags
            index = 0;    //appropriate quit condition
        }
    }
    int orderID = order_service.getOrderIdFromIndexSelectionForLocation(index, _locationID);
    order_service.markPizzaAsPaidByOrderIDAndLocation(orderID, _locationID);
}

void deliveryUI::selectAndMarkOrderAsDelivered(){
    int index = -1;
    while(index < 0 || index > pizza_service.howManyActivePizzasForLocation(_locationID)) {
        uf.clearScreen();
        //False to show all orders not just ready orders
        order_service.listOrderFromLocationWithID(_locationID, false);
        cout << "Please select a order to mark as DELIVERED (c to cancel): ";
        cin >> index;
        if(cin.fail()) {
            cin.clear();    //clear error flags
            index = 0;      //appropriate quit condition
        }
    }
    int orderID = order_service.getOrderIdFromIndexSelectionForLocation(index, _locationID);
    order_service.markPizzaAsDeliveredByOrderIDAndLocation(orderID, _locationID);
}
