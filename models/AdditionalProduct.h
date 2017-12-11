#ifndef ADDITIONALPRODUCT_H
#define ADDITIONALPRODUCT_H

#include "stringFunctions.h"
#include <string>
#include <iostream>

using namespace std;

class AdditionalProduct
{
    public:
        AdditionalProduct();
        AdditionalProduct(string name, int price);
        string getAdditionalProductName();
        int getPrice();
        string toString();

    private:
        string _name;
        int _price;

        stringFunctions stringfunc;
};

#endif // ADDITIONALPRODUCT_H
