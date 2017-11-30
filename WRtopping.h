#ifndef wrtopping_h
#define wrtopping_h

#include "Topping.h"

class WRtopping {

public:
  void saveNewTopping(Topping topping);
  Topping* retrieveToppings();
  virtual ~WRtopping();
private:

};

#endif
