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
#include <map>
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
    vector<string> devices;
    map<string, bool> availableFunctions;

    Passenger(string name, double rating, vector<string> devices, vector<struct Address*> addresses={}, vector<PaymentMethod> paymentMethods={}) :
                Person(move(name), rating){
        this->addresses = move(addresses);
        this->paymentMethods = move(paymentMethods);
        passengerList.push_back(this);
        this->devices = devices;
        availableFunctions = {
                {"specifyRide", true},
                {"showHistory", true},
                {"showPaymentMethods", true},
                {"updatePaymentMethods", true},
                {"seeCurrentCoordinates", true},
                {"showAddresses", true},
                {"createAddressPassenger", true},
                {"addAddress", true},
                {"deleteAddress", true},
                {"requestBill", true}
        };
    }

    void switchMobileDevice(istream& in, bool printInput) {
        cout << "Choose mobile device you want to use" << endl;
        int count = 1;
        for (string curDevice : devices) {
            cout << count << ") " << curDevice << endl;
            count++;
        }
        int option;
        in >> option;
        cout << "You have entered the system using " << devices[option - 1] << endl;
    }

    vector<struct Address*>* getAddresses() {
        return &addresses;
    }

    vector<PaymentMethod>* getPaymentMethod() {
        return &paymentMethods;
    }

    void showPaymentMethods() {
        if (!availableFunctions["showPaymentMethods"]) {
            cout << "This function is blocked" << endl;
            return;
        }
        cout << "Your payment methods: " << endl;
        int count = 0;
        for (PaymentMethod paymentMethod : paymentMethods) {
            count++;
            cout << count << ") ";
            printPaymentMethod(paymentMethod);
            cout << endl;
        }
    }

    void showHistory() {
        if (!availableFunctions["showHistory"]) {
            cout << "This function is blocked" << endl;
            return;
        }
        ((Person*)this)->showHistory();
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

    void updatePaymentMethods(istream& in, bool printInput) {
        if (!availableFunctions["updatePaymentMethods"]) {
            cout << "This function is blocked" << endl;
            return;
        }
        cout << "1) delete payment method" << endl;
        cout << "2) add payment method" << endl;
        cout << "3) return back" << endl;
        int option;
        in >> option;
        if (printInput) cout << option << endl;
        if (option == 2) addPaymentMethod(in, printInput);
        else if (option == 1) deletePaymentMethods(in, printInput);
        else if (option == 3) return;
    }

    void showAddresses() {
        if (!availableFunctions["showAddresses"]) {
            cout << "This function is blocked" << endl;
            return;
        }
        cout << "You have following addresses: " << endl;
        int count = 0;
        for (struct Address* address : addresses)  {
            count++;
            cout << count << ") ";
            address->showAddress();
        }
    }

    void addAddress(istream& in, bool printInput) {
        if (!availableFunctions["addAddress"]) {
            cout << "This function is blocked" << endl;
            return;
        }
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
        if (!availableFunctions["deleteAddress"]) {
            cout << "This function is blocked" << endl;
            return;
        }
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
        if (!history.empty()) {
            if (history.back()->endTime > time(nullptr)) {
                cout << "You last ride has not finished yet, so you cannot create a new one" << endl;
                return;
            }
        }
        if (!availableFunctions["specifyRide"]) {
            cout << "This function is blocked" << endl;
            return;
        }
        if (availableFunctions["showAddresses"]) showAddresses();
        else cout << "You cannot see the list of your addresses because this function was blocked" << endl;
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
            bool containRequiredCar = false;
            for (Car* curCar : driver->personalCars) {
                if (curCar->carType == carType && curCar->wasValidated) {
                    car = curCar;
                    break;
                }
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
                for (Car* curCar : driver->personalCars) {
                    if (curCar->carType == carType && curCar->wasValidated) {
                        auto ride = new struct AvailableRide(
                                addressList[a - 1], addressList[b - 1], this,
                                ridePrice, distance, PaymentMethod(number - 1), curCar);
                        driver->sendMessage(ride);
                        break;
                    }
                }
            }
        }
        cout << "Wait until someone accept your ride" << endl;
    }

    void createAddressPassenger() {
        if (!availableFunctions["createAddressPassenger"]) {
            cout << "This function is blocked" << endl;
            return;
        }
        createAddress();
    }

    void seeCurrentCoordinates(istream& in) {
        if (((Person*)this)->history.empty()) {
            cout << "You did not have any rides" << endl;
            return;
        }
        if (((Person*)this)->history.back()->startTime > time(nullptr)) {
            cout << "Your ride has not started yet" << endl;
        }
        else if (((Person*)this)->history.back()->endTime < time(nullptr)) {
            cout << "Your last ride was finished" << endl;
        }
        else {
            ((Person*)this)->history.back()->printCurrentCoordinates();
        }
    }

    void requestBill(istream& in) {
        if (!availableFunctions["requestBill"]) {
            cout << "This function is blocked" << endl;
            return;
        }
        if (((Person*)this)->history.empty()) {
            cout << "Your order history is empty" << endl;
        }
        else {
            ((Person*)this)->history.back()->requestBill();
        }
    }
};

#endif
