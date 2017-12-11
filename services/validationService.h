#ifndef validationservice_h
#define validationservice_h

#include "fileOperations.h"


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

private:
  fileOperations fo;

};

#endif
