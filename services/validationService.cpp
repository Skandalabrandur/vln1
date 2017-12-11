#include "validationService.h"

bool validationService::deliveryMenuValid() {
  return locationsExist();
}

bool validationService::bakerMenuValid() {
  return locationsExist();
}

bool validationService::salesMenuValid() {
  return ordersExist() && locationsExist();
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
