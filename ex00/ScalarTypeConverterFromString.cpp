#include <iostream>
#include <locale>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
#include <limits>
#include <string>
#include "ScalarTypeConverterFromString.hpp"


ScalarTypeConverterFromString::ScalarTypeConverterFromString(void)
{}

ScalarTypeConverterFromString::ScalarTypeConverterFromString(std::string input) : _input(input)
{
	this->_doublePrecisionNumber = atof(input.c_str());
    this->convertInput();
}

ScalarTypeConverterFromString::ScalarTypeConverterFromString(const ScalarTypeConverterFromString &other)
{
    *this = other;
}


ScalarTypeConverterFromString::~ScalarTypeConverterFromString(void)
{}


ScalarTypeConverterFromString   &ScalarTypeConverterFromString::operator=(const ScalarTypeConverterFromString &src)
{
    if (this != &src)
    {
        this->_input = src.getInput();
        this->_inputTypeFlag = src.getInputTypeFlag();
        this->_character = src.getChar();
        this->_integer = src.getInt();
        this->_floatingPointNumber = src.getFloat();
        this->_doublePrecisionNumber = src.getDouble();
    }
    return (*this);
}

std::string ScalarTypeConverterFromString::getInput(void) const
{
    return (this->_input);
}

int     ScalarTypeConverterFromString::getInputTypeFlag(void) const
{
    return (this->_inputTypeFlag);
}

char    ScalarTypeConverterFromString::getChar(void) const
{
    return (this->_character);
}

int     ScalarTypeConverterFromString::getInt(void) const
{
    return (this->_integer);
}

float   ScalarTypeConverterFromString::getFloat(void) const
{
    return (this->_floatingPointNumber);
}

double  ScalarTypeConverterFromString::getDouble(void) const
{
    return (this->_doublePrecisionNumber);
}


int     ScalarTypeConverterFromString::checkInput(void)
{
    // does not check, if the char appeares more than once. Thus, only ok since the user input for this project has to be correctly formatted.
    if (this->_input == "nan" || this->_input == "+inf" || this->_input == "-inf"
		|| this->_input == "nanf" || this->_input == "+inff" || this->_input == "-inff")
        return (NAN_INF);
	else if (this->_input.length() == 1 && (this->_input[0] == 'f' || this->_input[0] == '-' || this->_input[0] == '+' || this->_input[0] == '.'))
		return (CHAR);
    else if (this->_input.find_first_not_of("0123456789-+") == std::string::npos)
        return (INT);
    else if (this->_input.find_first_not_of("0123456789-+.") == std::string::npos)
        return (DOUBLE);
    else if (this->_input.find_first_not_of("0123456789-+.f") == std::string::npos)
	{
		if (*(this->_input.rbegin()) != 'f')
			return (IMPOSSIBLE);
		else
			return (FLOAT);
	}
	else if ((this->_input.length() == 1 && std::isprint(this->_input[0])) || (this->_input.length() == 1 && std::isalpha(this->_input[0])))
        return (CHAR);
    else
        return (ERROR);
}

void    ScalarTypeConverterFromString::convertInput(void)
{
    this->_inputTypeFlag = checkInput();
   
    if (this->_inputTypeFlag == NAN_INF)
        return ;
    else if (this->_inputTypeFlag == IMPOSSIBLE)
        return ;
    else if (this->_inputTypeFlag == CHAR)
        convertFromChar();
    else if (this->_inputTypeFlag == INT)
        convertFromInt();
    else if (this->_inputTypeFlag == FLOAT)
        convertFromFloat();
    else if (this->_inputTypeFlag == DOUBLE)
        convertFromDouble();
    else
        std::cerr << "Error: Input not printable!" << std::endl;
}

void    ScalarTypeConverterFromString::convertFromChar(void)
{
    //this->_character = static_cast<unsigned char>(this->_input[0]);
    this->_character = static_cast<unsigned char>(this->_input[0]);
    this->_integer = static_cast<int>(this->_character);
    this->_floatingPointNumber = static_cast<float>(this->_character);
    this->_doublePrecisionNumber = static_cast<double>(this->_character);
}

void    ScalarTypeConverterFromString::convertFromInt(void)
{
	this->_integer = static_cast<int>(this->_doublePrecisionNumber);
    this->_character = static_cast<char>(this->_integer);
    this->_floatingPointNumber = static_cast<float>(this->_doublePrecisionNumber);
}

void    ScalarTypeConverterFromString::convertFromFloat(void)
{
	this->_floatingPointNumber = static_cast<float>(this->_doublePrecisionNumber);
    this->_character = static_cast<char>(this->_floatingPointNumber);
    this->_integer = static_cast<int>(this->_floatingPointNumber);
}

void    ScalarTypeConverterFromString::convertFromDouble(void)
{
    this->_character = static_cast<char>(this->_doublePrecisionNumber);
    this->_integer = static_cast<int>(this->_doublePrecisionNumber);
    this->_floatingPointNumber = static_cast<float>(this->_doublePrecisionNumber);
}

bool		ScalarTypeConverterFromString::isPrintable( double	numToCheck ) const
{
	if (numToCheck<= std::numeric_limits<int>::max() && numToCheck >= std::numeric_limits<int>::min())
		return (true);
	return (false);
}

void        ScalarTypeConverterFromString::print(void)
{
    if (this->_inputTypeFlag == ERROR)
        return ;
	
	// -------------------------- PRINT CHAR -----------------------------
    if (this->_inputTypeFlag != NAN_INF &&  this->_inputTypeFlag != IMPOSSIBLE
			&& (this->isPrintable(this->_doublePrecisionNumber) == true))
    {
        if (std::isprint(this->_character))
            std::cout << "char: '" << this->_character << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    }
    else
        std::cout << "char: impossible" << std::endl;
    
	// -------------------------- PRINT INT -----------------------------
    if (this->_inputTypeFlag != NAN_INF && this->_inputTypeFlag != IMPOSSIBLE
			&& (this->isPrintable(this->_doublePrecisionNumber) == true))
        std::cout << "int: " << this->_integer << std::endl;
    else
        std::cout << "int: impossible" << std::endl;
    
	// -------------------------- PRINT FLOAT -----------------------------
    if (this->_inputTypeFlag != NAN_INF && this->_inputTypeFlag != IMPOSSIBLE)
    {
        std::cout << "float: " << this->_floatingPointNumber;
        if (this->_floatingPointNumber - static_cast<int>(this->_floatingPointNumber) == 0)
            std::cout << ".0f";
        else
            std::cout << "f";
        std::cout << std::endl;
    }
    else
    {
		if (this->_inputTypeFlag == IMPOSSIBLE)
			std::cout << "float: impossible" << std::endl;
		else if (this->_input == "nan" || this->_input == "nanf")
            std::cout << "float: nanf" << std::endl;
        else if (this->_input[0] == '+')
            std::cout << "float: +inff" << std::endl;
        else
            std::cout << "float: -inff" << std::endl;
    }

	// -------------------------- PRINT DOUBLE -----------------------------
    if (this->_inputTypeFlag != NAN_INF && this->_inputTypeFlag != IMPOSSIBLE)
    {
        std::cout << "double: " << this->_doublePrecisionNumber;
        if (this->_doublePrecisionNumber - static_cast<int>(this->_doublePrecisionNumber) == 0
				|| (this->isPrintable(this->_doublePrecisionNumber) == false))
            std::cout << ".0";
        std::cout << std::endl;
    }
    else
    {
		if (this->_inputTypeFlag == IMPOSSIBLE)
			std::cout << "double: impossible" << std::endl;
		else if (this->_input == "nan" || this->_input == "nanf")
            std::cout << "double: nan" << std::endl;
        else if (this->_input[0] == '+')
            std::cout << "double: +inf" << std::endl;
        else
            std::cout << "double: -inf" << std::endl;
    }
}
