#include "salesUI.h"

void salesUI::displaySalesMenu() {
  char userInput;
  while (userInput != 'b') {
    do {
      uf.clearScreen();
      cout << "P - PLACE ORDER" << endl;
      cout << "L - LIST ORDERS" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "plb"));

    userInput = tolower(userInput);

    if(userInput == 'p') {
      order_service.createNewOrder();
    }

    if(userInput == 'l') {
      uf.clearScreen();
      order_service.listOrderOverviewWithIndices();

      int selection;
      cout << "Select an order for more info: ";
      cin >> selection;

      int adjustedSelection = order_service.getOrderIdFromIndexSelection(selection-1);
      uf.clearScreen();
      order_service.listSpecificOrderWithInfo(adjustedSelection);
      uf.pressEnter();
    }
  }
}
