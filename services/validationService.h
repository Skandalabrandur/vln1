#ifndef validationservice_h
#define validationservice_h

#include "fileOperations.h"
#include "stringFunctions.h"
#include <string>
#include <iostream>
#include <vector>


class validationService {

public:
  bool deliveryMenuValid();
  bool bakerMenuValid();
  bool salesMenuValid();
  bool menuPizzasExist();
  bool activePizzasExist();
  bool toppingsExist();
  bool locationsExist();
  bool ordersExist();
  bool addProductsExist();
  bool pizzasExistForOrderID(int orderID);
  bool pizzasExistForLocationID(int locationID);
  bool ordersExistForLocationID(int locationID);

private:
  fileOperations fo;
  stringFunctions stringfunc;

};

#endif
