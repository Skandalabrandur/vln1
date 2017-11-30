#include "MainUI.h"
#include "AdminPizza.h"
#include "WRpizza.h"
#include "WRtopping.h"
#include "UImanagement.h"
#include "UIsales.h"
#include <string>

//Solution taken from:
//http://www.cplusplus.com/articles/4z18T05o/
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

using namespace std;


//char chosen is input from user
//legitChoices is a string of legit characters e.g. "aAbBcC"
bool MainUI::good_choice(char chosen, string legitChoices) {
  bool legit = false; //initialize return to false
  int numOfChoices = legitChoices.size();
  for(int i = 0; i < numOfChoices; i++) {
    if(chosen == legitChoices[i]) {
      legit = true;   //the function will now return true
      break;
    }
  }

  return legit;
}

void MainUI::clearScreen() {
  //Solution from:
  //http://www.cplusplus.com/articles/4z18T05o/
  if (system("CLS")) system("clear");
}

void MainUI::pressEnter() {
  cout << "Press enter to continue" << endl;
  cin.ignore();     //ignore cin buffer (for instance if it contains '\n')
  cin.get();        //Halts program until user presses the Enter key
}

void MainUI::startUI() {
  char choice;
  do {
    clearScreen();
    cout << "M - MANAGEMENT" << endl;
    cout << "S - SALES" << endl;
    cout << "B - BAKERS" << endl;
    cout << "D - DELIVERY" << endl;
    cout << endl << "Q - QUIT" << endl;
    cin >> choice;

  } while( !good_choice(choice, "msbdqMSBDQ"));

  if(choice == 'm' || choice == 'M') {
    UImanagement uimanagement;
    clearScreen();
    uimanagement.managementUI();
  }

  if(choice == 's' || choice == 'S') {
    salesUI();
  }

  if(choice == 'b' || choice == 'B') {
    bakersUI();
  }

  if(choice == 'd' || choice == 'D') {
    deliveryUI();
  }

  //Gets called after users exits any chosen UI
  if(choice != 'q' && choice != 'Q') {
    //trigger main menu again
    startUI();
  }

}


void MainUI::salesUI() {
    clearScreen();
    cout << "O - ORDER PIZZA" << endl;
    cout << "M - ORDER PIZZA FROM MENU" << endl << endl;
    cout << "B - BACK" << endl;
    UIsales uisales;
    char choice;
    cin >> choice;
    if(choice == 'o' || choice == 'O') {
        clearScreen();
        uisales.orderPizza();
    }
    
    if(choice == 'm' || choice == 'M') {
        clearScreen();
        uisales.orderPizzaMenu();
    }
    //Gets called after users exits any chosen UI
    if(choice != 'q' && choice != 'Q') {
        //trigger main menu again
        startUI();
    }
}

void MainUI::bakersUI() {
  cout << "bakersUI not yet implemented. <enter>You will return to main menu" << endl;
  pressEnter();
}

void MainUI::deliveryUI() {
  cout << "deliveryUI not yet implemented. <enter>You will return to main menu" << endl;
  pressEnter();
}
