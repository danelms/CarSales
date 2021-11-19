#include <iostream>
#include <cstring>
#include "ReadLine.h"
#include "Car.cpp"
#include "Sales.cpp"
void mainMenu();
void viewCars();
void buyCars();
void adminMenu();
void addStock();
void removeStock();
void viewSales();
void loadFiles();
void saveFiles();

#define MAX_LEN 255
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

Car* _stock[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
Sale* _sales[];

const char* _adminPassword = "hardPasswordToGuess123!#";

int main()
{
    //loadFiles()
    mainMenu();
}

void mainMenu()
{
    bool _quit = false;

    while (!_quit)
    {
        printf("\nMain Menu:\n\n1. View Cars in Stock\n2. Purchase a Car\n3. Admin Menu\n4. Quit\n\n");

        int _selection = readIntInRange("Select an option from the menu: ",1,4);

        if (_selection == 1)
        {
            viewCars();
        }
        else if (_selection == 2)
        {
            printf("\nSelection 2\n");
        }
        else if (_selection == 3)
        {
            adminMenu();
        }
        else if (_selection == 4)
        {
            _quit = true;
        }
    }

    printf("\nThank you for visiting!\n");
}

void viewCars()
{
    //TEST
    _stock[0] = new Car;
    _stock[0]->setMake("Volkswagen");
    _stock[0]->setModel("Golf");
    //ENDTEST

    for (Car* _car : _stock)
    {
        if (_car != NULL)
        {
            printf("%s %s\n", _car->getMake(), _car->getModel());
        }
    }
}

void buyCars()
{

}

void adminMenu()
{
    char _password[MAX_LEN];
    readString("!Authorised access only!\n\nEnter the administrator password to access this menu: ", _password, MAX_LEN);

    if (strcmp(_password, _adminPassword) == 0)
    {
        bool _quit = false;

        while (!_quit)
        {
            printf("Admin Menu:\n\n1.Add Stock\n2.Remove Stock\n3.View Sales History\n\n");
            
            int _selection = readIntInRange("Select an option from the menu",1,4);

            switch (_selection)
            {
            case 1:
                addStock();
                break;
            }
        }
    }
    else
    {
        printf("\n!Access Denied: Incorrect Password!\n");
    }
}

void addStock()
{
    char _make[MAX_LEN];
    char _model[MAX_LEN];
    readString("Enter car make: ", _make, MAX_LEN);
    readString("Enter car model: ", _model, MAX_LEN);
    double _price = readDouble("Enter price: ");
    int _stock = readInt(("Enter number of %s %ss to be added to stock:", _make, _model));

    Car _newCar;
    _newCar.setMake(_make);
    _newCar.setModel(_model);
    _newCar.setPrice(_price);
    _newCar.setStock(_stock);

    /////////////UPDATE TO ADD _newCar TO _stock!!!!!!!!!!!!!!!!//////////
}

void removeStock()
{

}

void viewSales()
{
    
}

void loadFiles()
{
   //READ DATA FROM CSV INTO _stock
   //READ DATA FROM CSV INTO _sales
}

void saveFiles()
{
    //WRITE DATA FROM _stock INTO CSV
    FILE* _fp; //File Pointer

    fopen_s(&_fp, "carStock.csv", "w"); //Open file for write
    //WRITE DATA FROM _sales INTO CSV
}