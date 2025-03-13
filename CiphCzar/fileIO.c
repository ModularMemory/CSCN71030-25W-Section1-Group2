#include <stdlib.h>

#include "fileIO.h"

// these function open and close from a file name
result_t read_data(char* filename, data_t* data) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		return result_error("File not found");
	}


	fclose(fp);
}

result_t write_data(char* filename, data_t* data) {

}

//result_t read_recipe(char* filename, recipe_t* recipe) {
//	FILE* fp = fopen(filename, "r");
//	if (fp == NULL) {
//		return result_error("File not found");
//	}
//
//	fclose(fp);
//}

//result_t write_recipe(char* filename, recipe_t* recipe) {
//
//}
////

// these functions take an already open file 
result_t write_string_to_stream(FILE* fp, char* data) {

}

result_t write_int_to_stream(FILE* fp, int data) {

}

result_t write_float_to_stream(FILE* fp, float data) {

}

result_t read_string_from_stream(FILE* fp, char* data) {

}

result_t read_int_from_stream(FILE* fp, int* data) {

}

result_t read_float_from_file(FILE* fp, float* data) {

}
////