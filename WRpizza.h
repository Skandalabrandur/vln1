#ifndef wrpizza_h
#define wrpizza_h

#include "Pizza.h"

class WRpizza {

public:
  void saveNewPizza(Pizza& pizza);
  Pizza* retrievePizzas();
  virtual ~WRpizza();

private:


};

#endif
