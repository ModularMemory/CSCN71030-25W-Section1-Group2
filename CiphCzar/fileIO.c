
#include <stdlib.h>
#include <sys/stat.h>
#include "fileIO.h"
#include "argument.h"
#include "data.h"
#include "status_result.h"
#include "utils.h"
#include "recipe.h"

#define NULL_TERMINATOR_LEN 1
#define MAXALG 30
#define MAXARG 10

static long long get_file_size(const char* filename) {
    struct __stat64 st;
    if (_stat64(filename, &st) != 0) {
        // Error reading file length
        return -1;
    }

    return st.st_size;
}

// these function open and close from a file name
status_t read_data(const char* filename, data_t* data) {
	//open the file
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		return status_error("File not found");
	}

	//find the length of the file
	long long length = get_file_size(filename);
	//if the file is empty, there's nothing to read so return an error
	if (length <=0 ) {
		fclose(fp);
		return status_error("File is empty");
	}

	//create a space in memory big enough to fit the file contents
	result_t out_res = allocate_string(length);
	if (!out_res.success) {
		fclose(fp);
		return to_status(out_res);
	}
	
	//get the data from the file and put it in the allocated space
	fgets(out_res.data, length + NULL_TERMINATOR_LEN, fp);
	
	//create the data wrapper 
	data_t* output;
	*output = create_data(out_res.data, sizeof(out_res.data));
	data = output;

	fclose(fp);
	return status_ok();
}

status_t write_data(const char* filename, data_t data) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		return status_error("File not found");
	}
	fputs(data.data, fp);
	return status_ok();
}


// The save file will look something like: 
// 
// algorithm_name algorithm_name algorithm_name etc.. \n
// arg arg arg arg etc EOF
// 
// reading the file will first get all the algorithms by reading characters one by one until a space, then using get_algorithm_by_name
// to convert it to an algorithm struct which gets saved in the recipe linked list, it does it until it hits a \n then it starts reading
// for arguments 
status_t read_recipe(const char* filename, recipe_t* recipe, pargument_t arguments) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		return status_error("File not found");
	}

	char currChar = '\0';
	char algorithm_name[MAXALG] = {'\0'};
	int i = 0;
	
	//reading all the algorithm names and putting them into a recipe
	while(currChar != '\n') {
		while (i + NULL_TERMINATOR_LEN < MAXALG && ((currChar = fgetc (fp)) != ' ' && currChar != EOF)) {
			algorithm_name[i++] = currChar;
		}
		result_t algorithm_res = get_algorithm_by_name(algorithm_name);
		if(!algorithm_res.success) {
			return status_error("Failed to load algorithm");
		}
		algorithm_t* algorithm = algorithm_res.data;
		recipe_push(*recipe, *algorithm);
	}

	//reading all the arguments and adding them to the argument list (basically copying get_args.c except changing it to work for a file)
	recipe_t current = *recipe;
	char algChar = '\0';

	while (current->head != NULL) {

		algorithm_t alg = current->head->algorithm;
		if (alg.additional_args != NULL) {
			arguments = alg.additional_args;
			argument_union_t arg_union;
			int arg_int;
			float arg_flt;
			char argument[MAXARG] = { 0 };
			int i = 0;

			while (arguments != NULL) {
				switch (arguments->arg_type) {
				case INTEGER_ARG:
					while(i + NULL_TERMINATOR_LEN < MAXARG && ((algChar = fgetc (fp)) != ' ' && algChar != EOF)) {
						argument[i++] = algChar;
					}
					arg_int = atoi(argument);
					arg_union = (argument_union_t) { .integer = arg_int };
					arguments->arg_union = arg_union;
					break;
				case FLOAT_ARG:
					while(i + NULL_TERMINATOR_LEN < MAXARG && ((algChar = fgetc (fp)) != ' ' && algChar != EOF)) {
						argument[i++] = algChar;
					}
					arg_flt = atof(argument);
					arg_union = (argument_union_t) { .fp = arg_flt };
					arguments->arg_union = arg_union;
					break;
				case STRING_ARG:
					while(i + NULL_TERMINATOR_LEN < MAXARG && ((algChar = fgetc (fp)) != ' ' && algChar != EOF)) {
						argument[i++] = algChar;
					}
					arg_union = (argument_union_t) { .string = argument };
					arguments->arg_union = arg_union;
				}

				arguments = arguments->next;
			}
		}
		current->head = current->head->next;
	}

	fclose(fp);
	return status_ok();
}

status_t write_recipe(const char* filename, recipe_t recipe) {

	return status_ok();
}
////

// // these functions take an already open file 
// status_t write_string_to_stream(FILE* fp, char* data) {

// }

// status_t write_int_to_stream(FILE* fp, int data) {

// }

// status_t write_float_to_stream(FILE* fp, float data) {

// }

// status_t read_string_from_stream(FILE* fp, char** data) {

// }

// status_t read_int_from_stream(FILE* fp, int* data) {

// }

// status_t read_float_from_file(FILE* fp, float* data) {

// }
// ////