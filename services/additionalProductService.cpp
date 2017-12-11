#include "additionalProductService.h"

void additionalProductService::listAdditionalProduct(){
    fo.printLines("data/additionalProducts.txt");
}

void additionalProductService::createNewAdditionalProduct(){
    string name;

    uf.clearScreen();
    cout << "Enter product name: ";
    cin >> name;

    //Find location id
    int id = howManyAdditionalProduct() + 1;
    cout << name << " product ID is " << id << endl;
    uf.pressEnter();

    AdditionalProduct product(name, id);
    fo.appendLineToFile(product.toString(), "data/additionalProducts.txt");

    uf.clearScreen();
    cout << "Product: \"" << product.toString() << "\" created!" << endl;
    uf.pressEnter();
}

int additionalProductService::howManyAdditionalProduct(){
    return fo.countLines("data/additionalProducts.txt");
}
