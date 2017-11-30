#ifndef wrtopping_h
#define wrtopping_h

#include "Topping.h"

class WRtopping {

public:
  void saveNewTopping(Topping topping);
  //Topping* retrieveToppings();
  void listToppings();
  int listAndCountToppings();
  void selectTopping(int index, Topping& topping);
  virtual ~WRtopping();
private:

};

#endif
