#ifndef UNTITLED3_PERSON_H
#define UNTITLED3_PERSON_H

#include "../Ride.h"
#include "../Cars.h"
#include <iostream>
#include <random>
#include <utility>

/**
 * base class for passenger and driver classes
 */
class Person {
public:
    double rating;
    string name;
    vector<Ride*> history; // all the rides person had during the program execution

    Person(string name, double rating) {
        this->name = move(name);
        this->rating = rating;
        history = {};
    }

    string getName() const {
        return name;
    }

    /**
     * the function prints out all the rides in the history of a user
     */
    void showHistory() {
        int count = 0;
        if (history.empty()) {
            cout << "Your history is empty" << endl;
            return;
        }
        for (Ride* ride : history) {
            count++;
            cout << "Ride number " << count << endl;
            ride->showRide();
            if (ride != history.back()) cout << endl;
        }
    }

    /**
     * the function is required to add ride to the history of some user
     * @param ride
     */
    void addHistoryRide(Ride* ride) {
        history.push_back(ride);
    }

    static void createRide(Address* from, Address* to, Person* driver, Person* passenger, Car* driversCar, PaymentMethod pm) {
        Car* car = driversCar;
        double distance = sqrt((car->x - from->x) * (car->x - from->x) + (car->y - from->y) * (car->y - from->y));
        int additionalTime = (int) distance / car->getSpeed();
        int rate = rand() % 6;
        auto ride = new Ride(*from, *to, driversCar, passenger->getName(), driver->getName(), pm, additionalTime, rate);
        passenger->addHistoryRide(ride);
        driver->addHistoryRide(ride);
    }
};

#endif //UNTITLED3_PERSON_H
