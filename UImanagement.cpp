#include "UImanagement.h"
#include "WRpizza.h"
#include "WRtopping.h"

void UImanagement::managementUI() {
  char choice;
  do {
    cout << "P - Manage Pizzas" << endl;
    cout << "T - Manage Toppings" << endl;
    cout << endl << "B - Go Back" << endl;
    cin >> choice;
  } while( !ui.good_choice(choice, "pPbBtT"));

  if(choice == 'P' || choice == 'p') {
    manage_pizzas();
  }

  if(choice == 't' || choice == 'T') {
    manage_toppings();
  }

}

void UImanagement::manage_pizzas() {
  char choice;
  do {
    ui.clearScreen();
    cout << "What do?" << endl << endl;
    cout << "C - Create Pizza" << endl;
    cout << "Q - Quit" << endl;
    cin >> choice;
  } while ( !ui.good_choice(choice, "cqCQ") );

  //We need to check if toppings exists

  if(choice == 'c' || choice == 'C') {
    ui.clearScreen();
    WRpizza writer;
    WRtopping examiner;
      if(examiner.toppingsExist()) {
        Pizza pizza;
        cin >> pizza;
        ui.clearScreen();
        cout << endl << "Created: " << pizza << endl;
        writer.saveNewPizza(pizza);
        ui.pressEnter();
    } else {
      cout << "No toppings exist" << endl;
      cout << "Create some toppings in the system via" << endl;
      cout << "\tManage->Manage Toppings->Create Topping" << endl;
      ui.pressEnter();
    }
  }
}

void UImanagement::manage_toppings() {
  char choice;
  do {
    ui.clearScreen();
    cout << "What do?" << endl << endl;
    cout << "C - Create Topping" << endl;
    cout << "L - List Toppings" << endl;
    cout << "Q - Quit" << endl;
    cin >> choice;
  } while ( !ui.good_choice(choice, "cCqQlL"));

  if(choice == 'c' || choice == 'C') {
    ui.clearScreen();
    Topping topping;
    cin >> topping;
    cout << "Created: " << topping << endl;
    WRtopping writer;
    writer.saveNewTopping(topping);
    ui.pressEnter();
  }

  if(choice == 'l' || choice == 'L') {
    ui.clearScreen();
    WRtopping reader;
    reader.listToppings();
    ui.pressEnter();
  }
}
