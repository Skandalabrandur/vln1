#include "salesUI.h"

void salesUI::displaySalesMenu() {
  char userInput;
  while (userInput != 'b') {
    do {
      uf.clearScreen();
      cout << "HOME/SALES" << endl << endl;
      cout << "1 - PLACE ORDER" << endl;
      cout << "2 - LIST ORDERS" << endl;
      cout << "3 - MARK ORDER AS DELIVERED" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "123b"));

    userInput = tolower(userInput);

    if(userInput == '1') {
      uf.clearScreen();
      cout << "HOME/SALES/PLACE ORDER" << endl << endl;
      order_service.createNewOrder();
      uf.pressEnter();
    }

    else if(userInput == '2') {
      if(vs.ordersExist()) {
        uf.clearScreen();
        cout << "HOME/SALES/LIST ORDERS" << endl << endl;
        listOrders();
      } else {
        cout << "No orders exist!" << endl;
      }
      uf.pressEnter();
    }

    else if(userInput == '3') {
      if(vs.ordersExist()) {
        uf.clearScreen();
        cout << "HOME/SALES/MARK PAID" << endl << endl;
        selectAndMarkOrderAsPaid();
      } else {
        cout << "No orders exist!" << endl;
        uf.pressEnter();
      }
    }
  }
}

void salesUI::selectAndMarkOrderAsPaid(){
  int index = -1;
  while(index < 0 || index > order_service.howManyOrders()) {
      //TO FIX: If user inputs a number that is not on the location list
      //but is an order in the file it will get changed

      listOrders();
      cout << "Please select a order to mark as PAID (0 to quit): ";
      cin >> index;
  }
  int orderID = order_service.getOrderID(index);
  order_service.markPizzaAsPaidByOrderID(orderID);
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
