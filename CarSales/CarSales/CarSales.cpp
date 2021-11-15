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

#define MAX_LEN 255

Car *_stock[];
Sale* _sales[];

const char* _adminPassword = "hardPasswordToGuess123!#";

int main()
{
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
            printf("\nSelection 1\n");
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
        printf("Admin Menu:\n\n1.Add Stock\n2.Remove Stock\n3.View Sales History\n\n");
    }
    else
    {
        printf("\n!Access Denied: Incorrect Password!\n");
    }
}

void addStock()
{

}

void removeStock()
{

}

void viewSales()
{

}