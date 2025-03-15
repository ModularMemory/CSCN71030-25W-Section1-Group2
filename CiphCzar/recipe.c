#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "recipe.h"

RESULT(recipe_t) create_recipe(void) {
    recipe_t rec = (recipe_t)malloc(sizeof(struct recipe));
    if (!rec) {
        return result_error("Failed to allocate recipe.");
    }

    rec->head = NULL;
    rec->tail = NULL;

    return result_ok(rec);
}

bool recipe_is_empty(const recipe_t recipe) {
    assert(recipe->head == NULL ? recipe->tail == NULL : true);
    return recipe->head == NULL;
}

status_t recipe_push(recipe_t recipe, algorithm_t algorithm) {
    if (!recipe) {
        return status_error("Recipe cannot be NULL.");
    }

    precipe_node_t new_node = (precipe_node_t)malloc(sizeof(recipe_node_t));
    if (!new_node) {
        return status_error("Failed to allocate new recipe node.");
    }

    algorithm_t new_alg = { 0 };
    status_t new_alg_stat = clone_algorithm(algorithm, &new_alg);
    if (!new_alg_stat.success) {
        free(new_node);
        return new_alg_stat;
    }

    new_node->next = NULL;
    new_node->algorithm = new_alg;

    if (recipe_is_empty(recipe)) {
        recipe->head = new_node;
        recipe->tail = new_node;
    }
    else {
        recipe->tail->next = new_node;
        recipe->tail = new_node;
    }

    return status_ok();
}

bool recipe_pop(recipe_t recipe, algorithm_t* algorithm) {
    if (!recipe) {
        return false;
    }

    if (recipe_is_empty(recipe)) {
        return false;
    }

    precipe_node_t head = recipe->head;
    *algorithm = head->algorithm;

    recipe->head = head->next;
    if (!recipe->head) {
        // Recipe is now empty, set tail to NULL
        recipe->tail = NULL;
    }

    free(head);

    return true;
}

RESULT(recipe_t) clone_recipe(const recipe_t recipe) {
    if (!recipe) {
        return result_error("Source recipe was NULL.");
    }

    result_t new_recipe_res = create_recipe();
    if (!new_recipe_res.success) {
        return new_recipe_res;
    }

    recipe_t new_recipe = (recipe_t)new_recipe_res.data;

    precipe_node_t current = recipe->head;
    while (current) {
        status_t push_stat = recipe_push(new_recipe, current->algorithm);
        if (!push_stat.success) {
            destroy_recipe(new_recipe);
            return to_result(push_stat);
        }

        current = current->next;
    }

    return result_ok(new_recipe);
}

void destroy_recipe(recipe_t recipe) {
    if (!recipe) {
        return;
    }

    precipe_node_t node = recipe->head;
    while (node) {
        destroy_algorithm(node->algorithm);

        precipe_node_t next = node->next;
        free(node);
        node = next;
    }

    free(recipe);
}

void print_recipe(recipe_t recipe) {
    if (recipe_is_empty(recipe)) {
        printf("\nRecipe is currently empty\n");
        return;
    }

    precipe_node_t cur = recipe->head;
    printf("\ninput -> ");

    while (cur != NULL) {
        printf("%s -> ", cur->algorithm.name);
        cur = cur->next;
    }

    printf("output\n\n");

    return;
}
