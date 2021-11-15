#include <iostream>
#include <cstring>

#define MAX_LEN 255

class Car
{
    double _price;
    char _make[MAX_LEN];
    char _model[MAX_LEN];
    int _stock, _menuPlace;

public:
    void setMake(const char* _newMake)
    {
        strcpy_s(_make, _newMake);
    }
    char* getName()
    {
        return _make;
    }
    void setModel(const char* _newModel)
    {
        strcpy_s(_model, _newModel);
    }
    char* getModel()
    {
        return _model;
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