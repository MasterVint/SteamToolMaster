#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <cstdlib>
static bool openFile(const std::string& path) {
	return system(("start " + path).c_str()) == 0;
}
size_t countArguments(const char* args[]) {
	size_t count = 0;
	while (args[count] != nullptr) {
		count++;
	}
	return count;
}

bool CompareCharArray(const char* argv, const char* comparative[]) {
	size_t ParameterCount = countArguments(comparative);
	for (size_t i = 0; i < ParameterCount; i++) {
		if (strcmp(argv, comparative[ParameterCount]) == 0) {
			return true;
		}
	}
	return false;
}
size_t intPow(size_t base, size_t exponent) {
	if (exponent == 0) {
		return 1;
	}
	for (size_t i = 1; i < exponent; i++) {
		base *= base;
	}
	return base;
}
size_t CharToNumber(char number) {
	if (int(number) == 48) {
		return 0;
	} else if (int(number) == 49) {
		return 1;
	} else if (int(number) == 50) {
		return 2;
	} else if (int(number) == 51) {
		return 3;
	} else if (int(number) == 52) {
		return 4;
	} else if (int(number) == 53) {
		return 5;
	} else if (int(number) == 54) {
		return 6;
	} else if (int(number) == 55) {
		return 7;
	} else if (int(number) == 56) {
		return 8;
	} else if (int(number) == 57) {
		return 9;
	}
	return 0;
}

//lets practice using input 178 = 1.78
// 1914 = 19.14
char* InsertDecimalPoint(char* number) {
	size_t length = 0; // this would become 3 for 178
	while (number[length] != '\0') {
		length++;
	}

	if (length == 0) {
		printf("Error, string is empty, please open an issue or contact the developers if this was unintended.");
		return number;
	}
	if (length > 1) {
		char* Decimal = new char[length + 1];
		for (size_t i = 0; i < length; i++) {
			Decimal[i] = number[i];
			std::cout << number[i];
			if (i == length - 3 || (length <= 2 && i == 0)) {
				Decimal[i + 1] = '.';
				std::cout << '.';
			}
		}
		return Decimal;
	}
	else {
		char* Decimal = new char[length + 3];
		Decimal[0] = '0';
		Decimal[1] = '.';
		Decimal[2] = '0';
		Decimal[3] = number[0];
		return Decimal;
	}
	return number;
	
}

//Must use delete keyword on output to prevent a memory leak.
char* SerializePositiveNumber(size_t& number) {
	size_t temp = number;
	size_t digitCount = 0;

	do {
		digitCount++;
		temp /= 10;
	} while (temp > 0);

	char* serialized = new char[digitCount + 1];
	serialized[digitCount] = '\0'; // Null-terminate the string

	temp = number;
	for (size_t i = digitCount; i > 0; i--) {
		serialized[i - 1] = '0' + (temp % 10);
		temp /= 10;
	}

	//serialized must later be deleted after usage.
	return serialized;
}
size_t parsePositiveNumber(char* numberStr, const size_t strLen, size_t start, size_t end) {
	size_t ReturnValue = 0;
	size_t numbersize = 0;
	for (size_t i = start; i < end; i++) {
		if (int(numberStr[i]) == 0) {
			if (i == 0) {
				return false;
			}
			break; // index is a '/0' character, aka no more input
		}
		if (int(numberStr[i]) >= 48 && int(numberStr[i]) <= 57) {
			//character is a number
			numbersize++;
		}
		else {
			std::cout << "false!\n";
			numbersize = -1;
			return false;
			break;
		}
		//std::cout << "numberstr: " << numberStr[i] << std::endl;
	}

	for (size_t i = numbersize; i > 0; i--) {
		//std::cout << numberStr[numbersize - i + start] << '\n';
		ReturnValue += CharToNumber(numberStr[numbersize - i + start]) * intPow(10, i - 1);
	}
	//std::cout << "retval: " << ReturnValue << '\n';
	return ReturnValue;
}
size_t parsePositiveNumber(char* numberStr, const size_t strLen) {
	size_t ReturnValue = 0;
	size_t numbersize = 0;
	for (size_t i = 0; i < strLen; i++) {
		if (int(numberStr[i]) == 0) {
			if (i == 0) {
				return false;
			}
			break; // index is a '/0' character, aka no more input
		}
		if (int(numberStr[i]) >= 48 && int(numberStr[i]) <= 57) {
			//character is a number
			numbersize++;
		}
		else {
			numbersize = -1;
			return false;
			break;
		}
		//std::cout << int(input[i]) << std::endl;
	}

	for (size_t i = numbersize; i > 0; i--) {
		ReturnValue += CharToNumber(numberStr[numbersize - i]) * intPow(10, i - 1);
	}
	return ReturnValue;
}

bool AskForPositiveNumber(size_t &ReturnValue, char* input, const size_t &MAX_SIZE) {
	size_t numbersize = 0;
	std::cin.clear();
	std::cin.get(input, MAX_SIZE);
	std::cin.ignore(1000, '\n');

	for (size_t i = 0; i < MAX_SIZE; i++) {
		if (int(input[i]) == 0) {
			if (i == 0) {
				return false;
			}
			break; // index is a '/0' character, aka no more input
		}
		if (int(input[i]) >= 48 && int(input[i]) <= 57) {
			//character is a number
			numbersize++;
		}
		else {
			numbersize = -1;
			return false;
			break;
		}
		//std::cout << int(input[i]) << std::endl;
	}

	for (size_t i = numbersize; i > 0; i--) {
		ReturnValue += CharToNumber(input[numbersize - i]) * intPow(10, i - 1);
	}
	return true;
}

size_t ReturnKeyWeaponValue(size_t keyPrice[4]) {
	size_t weapon_value = 0;
	weapon_value += keyPrice[0] * 18; //refined
	weapon_value += keyPrice[1] * 6; // reclaimed
	weapon_value += keyPrice[2] * 2; // scrap
	weapon_value += keyPrice[3] * 1; //weapon
	return weapon_value;

}

void MetalHelper(size_t &CheckAgainst, size_t &Increasing, size_t denomination) {
	while (true) {
		if (CheckAgainst >= denomination) {
			Increasing += 1;
			CheckAgainst -= denomination;
		}
		else {
			break;
		}
	}
}

//a function to return everything to proper denominations
//Example: if you have 4 scrap metal, we can convert 3 of those into 1 reclaimed metal since 3 scrap = 1 reclaimed, giving us an end value of 1 reclaimed + 1 scrap
void CleanValue(size_t &refined, size_t &reclaimed, size_t &scrap, size_t &weapons) {
	MetalHelper(weapons, scrap, 2);
	MetalHelper(scrap, reclaimed, 3);
	MetalHelper(reclaimed, refined, 3);
}
#endif
