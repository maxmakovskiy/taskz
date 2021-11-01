#include <iostream>

#include "person.h"

int main()
{
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	std::cout << person.GetFullNameWithHistory(1990) << std::endl;

	person.ChangeFirstName(1966, "Pauline");
	std::cout << person.GetFullNameWithHistory(1966) << std::endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	std::cout << person.GetFullNameWithHistory(1967) << std::endl;

    return 0;
}
