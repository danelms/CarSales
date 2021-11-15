#include <iostream>
#include <cstring>

class Car
{
    double _price;
    char _name[50];
    int _stock, _menuPlace;

public:
    void setName(const char* _newName)
    {
        strcpy_s(_name, _newName);
    }
    char* getName()
    {
        return _name;
    }
    void setStock(int _stockSet)
    {
        _stock = _stockSet;
    }
    int getStock()
    {
        return _stock;
    }
    void setPrice(const double _priceSet)
    {
        _price = _priceSet;
    }
    double getPrice()
    {
        return _price;
    }
    void setMenuPlace(int _newMenuPlace)
    {
        _menuPlace = _newMenuPlace;
    }
    int getMenuPlace()
    {
        return _menuPlace;
    }

};