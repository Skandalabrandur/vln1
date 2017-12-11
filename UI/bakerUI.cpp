#include "bakerUI.h"

using namespace std;

void bakerUI::displayBakerMenu() {
    //DO DO: choose location
    uf.clearScreen();
    chooseLocation();

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

void bakerUI::chooseLocation(){
    //lists locations from file, user inputs their location
    location_service.listLocationsWithIndex();
    int numLocations = location_service.howManyLocations();
    int choice;
    do{
        cout << "Select your location: ";
        cin >> choice;
    }while(choice <= 0 || choice > numLocations);
    //If changed so admin can delete locations then this does probably not work
    //Could make a function getLocationID(choice)
    _locationID = choice;
}

void bakerUI::viewPizzas() {
  uf.clearScreen();
  pizza_service.listFromLocationActivePizzas(_locationID);
  uf.pressEnter();
}

//TO DO: only show chosen location
void bakerUI::selectAndMarkPizzaAsBaked() {
  int index = -1;
  while(index < 1 || index > pizza_service.howManyActivePizzas()) {
    uf.clearScreen();
    pizza_service.listActivePizzasWithIndicesForBakery(false);
    cout << "Please select a pizza to mark as BAKED: ";
    cin >> index;
  }
  int adjustedIndex = pizza_service.adjustBakerIndexForBaked(false, index);
  pizza_service.setActivePizzaStatus((adjustedIndex), "baked", true);
  uf.pressEnter();
}

//TO DO: only show chosen location
void bakerUI::selectAndMarkPizzaAsUnbaked() {
  int index = -1;
  while(index < 1 || index > pizza_service.howManyActivePizzas()) {
    uf.clearScreen();
    pizza_service.listActivePizzasWithIndicesForBakery(true);
    cout << "Please select a pizza to mark as UNBAKED: ";
    cin >> index;
  }
  int adjustedIndex = pizza_service.adjustBakerIndexForBaked(true, index);
  pizza_service.setActivePizzaStatus(adjustedIndex, "baked", false);
  uf.pressEnter();
}
