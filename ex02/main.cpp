#include <iostream>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

/* ------------------------------------------------------------------------- */
// C++ Standard, section 5.2.7/9
// If dynamic_cast on pointer fails, 'nullptr' is returned.
// If dynamic_cast on reference fails, it can't return a nullptr and throws
// bad_cast exception instead.
/* ------------------------------------------------------------------------- */

Base	*generate(void)
{
	int	randomInt;

	srand(time(NULL));

	switch(randomInt = rand() % 3)
	{
	case 0:
		return (new A());
	case 1:
		return (new B());
	case 2:
		return (new C());
	default:
		return (nullptr);
	}
}

void	identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void	identify(Base &p)
{
	try
	{
		A	&a = dynamic_cast<A &>(p);
		(void )a;
		std::cout << "A" << std::endl;
	}
	catch (std::bad_cast &bc)
	{
		try
		{
			B	&b = dynamic_cast<B &>(p);
			(void )b;
			std::cout << "B" << std::endl;
		}
		catch (std::bad_cast &bc)
		{
			try
			{
				C	&c = dynamic_cast<C &>(p);
				(void )c;
				std::cout << "C" << std::endl;
			}
			catch (std::bad_cast &bc)
			{
				std::cout << "Unknown type" << std::endl;
			}
		}
	}
}

int	main()
{
	Base	*one = generate();
	
	if (one != nullptr)
	{
		identify(one);
		identify(*one);
		delete (one);
	}

	return (0);
}
