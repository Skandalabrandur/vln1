#include "AdditionalProduct.h"

AdditionalProduct::AdditionalProduct()
{
    _name = "";
    _price = 0;
}

AdditionalProduct::AdditionalProduct(string name, int price){
    _name = name;
    _price = price;
}

string AdditionalProduct::toString(){
     return _name + " " + stringfunc.intToString(_price);
}

string AdditionalProduct::getAdditionalProductName(){
    return _name;
}

int AdditionalProduct::getPrice(){
    return _price;
}
