#ifndef ADDITIONALPRODUCTSERVICE_H
#define ADDITIONALPRODUCTSERVICE_H

#include "UIFunctions.h"
#include "fileOperations.h"
#include "stringFunctions.h"
#include "AdditionalProduct.h"
#include <iostream>
using namespace std;

class additionalProductService
{
    public:
        void listAdditionalProducts();
        void createNewAdditionalProduct();
        int howManyAdditionalProducts();

    private:
        fileOperations fo;
        stringFunctions stringfunc;
        UIFunctions uf;
};

#endif // ADDITIONALPRODUCTSERVICE_H
