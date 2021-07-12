#ifndef UNTITLED3_RIDE_H
#define UNTITLED3_RIDE_H

#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <utility>
#include "Address.h"
#include "Cars.h"

using namespace std;

class Ride;

static vector<Ride*> rideList;

class Ride {
public:
    struct Address from, to;
    double price;
    int rate;
    PaymentMethod paymentMethod;
    Car* car;
    string passengerName, driverName;
    int additionalTime;
    time_t startTime, endTime;
    Ride(Address from, Address to, Car* car, string passengerName, string driverName, PaymentMethod pm, int additionalTime, int rate, unsigned long  st=0, unsigned long et=0) {
        this->from = move(from);
        this->to = move(to);
        this->rate = rate;
        this->additionalTime = additionalTime;
        this->car = car;
        this->passengerName = move(passengerName);
        this->driverName = move(driverName);
        paymentMethod = pm;
        double distance = 10 * Address::distance(from, to);
        price = distance * car->priceCoefficient;
        if (st == 0 && et == 0) {
            startTime = additionalTime + time(nullptr);
            endTime = startTime + (unsigned long) distance / car->getSpeed();
        }
        else {
            startTime = st;
            endTime = et;
        }
        rideList.push_back(this);
    }

    void showRide() {
        cout << "From:" << endl;
        from.showAddress();
        cout << "To:" << endl;
        to.showAddress();
        cout << "Driver: " << driverName << endl;
        cout << "Passenger: " << passengerName << endl;
        cout << "Price: " << price << endl;
        cout << "Rate: " << rate << endl;
        cout << "Payment method: ";
        printPaymentMethod(paymentMethod);
        cout << endl;
        cout << "Start time: " << asctime(localtime(&startTime));
        cout << "End time: " << asctime(localtime(&endTime));
    }

    void requestBill() const {
        cout << "This ride cost " << price << endl;
        cout << "Your driver's name is " << driverName << endl;
        string paymentMethodName;
        cout << "Payment method: ";
        printPaymentMethod(paymentMethod);
        cout << endl;
    }

    /**
     * the function calculates current position of a car
     * and prints it out
     * PS it is called only if the car is in the ride
     */
    void printCurrentCoordinates() const {
        unsigned long timePassed = time(nullptr) - startTime;
        unsigned long totalTime = endTime - startTime;
        int x = (int)(((double)timePassed / (double)totalTime) * abs(from.x - to.x) + from.x);
        int y = (int)(((double)timePassed / (double)totalTime) * abs(from.y - to.y) + from.y);
        cout << "Your current coordinates: " << endl;
        cout << "x: " << x << ", y: " << y << endl;
    };
};

#endif