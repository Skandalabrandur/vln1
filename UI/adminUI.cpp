#include "adminUI.h"

void adminUI::displayAdminMenu() {
  char userInput = 'i';     //init to invalid just in case
  while (userInput != 'b') {
    do {
      uf.clearScreen();
      cout << "P - MANAGE PIZZAS" << endl;
      cout << "T - MANAGE TOPPINGS" << endl;
      cout << "L - MANAGE LOCATIONS" << endl;
      cout << "A - MANAGE ADDITIONAL PRODUCTS" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "ptbla"));

    userInput = tolower(userInput);

    if(userInput == 'p') {
      displayPizzaMenu();
    }

    if(userInput == 't') {
      displayToppingMenu();
    }

    if(userInput == 'l') {
        displayLocationMenu();
    }

    if(userInput == 'a') {
        displayAdditionalProductsMenu();
    }
  }
}

void adminUI::displayPizzaMenu() {
  char userInput;
  while(userInput != 'b') {
    do {
      userInput = 'i'; //for invalid so that we don't end up with an infinte loop
      uf.clearScreen();
      cout << "C - CREATE A NEW MENU PIZZA" << endl;
      cout << "L - LIST MENU PIZZAS" << endl;
      cout << "D - DELETE MENU PIZZA" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "cldb"));

    userInput = tolower(userInput);

    if(userInput == 'c') {
      if(vs.toppingsExist()) {
        pizza_service.createAndAppendMenuPizza();
      } else {
        cout << "No toppings exist!" << endl;
        uf.pressEnter();
      }
    }

    if(userInput == 'l') {
      uf.clearScreen();
      if(vs.menuPizzasExist()) {
          pizza_service.listMenuPizzas();
      } else {
        cout << "No menu pizzas exist!" << endl;
      }
      uf.pressEnter();
    }

    if(userInput == 'd') {
      uf.clearScreen();
      if(vs.menuPizzasExist()) {
        pizza_service.deleteMenuPizza();
      } else {
        cout << "No menu pizzas exist!" << endl;
      }
      uf.pressEnter();
    }
  }
}

void adminUI::displayToppingMenu() {
  char userInput = 'i';     //init to invalid just in case
  while(userInput != 'b') {
    do {
      uf.clearScreen();
      cout << "C - CREATE NEW TOPPING" << endl;
      cout << "L - LIST TOPPINGS" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "clb"));

    userInput = tolower(userInput);

    if(userInput == 'c') {
      topping_service.createNewTopping();
    }

    if(userInput == 'l') {
      if(vs.toppingsExist()) {
        uf.clearScreen();
        topping_service.listToppings();
      } else {
        cout << "No toppings exist!" << endl;
      }
      uf.pressEnter();
    }
  }
}

void adminUI::displayLocationMenu() {
    char userInput = 'i';     //init to invalid just in case
    while(userInput != 'b') {
        do {
            uf.clearScreen();
            cout << "C - CREATE NEW LOCATION" << endl;
            cout << "L - LIST LOCATIONS" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "clb"));

        userInput = tolower(userInput);

        if(userInput == 'c') {
            location_service.createNewLocation();
        }

        if(userInput == 'l') {
          if(vs.locationsExist()) {
            uf.clearScreen();
            location_service.listLocations();
          } else {
              cout << "No locations exist!" << endl;
          }
          uf.pressEnter();
        }
    }
}

void adminUI::displayAdditionalProductsMenu(){
    char userInput = 'i';     //init to invalid just in case
    while(userInput != 'b') {
        do {
            uf.clearScreen();
            cout << "C - CREATE NEW ADDITIONAL PRODUCT" << endl;
            cout << "L - LIST ADDITIONAL PRODUCTS" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "clb"));

        userInput = tolower(userInput);

        if(userInput == 'c') {
            uf.clearScreen();
            additionalProduct_service.createNewAdditionalProduct();
        }

        if(userInput == 'l') {
          if(vs.addProductsExist()) {
            uf.clearScreen();
            additionalProduct_service.listAdditionalProducts();
          } else {
            cout << "No additional products exist!" << endl;
            uf.pressEnter();
          }
        }
    }
}
