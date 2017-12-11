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
            cout << "L - LIST ALL PIZZAS" << endl;
            cout << "O - LIST PIZZAS BY ORDERS" << endl;
            cout << "M - MARK PIZZA AS BAKED" << endl;
            cout << "U - MARK PIZZA AS UNBAKED" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "mblou"));

        userInput = tolower(userInput);

        if(userInput == 'l') {
          viewPizzas();
        }

        if(userInput == 'o') {
          uf.clearScreen();
          order_service.listOrderOverviewWithIndicesForLocation(_locationID);

          int selection;
          cout << "Select an order for more info: ";
          cin >> selection;

          int adjustedSelection = order_service.getOrderIdFromIndexSelectionForLocation(selection, _locationID);
          uf.clearScreen();
          order_service.listSpecificOrderWithInfo(adjustedSelection);
          uf.pressEnter();
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
  while(index < 0 || index > pizza_service.howManyActivePizzas()) {
    uf.clearScreen();
    pizza_service.listActiveWithIndicesForBakeryAndLocation(false, _locationID);
    cout << "Please select a pizza to mark as BAKED (0 to cancel): ";
    cin >> index;
  }
  if(index != 0) {
  int adjustedIndex = pizza_service.adjustBakerIndexForBaked(false, _locationID, index);
    pizza_service.setActivePizzaStatus((adjustedIndex), "baked", true);
    uf.pressEnter();
  }
}

//TO DO: only show chosen location
void bakerUI::selectAndMarkPizzaAsUnbaked() {
  int index = -1;
  while(index < 0 || index > pizza_service.howManyActivePizzas()) {
    uf.clearScreen();
    pizza_service.listActiveWithIndicesForBakeryAndLocation(true, _locationID);
    cout << "Please select a pizza to mark as UNBAKED (0 to cancel): ";
    cin >> index;
  }
  if(index != 0) {
    int adjustedIndex = pizza_service.adjustBakerIndexForBaked(true, _locationID, index);
    pizza_service.setActivePizzaStatus(adjustedIndex, "baked", false);
    uf.pressEnter();
  }
}
