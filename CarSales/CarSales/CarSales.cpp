#include <iostream>
#include <cstring>
#include <Windows.h>
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
void addSale(char* _custName, int _custAge, char* _custEmail, char* _newMake, char* _newModel, int _newAmount, double _newPrice, double _newOffer, bool _newFinal);
void loadFiles();
void saveFiles();
void BubbleSortDescStock(Car* _cars[]);
Date getDate();

#define MAX_LEN 255

SYSTEMTIME _sysDate;

Car* _stock[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
Sale* _sales[];

FILE* _fptr;

const char* _adminPassword = "hardPasswordToGuess123!#";
int i, _carIndex = 0, _salesIndex = 0;

int main()
{
    loadFiles();
    mainMenu();
    saveFiles();
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
            buyCars();
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
    BubbleSortDescStock(_stock);

    printf("\n");
    bool _inStock = false;

    for (Car* _car : _stock)
    {
        if (_car != NULL)
        {
            _inStock = true;
            printf("%d. %s %s. In Stock: %d\n",_car->getMenuPlace(), _car->getMake(), _car->getModel(), _car->getStock());
        }
    }

    if (!_inStock)
    {
        printf("No cars currently in stock.\n");
    }
}

void buyCars()
{
    viewCars();
    printf("%d. Return to Main Menu\n\n", _carIndex + 1);

    int _selection = readIntInRange("Select the car you would like to purchase: ",1,_carIndex + 1);
    bool _quit = false, _currentSet = false;
    Car* _currentSelection = NULL;

    while (!_quit)
    {
        if (_selection == _carIndex + 1)
        {
            _quit = true;
        }
        else
        {
            for (Car* _car : _stock)
            {
                if (NULL != _car &&_selection == _car->getMenuPlace())
                {
                    _currentSelection = _car;
                    _currentSet = true;
                }
            }

            if (!_currentSet)
            {
                printf("\n!Unforseen Error, returning to main menu!\n");
                _quit = true;
            }

            int _amount = readInt("\nHow many would you like to purchase?: ");
            double _offer;

            if (_amount > _currentSelection->getStock())
            {
                printf("\nERROR: Not that many currently in stock.\n");
            }
            else if (_amount < 1)
            {
                printf("\nERROR: You cannot purchase less than 1 car.\n");
            }
            else
            {
                _currentSelection->setStock(_currentSelection->getStock() - _amount); //Remove amount desired from current stock
                printf("\nAsking price: %.2lf\n", _currentSelection->getPrice());
                _offer = readDouble("\nEnter the full asking price to complete purchase now, or make an offer\nYour offer (per car): ");
                char* _name{};
                char* _email{};
                int _age;

                if (_offer > _currentSelection->getPrice())
                {
                    printf("\nError: Sorry, we cannot accept offers over the asking price\nPlease enter the full asking price or make an offer\n");
                }
                else if (_offer < _currentSelection->getPrice())
                {
                    printf("\nPlease provide some details so we can get in touch and improve analytics\nPlease ensure these details are correct\n");
                    readString("Your name: ", _name, MAX_LEN);
                    readString("Your email address: ", _email, MAX_LEN);
                    _age = readIntInRange("Your age: ", 1, 130);

                    addSale(_name, _age, _email, _currentSelection->getMake(), _currentSelection->getModel(), _amount, _currentSelection->getPrice(), _offer, false);
                    printf("\nThank you!\nYour offer has been recorded and is pending confirmation\nWe will contact you by email shortly\n");
                }
                else if (_offer == _currentSelection->getPrice())
                {
                    printf("\nPlease provide some details so we can get in touch and improve analytics\nPlease ensure these details are correct\n");
                    readString("Your name: ", _name, MAX_LEN);
                    readString("Your email address: ", _email, MAX_LEN);
                    _age = readIntInRange("Your age: ", 1, 130);

                    addSale(_name, _age, _email, _currentSelection->getMake(), _currentSelection->getModel(), _amount, _currentSelection->getPrice(), _offer, true);
                    printf("\nThank you! Your offer has been accepted\nWe will contact you by email shortly\n");
                }

                _quit = true;
            }
        }
        
    }
    
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
            printf("Admin Menu:\n\n1.Add Stock\n2.Remove Stock\n3.View Sales History\n4.Main Menu\n\n");
            
            int _selection = readIntInRange("Select an option from the menu: ",1,4);

            if (_selection == 1)
            {
                addStock();   
            }
            else if (_selection == 4)
            {
                _quit = true;
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
    int _inStock = readInt("Enter number to add to stock: ");

    Car* _newCar = new Car();
    _newCar->setMake(_make);
    _newCar->setModel(_model);
    _newCar->setPrice(_price);
    _newCar->setStock(_inStock);

    _stock[_carIndex] = _newCar;

    _carIndex++;
}

void removeStock()
{

}

void viewSales()
{
    
}

void addSale(char* _custName, int _custAge, char* _custEmail, char* _newMake, char* _newModel, int _newAmount, double _newPrice, double _newOffer, bool _newFinal) //Creates and adds a sale to _sales array
{
   //OG ATTEMPT
    
   //Sale* _sale = new Sale;

   /* _sale->_nameOfCust = _custName;
    _sale->_ageOfCust = _custAge;
    _sale->_emailAddOfCust = _custEmail;

    _sale->_make = _newMake;
    _sale->_model = _newModel;
    _sale->_price = _newPrice;
    _sale->_offer = _newOffer;
    _sale->_final = _newFinal;
    
    _sale->_dateOfSale = getDate();
    
    _sales[_salesIndex] = _sale;*/


    //NEW ATTEMPT

    _sales[_salesIndex]->_nameOfCust = _custName;
    /*_sales[_salesIndex]->_ageOfCust = _custAge;
    _sales[_salesIndex]->_emailAddOfCust = _custEmail;
    _sales[_salesIndex]->_make = _newMake;
    _sales[_salesIndex]->_model = _newModel;
    _sales[_salesIndex]->_amount = _newAmount;
    _sales[_salesIndex]->_price = _newPrice;
    _sales[_salesIndex]->_offer = _newOffer;
    _sales[_salesIndex]->_final = _newFinal;

    _sales[_salesIndex]->_dateOfSale = getDate();

    _salesIndex++;*/
}

void loadFiles()
{
   //READ DATA FROM CSV INTO _stock
    char _buffer[MAX_LEN];
    char _tempMake[MAX_LEN];
    char _tempModel[MAX_LEN];
    double _tempPrice;
    int _tempStock;

    fopen_s(&_fptr, "stock.csv", "r");

    if (NULL == _fptr)
    {
        printf("\nAttention! No current file containing stock information found, one will be created upon exit of program.\n");
    }
    else
    {
        char* _start;
        char* _end;
        i = 0;

        while (!feof(_fptr))
        {
            fgets(_buffer, MAX_LEN, _fptr);
            
            if (_buffer[0] == '#')      //if line starts with a '#' (has been written to)
            {
                printf("\nBUFFER: %s\n", _buffer);//TROUBLESHOOTER - REMEMBER TO REMOVE !!!!!!!!
                _start = _buffer + 1;                                   //Point to start of _buffer
                _end = strchr(_buffer, ',');                        //Point to first comma in _buffer (end of car make)
                strncpy_s(_tempMake, _start, int(_end - _start));     //_tempMake is assigned the string comprised of everything up until _end (first comma)
                _start = _end + 1;
                _end += 1;
                while (*_end != ',')                              //Iterate until next comma
                {
                    _end++;
                }
                strncpy_s(_tempModel, _start, int(_end - _start));    //tempModel is assigned the string comprised of everything from _start to _end (1st letter of model to next comma)
                _start = _end + 1;
                sscanf_s(_start, "%lf,%d\n", &_tempPrice, &_tempStock); //Remaining two values assigned to _tempPrice & _tempStock

                _stock[i] = new Car;                    //Create new car object using data from CSV
                _stock[i]->setMake(_tempMake);
                _stock[i]->setModel(_tempModel);
                _stock[i]->setPrice(_tempPrice);
                _stock[i]->setStock(_tempStock);

                i++;
                _carIndex++;
            }
            
        }

    }

    fclose(_fptr);

   //READ DATA FROM CSV INTO _sales
}

void saveFiles()
{
    //WRITE DATA FROM _stock INTO CSV
    _fptr = fopen("stock.csv", "w"); //Open "stock.csv" in write (Create new file / overwrite file)

    if (_fptr == NULL)
    {
        printf("Error creating new file \"stock.csv\"");
    }
    else
    {
        for (Car* _car : _stock)
        {
            if (_car != NULL)
            {
                fprintf(_fptr, "#%s,%s,%.2lf,%d\n", _car->getMake(), _car->getModel(), _car->getPrice(), _car->getStock());
            }
        }

        fclose(_fptr);
    }
    
    //WRITE DATA FROM _sales INTO CSV
}

void BubbleSortDescStock(Car* _cars[])
{
    bool _swapped = true;
    Car* _carTemp;

    while (_swapped)
    {
        _swapped = false;

        for (i = 0; i < 10; i++)
        {
            if ((_cars[i] != NULL) && (_cars[i + 1] != NULL))
            {
                if (_cars[i]->getStock() < _cars[i + 1]->getStock())
                {
                    _carTemp = _cars[i];
                    _cars[i] = _cars[i + 1];
                    _cars[i + 1] = _carTemp;

                    _swapped = true;
                }
            }
            
            if (_cars[i] != NULL)
            {
                _cars[i]->setMenuPlace(i + 1);
            }
        }
    }
}

Date getDate() //Creates and returns a Date struct containing today's date
{
    Date* _date = new Date;
    _date->_day = _sysDate.wDay;
    _date->_month = _sysDate.wMonth;
    _date->_year = _sysDate.wYear;

    return *_date;
}