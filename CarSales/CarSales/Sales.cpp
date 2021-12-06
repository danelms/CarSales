/*
Function: 
Author: 2121058
Version: 1
Date:
*/

#include <iostream>
#define MAX_LEN 255

/// <summary>
/// Struct used to store the date (day, month, year)
/// </summary>
struct Date
{
	int _day;
	int _month;
	int _year;
};

/// <summary>
/// Struct used to store details of a sale (What car sold, for how much, when, and to whom)
/// </summary>
struct Sale 
{
	char _nameOfCust[MAX_LEN]; 	
	int _ageOfCust; 
	char _emailAddOfCust[MAX_LEN]; 

	char* _make; 
	char* _model;
	int _amount;
	double _price;
	double _offer;
	Date _dateOfSale;

	bool _final; 
};