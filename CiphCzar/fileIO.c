
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
	fread(out_res.data, sizeof(char),  length, fp);
	
	//create the data wrapper 
	*data = create_data(out_res.data, sizeof(out_res.data));

	fclose(fp);
	return status_ok();
}

status_t write_data(const char* filename, data_t data) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		return status_error("File not found");
	}
	fwrite(data.data, sizeof(char), data.len, fp);
	return status_ok();
}

status_t read_recipe(const char* filename, recipe_t* recipe) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		return status_error("File not found");
	}

	int count;

	status_t res_count = read_int_from_stream(fp, &count);
	if (!res_count.success) {
		fclose(fp);
		return res_count;
	}

	for (int i = 0; i < count; i++) {
		char* alg_name;
		status_t res_alg_name = read_string_from_stream(fp, &alg_name);
		if (!res_alg_name.success) {
			fclose(fp);
			return res_alg_name;
		}
		
		result_t alg_res = get_algorithm_by_name(alg_name);
		if (!alg_res.success) {
			fclose(fp);
			return to_status(alg_res);
		}
			
		algorithm_t alg;
		status_t res_clone = clone_algorithm(*((algorithm_t*)alg_res.data), &alg);
		if (!res_clone.success) {
			fclose(fp);
			return res_clone;
		}

		pargument_t current = alg.additional_args;
		while (current) {
			switch (current->arg_type) {
			case INTEGER_ARG:
			{
				int data_int;
				status_t res_int = read_int_from_stream(fp, &data_int);
				if (!res_int.success) {
					fclose(fp);
					return res_int;
				}
				current->arg_union.integer = data_int;
				break;
			}
			case FLOAT_ARG:
			{
				float data_flt;
				status_t res_flt = read_float_from_stream(fp, &data_flt);
				if (!res_flt.success) {
					fclose(fp);
					return res_flt;
				}
				current->arg_union.integer = data_flt;
			}
			case STRING_ARG:
			{
				char* data_str;
				status_t res_str = read_string_from_stream(fp, &data_str);
				if (!res_str.success) {
					fclose(fp);
					return res_str;
				}
				current->arg_union.string = data_str;
			}
			}
			current = current->next;
		}
		status_t validation = alg.validate_args(alg.additional_args);
		if (!validation.success) {
			fprintf(stderr, "Failed to validate args for %s. Using default values.", alg.name);
			alg.reset_args(&alg);	
		}
	}
	fclose(fp);
	return status_ok();
}

status_t write_recipe(const char* filename, recipe_t recipe) {

	return status_ok();
}

status_t write_string_to_stream(FILE* fp, char* data) {
	fprintf(fp, "%llu\n", strlen(data));
	fwrite (data, sizeof(char), strlen(data), fp);
	return status_ok();
}

status_t write_int_to_stream(FILE* fp, int data) {
	fprintf(fp, "%d\n", data);
	return status_ok();
}

status_t write_float_to_stream(FILE* fp, float data) {
	fprintf(fp, "%f\n", data);
	return status_ok();
}

status_t read_string_from_stream(FILE* fp, char** data) {
	unsigned long long len;
	fscanf_s(fp, "%llu\n", &len);

	result_t res_str = allocate_string(len);
	if (!res_str.success) {
		return status_error("Failed to allocate memory");
	}
	*data = res_str.data;
	fread(*data, sizeof(char), len, fp);
	return status_ok();
}

status_t read_int_from_stream(FILE* fp, int* data) {
	if (fscanf_s(fp, "%d\n", data) <= 0) {
		return status_error("failed to read an integer");
	}
	else {
		return status_ok();
	}

}

status_t read_float_from_stream(FILE* fp, float* data) {
	if (fscanf_s(fp, "%f\n", data) <= 0) {
		return status_error("failed to read a float");
	}
	else {
		return status_ok();
	}
}
