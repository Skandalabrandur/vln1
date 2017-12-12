#include "salesUI.h"

void salesUI::displaySalesMenu() {
  char userInput;
  while (userInput != 'b') {
    do {
      uf.clearScreen();
      cout << "HOME/SALES" << endl;
      cout << "P - PLACE ORDER" << endl;
      cout << "L - LIST ORDERS" << endl;
      cout << "D - MARK ORDER AS DELIVERED" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "plbd"));

    userInput = tolower(userInput);

    if(userInput == 'p') {
      uf.clearScreen();
      cout << "HOME/SALES/PLACE ORDER" << endl;
      order_service.createNewOrder();
      uf.pressEnter();
    }

    else if(userInput == 'l') {
      if(vs.ordersExist()) {
        uf.clearScreen();
        cout << "HOME/SALES/LIST ORDERS" << endl;
        listOrders();
      } else {
        cout << "No orders exist!" << endl;
      }
      uf.pressEnter();
    }

    else if(userInput == 'd') {
      if(vs.ordersExist()) {
        uf.clearScreen();
        cout << "HOME/SALES/MARK DELIVERED" << endl;
        selectAndMarkOrderAsDelivered();
      } else {
        cout << "No orders exist!" << endl;
        uf.pressEnter();
      }
    }
  }
}

void salesUI::selectAndMarkOrderAsDelivered(){
    int index = -1;
    while(index < 0 || index > order_service.howManyOrders()) {
        order_service.listOrderOverviewWithIndices();
        cout << "Please select an order to mark as DELIVERED (c to cancel): ";
        cin >> index;
        if(cin.fail()) {
          cin.clear();  //clear error flags
          index = 0;    //appropriate quit condition
        }
    }
    int orderID = order_service.getOrderID(index);
    int locationID = order_service.getOrderLocationID(index);
    order_service.markPizzaAsDeliveredByOrderIDAndLocation(orderID, locationID);
    //move to legacy file
    uf.pressEnter();
}

void salesUI::listOrders() {
  order_service.listOrderOverviewWithIndices();
  int selection = -1;
  do{
      cout << "Select an order for more info (c to cancel): ";
      cin >> selection;
      if(cin.fail()) {
        cin.clear();    //clear error flags
        selection = 0;  //appropriate quit condition
      }
      if(selection >= 1 && selection <= order_service.howManyOrders()){
          int adjustedSelection = order_service.getOrderIdFromIndexSelection(selection-1);
          uf.clearScreen();
          cout << adjustedSelection << endl;
          order_service.listSpecificOrderWithInfo(adjustedSelection);
      }
  }while((selection < 0) || (selection > order_service.howManyOrders()));
}
