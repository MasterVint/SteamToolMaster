#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
bool CompareCharArray(const char* argv, const char* comparative) {
	int input_size = strlen(argv);
	int compare_size = strlen(comparative);

	if (compare_size == input_size) {
		for (int i = 0; i < compare_size; i++) {
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
#endif
