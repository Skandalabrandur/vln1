#ifndef validationservice_h
#define validationservice_h

#include "locationService.h"
#include "orderService.h"
#include "toppingService.h"
#include "fileOperations.h"


class validationService {
public:
  bool deliveryMenuValid();
  bool bakerMenuValid();
  bool salesMenuValid();

private:
  toppingService topping_service;
  orderService order_service;
  locationService location_service;
  fileOperations fo;

};

#endif
