#include <__bit_reference>

#ifndef UNTITLED3_ADDRESS_H
#define UNTITLED3_ADDRESS_H

#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

struct Address {
    string title;
    string locality;
    int houseNumber;
    int flatNumber;
    int x, y;

    void showAddress() const {
        cout << title << endl;
        cout << "Locality: " << locality << endl;
        cout << "Number of the house: " << houseNumber << endl;
        cout << "Number of the flat: " << flatNumber << endl;
        cout << "Coordinates: " << x << " " << y << endl;
    }

    static double distance (Address& from, Address& to) {
        return sqrt((from.x - to.x) * (from.x - to.x) + (from.y - to.y) + ((from.y - to.y)));
    }
};

static vector<struct Address*> addressList;

/**
 * the function lets the user to create an address
 * himself/herself from the console (not from the code)
 */
void createAddress() {
    string title;
    string locality;
    int houseNumber;
    int flatNumber;
    int x, y;
    cout << "How do you want to entitle this place: " << endl;
    cin >> title;
    cout << endl << "Name of your town/city/country: " << endl;
    cin >> locality;
    cout << endl << "Number of the house: " << endl;
    cin >> houseNumber;
    cout << endl << "Number of the flat: " << endl;
    cin >> flatNumber;
    cout << endl << "Coordinates of this place (in format 'x y'): " << endl;
    cin >> x >> y;
    auto newAddress = new struct Address;
    *newAddress = {.title = title, .locality = locality, .houseNumber = houseNumber, .flatNumber = flatNumber, .x = x, .y = y};
    addressList.push_back(newAddress);
};

/**
 * this function is required to create addresses from the code
 */
void createAddress(string title, string locality, int houseNumber, int flatNumber, int x, int y) {
    auto newAddress = new struct Address();
    *newAddress = {.title = title, .locality = locality,  .houseNumber = houseNumber, .flatNumber = flatNumber, .x = x, .y = y};
    addressList.push_back(newAddress);
}

#endif //UNTITLED3_ADDRESS_H
