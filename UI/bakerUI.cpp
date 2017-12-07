#include "bakerUI.h"

using namespace std;

void bakerUI::displayBakerMenu() {
    char userInput;
    while (userInput != 'b') {
        do {
            uf.clearScreen();
            cout << "L - LIST PIZZAS" << endl;
            cout << "M - MARK PIZZA AS BAKED" << endl;
            cout << "U - MARK PIZZA AS UNBAKED" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "mblu"));

        userInput = tolower(userInput);

        if(userInput == 'l') {
          viewPizzas();
        }

        if(userInput == 'm') {
          selectAndMarkPizzaAsBaked();
        }

        if(userInput == 'u') {
          selectAndMarkPizzaAsUnbaked();
        }

    }
}

void bakerUI::viewPizzas() {
  uf.clearScreen();
  pizza_service.listActivePizzas();
  uf.pressEnter();
}

void bakerUI::selectAndMarkPizzaAsBaked() {

  int index = -1;
while(index < 1 || index > pizza_service.howManyActivePizzas()) {
    uf.clearScreen();
    pizza_service.listActivePizzasWithIndices();
    cout << "Please select a pizza to mark as BAKED: ";
    cin >> index;
  }
  pizza_service.setActivePizzaStatus((index-1), "baked", true);
  uf.pressEnter();
}

void bakerUI::selectAndMarkPizzaAsUnbaked() {
  int index = -1;
  while(index < 1 || index > pizza_service.howManyActivePizzas()) {
    uf.clearScreen();
    pizza_service.listActivePizzasWithIndices();
    cout << "Please select a pizza to mark as UNBAKED: ";
    cin >> index;
  }
  pizza_service.setActivePizzaStatus((index-1), "baked", false);
  uf.pressEnter();
}
