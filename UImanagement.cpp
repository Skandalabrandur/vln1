#include "UImanagement.h"
#include "WRpizza.h"
#include "WRtopping.h"
#include "WRplace.h"

void UImanagement::managementUI() {
  char choice;
  do {
    cout << "P - Manage Pizzas" << endl;
    cout << "T - Manage Toppings" << endl;
    cout << "S - Manage Stores" << endl;
    cout << endl << "B - Go Back" << endl;
    cin >> choice;
  } while( !ui.good_choice(choice, "pPbBtTsS"));

  if(choice == 'P' || choice == 'p') {
    manage_pizzas();
  }

  if(choice == 't' || choice == 'T') {
    manage_toppings();
  }
  if(choice == 's' || choice == 'S') {
    manage_places();
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
        AdminPizza pizza;
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

void UImanagement::manage_places(){
  char choice;
  do {
    ui.clearScreen();
    cout << "What do?" << endl << endl;
    cout << "N - New Store" << endl;
    cout << "L - List Stores" << endl;
    cout << "Q - Quit" << endl;
    cin >> choice;
  } while ( !ui.good_choice(choice, "nNqQlL"));

  if(choice == 'n' || choice == 'N'){
    ui.clearScreen();
    Place place;
    place.setVerbose(true);
    cin >> place;
    cout << "Created: " << place << endl;
    WRplace writer;
    place.setVerbose(false);
    writer.saveNewPlace(place);
    ui.pressEnter();
  }
  else if(choice == 'l' || choice == 'L'){
    ui.clearScreen();
    WRplace reader;
    int count = reader.listAndCountPlaces();
    ui.pressEnter();
  }

}
