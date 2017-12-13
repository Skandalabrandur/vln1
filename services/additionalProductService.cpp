#include "additionalProductService.h"

void additionalProductService::listAdditionalProducts(){
    //fo.printLines("data/additionalProducts.txt");
    vector<string> lines = fo.getLinesFromFile("data/additionalProducts.txt");
    vector<string> headers;
    headers.push_back("Name");
    headers.push_back("Price");

    uf.printItNice(lines, headers);
}

void additionalProductService::listAdditionalProductsWithIndexes(){
    fo.printLinesWithIndices("data/additionalProducts.txt");
}

void additionalProductService::createNewAdditionalProduct(){
    string name;

    cout << "Enter product name or 0 to cancel: ";
    cin >> name;
    if(name != "0"){
    int price = 0;

    do {
      cout << "Enter price: ";
      cin >> price;

      if(cin.fail()) {
        cin.clear();    //reset error flags
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
        price = -1;     //set price to continue
      }
    } while(price < 0);

    AdditionalProduct product(name, price);
    fo.appendLineToFile(product.toString(), "data/additionalProducts.txt");

    uf.clearScreen();
    cout << "Product: \"" << product.toString() << "\" created!" << endl;
    }
}

int additionalProductService::howManyAdditionalProducts(){
    return fo.countLines("data/additionalProducts.txt");
}

AdditionalProduct additionalProductService::getAdditionalProductAt(int index) {
  vector<string> productFromFile = fo.getWordsFromLine(index, "data/additionalProducts.txt");
  AdditionalProduct product(productFromFile[0], stringfunc.stringToInt(productFromFile[1]));

  return product;
}

void additionalProductService::saveAdditionalProducts(int orderID){
    string ID = stringfunc.intToString(orderID);
    AdditionalProduct product;
    int input;
    listAdditionalProductsWithIndexes();
    while(true){
        cin >> input;
        if(input != 0){
            product = getAdditionalProductAt(input-1);
            string builder = ID + " " + product.toString();
            fo.appendLineToFile(builder, "data/activeAdditionalProducts.txt");
        }else{
            break;
        }
    }
}

vector<AdditionalProduct> additionalProductService::getSavedProductFromOrderID(int orderID) {
    int numProducts = fo.countLines("data/activeAdditionalProducts.txt");
    vector<AdditionalProduct> products;
    for(unsigned int i = 0; i < numProducts; i++){
        vector<string> productFromFile = fo.getWordsFromLine(i, "data/activeAdditionalProducts.txt");
        int ID = stringfunc.stringToInt(productFromFile[0]);
        if(ID == orderID){
          AdditionalProduct product(productFromFile[1], stringfunc.stringToInt(productFromFile[2]));
          products.push_back(product);
        }
    }
    return products;
}

void additionalProductService::deleteAdditionalProduct() {
  int howManyAdditionalProductsExist = howManyAdditionalProducts();
  int selection = -1;

  while(selection < 0 || selection > howManyAdditionalProductsExist) {
    uf.clearScreen();
    listAdditionalProductsWithIndexes();
    cout << endl << "Select a topping to delete or 0 to cancel: ";
    cin >> selection;
    if(cin.fail()) {
      cin.clear();      //reset error flags
      cin.ignore(numeric_limits<streamsize>::max(),'\n'); //dump input
      selection = -1;   //set selection to continue
    }
  }
    if( selection > 0){
  vector<string> additionalProductsFile = fo.getLinesFromFile("data/additionalProducts.txt");

  //Get name of deleted product
  //reminder: split returns a vector from a string
  string deletedAdditionalProductName =  stringfunc.split(additionalProductsFile.at(selection-1)).at(0);

  //erase selection from the vector representing the file
  //file is 0-indexed, selection is 1-indexed
  additionalProductsFile.erase(additionalProductsFile.begin() + (selection-1));

  //overwrite
  fo.writeFile(additionalProductsFile, "data/additionalProducts.txt");

  cout << "Deleted: " << deletedAdditionalProductName << endl;
    }
}
