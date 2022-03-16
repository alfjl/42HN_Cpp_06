#include <iostream>

typedef struct	s_data
{
	std::string	name;
	int			ageInYears;
	float		heightInMeters;
	double		weightInKilos;
}		Data;

uintptr_t	serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data		*deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}

int	main()
{
	Data		dataStruct;
	Data		*deserializedDataStruct;
	uintptr_t	pointerToDataStruct;

	dataStruct.name = "DataStruct1";
	dataStruct.ageInYears = 30;
	dataStruct.heightInMeters = 1.83f;
	dataStruct.weightInKilos = 85.9;

	pointerToDataStruct = serialize(&dataStruct);
	deserializedDataStruct = deserialize(pointerToDataStruct);

	std::cout << "\n########## TESTS ##########" << std::endl;
	std::cout
		<< "dataStruct.name: " << dataStruct.name << " / deserialized: " << deserializedDataStruct->name
		<< "\ndataStruct.ageInYears: " << dataStruct.ageInYears << " / deserialized: " << deserializedDataStruct->ageInYears
		<< "\ndataStruct.heightInMeters: " << dataStruct.heightInMeters << " / deserialized: " << deserializedDataStruct->heightInMeters
		<< "\ndataStruct.weightInKilos: " << dataStruct.weightInKilos << " / deserialized: " << deserializedDataStruct->weightInKilos
		<< std::endl;




	return (0);
}
