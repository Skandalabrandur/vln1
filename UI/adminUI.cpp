#include "adminUI.h"

bool adminUI::requestPassword(){
    string id;
    uf.clearScreen();
    cout << "Admin password: " << endl;
    cout << endl << uf.prompt();
    cin >> id;
    if(id == "pw")
        return true;
    return false;
}

void adminUI::displayAdminMenu() {
  char userInput = 'i';     //init to invalid just in case
  while (userInput != 'b') {

    do {
      uf.clearScreen();
      cout << "HOME/ADMIN" << endl << endl;
      cout << "1 - MANAGE MENU PIZZAS" << endl;
      cout << "2 - MANAGE TOPPINGS" << endl;
      cout << "3 - MANAGE STORE LOCATIONS" << endl;
      cout << "4 - MANAGE ADDITIONAL PRODUCTS" << endl;
      cout << "5 - VIEW LEGACY ORDERS" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "12345b"));

    userInput = tolower(userInput);

    if(userInput == '1') {
      if(vs.toppingsExist() || vs.menuPizzasExist()) {
        displayPizzaMenu();
      } else {
        cout << "Neither toppings nor menu-pizzas exist." << endl;
        cout << "Returning to admin menu..." << endl;
        uf.pressEnter();
      }
    }

    if(userInput == '2') {
      displayToppingMenu();
    }

    if(userInput == '3') {
      displayLocationMenu();
    }

    if(userInput == '4') {
      displayAdditionalProductsMenu();
    }

    if(userInput == '5') {
      if(vs.legacyFileExists()) {
        order_service.printLegacyFile();
      } else {
        cout << "No legacy file exists!" << endl;
      }
      uf.pressEnter();
    }
  }
}

void adminUI::displayPizzaMenu() {
  char userInput;

  while(userInput != 'b') {
    do {
      uf.clearScreen();
      userInput = 'i'; //for invalid so that we don't end up with an infinte loop
      cout << "HOME/ADMIN/MANAGE MENU PIZZAS" << endl;
      cout << "1 - CREATE A NEW MENU PIZZA" << endl;
      cout << "2 - LIST MENU PIZZAS" << endl;
      cout << "3 - DELETE MENU PIZZA" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "123b"));

    userInput = tolower(userInput);

    if(userInput == '1') {
      if(vs.toppingsExist()) {
        uf.clearScreen();
        cout << "HOME/ADMIN/MANAGE MENU PIZZAS/CREATE NEW MENU PIZZA" << endl << endl;
        pizza_service.createAndAppendMenuPizza();
      } else {
        cout << "No toppings exist!" << endl;
      }
      uf.pressEnter();
      uf.clearScreen();
    }

    if(userInput == '2') {
      if(vs.menuPizzasExist()) {
          uf.clearScreen();
          cout << "HOME/ADMIN/MANAGE MENU PIZZAS/LIST MENU PIZZAS" << endl << endl;
          pizza_service.listMenuPizzas();
      } else {
        cout << "No menu pizzas exist!" << endl;
      }
      uf.pressEnter();
      uf.clearScreen();
    }

    if(userInput == '3') {
      if(vs.menuPizzasExist()) {
        uf.clearScreen();
        cout << "HOME/ADMIN/MANAGE MENU PIZZAS/DELETE MENU PIZZA" << endl << endl;
        pizza_service.deleteMenuPizza();
      } else {
        cout << "No menu pizzas exist!" << endl;
        uf.pressEnter();
      }
      uf.clearScreen();
    }
  }
}

void adminUI::displayToppingMenu() {
  char userInput = 'i';     //init to invalid just in case
  while(userInput != 'b') {
    do {
        uf.clearScreen();
        cout << "HOME/ADMIN/MANAGE TOPPINGS" << endl << endl;
      cout << "1 - CREATE NEW TOPPING" << endl;
      cout << "2 - LIST TOPPINGS" << endl;
      cout << "3 - DELETE TOPPING" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "123b"));

    userInput = tolower(userInput);

    if(userInput == '1') {
      uf.clearScreen();
      cout << "HOME/ADMIN/MANAGE TOPPINGS/CREATE NEW TOPPING" << endl << endl;
      topping_service.createNewTopping();
      uf.pressEnter();
      uf.clearScreen();
    }

    if(userInput == '2') {
      if(vs.toppingsExist()) {
        uf.clearScreen();
        cout << "HOME/ADMIN/MANAGE TOPPINGS/LIST TOPPINGS" << endl << endl;
        topping_service.listToppings();
      } else {
        cout << "No toppings exist!" << endl;
      }
      uf.pressEnter();
      uf.clearScreen();
    }

    if(userInput == '3') {
      if(vs.toppingsExist()) {
        uf.clearScreen();
        cout << "HOME/ADMIN/MANAGE TOPPINGS/DELETE TOPPING" << endl << endl;
        topping_service.deleteTopping();
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
            uf.clearScreen();
            cout << "HOME/ADMIN/MANAGE LOCATIONS" << endl << endl;
            cout << "1 - CREATE NEW STORE LOCATION" << endl;
            cout << "2 - LIST STORE LOCATIONS" << endl;
            cout << "3 - DELETE LOCATION" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "123b"));

        userInput = tolower(userInput);

        if(userInput == '1') {
            uf.clearScreen();
            cout << "HOME/ADMIN/MANAGE LOCATIONS/CREATE NEW LOCATION" << endl << endl;
            location_service.createNewLocation();
            uf.pressEnter();
            uf.clearScreen();
        }

        if(userInput == '2') {
          if(vs.locationsExist()) {
            uf.clearScreen();
            cout << "HOME/ADMIN/MANAGE LOCATIONS/LIST LOCATIONS" << endl << endl;
            location_service.listLocations();
          } else {
              cout << "No locations exist!" << endl;
          }
          uf.pressEnter();
          uf.clearScreen();
        }

        if(userInput == '3') {
          if(vs.locationsExist()) {
            uf.clearScreen();
            cout << "HOME/ADMIN/DELETE LOCATION" << endl << endl;
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
            uf.clearScreen();
            cout << "HOME/ADMIN/MANAGE ADDITIONAL PRODUCTS" << endl << endl;
            cout << "1 - CREATE NEW ADDITIONAL PRODUCT" << endl;
            cout << "2 - LIST ADDITIONAL PRODUCTS" << endl;
            cout << "3 - DELETE ADDITIONAL PRODUCT" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "123b"));

        userInput = tolower(userInput);

        if(userInput == '1') {
            uf.clearScreen();
            cout << "HOME/ADMIN/MANAGE ADDITIONAL PRODUCTS/CREATE NEW PRODUCT" << endl << endl;
            additionalProduct_service.createNewAdditionalProduct();
            uf.pressEnter();
        }

        if(userInput == '2') {
          if(vs.addProductsExist()) {
            uf.clearScreen();
            cout << "HOME/ADMIN/MANAGE ADDITIONAL PRODUCTS/LIST PRODUCTS" << endl << endl;
            additionalProduct_service.listAdditionalProducts();
          } else {
            cout << "No additional products exist!" << endl;
          }
          uf.pressEnter();
        }

        if(userInput == '3') {
          if(vs.addProductsExist()) {
            uf.clearScreen();
            cout << "HOME/ADMIN/DELETE ADDITIONAL PRODUCTS" << endl << endl;
            additionalProduct_service.deleteAdditionalProduct();
          } else {
            cout << "No additional products exist!" << endl;
          }
          uf.pressEnter();
        }
    }
}
