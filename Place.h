#ifndef PLACE_H
#define PLACE_H

#include <iostream>
using namespace std;

class Place
{
    private:
        string _place;
        bool _vbose;

    public:
        Place();
        Place(string place);
        ~Place();
        void setVerbose(bool set);
        void setName(string name);
        friend ostream& operator << (ostream& out, const Place& place);
        friend istream& operator >> (istream& in, Place& place);
};

#endif // PLACE_H
