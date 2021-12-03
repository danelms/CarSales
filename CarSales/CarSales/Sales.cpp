#include <iostream>
#define MAX_LEN 255

struct Date //Struct used to store the date of a sale / offer
{
	int _day;
	int _month;
	int _year;
};

struct Sale //Struct to store details of a sale (What car sold, for how much, when, and to whom)
{
	char _nameOfCust[MAX_LEN]; //Customer Name	
	int _ageOfCust; //Customer Age
	char _emailAddOfCust[MAX_LEN]; //Customer Email Address

	char* _make; 
	char* _model;
	int _amount;
	double _price;
	double _offer;
	Date _dateOfSale;

	bool _final; //Bool to differentiate between pending and finalised sales
};