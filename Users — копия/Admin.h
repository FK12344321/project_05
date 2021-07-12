#ifndef UNTITLED3_ADMIN_H
#define UNTITLED3_ADMIN_H

#include "Passenger.h"
#include "Driver.h"

class Admin {
private:
    string name = "Admin Admin";
    bool loggedIn = false;
public:
    Admin() = default;

    void login(string name) {
        loggedIn = name == this->name;
        if (loggedIn) cout << "Admin has logged in successfully" << endl;
    }

    Admin(string name) {
        login(name);
    }

    bool isLoggedIn() const {
        if (!loggedIn) {
            cout << "The admin is not logged in, so he cannot do anything" << endl;
            return false;
        }
        return true;
    }

    bool isAdmin(string name) {
        return name == this->name;
    }

    static Passenger* getPassenger(string name) {
        for (Passenger* passenger : passengerList) {
            if (passenger->name == name) return passenger;
        }
        return nullptr;
    }

    static Driver* getDriver(string name) {
        for (Driver* driver : driverList) {
            if (driver->name == name) return driver;
        }
        return nullptr;
    }

    void showPersonalHistory(Person* person) const {
        if (!isLoggedIn()) return;
        person->showHistory();
    }

    void showDriverStatus(Driver* driver) const {
        if (!isLoggedIn()) return;
        if (driver->canWork) cout << "The driver is working now" << endl;
        else cout << "The driver is not working now" << endl;
    }

    void showDriverCars(Driver* driver) const {
        if (!isLoggedIn()) return;
        driver->showPersonalCars();
    }

    void showDriverAvailableOrders(Driver* driver) const {
        if (!isLoggedIn()) return;
        driver->showAvailableOrders();
    }

    void showPassengerPaymentMethod(Passenger* passenger) const {
        if (!isLoggedIn()) return;
        passenger->showPaymentMethods();
    }

    void showPassengerAddressList(Passenger* passenger) const {
        if (!isLoggedIn()) return;
        passenger->showAddresses();
    }

    void validateCar(Car* car) const {
        if (!isLoggedIn()) return;
        car->wasValidated = true;
    }

    void validateCarBack(Car* car) const {
        if (!isLoggedIn()) return;
        car->wasValidated = false;
    }

    void blockPassengerFunction(Passenger* passenger, string functionName) {
        passenger->availableFunctions[functionName] = false;
    }

    void unblockPassengerFunction(Passenger* passenger, string functionName) {
        passenger->availableFunctions[functionName] = true;
    }

    void blockDriverFunction(Driver* driver, string functionName) {
        driver->availableFunctions[functionName] = false;
    }

    void unblockDriverFunction(Driver* driver, string functionName) {
        driver->availableFunctions[functionName] = true;
    }
};

#endif //UNTITLED3_ADMIN_H