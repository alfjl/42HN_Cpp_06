#pragma once

#include <string>
#include <exception>

typedef enum e_type
{
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    NAN_INF,
	IMPOSSIBLE,
    ERROR
}           t_type;

class   ScalarTypeConverterFromString
{
private:
    std::string _input;
    int         _inputTypeFlag;
    char        _character;
    int         _integer;
    float       _floatingPointNumber;
    double      _doublePrecisionNumber;

    int         checkInput( void );
    void        convertInput( void );

    void        convertFromChar( void );
    void        convertFromInt( void );
    void        convertFromFloat( void );
    void        convertFromDouble( void );
    
    ScalarTypeConverterFromString( void );

public:
    ScalarTypeConverterFromString( std::string input );
    ScalarTypeConverterFromString( const ScalarTypeConverterFromString &other );
    ~ScalarTypeConverterFromString( void );

    ScalarTypeConverterFromString   &operator=( const ScalarTypeConverterFromString &src );

    std::string getInput( void ) const;
    int         getInputTypeFlag( void ) const;
    char        getChar( void ) const;
    int         getInt( void ) const;
    float       getFloat( void ) const;
    double      getDouble( void ) const;

	bool		isPrintable( double	numToCheck ) const;
    void        print( void );
};
