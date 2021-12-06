/*
Function: Set of functions used to get user input from the keyboard
Author: 2121058
Version: 1
Date: 
*/


#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ReadLine.h"

const int MAX_LINE = 255;

/// <summary>
/// Used to get an integer value from keyboard input
/// </summary>
/// <param name="_prompt">Prompt message e.g "enter an integer: "</param>
/// <returns></returns>
int readInt(const char* _prompt)
{
	char _input[MAX_LINE]; //Char array of size 255
	int _num;
	int _errorCode; //Used to indicate error using sscanf
	char* _result;  //Used to indicate whether anything has been entered
	bool _success = false;

	while (!_success)
	{
		printf(_prompt);
		if ((_result = gets_s(_input, MAX_LINE)) != NULL)
		{
			if ((_errorCode = sscanf_s(_input, "%d", &_num)) != 1)
			{
				printf("\nPlease enter a valid integer\n");
			}
			else
			{
				_success = true;
			}
		}
	}

	return _num;
}

float readFloat(const char* _prompt)
{
	char _input[MAX_LINE]; //Char array of size 255
	float _num;
	int _errorCode; //Used to indicate error using sscanf
	char* _result;  //Used to indicate whether anything has been entered
	bool _success = false;


	while (!_success)
	{
		printf(_prompt);
		if ((_result = gets_s(_input, MAX_LINE)) != NULL)
		{
			if ((_errorCode = sscanf_s(_input, "%f", &_num)) != 1)
			{
				printf("\nPlease enter a valid float\n");
			}
			else
			{
				_success = true;
			}
		}
	}

	return _num;
}

double readDouble(const char* _prompt)
{
	char _input[MAX_LINE]; //Char array of size 255
	double _num;
	int _errorCode; //Used to indicate error using sscanf
	char* _result;  //Used to indicate whether anything has been entered
	bool _success = false;


	while (!_success)
	{
		printf(_prompt);
		if ((_result = gets_s(_input, MAX_LINE)) != NULL)
		{
			if ((_errorCode = sscanf_s(_input, "%lf", &_num)) != 1)
			{
				printf("\nPlease enter a valid double\n");
			}
			else
			{
				_success = true;
			}
		}
	}

	return _num;
}

long readLongInt(const char* _prompt)
{
	char _input[MAX_LINE]; //Char array of size 255
	long _num;
	int _errorCode; //Used to indicate error using sscanf
	char* _result;  //Used to indicate whether anything has been entered
	bool _success = false;


	while (!_success)
	{
		printf(_prompt);
		if ((_result = gets_s(_input, MAX_LINE)) != NULL)
		{
			if ((_errorCode = sscanf_s(_input, "%li", &_num)) != 1)
			{
				printf("\nPlease enter a valid (long) integer\n");
			}
			else
			{
				_success = true;
			}
		}
	}

	return _num;
}

/// <summary>
/// Takes arguments for a prompt, a lower and a higher input limit, returns
/// input if in range
/// </summary>
/// <param name="_prompt">Prompt to display when method called</param>
/// <param name="_low">Int to specify lower limit</param>
/// <param name="_high">Int to specify upper limit</param>
/// <returns>Integer</returns>
int readIntInRange(const char* _prompt, int _low, int _high)
{
	int _num = 1;

	do
	{
		_num = readInt(_prompt);

		if (_num < _low || _num > _high)
		{
			printf("\nERROR: Enter a number between %d and %d\n", _low, _high);
		}

	} while ((_num < _low) || (_num > _high));

	return _num;
}

/// <summary>
/// 
/// </summary>
/// <param name="_prompt">Message to display</param>
/// <param name="_destination">Variable to store returned string</param>
/// <param name="_maxLen">Specifies maximum length of returned string (actual input max is _maxLen - 1 due to inclusion of '\0')</param>
void readString(const char* _prompt, char* _destination, int _maxLen)
{
	char _input[MAX_LINE];

	bool _success = false;

	while (!_success)
	{
		printf(_prompt);
		gets_s(_input, MAX_LINE);

		if ((strlen(_input)) >= _maxLen)
		{
			printf("\nInput exceeds maximum length (%d characters)\n\n", (_maxLen - 1));
		}
		else
		{
			strcpy_s(_destination, _maxLen, _input);
			_success = true;
		}
	}
}

char readChar(const char* _prompt)
{
	char _input[MAX_LINE];
	char _returnValue;
	bool _success = false;

	while (!_success)
	{
		printf(_prompt);
		gets_s(_input, MAX_LINE);

		if (strlen(_input) != 1)
		{
			printf("\nPlease enter a single character\n");
		}
		else
		{
			_returnValue = _input[0];
			_success = true;
		}
	}
	return _returnValue;
}