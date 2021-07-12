#ifndef UNTITLED3_DATAUPDATE_H
#define UNTITLED3_DATAUPDATE_H

#include "../Cars.h"
#include "../Address.h"
#include "../Ride.h"
#include "../Users/Driver.h"
#include "../Users/Passenger.h"
#include "../PaymentMethods.h"
#include <cstdio>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * the function parses all the data to necessary format
 * and uploads it to the data base file
 */
void uploadData() {
    ofstream output;
    output.open("../DataBase/Data");
    output << "***" << endl;
    output << "**" << endl;
    int count = -1;
    for (Address* address : addressList) {
        output << "*" << endl;
        count++;
        output << count << endl;
        output << address->title << endl;
        output << address->locality << endl;
        output << address->houseNumber << endl;
        output << address->flatNumber << endl;
        output << address->x << endl;
        output << address->y << endl;
    }
    output << "*" << endl << "**" << endl;
    count = -1;
    for (Car* car : carList) {
        output << "*" << endl;
        count++;
        output << count << endl;
        output << car->carType << endl;
        output << car->model << endl;
        output << car->x << endl;
        output << car->y << endl;
        output << car->color << endl;
        output << car->number << endl;
        output << car->wasValidated << endl;
    }
    output << "*" << endl << "**" << endl;
    count = -1;
    for (Driver* driver : driverList) {
        output << "*" << endl;
        count++;
        output << count << endl;
        output << driver->name << endl;
        output << driver->rating << endl;
        for (int i = 0; i < carList.size(); i++) {
            for (Car* car : driver->personalCars) {
                if (car == carList[i]) output << i << ",";
            }
        }
        if (driver->personalCars.empty()) output << ",," << endl;
        else output << "," << endl;
        output << driver->canWork << endl;
    }
    output << "*" << endl << "**" << endl;
    count = -1;
    for (Passenger* passenger : passengerList) {
        output << "*" << endl;
        count++;
        output << count << endl;
        output << passenger->name << endl;
        output << passenger->rating << endl;
        for (int i = 0; i < passenger->addresses.size(); i++) {
            for (int j = 0; j < addressList.size(); j++) {
                if (passenger->addresses[i] == addressList[j]) output << j << ",";
            }
        }
        if (addressList.empty()) output << ",," << endl;
        else output << "," << endl;
        for (PaymentMethod pm : passenger->paymentMethods)
            output << (int)pm << ",";
        if (passenger->paymentMethods.empty()) output << ",," << endl;
        else output << "," << endl;
        for (string device : passenger->devices)
            output << device << ",";
        if (passenger->devices.empty()) output << ",," << endl;
        else output << "," << endl;
    }
    output << "*" << endl << "**" << endl;
    count = -1;
    for (Ride* ride : rideList) {
        output << "*" << endl;
        count++;
        output << count << endl;
        for (int i = 0; i < addressList.size(); i++) {
            if (ride->from.title == addressList[i]->title) {
                output << i << endl;
            }
        }
        for (int i = 0; i < addressList.size(); i++) {
            if (ride->to.title == addressList[i]->title) {
                output << i << endl;
            }
        }
        for (int i = 0; i < carList.size(); i++) {
            if (carList[i] == ride->car) {
                output << i << endl;
                break;
            }
        }
        for (int i = 0; i < passengerList.size(); i++) {
            if (passengerList[i]->name == ride->passengerName) {
                output << i << endl;
            }
        }
        for (int i = 0; i < passengerList.size(); i++) {
            if (driverList[i]->name == ride->driverName) {
                output << i << endl;
            }
        }
        output << (int)ride->paymentMethod << endl;
        output << ride->additionalTime << endl;
        output << ride->startTime << endl;
        output << ride->endTime << endl;
        output << ride->rate << endl;
    }
    output << "*" << endl << "**" << endl;
    output << time(nullptr) << endl << "**" << endl << "***";
    output.close();
};

/**
 * the function parses all the data from the file
 * to normal format and download it to the program, so users
 * can use and update it
 */
void downloadData() {
    fstream input;
    input.open("../DataBase/Data");
    if (!input.is_open()) {
        cout << "Error of data upload" << endl;
        return;
    }
    string currentLine;
    getline(input, currentLine);
    int sectionNumber = 0;
    while (sectionNumber != 7) {
        sectionNumber++;
        switch (sectionNumber) {
            case 1:
                getline(input, currentLine);
                getline(input, currentLine);
                while (true) {
                    getline(input, currentLine);
                    if (currentLine == "**") break;
                    int number = stoi(currentLine);
                    getline(input, currentLine);
                    string title = currentLine;
                    getline(input, currentLine);
                    string locality = currentLine;
                    getline(input, currentLine);
                    int houseNumber = stoi(currentLine);
                    getline(input, currentLine);
                    int flatNumber = stoi(currentLine);
                    getline(input, currentLine);
                    int x = stoi(currentLine);
                    getline(input, currentLine);
                    int y = stoi(currentLine);
                    createAddress(title, locality, houseNumber, flatNumber, x, y);
                    getline(input, currentLine);
                }
                break;
            case 2:
                getline(input, currentLine);
                while (true) {
                    getline(input, currentLine);
                    if (currentLine == "**") break;
                    int number = stoi(currentLine);
                    getline(input, currentLine);
                    string carType = currentLine;
                    getline(input, currentLine);
                    string model = currentLine;
                    getline(input, currentLine);
                    int x = stoi(currentLine);
                    getline(input, currentLine);
                    int y = stoi(currentLine);
                    getline(input, currentLine);
                    string color = currentLine;
                    getline(input, currentLine);
                    string carNumber = currentLine;
                    getline(input, currentLine);
                    bool wasValidated = (bool)stoi(currentLine);
                    if (carType == "Economy")
                        auto car = new Economy(model, x, y, color, carNumber, wasValidated);
                    else if (carType == "Comfort")
                        auto car = new Comfort(model, x, y, color, carNumber, wasValidated);
                    else if (carType == "ComfortPlus")
                        auto car = new ComfortPlus(model, x, y, color, carNumber, wasValidated);
                    else if (carType == "Business")
                        auto car = new Business(model, x, y, color, carNumber, wasValidated);
                    getline(input, currentLine);
                }
                break;
            case 3:
                getline(input, currentLine);
                while (true) {
                    getline(input, currentLine);
                    if (currentLine == "**") break;
                    int number = stoi(currentLine);
                    getline(input, currentLine);
                    string name = currentLine;
                    getline(input, currentLine);
                    double rating = stod(currentLine);
                    vector<Car*> cars;
                    while (true) {
                        string carNumber;
                        getline(input, carNumber, ',');
                        if (carNumber.empty()) break;
                        cars.push_back(carList[stoi(carNumber)]);
                    }
                    getline(input, currentLine, '\n');
                    getline(input, currentLine);
                    bool canWork = (bool)stoi(currentLine);
                    getline(input, currentLine);
                    auto driver = new Driver(name, rating, cars, canWork);
                }
                break;
            case 4:
                getline(input, currentLine);
                while (true) {
                    getline(input, currentLine);
                    if (currentLine == "**") break;
                    int number = stoi(currentLine);
                    getline(input, currentLine);
                    string name = currentLine;
                    getline(input, currentLine);
                    double rating = stod(currentLine);
                    vector<struct Address*> addresses;
                    while (true) {
                        string addressNumber;
                        getline(input, addressNumber, ',');
                        if (addressNumber.empty()) break;
                        addresses.push_back(addressList[stoi(addressNumber)]);
                    }
                    getline(input, currentLine, '\n');
                    vector<PaymentMethod> pm;
                    while (true) {
                        string paymentMethod;
                        getline(input, paymentMethod, ',');
                        if (paymentMethod.empty()) break;
                        pm.push_back((PaymentMethod)stoi(paymentMethod));
                    }
                    getline(input, currentLine, '\n');
                    vector<string> devices;
                    while (true) {
                        string device;
                        getline(input, device, ',');
                        if (device.empty()) break;
                        devices.push_back(device);
                    }
                    getline(input, currentLine, '\n');
                    auto passenger = new Passenger(name, rating, devices, addresses, pm);
                    getline(input, currentLine);
                }
                break;
            case 5:
                getline(input, currentLine);
                while (true) {
                    getline(input, currentLine);
                    if (currentLine == "**") break;
                    int number = stoi(currentLine);
                    getline(input, currentLine);
                    int from = stoi(currentLine);
                    getline(input, currentLine);
                    int to = stoi(currentLine);
                    getline(input, currentLine);
                    int car = stoi(currentLine);
                    getline(input, currentLine);
                    int passenger = stoi(currentLine);
                    getline(input, currentLine);
                    int driver = stoi(currentLine);
                    getline(input, currentLine);
                    auto pm = (PaymentMethod) stoi(currentLine);
                    getline(input, currentLine);
                    int additionalTime = stoi(currentLine);
                    getline(input, currentLine);
                    unsigned long startTime = stoi(currentLine);
                    getline(input, currentLine);
                    unsigned long endTime = stoi(currentLine);
                    getline(input, currentLine);
                    int rate = stoi(currentLine);
                    auto ride = new Ride(*addressList[from], *addressList[to], carList[car],
                                         passengerList[passenger]->getName(),
                                         driverList[driver]->getName(), pm, additionalTime,
                                         rate, startTime, endTime);
                    getline(input, currentLine);
                    passengerList[passenger]->addHistoryRide(ride);
                    driverList[driver]->addHistoryRide(ride);
                }
                break;
            case 7:
                getline(input, currentLine);
                int totalTime = stoi(currentLine);
                getline(input, currentLine);
                getline(input, currentLine);
                break;
        }
    }
    input.close();
};

#endif //UNTITLED3_DATAUPDATE_H
