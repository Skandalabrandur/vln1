#include "adminUI.h"

void adminUI::displayAdminMenu() {
  char userInput = 'i';     //init to invalid just in case
  while (userInput != 'b') {
    do {
      uf.clearScreen();
      cout << "HOME/ADMIN" << endl;
      cout << "P - MANAGE MENU PIZZAS" << endl;
      cout << "T - MANAGE TOPPINGS" << endl;
      cout << "L - MANAGE STORE LOCATIONS" << endl;
      cout << "A - MANAGE ADDITIONAL PRODUCTS" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "ptbla"));

    userInput = tolower(userInput);

    if(userInput == 'p') {
      uf.clearScreen();
      displayPizzaMenu();
    }

    if(userInput == 't') {
      uf.clearScreen();
      cout << "HOME/ADMIN/MANAGE TOPPINGS" << endl;
      displayToppingMenu();
    }

    if(userInput == 'l') {
      uf.clearScreen();
      cout << "HOME/ADMIN/MANAGE LOCATIONS" << endl;
      displayLocationMenu();
    }

    if(userInput == 'a') {
      uf.clearScreen();
      cout << "HOME/ADMIN/MANAGE ADDITIONAL PRODUCTS" << endl;
      displayAdditionalProductsMenu();
    }
  }
}

void adminUI::displayPizzaMenu() {
  char userInput;
  while(userInput != 'b') {
    do {
      userInput = 'i'; //for invalid so that we don't end up with an infinte loop
      cout << "HOME/ADMIN/MANAGE MENU PIZZAS" << endl;
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
        uf.clearScreen();
        cout << "HOME/ADMIN/MANAGE MENU PIZZAS/CREATE NEW MENU PIZZA" << endl;
        pizza_service.createAndAppendMenuPizza();
        //ath s�nir ekki cout setnigu � fallinu
        cin >> ws;
        uf.pressEnter();
        uf.clearScreen();
      } else {
        cout << "No toppings exist!" << endl;
        uf.pressEnter();
      }
    }

    if(userInput == 'l') {
      if(vs.menuPizzasExist()) {
          uf.clearScreen();
          cout << "HOME/ADMIN/MANAGE MENU PIZZAS/LIST MENU PIZZAS" << endl;
          pizza_service.listMenuPizzas();
      } else {
        cout << "No menu pizzas exist!" << endl;
      }
      uf.pressEnter();
    }

    if(userInput == 'd') {
      if(vs.menuPizzasExist()) {
        uf.clearScreen();
        cout << "HOME/ADMIN/MANAGE MENU PIZZAS/DELETE MENU PIZZA" << endl;
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
      cout << "C - CREATE NEW TOPPING" << endl;
      cout << "L - LIST TOPPINGS" << endl;
      cout << "D - DELETE TOPPING" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "cldb"));

    userInput = tolower(userInput);

    if(userInput == 'c') {
      uf.clearScreen();
      cout << "HOME/ADMIN/MANAGE TOPPINGS/CREATE NEW TOPPING" << endl;
      topping_service.createNewTopping();
      uf.pressEnter();
      uf.clearScreen();
    }

    if(userInput == 'd') {
      if(vs.toppingsExist()) {
        uf.clearScreen();
        topping_service.deleteTopping();
      } else {
        cout << "No toppings exist!" << endl;
      }
      uf.pressEnter();
      uf.clearScreen();
    }

    if(userInput == 'l') {
      if(vs.toppingsExist()) {
        uf.clearScreen();
        cout << "HOME/ADMIN/MANAGE TOPPINGS/LIST TOPPINGS" << endl;
        topping_service.listToppings();
      } else {
        cout << "No toppings exist!" << endl;
      }
      uf.pressEnter();
      uf.clearScreen();
    }
  }
}

void adminUI::displayLocationMenu() {
    char userInput = 'i';     //init to invalid just in case
    while(userInput != 'b') {
        do {
            cout << "C - CREATE NEW STORE LOCATION" << endl;
            cout << "L - LIST STORE LOCATIONS" << endl;
            cout << "D - DELETE LOCATION" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "cldb"));

        userInput = tolower(userInput);

        if(userInput == 'c') {
            uf.clearScreen();
            cout << "HOME/ADMIN/MANAGE LOCATIONS/CREATE NEW LOCATION" << endl;
            location_service.createNewLocation();
            uf.pressEnter();
            uf.clearScreen();
        }

        if(userInput == 'l') {
          if(vs.locationsExist()) {
            uf.clearScreen();
            cout << "HOME/ADMIN/MANAGE LOCATIONS/LIST LOCATIONS" << endl;
            location_service.listLocations();
          } else {
              cout << "No locations exist!" << endl;
          }
          uf.pressEnter();
          uf.clearScreen();
        }

        if(userInput == 'd') {
          if(vs.locationsExist()) {
            uf.clearScreen();
            location_service.deleteLocation();
          } else {
              cout << "No locations exist!" << endl;
          }
          uf.pressEnter();
          uf.clearScreen();
        }
    }
}

void adminUI::displayAdditionalProductsMenu(){
    char userInput = 'i';     //init to invalid just in case
    while(userInput != 'b') {
        do {
            cout << "C - CREATE NEW ADDITIONAL PRODUCT" << endl;
            cout << "L - LIST ADDITIONAL PRODUCTS" << endl;
            cout << "D - DELETE ADDITIONAL PRODUCT" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "cldb"));

        userInput = tolower(userInput);

        if(userInput == 'c') {
            uf.clearScreen();
            cout << "HOME/ADMIN/MANAGE ADDITIONAL PRODUCTS/CREATE NEW PRODUCT" << endl;
            additionalProduct_service.createNewAdditionalProduct();
            uf.pressEnter();
            uf.clearScreen();
        }

        if(userInput == 'l') {
          if(vs.addProductsExist()) {
            uf.clearScreen();
            cout << "HOME/ADMIN/MANAGE ADDITIONAL PRODUCTS/LIST PRODUCTS" << endl;
            additionalProduct_service.listAdditionalProducts();
          } else {
            cout << "No additional products exist!" << endl;
            uf.pressEnter();
            uf.clearScreen();
          }
        }

        if(userInput == 'd') {
          if(vs.addProductsExist()) {
            uf.clearScreen();
            additionalProduct_service.deleteAdditionalProduct();
          } else {
            cout << "No additional products exist!" << endl;
          }
          uf.pressEnter();
          uf.clearScreen();
        }
    }
}
