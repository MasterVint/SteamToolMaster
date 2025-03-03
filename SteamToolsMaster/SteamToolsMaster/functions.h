#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>

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

size_t AskForPositiveNumber(char* input, const size_t &MAX_SIZE) {
	size_t ReturnValue = 0;
	size_t numbersize = 0;
	std::cin.get(input, MAX_SIZE);

	for (size_t i = 0; i < MAX_SIZE; i++) {
		if (int(input[i]) == 0) {
			break; // /0 character, aka no more input
		}
		if (int(input[i]) >= 48 || int(input[i]) <= 57) {
			//character is a number
			numbersize++;
		}
		else {
			//its not a number, this means that the input is invalid
			numbersize = -1;
			break;
		}
		//std::cout << int(input[i]) << std::endl;
	}

	for (size_t i = numbersize; i > 0; i--) {
		std::cout << "I: " << i << std::endl;
		//2, 1
		ReturnValue += CharToNumber(input[numbersize - i]) * intPow(10, i - 1);//std::pow(10, numbersize - 1);
	}
	std::cout << "returning" << std::endl;
	return ReturnValue; 
}

size_t ReturnKeyWeaponValue(size_t keyPrice[4], size_t keyAmount) {
	size_t weapon_value = 0;
	weapon_value += keyPrice[0] * 18; //refined
	weapon_value += keyPrice[0] * 6; // reclaimed
	weapon_value += keyPrice[0] * 2; // scrap
	weapon_value += keyPrice[0] * 1; //weapon
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

void CleanValue(size_t &refined, size_t &reclaimed, size_t &scrap, size_t &weapons) {
	MetalHelper(weapons, scrap, 2);
	MetalHelper(scrap, reclaimed, 3);
	MetalHelper(reclaimed, refined, 3);

	//size_t Value[4] = { refined, reclaimed, scrap, weapons }; // ref, reclaimed, scrap, weapons
	//return Value;
}
#endif
