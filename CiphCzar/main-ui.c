#define LOGO \
"\x1b[31m             _______  _________  ______      ___     ___     \x1b[34m_________  ____________   ________    _____\n" \
"\x1b[31m            /AAAAAA/ /AAAAAAAA/ /AAAAAA\\    /AA/    /AA/    \x1b[34m/AAAAAAAA/ /AAAAAAAAAA,*  /AAAAAAAA\\  /AAAAA\\ \n"\
"\x1b[31m           /XXXXXX/ /XXXXXXXX/ /XX/  \\XX\\  /XX/    /XX/    \x1b[34m/XXXXXXXX/ /XXXXX,XXX,*   /XX,^^^,XX/ /XX/ \\XX\\ \n"\
"\x1b[31m          /oo/        /oo/    /ooo\\__/oo/ /oo/____/oo/    \x1b[34m/oo/            ,*oo,*    /oo/___/oo/ /oo/__/oo/ \n"\
"\x1b[31m         /xx/        /xx/    /xx,xxxxxx/ /xx,xxxx,xx/    \x1b[34m/xx/           ,*xx,*     /xxxxxxxxx/ /xx,xxxxx/ \n"\
"\x1b[31m        /~~/____  __/~~/__  /~~/        /~~/    /~~/    \x1b[34m/~~/______    ,*~~,*____  /~~/   /~~/ /~~/\\~~\\ \n"\
"\x1b[31m       /'''''''/ /'''''''/ /''/        /''/    /''/    \x1b[34m/'''''''''/  ,*'''''''''/ /''/   /''/ /''/  ^''^ \n"\
"\x1b[31m      /_______/ /_______/ /__/        /__/    /__/    \x1b[34m/_________/ ,*__________/ /__/   /__/ /__/    \\__\\ \n"\
"\x1b[35m  __________________________________________________________________________________________________________ \n"\
" /                                                                                                         / \n"\
"/_________________________________________________________________________________________________________/ \n \x1b[0m"

#include "main-ui.h"
#include "user_input.h"
#include <stdio.h>



void printIntro() {
	printf("%s\n\n", LOGO);
	printf("Welcome to CyphCzar!\n");
	return;
}



void printMainMenu() {
	char response = '\0';

	printf("A: Create recipe\n");
	printf("B: Execute recipe\n");
	printf("C: Print last output\n");
	printf("D: Update input\n");
	printf("E: Export to file\n\n");

	while ('a' > response || 'e' < response) {
		get_user_char(&response);
	}

	switch (response) {
	case 'a':
		// create recipe
		break;

	case 'b':
		// mods, execute him
		break;

	case 'c':
		// print output
		break;

	case 'd':
		result_t new_input = get_user_string();

		if (!new_input.success) {
			fprintf(stderr, "erm bad string idk placeholder error");
		}

		char* input = (char*)new_input.data;
		data_t new_data = create_data(input, strlen(new_input));
		break;

	case 'e':
		// export to outfile
		break;
	}

	printf("\n\nyou chose %c", response);

	return;
}

