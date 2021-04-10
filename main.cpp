#include <iostream>
#include <ctime>
#include "Users/Passenger.h"
#include "Users/Driver.h"
#include "DataBase/dataUpdate.h"

using namespace std;

Passenger* loginPassenger(string name) {
    for (Passenger *passenger : passengerList) {
        if (((Person *) passenger)->getName() == name) {
            cout << "You have entered the system as a passenger" << endl;
            return passenger;
        }
    }
    return nullptr;
}

Driver* loginDriver(string name) {
    for (Driver* driver : driverList) {
        if (((Person*)driver)->getName() == name) {
            cout << "You have entered the system as a driver" << endl;
            return driver;
        }
    }
    return nullptr;
}

/**
 * the main function of the main function here is
 * general interface
 * it allows the user to login and choose what the program
 * need to execute
 * depending on the choice, it calls necessary function from driver or passenger gateways
 * @return
 */
int main() {
    downloadData();
    fstream inputFile;
    inputFile.open("../example");
    bool printInput = true;
    istream& input = inputFile;
    while (true) {
        cout << "------------------------------------------" << endl;
        cout << "Login" << endl << "Your name: ";
        string name, surname;
        input >> name;
        if (printInput) cout << name << endl;
        cout << "Your surname: ";
        input >> surname;
        if (printInput) cout << surname << endl;
        string fullName = move(name) + " " + move(surname);
        cout << "------------------------------------------" << endl;
        Passenger* passenger = loginPassenger(fullName);
        Driver* driver = loginDriver(fullName);
        if (passenger != nullptr) {
            generalPassengerInterface:
            cout << "------------------------------------------" << endl;
            cout << "What do you want to do? (write a number)" << endl;
            cout << "1) order a ride" << endl;
            cout << "2) see your order history" << endl;
            cout << "3) see your payment methods" << endl;
            cout << "4) update payment methods" << endl;
            cout << "5) ask for the current coordinates" << endl;
            cout << "6) see a list of your addresses" << endl;
            cout << "7) create address" << endl;
            cout << "8) add an address to the list of your addresses" << endl;
            cout << "9) delete an address from the list of your addresses" << endl;
            cout << "10) ask for the bill of your last ride" << endl;
            cout << "11) log out" << endl;
            cout << "12) exit the system" << endl;
            cout << "------------------------------------------" << endl;
            int number;
            bool exitSystem = false;
            bool logOut = false;
            input >> number;
            if (printInput) cout << number << endl;
            switch (number) {
                case 1:
                    passenger->specifyRide(input, printInput);
                    break;
                case 2:
                    passenger->showHistory();
                    break;
                case 3:
                    passenger->showPaymentMethods();
                    break;
                case 4:
                    cout << "1) delete payment method" << endl;
                    cout << "2) add payment method" << endl;
                    cout << "3) return back" << endl;
                    int in;
                    input >> in;
                    if (printInput) cout << "in" << endl;
                    if (in == 2) passenger->addPaymentMethod(input, printInput);
                    else if (in == 1) passenger->deletePaymentMethods(input, printInput);
                    else if (in == 3) break;
                    break;
                case 5:
                    if (((Person*)passenger)->history.empty()) {
                        cout << "You did not have any rides" << endl;
                        break;
                    }
                    if (((Person*)passenger)->history.back()->startTime > time(nullptr)) {
                        cout << "Your ride has not started yet" << endl;
                    }
                    else if (((Person*)passenger)->history.back()->endTime < time(nullptr)) {
                        cout << "Your last ride was finished" << endl;
                    }
                    else {
                        ((Person*)passenger)->history.back()->printCurrentCoordinates();
                    }
                    break;
                case 6:
                    passenger->showAddresses();
                    break;
                case 7:
                    createAddress();
                    break;
                case 8:
                    passenger->addAddress(input, printInput);
                    break;
                case 9:
                    passenger->deleteAddress(input, printInput);
                    break;
                case 10:
                    if (((Person*)passenger)->history.empty()) {
                        cout << "Your order history is empty" << endl;
                    }
                    else {
                        ((Person*)passenger)->history.back()->requestBill();
                    }
                    break;
                case 11:
                    logOut = true;
                    break;
                case 12:
                    exitSystem = true;
                    break;
                case 404:
                    //special secret case to terminate the execution not storing
                    //the results of execution
                    return 0;
            }
            if (exitSystem) {
                uploadData();
                return 0;
            }
            if (logOut) continue;
            goto generalPassengerInterface;
        } else if (driver != nullptr) {
            generalDriverInterface:
            cout << "------------------------------------------" << endl;
            cout << "1) see your order history" << endl;
            cout << "2) see a car" << endl;
            cout << "3) update status" << endl;
            cout << "4) check available orders" << endl;
            cout << "5) log out" << endl;
            cout << "6) exit the system" << endl;
            cout << "------------------------------------------" << endl;
            int number;
            bool exitSystem = false;
            bool logOut = false;
            input >> number;
            if (printInput) cout << number << endl;
            switch (number) {
                case 1:
                    driver->showHistory();
                    break;
                case 2:
                    driver->personalCar->showCar();
                    break;
                case 3:
                    driver->updateStatus(input, printInput);
                    break;
                case 4:
                    driver->checkOrders(input, printInput);
                    break;
                case 5:
                    logOut = true;
                    break;
                case 6:
                    exitSystem = true;
                    break;
                case 404:
                    //special secret case to terminate the execution not storing
                    //the results of execution
                    return 0;
            }
            if (exitSystem) {
                uploadData();
                return 0;
            }
            if (logOut) continue;
            goto generalDriverInterface;
        } else {
            cout << "There is no such user. Try again" << endl;
            continue;
        }
    }
}
