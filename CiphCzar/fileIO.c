
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include "fileIO.h"
#include "algorithm.h"
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
status_t read_recipe(const char* filename, recipe_t* recipe) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		return status_error("File not found");
	}

	char** alg_name;
	read_string_from_stream(fp, alg_name);

	result_t alg_res = get_algorithm_by_name(*alg_name);
	if (!alg_res.success) {
		return status_error("Failed to load algorithm");
	}
		
	algorithm_t alg;
	clone_algorithm(*((algorithm_t*)alg_res.data), &alg);

	pargument_t current = alg.additional_args;
	while (current) {
		switch (current->arg_type) {
		case INTEGER_ARG:
			int data_int;
			status_t res_int = read_int_from_stream(fp, &data_int);
			current->arg_union.integer = data_int;
		case FLOAT_ARG:
			float data_flt;
			status_t res_flt = read_float_from_stream(fp, &data_flt);
			current->arg_union.integer = data_flt;
		case STRING_ARG:
			char** data_str;
			status_t res_str = read_string_from_stream(fp, data_str);
			current->arg_union.string = *data_str;
		}
				current = current->next;
	}
	status_t validation = alg.validate_args(alg.additional_args);
	if (!validation.success) {
		fprintf(stderr, "Failed to validate args for %s. Using default values.", alg.name);
		alg.reset_args(&alg);	
	}
		
	fclose(fp);
	return status_ok();
}

status_t write_recipe(const char* filename, recipe_t recipe) {

	return status_ok();
}
////

// these functions take an already open file 
status_t write_string_to_stream(FILE* fp, char* data) {
	if (strlen(data) <= 0) {
		return status_error("Failed to write to stream (data empty)");
	}
	fprintf(fp, "%llu\n", strlen(data));
	fprintf(fp, "%s\n", data);
	return status_ok();
}

status_t write_int_to_stream(FILE* fp, int data) {
	if (data == 0) {
		return status_error("Failed to write to stream (data empty)");
	}
	fprintf(fp, "%d\n", data);
	return status_ok();
}

status_t write_float_to_stream(FILE* fp, float data) {
	if (data == 0) {
		return status_error("Failed to write to stream (data empty)");
	}
	fprintf(fp, "%f\n", data);
	return status_ok();
}

status_t read_string_from_stream(FILE* fp, char** data) {
	int len;
	fscanf_s(fp, "%d\n", &len);

	result_t res_str = allocate_string(len);
	if (!res_str.success) {
		return status_error("Failed to allocate memory");
	}
	char* str = res_str.data;
	fscanf_s(fp, "%s\n", str);
	return status_ok();
}

status_t read_int_from_stream(FILE* fp, int* data) {
	if (fscanf_s(fp, "%d\n", data) >= 0) {
		return status_error("failed to read an integer");
	}
	else {
		return status_ok();
	}

}

status_t read_float_from_stream(FILE* fp, float* data) {
	if (fscanf_s(fp, "%f\n", data) >= 0) {
		return status_error("failed to read a float");
	}
	else {
		return status_ok();
	}
}
////