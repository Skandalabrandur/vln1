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

int WRplace::listAndCountPlaces(){

    ifstream fin;
    fin.open("files/placeslist.txt");
    int counter = 0;
    if(fin.is_open()) {
        string line;
        while(!fin.eof()) {
          getline(fin, line);
          counter++;
          //check end of file again so it doesn't print extra line
          if(!fin.eof()){
            cout << counter << "-\t" << line << endl;
          }
        }
        fin.close();
        return counter;
    }
    else {
        cout << "ERROR: NO PLACES FOUND!" << endl;
        cout << "Possible solution:" << endl;
        cout << "\tHave management create places!" << endl;
    }
    return counter;
}
