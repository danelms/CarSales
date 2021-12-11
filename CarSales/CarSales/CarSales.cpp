/*
Function: Program to allow purchase/sale of cars
Author: 2121058
Version: 1
Date:
*/

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
void viewAllSales();
void viewFinalSales();
void clearSales();
void addSale(char* _custName, int _custAge, char* _custEmail, char* _newMake, char* _newModel, int _newAmount, double _newPrice, double _newOffer, bool _newFinal);
void loadFiles();
void saveFiles();
void bubbleSortDescStock(Car* _cars[]);
void bubbleSortDescFinalSale(int _amount[], double _total[], char* _models[]);
Date getDate();

#define MAX_LEN 255
#define MAX_SALES 200

SYSTEMTIME _sysDate;

Car* _stock[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
Sale* _sales[MAX_SALES];

FILE* _fptr;

const char* _adminPassword = "hardPasswordToGuess123!#";
int i, _carIndex = 0, _salesIndex = 0;

int main()
{
    GetLocalTime(&_sysDate);
    loadFiles();
    mainMenu();
    saveFiles();
}

/// <summary>
/// Looping main menu, used to access all features of the program
/// </summary>
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

/// <summary>
/// Calls function to sort car by stock (desc. order) and then displays the results
/// </summary>
void viewCars()
{
    bubbleSortDescStock(_stock);

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

/// <summary>
/// Displays cars in stock, enables user to select a model to purchase, subsequently creates a sales struct to record the details
/// </summary>
void buyCars()
{
    if (_salesIndex < MAX_SALES)
    {
        viewCars();
        printf("%d. Return to Main Menu\n\n", _carIndex + 1);

        int _selection = readIntInRange("Select the car you would like to purchase: ", 1, _carIndex + 1);
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
                    if (NULL != _car && _selection == _car->getMenuPlace())
                    {
                        _currentSelection = _car;
                        _currentSet = true;
                    }
                }

                if (!_currentSet)
                {
                    printf("\n!Unforeseen Error, returning to main menu!\n");
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
                    _currentSelection->setStock(_currentSelection->getStock() - _amount);
                    printf("\nAsking price: %.2lf\n", _currentSelection->getPrice());
                    _offer = readDouble("\nEnter the full asking price to complete purchase now, or make an offer\nYour offer (per car): ");
                    char _name[MAX_LEN];
                    char _email[MAX_LEN];
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
    else
    {
        printf("\nSorry, the sales history is full. Purchasing will be available again soon.\n");
    }
    
}

/// <summary>
/// If the correct password is entered, displays the administrator's menu with specific functions, otherwise prints error and returns to main menu
/// </summary>
void adminMenu()
{
    char _password[MAX_LEN];
    readString("\n!Authorised access only!\n\nEnter the administrator password to access this menu: ", _password, MAX_LEN);

    if (strcmp(_password, _adminPassword) == 0)
    {
        bool _quit = false;

        while (!_quit)
        {
            printf("\nAdmin Menu:\n\n1. Add Stock\n2. Remove Stock\n3. View Sales History (All Sales)\n4. View Finalised Sales History by Model\n5. Delete Sales History\n6. Main Menu\n\n");
            
            int _selection = readIntInRange("Select an option from the menu: ",1,6);

            if (_selection == 1)
            {
                addStock();   
            }
            else if (_selection == 2)
            {
                removeStock();
            }
            else if (_selection == 3)
            {
                viewAllSales();
            }
            else if (_selection == 4)
            {
                viewFinalSales();
            }
            else if (_selection == 5)
            {
                clearSales();
            }
            else if (_selection == 6)
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

/// <summary>
/// Used to add more stock, up to maximum of 10 models
/// </summary>
void addStock()
{
    if (_carIndex < 10)
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
    else
    {
        printf("\nError: Too many different car models currently in stock.\n");
    }
}

/// <summary>
/// Used to manually remove stock, if all stock is depleted, the array index it occupied becomes NULL
/// </summary>
void removeStock()
{
    viewCars();

    Car* _currentSelection = NULL;
    int _selection = readIntInRange("\nWhich model's stock would you like to adjust?: ", 1, _carIndex + 1);

    for (Car* _car : _stock)
    {
        if (NULL != _car && _selection == _car->getMenuPlace())
        {
            _currentSelection = _car;
        }
    }

    if (NULL != _currentSelection)
    {
        if (_currentSelection->getStock() > 0)
        {
            int _removeAmnt = readIntInRange("How many would you like to remove from stock?: ", 1, _currentSelection->getStock());

            _currentSelection->setStock(_currentSelection->getStock() - _removeAmnt);
            printf("\n%d x \"%s %s\" removed from stock\n", _removeAmnt, _currentSelection->getMake(), _currentSelection->getModel());
        }
        else
        {
            printf("\n%s %s removed from stock list.\n", _currentSelection->getMake(), _currentSelection->getModel());
        }
    }

    if (_currentSelection->getStock() == 0)
    {
        _stock[_currentSelection->getMenuPlace() - 1] = NULL;
        _carIndex --;
    }

}

/// <summary>
/// Displays details for every single sale
/// </summary>
void viewAllSales()
{
    
    printf("\n\nSales History:\n\n");
    bool _salePresent = false;

    for (Sale* _sale : _sales)
    {
        if (_sale != NULL)
        {
            _salePresent = true;
            i = 1;

            printf("Date: %d/%d/%d", _sale->_dateOfSale._day, _sale->_dateOfSale._month, _sale->_dateOfSale._year);
            printf("\nCustomer Name: %s\nCustomer email: %s\nCustomer Age: %d", _sale->_nameOfCust, _sale->_emailAddOfCust, _sale->_ageOfCust);
            printf("\nCar Make & Model: %s %s\nQuantity Requested: %d\nAsking Price: %.2lf GBP\nCustomer's Offer: %.2lf GBP", _sale->_make, _sale->_model, _sale->_amount, _sale->_price, _sale->_offer);
            printf("\nOffer finalised: ");
            if (_sale->_final)
            {
                printf("Yes\n\n");
            }
            else
            {
                printf("No\n\n");
            }
        }
    }

    if (!_salePresent)
    {
        printf("There are no sales history records to display.\n\n");
    }
}

/// <summary>
/// Displays summary of finalised sales per model, in descending order of value
/// </summary>
void viewFinalSales()
{
    int _amount[MAX_SALES] = {0};
    int _pos = 0;
    double _total[MAX_SALES] = {0.0};
    char* _models[MAX_SALES] = {NULL};
    i = 0;
    bool _inList = false;

    for (Sale* _sale : _sales)
    {
        if (_sale != NULL)
        {

            for (char* _m : _models)
            {
                _inList = false;

                if (_m != NULL)
                {
                    if ((strcmp(_m, _sale->_model)) == 0 && _sale->_final)
                    {
                        _inList = true;
                        _pos = i;
                        break;
                    }
                }
                else if (_m == NULL && _sale->_final)
                {
                    _pos = i;
                    break;
                }
                else
                {
                    break;
                }

                i++;
            }

            i = 0;

            if (_inList)
            {
                _amount[_pos] += _sale->_amount;
                _total[_pos] += _sale->_offer * _sale->_amount;
            }
            else if (_sale->_final)
            {
                char* _newModel = new char[MAX_LEN];
                strcpy(_newModel, _sale->_model);
                _models[_pos] = _newModel;
                _amount[_pos] = _sale->_amount;
                _total[_pos] = _sale->_offer * _sale->_amount;
            }
        }
        else
        {
            break;
        }
    }

    bool _salePresent = false;

    bubbleSortDescFinalSale(_amount, _total, _models);

    for (i = 0; i < MAX_SALES; i++)
    {
        if (_amount[i] != 0)
        {
            _salePresent = true;
            printf("\n%d. %s sales: %d, for a total of %.2lf GBP\n", i + 1, _models[i], _amount[i], _total[i]);
        }
        else
        {
            break;
        }
    }

    if (!_salePresent)
    {
        printf("\nNo finalised sales to display\n");
    }
}

/// <summary>
/// Sets all Sales in _sales to NULL (effectively 'deleting' them)
/// </summary>
void clearSales()
{
    bool _abort;
    printf("\nWarning, once cleared the sales data cannot be recovered.\nPlease ensure that all sales have been recorded elsewhere before proceeding.\n\n");

    char _selection = readChar("Would you like to view sales before deletion? (Y/N, or any other input to abort): ");
    {
        if (_selection == 'y' || _selection == 'Y')
        {
            viewAllSales();
            _abort = false;
        }
        else if (_selection == 'n' || _selection == 'N')
        {
            _abort = false;
        }
        else 
        {
            printf("\nInput \"%c\" unrecognised, deletion aborted.\n", _selection);
            _abort = true;
        }

        if (!_abort)
        {
            i = 0;

            for (Sale* _sale : _sales)
            {
                if (_sale != NULL)
                {
                    _sales[i] = NULL;
                }
                else
                {
                    break;
                }

                i++;
            }

            _salesIndex = 0;
            printf("\nSales records deleted\n");
        }

    }
}

/// <summary>
/// Creates sales struct, adds it to _sales
/// </summary>
/// <param name="_custName">Name of customer</param>
/// <param name="_custAge">Age of customer</param>
/// <param name="_custEmail">Email address of customer</param>
/// <param name="_newMake">Car make</param>
/// <param name="_newModel">Car model</param>
/// <param name="_newAmount">Quantity of car requested</param>
/// <param name="_newPrice">Asking price</param>
/// <param name="_newOffer">Customer's offer</param>
/// <param name="_newFinal">Bool that represent whether or not the offer has been accepted</param>
void addSale(char* _custName, int _custAge, char* _custEmail, char* _newMake, char* _newModel, int _newAmount, double _newPrice, double _newOffer, bool _newFinal) //Creates and adds a sale record to _sales array
{   
   Sale* _sale = new Sale;

    strcpy_s(_sale->_nameOfCust, _custName);
    _sale->_ageOfCust = _custAge;
    strcpy_s(_sale->_emailAddOfCust, _custEmail);
    strcpy_s(_sale->_make, _newMake);
    strcpy_s(_sale->_model, _newModel);
    _sale->_amount = _newAmount;
    _sale->_price = _newPrice;
    _sale->_offer = _newOffer;
    _sale->_final = _newFinal;
    _sale->_dateOfSale = getDate();
    
    _sales[_salesIndex] = _sale;
    _salesIndex++;

}

/// <summary>
/// Uses CSV files (if present) to add previously saved data to _stock and _sales arrays
/// </summary>
void loadFiles()
{
   
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
            
            if (_buffer[0] == '#')      
            {
                _start = _buffer + 1;                                  
                _end = strchr(_buffer, ',');                        
                strncpy_s(_tempMake, _start, int(_end - _start));     
                _start = _end + 1;
                _end += 1;
                while (*_end != ',')                              
                {
                    _end++;
                }
                strncpy_s(_tempModel, _start, int(_end - _start));    
                _start = _end + 1;
                sscanf_s(_start, "%lf,%d\n", &_tempPrice, &_tempStock); 

                _stock[_carIndex] = new Car;                   
                _stock[_carIndex]->setMake(_tempMake);
                _stock[_carIndex]->setModel(_tempModel);
                _stock[_carIndex]->setPrice(_tempPrice);
                _stock[_carIndex]->setStock(_tempStock);

                _carIndex++;
            }
            
        }

        fclose(_fptr);
    }

    fopen_s(&_fptr, "sales.csv", "r");

    if (NULL == _fptr)
    {
        printf("\nAttention! No current file containing sales information found, one will be created upon exit of program.\n");
    }
    else
    {
        char* _start;
        char* _end;
        i = 0;
        int _tempBool;

        while (!feof(_fptr))
        {
            fgets(_buffer, MAX_LEN, _fptr);

            if (_buffer[0] == '#')
            {
                Sale* _sale = new Sale;

                _start = _buffer + 1;                                   
                _end = strchr(_buffer, ',');                        
                strncpy_s(_sale->_nameOfCust, _start, int(_end - _start));     
                _start = _end + 1;
                _end += 1;
                while (*_end != ',')                              
                {
                    _end++;
                }
                strncpy_s(_sale->_emailAddOfCust, _start, int(_end - _start));
                _start = _end + 1;
                _end += 1;
                while (*_end != ',')
                {
                    _end++;
                }
                strncpy_s(_sale->_make, _start, int(_end - _start));
                _start = _end + 1;
                _end += 1;
                while (*_end != ',')
                {
                    _end++;
                }
                strncpy_s(_sale->_model, _start, int(_end - _start));
                _start = _end + 1;
                sscanf_s(_start, "%d,%d,%lf,%lf,%d,%d,%d,%d\n", &_sale->_ageOfCust, &_sale->_amount, &_sale->_price, &_sale->_offer, &_sale->_dateOfSale._day, &_sale->_dateOfSale._month, &_sale->_dateOfSale._year, &_tempBool);

                if (_tempBool == 0)
                {
                    _sale->_final = false;
                }
                else
                {
                    _sale->_final = true;
                }

                _sales[_salesIndex] = _sale;
                _salesIndex++;
            }
        }

        fclose(_fptr);
    }
}

/// <summary>
/// Writes data from _stock and _sales arrays to CSV file
/// </summary>
void saveFiles()
{
    _fptr = fopen("stock.csv", "w");

    if (NULL == _fptr)
    {
        printf("\nError creating new file \"stock.csv\"\n");
    }
    else
    {
        for (Car* _car : _stock)
        {
            if (_car != NULL)
            {
                fprintf(_fptr, "\n#%s,%s,%.2lf,%d", _car->getMake(), _car->getModel(), _car->getPrice(), _car->getStock());
            }
        }

        fclose(_fptr);
    }
    
    _fptr = fopen("sales.csv", "w");

    if (NULL == _fptr)
    {
        printf("\nError creating new file \"sales.csv\"\n");
    }
    else
    {
        int _boolValue;

        for (Sale* _sale : _sales)
        {  
            if (_sale != NULL)
            {
                if (_sale->_final)
                {
                    _boolValue = 1;
                }
                else
                {
                    _boolValue = 0;
                }

                fprintf(_fptr, "\n#%s,%s,%s,%s,%d,%d,%lf,%lf,%d,%d,%d,%d", _sale->_nameOfCust, _sale->_emailAddOfCust, _sale->_make, _sale->_model, _sale->_ageOfCust, _sale->_amount, _sale->_price, _sale->_offer, _sale->_dateOfSale._day, _sale->_dateOfSale._month, _sale->_dateOfSale._year, _boolValue);
            }
        }

        fclose(_fptr);
    }
}

/// <summary>
/// Sorts an array of car painters by remaining stock (descending)
/// </summary>
/// <param name="_cars">Car pointer array to be sorted</param>
void bubbleSortDescStock(Car* _cars[])
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

/// <summary>
/// Used within viewFinalSales() to sort multiple arrays concerning sales data before display
/// </summary>
/// <param name="_amount">Array containing sales quantities</param>
/// <param name="_total">Array containing sales totals (money)</param>
/// <param name="_models">Array containing pointers to model names</param>
void bubbleSortDescFinalSale(int _amount[], double _total[], char* _models[])
{
    bool _swapped = true;
    int _amountTemp;
    double _totalTemp;
    char* _modelTemp;

    while (_swapped)
    {
        _swapped = false;

        for (i = 0; i < MAX_SALES; i++)
        {
            if (_amount[i] != 0 && _amount[i + 1] != 0)
            {
                if (_total[i] < _total[i + 1])
                {
                    _amountTemp = _amount[i];
                    _amount[i] = _amount[i + 1];
                    _amount[i + 1] = _amountTemp;

                    _totalTemp = _total[i];
                    _total[i] = _total[i + 1];
                    _total[i + 1] = _totalTemp;

                    _modelTemp = _models[i];
                    _models[i] = _models[i + 1];
                    _models[i + 1] = _modelTemp;

                    _swapped = true;
                }
            }
            else
            {
                break;
            }
        }
    }
}

/// <returns>Today's date as Date struct</returns>
Date getDate()
{
    Date* _date = new Date;
    _date->_day = _sysDate.wDay;
    _date->_month = _sysDate.wMonth;
    _date->_year = _sysDate.wYear;

    return *_date;
}