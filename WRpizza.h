#ifndef wrpizza_h
#define wrpizza_h

#include "AdminPizza.h"

class WRpizza {

public:
  void saveNewPizza(AdminPizza& pizza);
  AdminPizza retrievePizzas();
  virtual ~WRpizza();

private:


};

#endif
