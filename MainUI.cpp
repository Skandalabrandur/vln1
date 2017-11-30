#include "MainUI.h"
#include "Pizza.h"
#include "WRpizza.h"
#include "WRtopping.h"
#include <string>

//Solution taken from:
//http://www.cplusplus.com/articles/4z18T05o/
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

using namespace std;


//checks if character is found in the availableChoices string
bool MainUI::good_choice(char chosen, string legitChoices, int numOfChoices) {
  bool legit = false; //initialize return to false

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

  } while( !good_choice(choice, "msbdqMSBDQ", 8));

  if(choice == 'm' || choice == 'M') {
    clearScreen();
    managementUI();
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

void MainUI::managementUI() {
  char choice;
  do {
    cout << "P - Manage Pizzas" << endl;
    cout << "T - Manage Toppings" << endl;
    cout << endl << "B - Go Back" << endl;
    cin >> choice;
  } while( !good_choice(choice, "pPbBtT", 6));

  if(choice == 'P' || choice == 'p') {
    manage_pizzas();
  }

  if(choice == 't' || choice == 'T') {
    manage_toppings();
  }

}

void MainUI::salesUI() {
  cout << "SalesUI not yet implemented. You will return to main menu" << endl;
  pressEnter();
}

void MainUI::bakersUI() {
  cout << "bakersUI not yet implemented. <enter>You will return to main menu" << endl;
  pressEnter();
}

void MainUI::deliveryUI() {
  cout << "deliveryUI not yet implemented. <enter>You will return to main menu" << endl;
  pressEnter();
}

void MainUI::manage_pizzas() {
  char choice;
  do {
    clearScreen();
    cout << "What do?" << endl << endl;
    cout << "C - Create Pizza" << endl;
    cout << "Q - Quit" << endl;
    cin >> choice;
  } while ( !good_choice(choice, "cqCQ", 4) );

  //We need to check if toppings exists

  if(choice == 'c' || choice == 'C') {
    clearScreen();
    WRpizza writer;
    WRtopping examiner;
      if(examiner.toppingsExist()) {
        Pizza pizza;
        cin >> pizza;
        clearScreen();
        cout << endl << "Created: " << pizza << endl;
        writer.saveNewPizza(pizza);
        pressEnter();
    } else {
      cout << "No toppings exist" << endl;
      cout << "Create some toppings in the system via" << endl;
      cout << "\tManage->Manage Toppings->Create Topping" << endl;
      pressEnter();
    }
  }
}

void MainUI::manage_toppings() {
  char choice;
  do {
    clearScreen();
    cout << "What do?" << endl << endl;
    cout << "C - Create Topping" << endl;
    cout << "L - List Toppings" << endl;
    cout << "Q - Quit" << endl;
    cin >> choice;
  } while ( !good_choice(choice, "cCqQlL", 6));

  if(choice == 'c' || choice == 'C') {
    clearScreen();
    Topping topping;
    cin >> topping;
    cout << "Created: " << topping << endl;
    WRtopping writer;
    writer.saveNewTopping(topping);
    pressEnter();
  }

  if(choice == 'l' || choice == 'L') {
    clearScreen();
    WRtopping reader;
    reader.listToppings();
    pressEnter();
  }
}
