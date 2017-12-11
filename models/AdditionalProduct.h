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
        AdditionalProduct(string name, int productID);
        string getAdditionalProductName();
        int getProductID();
        string toString();

    private:
        string _name;
        int _productID;

        stringFunctions stringfunc;
};

#endif // ADDITIONALPRODUCT_H
