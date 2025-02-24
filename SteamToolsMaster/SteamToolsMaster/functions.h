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
#endif
