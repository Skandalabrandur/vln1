#include "WRplace.h"
#include <iostream>
#include <fstream>

using namespace std;

void WRplace::saveNewPlace(Place place){

    ofstream fout;
    fout.open("files/placeslist.txt", ios::app);

    fout << place << endl;

    fout.close();
}

void WRplace::listPlaces(){

    ifstream fin;
    fin.open("files/placeslist.txt");
    if(fin.is_open()) {
        string line;
        while(!fin.eof()) {
          getline(fin, line);
          cout << line << endl;
        }

        fin.close();
    }
    else {
        cout << "ERROR: NO PLACES FOUND!" << endl;
        cout << "Possible solution:" << endl;
        cout << "\tHave management create places!" << endl;
    }

}
