#include <iostream>

struct Date //Struct used to store the date of a sale
{
	int _day;
	int _month;
	int _year;
};

struct Sale //Struct to store details of a sale (What car sold, for how much and when)
{
	char* _make;
	char* _model;
	float _price;
	float _salePrice;
	Date _dateOfSale;
};