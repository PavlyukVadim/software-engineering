#include "Exception.h"
#include <cstdio>
#include <string.h>

Exception::Exception(char* message) {
	msg = new char[strlen(message) + 1];
	strcpy(msg, message);
}

Exception::~Exception() {
	delete[] msg;
	msg = NULL;
}

void Exception::show(void) {
	printf("Exeption: %s\n", msg);
}
