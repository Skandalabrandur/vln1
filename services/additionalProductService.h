#ifndef ADDITIONALPRODUCTSERVICE_H
#define ADDITIONALPRODUCTSERVICE_H

#include "UIFunctions.h"
#include "fileOperations.h"
#include "stringFunctions.h"
#include "AdditionalProduct.h"
#include <iostream>
#include <limits>
using namespace std;

class additionalProductService
{
    public:
        void listAdditionalProducts();
        void listAdditionalProductsWithIndexes();
        void createNewAdditionalProduct();
        int howManyAdditionalProducts();
        AdditionalProduct getAdditionalProductAt(int index);
        void saveAdditionalProducts(int orderID);
        vector<AdditionalProduct> getSavedProductFromOrderID(int orderID);
        void deleteAdditionalProduct();

    private:
        fileOperations fo;
        stringFunctions stringfunc;
        UIFunctions uf;
};

#endif // ADDITIONALPRODUCTSERVICE_H
