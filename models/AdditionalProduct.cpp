#include "AdditionalProduct.h"

AdditionalProduct::AdditionalProduct()
{
    _name = "";
    _productID = 0;
}

AdditionalProduct::AdditionalProduct(string name, int productID){
    _name = name;
    _productID = productID;
}

string AdditionalProduct::toString(){
     return _name + " " + stringfunc.intToString(_productID);
}

string AdditionalProduct::getAdditionalProductName(){
    return _name;
}
int AdditionalProduct::getProductID(){
    return _productID;
}
