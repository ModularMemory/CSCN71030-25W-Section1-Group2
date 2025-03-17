#pragma once

#include <stddef.h>

#include "argument.h"
#include "data.h"
#include "status_result.h"

typedef struct algorithm {
  const char *name;
  const char *description;
  status_t (*execute)(const data_t input, const pargument_t args,
                      data_t *output);
  status_t (*validate_args)(const pargument_t args);
  pargument_t additional_args;
  void (*reset_args)(struct algorithm *alg);
} algorithm_t;

status_t clone_algorithm(const algorithm_t source, algorithm_t *dest);

/// @brief Destroys an algorithm and its members
///
/// Only to be called on cloned algorithms!
void destroy_algorithm(algorithm_t alg);

typedef struct {
  algorithm_t *algorithms;
  size_t len;
} algorithm_list_t;

/// @brief Gets the number of known algorithms
size_t get_algorithms_count(void);

/// @brief Gets a read-only list of all available algorithms
const algorithm_list_t get_algorithms(void);

/// @brief Gets a read-only pointer to an algorithm by index in the algorithm
/// list.
RESULT(const algorithm_t *) get_algorithm_by_index(int index);

/// @brief Gets a read-only pointer to an algorithm by name (case insensitive).
RESULT(const algorithm_t *) get_algorithm_by_name(const char *name);

void destroy_algorithm_list(void);