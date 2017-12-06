#include "bakerUI.h"
#include "UIFunctions.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void bakerUI::displayBakerMenu() {
    char userInput;
    UIFunctions uf;
    while (userInput != 'b') {
        do {
            uf.clearScreen();
            cout << "L - LIST PIZZAS" << endl;
            cout << "B - BACK" << endl;
            cout << endl << uf.prompt();
            cin >> userInput;
        } while(!uf.goodInput(userInput, "bl"));
        
        userInput = tolower(userInput);
        
        if(userInput == 'l') {
            viewPizzas();
            char yn;
            cin >> yn;
        }
    }
}

void bakerUI::viewPizzas(){
    string pizza;
    ifstream fin;
    fin.open("data/activePizzas.txt");
    if(fin.is_open()){
        while(!fin.eof()){
            for(int i = 0; i < 15; i++){
                getline(fin,pizza);
                if(pizza != "")
                    cout << pizza << endl;
            }
        }
        fin.close();
    }else{
        cout << "Ekki hægt að lesa úr skrá" << endl;
    }
}
