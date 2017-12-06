#include "mainUI.h"
using namespace std;

void mainUI::displayMainMenu() {
  char userInput;
  while(userInput != 'q') {
    do {
      uf.clearScreen();
      cout << "A - ADMIN" << endl;
      cout << "S - SALES" << endl;
      cout << "B - BAKER" << endl;
      cout << "D - DELIVERY" << endl;
      cout << endl << "Q - QUIT" << endl;
      cout << endl << uf.prompt();

      cin >> userInput;
    } while(!uf.goodInput(userInput, "asbdq"));

    userInput = tolower(userInput);

    if(userInput == 'a') {
      admin_ui.displayAdminMenu();
    }

    if(userInput == 's') {
      sales_ui.displaySalesMenu();
    }
    if(userInput == 'b') {
        baker_ui.displayBakerMenu();
    }

  }
}
