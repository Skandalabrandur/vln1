#include "validationService.h"

bool validationService::deliveryMenuValid() {
  bool locations = (location_service.howManyLocations() != 0);
  return locations && (order_service.howManyOrders() != 0);
}

bool validationService::bakerMenuValid() {
  bool locations = (location_service.howManyLocations() != 0);
  return locations && (order_service.howManyOrders() != 0);
}

bool validationService::salesMenuValid() {
  bool toppings = (topping_service.howManyToppings() != 0);
  bool locations = (location_service.howManyLocations() != 0);
  return locations;
}
