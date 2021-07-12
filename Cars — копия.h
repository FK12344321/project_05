#ifndef UNTITLED3_CARS_H
#define UNTITLED3_CARS_H

#include <iostream>
#include <vector>
#include <random>
#include <utility>
using namespace std;

class Car;
class Economy;
class Comfort;
class ComfortPlus;
class Business;

static vector<Car*> carList;
static vector<Economy*> economyList;
static vector<Comfort*> comfortList;
static vector<ComfortPlus*> comfortPlusList;
static vector<Business*> businessList;

class Car {
public:
    string model;
    string color;
    string number;
    int speed;
    string carType;
    double priceCoefficient;
    int x, y;
    bool wasValidated;

    Car(string model, int x, int y, string color, string number,
            string carType, int speed, double priceCoefficient, bool wasValidated) {
        this->model = move(model);
        this->carType = move(carType);
        this->x = x;
        this->y = y;
        this->color = move(color);
        this->number = move(number);
        this->speed = speed;
        this->priceCoefficient = priceCoefficient;
        this->wasValidated = wasValidated;
    }

    int getSpeed() const {return speed;}

    void showCar() const {
        cout << "Car model: " << model << endl;
        cout << "Color: " << color << endl;
        cout << "Number: " << number << endl;
        cout << "Car type: " << carType << endl;
        cout << "Speed: " << speed << endl;
        if (wasValidated) cout << "It was validated by admin" << endl;
        else cout << "It was not validated" << endl;
    }
};

class Economy : public Car {
public:
    Economy(string model, int x, int y, string color, string number, bool wasValidated, string carType="Economy", int speed=60, double priceCoefficient=0.6) :
            Car(move(model), x, y, move(color), move(number), move(carType), speed, priceCoefficient, wasValidated) {
        economyList.push_back(this);
        carList.push_back(this);
    }

};

class Comfort : public Car {
private:
    int freeBottleOfWater;
public:
    Comfort(string model, int x, int y, string color, string number, bool wasValidated, int freeBottleOfWater=12, string carType="Comfort", int speed=60, double priceCoefficient=0.8) :
            Car(move(model), x, y, move(color), move(number), move(carType), speed, priceCoefficient, wasValidated) {
        this->freeBottleOfWater = freeBottleOfWater;
        comfortList.push_back(this);
        carList.push_back(this);
    }

    void reduceFreeBottleCount() {
        freeBottleOfWater -= rand() % 4;
        if (freeBottleOfWater < 0) freeBottleOfWater = 0;
    }
};

class ComfortPlus : public Car {
public:
    ComfortPlus(string model, int x, int y, string color, string number, bool wasValidated, string carType="ComfortPlus", int speed=60, double priceCoefficient=0.9) :
            Car(move(model), x, y, move(color), move(number), move(carType), speed, priceCoefficient, wasValidated) {
        comfortPlusList.push_back(this);
        carList.push_back(this);
    }
};

class Business : public Car {
public:
    Business(string model, int x, int y, string color, string number, bool wasValidated, string carType="Business", int speed=60, double priceCoefficient=1.2) :
            Car(move(model), x, y, move(color), move(number), move(carType), speed, priceCoefficient, wasValidated)  {
        businessList.push_back(this);
        carList.push_back(this);
    };

    void parkRightInFrontOfTheEntrance() {
        cout << "Parked right in front of the entrance" << endl;
    }
};


#endif //UNTITLED3_CARS_H
