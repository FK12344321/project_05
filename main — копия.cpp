#include "Interface.h"
#include "Users/Admin.h"

using namespace std;

void useInterface() {
    interface(cin, false);
}

void showInterfaceTest() {
    fstream inputFile;
    inputFile.open("../example");
    interface(inputFile, true);
}

void adminFunctionalExample() {
    Admin admin;
    carList[1]->showCar();
    cout << "------------------------------------------" << endl;
    // as you see admin cannot do anything because he is not logged in
    admin.validateCar(carList[1]);
    cout << "------------------------------------------" << endl;
    admin.login("Admin Admin"); // but here he logs in
    cout << "------------------------------------------" << endl;
    admin.validateCar(carList[1]); //and he can validate a car
    carList[1]->showCar(); // you see that the status of the car has really changed
    cout << "------------------------------------------" << endl;
    admin.validateCarBack(carList[1]); // and he can also cancel the validation
    // he can also see any personal users' information
    admin.showDriverCars(admin.getDriver("Anton Kirilin"));
    cout << "------------------------------------------" << endl;
    admin.showPassengerAddressList(admin.getPassenger("Pavel Roganin"));
    cout << "------------------------------------------" << endl;
    // and he can bock and unblock users' functions
    // he blocks the function "showAddresses" of Ruslan Khakimov
    admin.blockPassengerFunction(admin.getPassenger("Ruslan Khakimov"), "showAddresses");
    // and now Ruslan cannot use this function
    admin.getPassenger("Ruslan Khakimov")->showAddresses();
    cout << "------------------------------------------" << endl;
    // but admin unblocks this function and user can use it
    admin.unblockPassengerFunction(admin.getPassenger("Ruslan Khakimov"), "showAddresses");
    admin.getPassenger("Ruslan Khakimov")->showAddresses();
    cout << "------------------------------------------" << endl;
    // the same with drivers and all other functions
    admin.blockDriverFunction(admin.getDriver("Marina Malova"), "showPersonalCars");
    admin.getDriver("Marina Malova")->showPersonalCars();
    cout << "------------------------------------------" << endl;
    admin.unblockDriverFunction(admin.getDriver("Marina Malova"), "showPersonalCars");
    admin.getDriver("Marina Malova")->showPersonalCars();
};

int main() {
    downloadData();
    showInterfaceTest();
}
