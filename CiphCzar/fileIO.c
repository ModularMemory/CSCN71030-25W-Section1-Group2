#include <stdlib.h>

#include "fileIO.h"

// these function open and close from a file name
status_t read_data(const char* filename, data_t* data) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		return status_error("File not found");
	}


	fclose(fp);
}

status_t write_data(const char* filename, data_t data) {

}

status_t read_recipe(const char* filename, recipe_t* recipe) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		return status_error("File not found");
	}

	fclose(fp);
}

status_t write_recipe(const char* filename, recipe_t recipe) {

}
////

// these functions take an already open file 
status_t write_string_to_stream(FILE* fp, char* data) {

}

status_t write_int_to_stream(FILE* fp, int data) {

}

status_t write_float_to_stream(FILE* fp, float data) {

}

status_t read_string_from_stream(FILE* fp, char** data) {

}

status_t read_int_from_stream(FILE* fp, int* data) {

}

status_t read_float_from_file(FILE* fp, float* data) {

}
////