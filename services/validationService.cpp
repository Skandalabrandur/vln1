#include "validationService.h"

bool validationService::deliveryMenuValid() {
  return locationsExist();
}

bool validationService::bakerMenuValid() {
  return locationsExist() && activePizzasExist();
}

bool validationService::salesMenuValid() {
  return locationsExist();
}

bool validationService::menuPizzasExist() {
  return (fo.countLines("data/menuPizzas.txt") != 0);
}

bool validationService::activePizzasExist() {
  return (fo.countLines("data/activePizzas.txt") != 0);
}

bool validationService::toppingsExist() {
  return (fo.countLines("data/toppings.txt") != 0);
}

bool validationService::locationsExist() {
  return (fo.countLines("data/locations.txt") != 0);
}

bool validationService::ordersExist() {
  return (fo.countLines("data/orders.txt") != 0);
}

bool validationService::addProductsExist() {
  return (fo.countLines("data/additionalProducts.txt"));
}

bool validationService::pizzasExistForOrderID(int orderID) {
  int counter = 0;

  vector<string> lines = fo.getLinesFromFile("data/activePizzas.txt");

  for(int i = 0; i < lines.size(); i++) {
    vector<string> words = stringfunc.split(lines.at(i));

    if(stringfunc.stringToInt(words.at(0)) == orderID) {
      counter ++;
    }
  }

  return (counter > 0);
}

bool validationService::pizzasExistForLocationID(int locationID) {
  int counter = 0;

  vector<string> lines = fo.getLinesFromFile("data/activePizzas.txt");

  for(int i = 0; i < lines.size(); i++) {
    vector<string> words = stringfunc.split(lines.at(i));

    if(stringfunc.stringToInt(words.at(5)) == locationID) {
      counter ++;
    }
  }

  return (counter > 0);
}

bool validationService::ordersExistForLocationID(int locationID) {
  int counter = 0;

  vector<string> lines = fo.getLinesFromFile("data/orders.txt");

  for(int i = 0; i < lines.size(); i++) {
    vector<string> words = stringfunc.split(lines.at(i));

    if(stringfunc.stringToInt(words.at(2)) == locationID) {
      counter ++;
    }
  }

  return (counter > 0);
}
