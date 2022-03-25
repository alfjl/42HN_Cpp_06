#include <iostream>

typedef struct	s_data
{
	std::string	name;
	int			ageInYears;
	float		heightInMeters;
	double		weightInKilos;
	s_data		*next;
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
	Data		dataStruct2;
	Data		*deserializedDataStruct;
	uintptr_t	pointerToDataStruct;

	dataStruct.name = "DataStruct1";
	dataStruct.ageInYears = 30;
	dataStruct.heightInMeters = 1.83f;
	dataStruct.weightInKilos = 85.9;
	dataStruct.next = &dataStruct2;

	dataStruct2.name = "DataStruct2";
	dataStruct2.ageInYears = 100;
	dataStruct2.heightInMeters = 2.22f;
	dataStruct2.weightInKilos = 44.4;
	dataStruct2.next = nullptr;

	pointerToDataStruct = serialize(&dataStruct);
	deserializedDataStruct = deserialize(pointerToDataStruct);

	std::cout << "\n########## TESTS ##########" << std::endl;
	std::cout
		<< "dataStruct.name: " << dataStruct.name << " / deserialized: " << deserializedDataStruct->name
		<< "\ndataStruct.ageInYears: " << dataStruct.ageInYears << " / deserialized: " << deserializedDataStruct->ageInYears
		<< "\ndataStruct.heightInMeters: " << dataStruct.heightInMeters << " / deserialized: " << deserializedDataStruct->heightInMeters
		<< "\ndataStruct.weightInKilos: " << dataStruct.weightInKilos << " / deserialized: " << deserializedDataStruct->weightInKilos
		<< std::endl;
	std::cout << "\n########## TESTS *NEXT ##########" << std::endl;
	std::cout
		<< "dataStruct->next.name: " << (*dataStruct.next).name << " / deserialized: " << deserializedDataStruct->next->name
		<< "\ndataStruct->next.ageInYears: " << (*dataStruct.next).ageInYears << " / deserialized: " << deserializedDataStruct->next->ageInYears
		<< "\ndataStruct->next.heightInMeters: " << (*dataStruct.next).heightInMeters << " / deserialized: " << deserializedDataStruct->next->heightInMeters
		<< "\ndataStruct->next.weightInKilos: " << (*dataStruct.next).weightInKilos << " / deserialized: " << deserializedDataStruct->next->weightInKilos
		<< std::endl;

	return (0);
}
