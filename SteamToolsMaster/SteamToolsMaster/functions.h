#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
bool CompareCharArray(const char* argv, const char* comparative) {
	size_t input_size = strlen(argv);
	size_t compare_size = strlen(comparative);

	if (compare_size == input_size) {
		for (size_t i = 0; i < compare_size; i++) {
			if (argv[i] != comparative[i]) {
				return false;
			}
		}
	}
	else {
		return false;
	}

	return true;

}

size_t countArguments(const char* args[]) {
	size_t count = 0;
	while (args[count] != nullptr) {
		count++;
	}
	return count;
}

bool CompareCharArray(const char* argv, const char* comparative[]) {
	size_t input_size = strlen(argv);
	size_t compare_size = 0;

	size_t Parameters = countArguments(comparative);
	for (size_t o = 0; o < Parameters; o++) {
		bool ParameterResult = true;
		compare_size = strlen(comparative[o]);
		if (compare_size == input_size) {
			for (size_t i = 0; i < compare_size; i++) {
				if (argv[i] != comparative[o][i]) {
					ParameterResult =  false;
				}
			}
		}
		else {
			ParameterResult = false;
		}
		if (ParameterResult) {
			return ParameterResult;
		}
	}
}
#endif
