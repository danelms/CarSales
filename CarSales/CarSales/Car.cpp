/*
Function: Class used to instantiate/edit Car objects
Author: 2121058
Version: 1
Date: 12/12/21
*/

#include <iostream>
#include <cstring>

#define MAX_LEN 255
/// <summary>
/// Class to instantiate/edit Car objects.
/// </summary>
class Car
{
    double _price;
    char _make[MAX_LEN];
    char _model[MAX_LEN];
    int _stock, _menuPlace;

public:
    /// <param name="_newMake">Make of car to be set</param>
    void setMake(const char* _newMake)
    {
        strcpy_s(_make, _newMake);
    }
    /// <returns>Make of car</returns>
    char* getMake()
    {
        return _make;
    }
    /// <param name="_newModel">Model of car to be set</param>
    void setModel(const char* _newModel)
    {
        strcpy_s(_model, _newModel);
    }
    /// <returns>Model of car</returns>
    char* getModel()
    {
        return _model;
    }
    /// <param name="_stockSet">Number of car in stock to be set</param>
    void setStock(int _stockSet)
    {
        _stock = _stockSet;
    }
    /// <returns>Number of car in stock</returns>
    int getStock()
    {
        return _stock;
    }
    /// <param name="_priceSet">Price of car to be set</param>
    void setPrice(const double _priceSet)
    {
        _price = _priceSet;
    }
    /// <returns>Price of car</returns>
    double getPrice()
    {
        return _price;
    }
    /// <param name="_newMenuPlace">Menu place to be set</param>
    void setMenuPlace(int _newMenuPlace)
    {
        _menuPlace = _newMenuPlace;
    }
    /// <returns>Menu place for use in dynamic menus</returns>
    int getMenuPlace()
    {
        return _menuPlace;
    }

};