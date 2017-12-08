#include "Pizza.h"
#include "Topping.h"
#include "toppingService.h"

Pizza::Pizza() {
  _name = "";
  _price = -1;
  _orderID = -1;
  _baked = false;
  _paid = false;
  _delivered = false;
  _bottomType = ' ';
  _size = ' ';
}

Pizza::Pizza(string name, vector<Topping> toppings, int price) {
  _name = name;
  _toppings = toppings;
  _price = price;
  _orderID = -1;
  _bottomType = ' ';
  _size = ' ';
  _baked = false;
  _paid = false;
  _delivered = false;
}

string Pizza::getName() {
  return _name;
}

void Pizza::setName(string name) {
  _name = name;
}

int Pizza::getOrderID() {
  return _orderID;
}

void Pizza::setToppings(vector<Topping> toppings) {
  _toppings = toppings;
}

vector<Topping> Pizza::getToppings() {
  return _toppings;
}

bool Pizza::isBaked() {
  return _baked;
}

bool Pizza::isPaid() {
  return _paid;
}

bool Pizza::isDelivered() {
  return _delivered;
}

void Pizza::setOrderID(int set) {
  _orderID = set;
}

void Pizza::setBottomType(char set){
    _bottomType = set;
}

void Pizza::setSize(char set){
    _size = set;
}

char Pizza::getBottomType(){
    return _bottomType;
}

char Pizza::getSize(){
    return _size;
}

void Pizza::setBaked(bool set) {
  _baked = set;
}

void Pizza::setPrice(int set) {
    _price = set;
}

int Pizza::getPrice() {
  return _price;
}

void Pizza::setPaid(bool set) {
  _paid = set;
}

void Pizza::setDelivered(bool set) {
  _delivered = set;
}

void Pizza::setStoreID(int set) {
    _storeID = set;
}

void Pizza::setToppings(){
    toppingService ts;
    int i = 0;
    int input;
    ts.listToppingsWithIndex();
    while(true){
        cin >> input;
        if(input != 0){
            _toppings[i] = ts.getToppingAt(input-1);
        }else{
            break;
        }
    }
};

string Pizza::toString(bool showToppings) {
  string builder = "";
builder += stringfunc.intToString(_orderID) + " ";
  builder += _name + " ";

  if(showToppings) {
    for(int i = 0; i < _toppings.size(); i++) {
      builder += _toppings[i].getName() + " ";
    }
  }

  builder += stringfunc.cToStr(_bottomType) + " ";
  builder += stringfunc.cToStr(_size) + " ";
  builder += stringfunc.intToString(_price) + " ";

  if(_baked) {
    builder += "baked ";
  } else {
    builder += "unbaked ";
  }

  if(_paid) {
    builder += "paid ";
  } else {
    builder += "unpaid ";
  }

  if(_delivered) {
    builder += "delivered";
  } else {
    builder += "undelivered";
  }

  return builder;
}
