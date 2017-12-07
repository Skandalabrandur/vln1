#ifndef pizza_h
#define pizza_h
#include <vector>
#include <string>
#include <iostream>
#include "Topping.h"
#include "stringFunctions.h"

class Pizza {
public:

  Pizza(string name, vector<Topping> toppings, int price);

  string getName();
  int getOrderID();
  bool isBaked();
  bool isPaid();
  bool isDelivered();

  void setOrderID(int set);
    void setBottomType(char set);
    void setSize(char set);
    char getBottomType();
    char getSize();
    void setPrice(int set);
  void setBaked(bool set);
  void setPaid(bool set);
  void setDelivered(bool set);

  string toString(bool showToppings);

private:
    int _orderID;
    char _bottomType;
    char _size;
  string _name;
  vector<Topping> _toppings;
  int _price;
  bool _baked;
  bool _paid;
  bool _delivered;

  stringFunctions stringfunc;
};

#endif
