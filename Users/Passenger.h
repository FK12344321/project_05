#ifndef UNTITLED3_PASSENGER_H
#define UNTITLED3_PASSENGER_H

#include "../PaymentMethods.h"
#include "../Ride.h"
#include "../Address.h"
#include "Person.h"
#include "../Cars.h"
#include "Driver.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
using namespace std;

class Passenger;

static vector<Passenger*> passengerList; // list of all the passengers in the system

/**
 * passenger gateway class for user interaction
 */
class Passenger : public Person {
public:
    vector<struct Address*> addresses;
    vector<PaymentMethod> paymentMethods;
    vector<Ride> history;
    Passenger(string name, double rating, vector<struct Address*> addresses={}, vector<PaymentMethod> paymentMethods={}) :
                Person(move(name), rating){
        this->addresses = move(addresses);
        this->paymentMethods = move(paymentMethods);
        passengerList.push_back(this);
    }

    void showPaymentMethods() {
        cout << "Your payment methods: " << endl;
        int count = 0;
        for (PaymentMethod paymentMethod : paymentMethods) {
            count++;
            cout << count << ") ";
            printPaymentMethod(paymentMethod);
            cout << endl;
        }
    }

    void addPaymentMethod(istream& in, bool printInput) {
        cout << "You can add following payment methods:" << endl;
        cout << "1) cash" << endl << "2) bank card" << endl;
        cout << "3) online wallet" << endl << "4) bank transfer" << endl;
        cout << "5) promo code" << endl << "6) return back" << endl;
        cout << "Which one do you want to add? (print a number)" << endl;
        int number;
        in >> number;
        if (printInput) cout << number << endl;
        if (number == 6) return;
        auto toAdd = (PaymentMethod)(number - 1);
        bool alreadyExists = false;
        for (PaymentMethod paymentMethod : paymentMethods) {
            if (toAdd == paymentMethod) {
                cout << "You already have this  method of payment" << endl;
                alreadyExists = true;
                break;
            }
        }
        if (!alreadyExists) paymentMethods.push_back(toAdd);
    }

    void deletePaymentMethods(istream& in, bool printInput) {
        showPaymentMethods();
        cout << paymentMethods.size() + 1 <<") return back" << endl;
        cout << "Which one do you want to delete (print a number):" << endl;
        int number;
        in >> number;
        if (printInput) cout << number << endl;
        if (number == paymentMethods.size() + 1) return;
        paymentMethods.erase(paymentMethods.begin() + number - 1);
    }

    void showAddresses() {
        cout << "You have following addresses: " << endl;
        int count = 0;
        for (struct Address* address : addresses)  {
            count++;
            cout << count << ") ";
            address->showAddress();
        }
    }

    void addAddress(istream& in, bool printInput) {
        int count = 0;
        cout << "There are following addresses" << endl;
        for (Address* address : addressList) {
            count++;
            cout << count << ") ";
            address->showAddress();
            cout << endl;
        }
        cout << addressList.size() + 1 << ") return back" << endl;
        cout << "Which one do you want to add?" << endl;
        int number;
        in >> number;
        if (printInput) cout << number << endl;
        if (number == addressList.size() + 1) return;
        addresses.push_back(addressList[number - 1]);
    }

    void deleteAddress(istream& in, bool printInput) {
        showAddresses();
        cout << addresses.size() + 1 << ") return back" << endl;
        cout << "Which one do you want to delete? (print a number)" << endl;
        int number;
        in >> number;
        if (printInput) cout << number << endl;
        if (number == addresses.size() + 1) return;
        addresses.erase(addresses.begin() + number - 1);
    }

    void specifyRide(istream& in, bool printInput) {
        showAddresses();
        cout << addresses.size() + 1 << ") return back" << endl;
        cout << "Choose any two (write two numbers in the format 'a b')" << endl;
        int a, b;
        in >> a;
        if (a == addresses.size() + 1) {
            if (printInput) cout << a;
            return;
        }
        in >> b;
        if (printInput) cout << a << " " << b << endl;
        cout << "There are following car types:" << endl;
        cout << "1) Economy" << endl << "2) Comfort" << endl << "3) Comfort Plus" << endl << "4) Business" << endl;
        cout << "Choose any (write a number)" << endl;
        int number;
        double ridePrice;
        in >> number;
        if (printInput) cout << number << endl;
        string carType;
        if (number == 1) carType = "Economy";
        else if (number == 2) carType = "Comfort";
        else if (number == 3) carType = "ComfortPlus";
        else if (number == 4) carType = "Business";
        Car* car = nullptr;
        for (Driver* driver : availableDriverList) {
            if (driver->personalCar->carType == carType) {
                car = driver->personalCar;
            }
        }
        if (car == nullptr) {
            cout << "There are no available cars of this type" << endl;
            return;
        }
        double distance = Address::distance(*addressList[a - 1], *addressList[b - 1]);
        ridePrice = car->priceCoefficient * distance;
        cout << "The ride will cost " << ridePrice << endl;
        cout << "Do you still want to create a ride (1 - yes, 2 - no)? (write 1 or 2)" << endl;
        in >> number;
        if (printInput) cout << number << endl;
        if (number == 2) {
            return;
        }
        if (number == 1) {
            cout << "What payment method do you want to use? (print a number)" << endl;
            showPaymentMethods();
            in >> number;
            for (Driver* driver : availableDriverList) {
                if (driver->personalCar->carType == carType) {
                    auto ride = new struct AvailableRide(addressList[a - 1], addressList[b - 1], this, ridePrice, distance, PaymentMethod(number - 1));
                    driver->sendMessage(ride);
                }
            }
        }
        cout << "Wait until someone accept your ride" << endl;
    }
};

#endif
