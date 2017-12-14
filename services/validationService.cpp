#include "validationService.h"

bool validationService::deliveryMenuValid() {
  return locationsExist() && activePizzasExist();
}

bool validationService::bakerMenuValid() {
  return locationsExist() && activePizzasExist();
}

bool validationService::salesMenuValid() {
  return locationsExist() && menuPizzasExist();
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
  return (fo.countLines("data/additionalProducts.txt") != 0);
}

bool validationService::legacyFileExists() {
  return (fo.countLines("data/legacy.txt") != 0);
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

bool validationService::readyOrdersExistForLocationID(int locationID) {
  vector<string> activePizzas = fo.getLinesFromFile("data/activePizzas.txt");
  vector<string> orders = fo.getLinesFromFile("data/orders.txt");

  for(int i = 0; i < orders.size(); i++) {
    vector<string> order = stringfunc.split(orders.at(i));
    string orderID = order.at(1);
    int readyPizzas = 0;
    int totalPizzas = 0;

    for(int j = 0; j < activePizzas.size(); j++) {
        string builder;
        vector<string> words = stringfunc.split(activePizzas.at(j));
        if(orderID == words.at(0)) {
          builder = words.at(words.size() - 3) + words.at(words.size() - 2);
          totalPizzas++;

          if(builder == "bakedpaid") {
            readyPizzas++;
          }
        }

    }
    if (readyPizzas != 0 && (readyPizzas == totalPizzas)) {
      return true;
    }
  }
  return false;
}
