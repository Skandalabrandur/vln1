#include "mainUI.h"
using namespace std;

void mainUI::displayMainMenu() {
  char userInput;
  //The whole menu loops on 'q' for quit
  //Instead of quitting after choices are made elsewhere
  while(userInput != 'q') {
    do {
      uf.clearScreen();
      cout << "HOME" << endl;              //see UIFunctions.cpp
      cout << "A - ADMIN" << endl;
      cout << "S - SALES" << endl;
      cout << "B - BAKER" << endl;
      cout << "D - DELIVERY" << endl;
      cout << endl << "Q - QUIT" << endl;
      cout << endl << uf.prompt();   //see UIFunctions.cpp

      cin >> userInput;
    //see goodInput in customLibraries/UIFunctions.cpp
    } while(!uf.goodInput(userInput, "asbdq"));

    //tolower is a built-in function for converting to lowercase
    userInput = tolower(userInput);
    //I feel that a bunch of if conditionals are more
    //readable than a case-switch block
    if(userInput == 'a') {
      admin_ui.displayAdminMenu();
    }
    if(userInput == 's') {
      if(vs.salesMenuValid()) {
        sales_ui.displaySalesMenu();
      } else {
        cout << "Not a valid choice. Some data is missing!" << endl << "Please contact administrator" << endl;
        uf.pressEnter();
      }
    }
    if(userInput == 'b') {
      if(vs.bakerMenuValid()) {
        baker_ui.displayBakerMenu();
      } else {
        cout << "Not a valid choice. Some data is missing!" << endl << "Please contact administrator" << endl;
        uf.pressEnter();
      }
    }
    if(userInput == 'd') {
      if(vs.deliveryMenuValid()) {
        delivery_ui.displayDeliveryMenu();
      } else {
        cout << "Not a valid choice. Some data is missing!" << endl << "Please contact administrator" << endl;
        uf.pressEnter();
      }
    }
  }
}
