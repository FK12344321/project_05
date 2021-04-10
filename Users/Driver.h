#ifndef UNTITLED3_DRIVER_H
#define UNTITLED3_DRIVER_H

#include <utility>

#include "../Cars.h"
#include "Person.h"

class Driver;

static vector<Driver*> driverList; // list of all the drivers
static vector<Driver*> availableDriverList; // list of drivers who are workign at this moment

/**
 * struct storing all the information about the available ride for a driver
 */
struct AvailableRide {
    Person* passenger;
    string passengerName;
    PaymentMethod paymentMethod;
    double price;
    double distance;
    Address* from;
    Address* to;

    AvailableRide(Address* from, Address* to, Person* passenger, double price, double distance, PaymentMethod pm) {
        this->passengerName = passenger->getName();
        this->passenger = passenger;
        this->price = price;
        this->distance = distance;
        this->from = from;
        this->to = to;
        paymentMethod = pm;
    }
};

class Driver : public Person {
public:
    Car* personalCar;
    bool canWork;
    vector<struct AvailableRide*> availableRides;

    Driver(string name, double rating, Car* personalCar, bool canWork) : Person(move(name), rating) {
        this->canWork = canWork;
        this->personalCar = personalCar;
        availableRides = {};
        driverList.push_back(this);
        if (canWork) availableDriverList.push_back(this);
    }

    void checkOrders(istream& in, bool printInput) {
        // the function allow the driver to accept or decline available orders
        int count = 0;
        for (struct AvailableRide* ride : availableRides) {
            count++;
            cout << count << ") Passenger: " << ride->passengerName << endl;
            cout << "Price: " << ride->price << endl;
            cout << "Distance: " << ride->distance << endl;
            cout << "Payment method: ";
            printPaymentMethod(ride->paymentMethod);
            cout << endl;
        }
        cout << availableRides.size() + 1 << ") return back" << endl;
        cout << "Print a number of a ride you want to accept/decline or '" << availableRides.size() + 1;
        cout << "' if you want to return back" << endl;
        int number;
        in >> number;
        if (printInput) cout << number << endl;
        if (number == availableRides.size() + 1) return;
        cout << "------------------------------------------" << endl;
        cout << "1) accept" << endl << "2) decline" << endl;
        int option;
        in >> option;
        if (printInput) cout << option << endl;
        if (option == 2) availableRides.erase(availableRides.cbegin() + number - 1);
        if (option == 1) {
            for (int i = 0; i < driverList.size(); i++) {
                for (int j = 0; j < driverList[i]->availableRides.size(); j++) {
                    if (driverList[i]->availableRides[j] == availableRides[number - 1]) {
                        driverList[i]->availableRides.erase(driverList[i]->availableRides.cbegin() + j);
                    }
                }
            }
            Person::createRide(availableRides[number - 1]->from, availableRides[number - 1]->to, this,
                               availableRides[number - 1]->passenger, personalCar,
                               availableRides[number - 1]->paymentMethod);
            personalCar->x = history.back()->to.x;
            personalCar->y = history.back()->to.y;
            if (this->personalCar->carType == "Comfort" || this->personalCar->carType == "ComfortPlus")
                ((Comfort*)(this->personalCar))->reduceFreeBottleCount();
            if (this->personalCar->carType == "Business")
                ((Business*)(this->personalCar))->parkRightInFrontOfTheEntrance();
        }
    }

    /**
     * the function pushes an order to the list of available orders
     * @param newRide
     */
    void sendMessage(struct AvailableRide* newRide) {
        availableRides.push_back(newRide);
    }

    void updateStatus(istream& in, bool printInput) {
        if (canWork) cout << "You are working now" << endl;
        else cout << "You do not work now" << endl;
        cout << "Do you want to change your status?" << endl;
        cout << "1) yes" << endl << "2) no" << endl;
        int number;
        in >> number;
        if (printInput) cout << number << endl;
        if (number == 2) return;
        if (number == 1) {
            if (canWork) {
                canWork = false;
                for (int i = 0; i < availableDriverList.size(); i++) {
                    if (availableDriverList[i] == this) {
                        availableDriverList.erase(availableDriverList.cbegin() + i);
                        return;
                    }
                }
            }
            else {
                canWork = true;
                availableDriverList.push_back(this);
            }
        }
    }
};

#endif //UNTITLED3_DRIVER_H
