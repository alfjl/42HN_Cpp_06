#include <iostream>
#include "ScalarTypeConverterFromString.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: Only 1 argument allowed" << std::endl;
        return (1);
    }
    
    try
    {
        ScalarTypeConverterFromString   conversion(argv[1]);
        conversion.print();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return (0);
}
