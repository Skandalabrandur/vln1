#include "adminUI.h"

void adminUI::displayAdminMenu() {
  char userInput;
  while (userInput != 'b') {
    do {
      uf.clearScreen();
      cout << "P - MANAGE PIZZAS" << endl;
      cout << "T - MANAGE TOPPINGS" << endl;
      cout << "B - BACK" << endl;
      cout << endl << uf.prompt();
      cin >> userInput;
    } while(!uf.goodInput(userInput, "ptb"));

    userInput = tolower(userInput);

    if(userInput == 'p') {
      displayPizzaMenu();
    }

    if(userInput == 't') {
      displayToppingMenu();
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
      pizza_service.createAndAppendMenuPizza();
    }

    if(userInput == 'l') {
      uf.clearScreen();
      pizza_service.listMenuPizzas();
      uf.pressEnter();
    }

    if(userInput == 'd') {
      uf.clearScreen();
      pizza_service.deleteMenuPizza();
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
      uf.clearScreen();
      topping_service.listToppings();
      uf.pressEnter();
    }
  }
}
