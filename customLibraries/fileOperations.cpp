#include "fileOperations.h"
#include <fstream>
#include <iostream>

using namespace std;

//const char file[] works basically like const string
//but the ifstream.open and ostream.open ask for const char instead of string

//Returns all the lines from a file into a string vector
//f.x.
//  vector<string> lines = fo.getLinesFromFile("data/legacy.txt")
vector<string> fileOperations::getLinesFromFile(const char file[]) {
  ifstream fin;
  fin.open(file);

  vector<string> lines;

  if(fin.is_open()) {
    while(!fin.eof()) {
      string line;
      getline(fin, line);
      if(!line.empty()) {
        lines.push_back(line);
      }
    }
  } else {
    lines.push_back("ERROR");
  }

  return lines;
}

//Since almost everything in our files is space separated it is very
//convenient to have a function that returns from line number n, all the words
//from within that line
//Example, say line 3 contains "Pizza party pugs and platters"
//Then the output for getWordsFromLine(3, file):
//  vector<string> words
//    at(0): Pizza
//    at(1): party
//    etc...
vector<string> fileOperations::getWordsFromLine(int index, const char file[]) {
  string line = getLineAt(index, file);
  return stringFunc.split(line);
}

//Writes the "string line" at the end of the file designated by our filepath
void fileOperations::appendLineToFile(string line, const char file[]) {
  ofstream fout;
  //no check needed since fileNotExists triggers file creation
  fout.open(file, ios::app);    //ios::app for append
  if(!line.empty()) {
    fout << line << endl;
  }
  fout.close();
}

//WARNING: This function overwrites files completely
//Blank file, and then
//For every element in vector<string> lines,
//write element in one line
void fileOperations::writeFile(vector<string> lines, const char file[]) {
  ofstream fout;
  fout.open(file);  //don't flag for ios::app to overwrite
  for(int i = 0; i < lines.size(); i++) {
    if(!lines[i].empty()) {
      fout << lines[i] << endl;
    }
  }
  fout.close();
}

//Prints an entire file, line by line
void fileOperations::printLines(const char file[]) {
  vector<string> lines;
  lines = getLinesFromFile(file);

  for(int i = 0; i < lines.size(); i++) {
    cout << lines[i] << endl;
  }
}

//One indexed
//Might be deprecated since customization takes place much more
//with getLinesFromFile/getWordsFromLine combos where fields are
//given different weights
void fileOperations::printLinesWithIndices(const char file[]) {
  ifstream fin;

  fin.open(file);
  if(fin.is_open()) {
    int counter = 1;
    string line;
    while(!fin.eof()) {
      getline(fin, line);
      //we will get an extra line unless we do this
      if(!fin.eof()) {
        cout << counter << " - " << line << endl;
        counter++;
      }
    }
  } else {
    cout << "ERROR --- File: " << file << " not found! Possibly empty!" << endl;
  }
}

//Flagged as deprecated, would've been stripped next refactoring
string fileOperations::getLineAt(int index, const char file[]) {
  vector<string> lines = getLinesFromFile(file);
  if(index < 0 || index >= lines.size()) {
    return "ERROR --- INDEX OUT OF BOUNDS!";
  } else {
    return lines[index];
  }
}

int fileOperations::countLines(const char file[]) {
  ifstream fin;
  fin.open(file);

  if(fin.is_open()) {
    int counter = -1;   //one extra gets counted in the while loop
    string discarded;
    while(!fin.eof()) {
      getline(fin, discarded);
      counter++;
    }
    return counter;
  } else {
    return 0;
  }
}
