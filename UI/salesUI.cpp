#include "salesUI.h"

void salesUI::displaySalesMenu() {
  char userInput;
  while (userInput != 'b') {
    do {
      uf.clearScreen();
      cout << "P - PLACE ORDER" << endl;
      cout << "L - LIST ORDERS" << endl;
      cout << "D - MARK ORDER AS DELIVERED" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "plbd"));

    userInput = tolower(userInput);

    if(userInput == 'p') {
      order_service.createNewOrder();
    }

    else if(userInput == 'l') {
      uf.clearScreen();
      order_service.listOrderOverviewWithIndices();
      int selection = -1;
      do{
          cout << "Select an order for more info (0 to quit): ";
          cin >> selection;
          if(selection > 1 && selection <= order_service.howManyOrders()){
              int adjustedSelection = order_service.getOrderIdFromIndexSelection(selection-1);
              uf.clearScreen();
              order_service.listSpecificOrderWithInfo(adjustedSelection);
          }
      }while((selection < 0) || (selection > order_service.howManyOrders()));
      uf.pressEnter();
    }

    else if(userInput == 'd') {
        selectAndMarkOrderAsDelivered();
    }
  }
}

void salesUI::selectAndMarkOrderAsDelivered(){
    int index = -1;
    while(index < 0 || index > order_service.howManyOrders()) {
        uf.clearScreen();
        order_service.listOrderOverviewWithIndices();
        cout << "Please select a order to mark as DELIVERED (0 to quit): ";
        cin >> index;
    }
    int orderID = order_service.getOrderID(index);
    order_service.markPizzaAsDeliveredByOrderID(orderID);
    uf.pressEnter();
}
