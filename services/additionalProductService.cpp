#include "additionalProductService.h"

void additionalProductService::listAdditionalProducts(){
    fo.printLines("data/additionalProducts.txt");
    uf.pressEnter();
}

void additionalProductService::listAdditionalProductsWithIndexes(){
    fo.printLinesWithIndices("data/additionalProducts.txt");
    uf.pressEnter();
}

void additionalProductService::createNewAdditionalProduct(){
    string name;

    uf.clearScreen();
    cout << "Enter product name: ";
    cin >> name;

    int price = 0;
    cout << "Enter price: ";
    cin >> price;

    AdditionalProduct product(name, price);
    fo.appendLineToFile(product.toString(), "data/additionalProducts.txt");

    uf.clearScreen();
    cout << "Product: \"" << product.toString() << "\" created!" << endl;
    uf.pressEnter();
}

int additionalProductService::howManyAdditionalProducts(){
    return fo.countLines("data/additionalProducts.txt");
}
