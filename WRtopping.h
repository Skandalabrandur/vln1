#ifndef wrtopping_h
#define wrtopping_h

#include "Topping.h"

class WRtopping {

public:
  void saveNewTopping(Topping topping);
  //Topping* retrieveToppings();
  void listToppings();
  virtual ~WRtopping();
private:

};

#endif
