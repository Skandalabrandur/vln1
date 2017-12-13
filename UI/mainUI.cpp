#include "mainUI.h"
using namespace std;

void mainUI::displayMainMenu() {
  char userInput;
  //The whole menu loops on 'q' for quit
  //Instead of quitting after choices are made elsewhere
  while(userInput != 'q') {
    do {
      uf.clearScreen();               //see UIFunctions.cpp
      cout << "HOME" << endl << endl;
      cout << "1 - ADMIN" << endl;
      cout << "2 - SALES" << endl;
      cout << "3 - BAKER" << endl;
      cout << "4 - DELIVERY" << endl;
      cout << endl << "Q - QUIT" << endl;
      cout << endl << uf.prompt();   //see UIFunctions.cpp

      cin >> userInput;
    //see goodInput in customLibraries/UIFunctions.cpp
    } while(!uf.goodInput(userInput, "1234q"));

    //tolower is a built-in function for converting to lowercase
    userInput = tolower(userInput);
    //I feel that a bunch of if conditionals are more
    //readable than a case-switch block
    if(userInput == '1') {
        if(admin_ui.requestPassword()){
            admin_ui.displayAdminMenu();
        }
    }
    if(userInput == '2') {
      if(vs.salesMenuValid()) {
        sales_ui.displaySalesMenu();
      } else {
        if(!vs.toppingsExist()) {
          cout << "There are no toppings in the system. " << endl;
        }
        cout << endl;
        if(!vs.locationsExist()) {
          cout << "There are no store locations in the system" << endl;
        }

        cout << endl << "Please contact Administrator" << endl;
        uf.pressEnter();
      }
    }
    if(userInput == '3') {
      if(vs.bakerMenuValid()) {
        baker_ui.displayBakerMenu();
      } else {
        if(!vs.activePizzasExist()) {
          cout << "There are no pizzas active in the system. Nothing to bake!" << endl;
          cout << "I suggest you go clean the kitchen in the meanwhile, if needed" << endl;
        }

        if(!vs.locationsExist()) {
          cout << "There are no store locations in the system." << endl;
          cout << "If you're in a kitchen right now it techically shouldn't exist!" << endl;
          cout << "Please contact an administrator!" << endl;
        }
        uf.pressEnter();
      }
    }
    if(userInput == '4') {
      if(vs.deliveryMenuValid()) {
        delivery_ui.displayDeliveryMenu();
      } else {
        if(!vs.locationsExist()) {
          cout << "There are no store locations in the system." << endl;
          cout << "If you're working the register somewhere then techically..." << endl;
          cout << "\tThat place shouldn't exist." << endl;
          cout << "Please contact and administrator" << endl;
        }

        if(!vs.activePizzasExist()) {
          cout << "There are no active pizzas in the system" << endl;
          cout << "Relax, read a book. But don't complain about your minimum wages" << endl;
          cout << "\t ...please." << endl;
        }
        uf.pressEnter();
      }
    }
  }
}
