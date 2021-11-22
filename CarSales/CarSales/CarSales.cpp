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
void BubbleSortDescStock(Car* _cars[]);

#define MAX_LEN 255
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

Car* _stock[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
Sale* _sales[];

FILE* _fptr;

const char* _adminPassword = "hardPasswordToGuess123!#";
int i;

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
    ////TEST
    //_stock[0] = new Car;
    //_stock[0]->setMake("Volkswagen");
    //_stock[0]->setModel("Golf");
    //_stock[0]->setMenuPlace(1);
    //_stock[0]->setPrice(18999.99);
    //_stock[0]->setStock(5);
    ////ENDTEST

    BubbleSortDescStock(_stock);

    printf("\n");

    for (Car* _car : _stock)
    {
        if (_car != NULL)
        {
            printf("%d. %s %s\t\tIn Stock: %d\n",_car->getMenuPlace(), _car->getMake(), _car->getModel(), _car->getStock());
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
        int _count = 0;

        while (!feof(_fptr))
        {
            fgets(_buffer, MAX_LEN, _fptr);
            _start = _buffer;                                   //Point to start of _buffer
            _end = strchr(_buffer, ',');                        //Point to first comma in _buffer (end of car make)
            printf("%d", int(_end - _start));
            strncpy_s(_tempMake, _start, int(_end - _start));     //_tempMake is assigned the string comprised of everything up until _end (first comma)
            _start = _end + 1;
            _end += 1;
            while (*_end != ',')                              //Iterate until next comma
            {
                _end++;
            }
            printf("%d", int(_end - _start));
            strncpy_s(_tempModel, _start, int(_end - _start));    //tempModel is assigned the string comprised of everything from _start to _end (1st letter of model to next comma)
            _start = _end + 1;
            sscanf_s(_start, "%lf,%d\n", &_tempPrice, &_tempStock); //Remaining two values assigned to _tempPrice & _tempStock

            _stock[i] = new Car;
            _stock[i]->setMake(_tempMake);
            _stock[i]->setModel(_tempModel);
            _stock[i]->setPrice(_tempPrice);
            _stock[i]->setStock(_tempStock);

            _count++;
        }

        fclose(_fptr);
    }

   

   //READ DATA FROM CSV INTO _sales
}

void saveFiles()
{
    //WRITE DATA FROM _stock INTO CSV
    _fptr = fopen("stock.csv", "w"); //Open "stock.csv" in write (Create new file)

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
                fprintf(_fptr, "%s,%s,%.2lf,%d\n", _car->getMake(), _car->getModel(), _car->getPrice(), _car->getStock());
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
            
        }
    }

    for (i = 0; i < 10; i++)
    {
        if (_cars[i] != NULL)
        {
            _cars[i]->setMenuPlace(i);
        }
    }

}
