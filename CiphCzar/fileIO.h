#pragma once


result_t read_data(char* filename, data_t* data);

result_t write_data(char* filename, data_t* data);

result_t read_recipe(char* filename, recipe_t* recipe);

result_t write_recipe(char* filename, recipe_t* recipe);

result_t write_string_to_stream(FILE* fp, char* data);

result_t write_int_to_stream(FILE* fp,int data);

result_t write_float_to_stream(FILE* fp,float data);

result_t read_string_from_stream(FILE* fp,char* data);

result_t read_int_from_stream(FILE* fp,int* data);

result_t read_float_from_file(FILE* fp,float* data);