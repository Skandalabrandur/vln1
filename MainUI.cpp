#include "MainUI.h"
#include "Pizza.h"
#include "WRpizza.h"
#include "WRtopping.h"
#include <string>

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

void MainUI::startUI() {
  char choice;
  do {
    cout << "M - MANAGEMENT" << endl;
    cout << "S - SALES" << endl;
    cout << "B - BAKERS" << endl;
    cout << "D - DELIVERY" << endl;
    cout << endl << "Q - QUIT" << endl;
    cin >> choice;

  } while( !good_choice(choice, "msbdqMSBDQ", 8));

  if(choice == 'm' || choice == 'M') {
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
}

void MainUI::bakersUI() {
  cout << "bakersUI not yet implemented. You will return to main menu" << endl;
}

void MainUI::deliveryUI() {
  cout << "deliveryUI not yet implemented. You will return to main menu" << endl;
}

void MainUI::manage_pizzas() {
  char choice;
  do {
    cout << "What do?" << endl << endl;
    cout << "P - Create Pizza" << endl;
    cout << "Q - Quit" << endl;
    cin >> choice;
  } while ( !good_choice(choice, "pqPQ", 4) );
  if(choice == 'p' || choice == 'P') {
    Pizza pizza;
    cin >> pizza;
    cout << "Created: " << pizza << endl;
    WRpizza writer;
    writer.saveNewPizza(pizza);
  }
}

void MainUI::manage_toppings() {
  char choice;
  do {
    cout << "What do?" << endl << endl;
    cout << "T - Create Toppings" << endl;
    cout << "Q - Quit" << endl;
    cin >> choice;
  } while ( !good_choice(choice, "tTqQ", 4));

  if(choice == 't' || choice == 'T') {
    Topping topping;
    cin >> topping;
    cout << "Created: " << topping << endl;
    WRtopping writer;
    writer.saveNewTopping(topping);
  }
}
