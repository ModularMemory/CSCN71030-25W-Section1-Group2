#include <stdio.h>
#include <string.h>

#include "app_args.h"
#include "utils.h"

#define QUIET_ARG "--quiet"
#define INPUT_RECIPE_ARG "--recipe"
#define OUTPUT_FILE_ARG "--output"
#define DEFAULT_INPUT_ARG "--input"
#define INPUT_FILE_ARG "--input-file"

bool parse_app_arguments(int argc, const char** argv, app_args_t* args) {
    *args = (app_args_t) { 0 };

    if (argc <= 1) {
        return true;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], QUIET_ARG) == 0) {
            args->quiet = true;
        }
        else if (i + 1 < argc && strcmp(argv[i], INPUT_RECIPE_ARG) == 0) {
            args->recipe_file = argv[i + 1];
            i++;
        }
        else if (i + 1 < argc && strcmp(argv[i], OUTPUT_FILE_ARG) == 0) {
            args->output_file = argv[i + 1];
            i++;
        }
        // Default input and input file are mutually exclusive
        else if (i + 1 < argc && !args->input_file && strcmp(argv[i], DEFAULT_INPUT_ARG) == 0) {
            args->default_input = argv[i + 1];
            i++;
        }
        // Default input and input file are mutually exclusive
        else if (i + 1 < argc && !args->default_input && strcmp(argv[i], INPUT_FILE_ARG) == 0) {
            args->input_file = argv[i + 1];
            i++;
        }
        else {
            // Invalid argument read; stop parsing.
            if (!args->quiet) {
                // Write argument help message
                fprintf(stderr, "Usage: %s", get_file_name(argv[0]));
                fprintf(stderr, " [%s]", QUIET_ARG);
                fprintf(stderr, " [%s <recipe path>]", INPUT_RECIPE_ARG);
                fprintf(stderr, " [%s <output path>]", OUTPUT_FILE_ARG);
                fprintf(stderr, " [%s <default input> | %s <input path>]", DEFAULT_INPUT_ARG, INPUT_FILE_ARG);
                fprintf(stderr, "\n\nOptions:");

                const int arg_desc_offset = 21;
                fprintf(stderr, "\n  %-*s Supresses messages from being written to to stdout. Errors may still be written to stderr.", arg_desc_offset, QUIET_ARG);
                fprintf(stderr, "\n  %-*s Loads a recipe save file on application startup.", arg_desc_offset, INPUT_RECIPE_ARG" <path>");
                fprintf(stderr, "\n  %-*s The default recipe output file path.", arg_desc_offset, OUTPUT_FILE_ARG" <path>");
                fprintf(stderr, "\n  %-*s The default recipe input string. Cannot be used in conjunction with %s.", arg_desc_offset, DEFAULT_INPUT_ARG" <string>", INPUT_FILE_ARG);
                fprintf(stderr, "\n  %-*s A path to a file to be used as the default recipe input. Cannot be used in conjunction with %s.", arg_desc_offset, INPUT_FILE_ARG" <path>", DEFAULT_INPUT_ARG);
                fprintf(stderr, "\n");
            }

            return false;
        }
    }

    return true;
}