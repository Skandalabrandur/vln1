#ifndef wrtopping_h
#define wrtopping_h

#include "Topping.h"

class WRtopping {

public:
  void saveNewTopping(Topping topping);
  void listToppings();
  int listAndCountToppings();
  void selectTopping(int index, Topping& topping);
  bool toppingsExist();
  virtual ~WRtopping();
private:

};

#endif
