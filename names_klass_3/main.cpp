#include <iostream>

#include "person.h"

int main()
{
	Person person("Polina", "Sergeeva", 1960);

	for (int year : {1959, 1960}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : {1965, 1967}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

    return 0;
}
