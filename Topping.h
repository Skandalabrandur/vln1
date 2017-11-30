#ifndef topping_h
#define topping_h

#include <iostream>
using namespace std;

class Topping {
public:
  Topping();
  Topping(string name);               //No price in constructor
                                      //Intended for early testing purposes
  Topping(string name, int price);
  void setVerbose(bool set);
  virtual ~Topping();

  friend ostream& operator << (ostream& out, const Topping& topping);
  friend istream& operator >> (istream& in, Topping& topping);

private:
  int _price;
  string _name;
  bool vbose;

};

#endif
