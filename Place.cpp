#include "Place.h"

Place::Place()
{
    _place = "Place";
    _vbose = false;
}

Place::Place(string place)
{
    _place = place;
}

Place::~Place()
{

}

void Place::setVerbose(bool vbose){
    _vbose = vbose;
}

void Place::setName(string name){
    _place = name;
}

ostream& operator << (ostream& out, const Place& place){

    out << place._place;

    return out;
}

istream& operator >> (istream& in, Place& place){

    if(place._vbose) {
        cout << "Input name of place: ";
    }
    in >> place._place;

    return in;
}
