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
        void listAdditionalProduct();
        void createNewAdditionalProduct();
        int howManyAdditionalProduct();

    private:
        fileOperations fo;
        stringFunctions stringfunc;
        UIFunctions uf;
};

#endif // ADDITIONALPRODUCTSERVICE_H
