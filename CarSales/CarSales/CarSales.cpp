#include <iostream>
#include <cstring>
#include "ReadLine.h"
#include "Car.cpp"
void mainMenu();
void viewCars();
void buyCars();
void adminMenu();
void addStock();
void removeStock();
void viewSales();

Car *_stock[];

int main()
{
    mainMenu();
}

void mainMenu()
{
    bool _quit = false;

    while (!_quit)
    {
        printf("Main Menu:\n\n1. View Cars in Stock\n2.Purchase a Car\n3.Admin Menu\n4. Quit\n");

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
            printf("\nSelection 3\n");
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

}

void addStock()
{

}

void removeStock()
{

}