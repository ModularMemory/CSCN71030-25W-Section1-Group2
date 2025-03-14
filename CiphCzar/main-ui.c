#define LOGO "temp :p"

#include "main-ui.h"
#include <stdio.h>

void printIntro() {
	printf("%s\n\n" "\x1b[0m", LOGO);
	printf("Welcome to CyphCzar!\n" "\x1b[0m");
	return;
}

void printMainMenu() {
	char response = '\0';

	printf("Main menu:\n");

	do {
		while (response == '\0');
		if (97 <= (int)response <= 101) break;
		response = '\0';
	}

	return;
}

