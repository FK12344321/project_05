# project_05
# ItP_HW04
##### <a name="Parag"></a>IDE: Clion
##### <a name="Parag"></a>Basic idea: 
There are two classes that intertact with each: passenger and driver gateways. Their capabilities are described in requiremens. 
##### <a name="Parag"></a>Features of interaction with user:
All the interaction with a user is implimented through the console. Firstly, the user should login to the system. The program checks if there is such a user in the list of passengers or in the list of drivers. If there is no such user it asks the user to try again, othrerwise it prints out the general interface of a driver or passenger. This interface is implimented in the main.cpp file. Depending on user's input it executes different functions from the Passenger class or Driver class. These user classes also provide additional interface for futher interaction with a user (for example to choose "from" and "to" of a ride or to choose payment method ). User can print the number of action he wants to be executed. 
![Снимок экрана 2021-04-10 в 15 46 38](https://user-images.githubusercontent.com/69464701/114270261-08a53400-9a14-11eb-8ee8-61c120f94a4c.png)

User can order a ride, specify payment method, car typr, and "from" and "to" addresses. He can also reject this ride when program calculate the price of the ride. When he confirms that he want to create an order: this order goes to the lists of available orders of all the suitable drivers (those who is working now and have suitable car type). After that driver need to login and confirm that he wants to take this ride (he also can decline it). When he confirms it, the ride starts. Actually the ride is created and pushed to the history of a driver and passenger. Anyway, driver need time to get to the "from" address (this time is calculated accrording the current position of a car and its speed). When the driver arrives to the "from" address, passenger can see the current coordinates of a car. After the ride he can request a bill of this ride and see it in his history. Driver also can see this ride in his history. 
##### <a name="Parag"></a>Data base:
My data base is just a text file in a special (created by me) format. There are two functions: uploadData function parses all the data of the program (personal information of users, addresses, rides and etc) to the rrequired format and uploads it to the file, downloadData function downloads all the necessary data from the file and parses it to the suitable format and downloads it to the program, creating objects and so on. These functions are called at the beginning and end of execution. 
##### <a name="Parag"></a>Format of data base: 
There are following sections: addresses, cars, drivers, passengers, and rides. Every sections is separated with double stars and every section contains informastion about objects of this sections (for example information of some users). Every object is separated with a single star. Every object has a number n, so if I need to bind two objects together (for example, a driver with a car), I will have a number of a car in the carList, so I can create a pointer to this object. There is also AdditionalDataFile that store the same information as Data file(just in case). 

To check that data base works correctly you can enter the system as Ruslan Khakimov, create an address, exit the system (there is such option in the general interface), switch on the program, enter the system as "Ruslan Khakimov", choose "add an address to the list of your addresses", and you will see that newly created address will be in the list of available addresses. You can also see this address in the Data file after the execution of the program. 
##### <a name="Parag"></a>How you can test my priogram: 
There is an "example" text file. By default the program reads all the commands from this file (not from the console). This file is required to show you functional of my project. In this file you can read its description and look at console output to understand what is going on. 

To begin interacting with the program yourself you need to 1) assign false to a variable "printInput" on the 41-st line of main.cpp and assign a value "cin" to input variable (instead of "inputFile")on the 42-nd line. 


![Снимок экрана 2021-04-10 в 16 50 45](https://user-images.githubusercontent.com/69464701/114272021-f54a9680-9a1c-11eb-93fe-d098d158d326.png)


One important functions are not covered in the "example" file, but you can check it yourself. You need to enter the system as "Pavel Roganin" (or any other user from the Data file), order ride, choose addresses "1" and "3", select "Business" class, confirm that you want ot create the ride, choose cash as a payment method, log out, enter the system as "Andrey Kuzmicky", check available orders, choose the first available order, accept it, log out, enter the system as Pavel Roganin, and begin requesting current coordinates. When the driver arrives to your location, you will see how coordinates are changed every time you request current coordinates until you come to "to" adderss. After that you will be able to see this ride in your order history and request a bill for this ride. 
