#include <assert.h>
#include <stdlib.h>

#include "recipe.h"

result_t create_recipe(void) {
    Recipe rec = (Recipe)malloc(sizeof(struct recipe));
    if (!rec) {
        return result_error("Failed to allocate recipe.");
    }

    rec->head = NULL;
    rec->tail = NULL;

    return result_ok(rec);
}

bool recipe_is_empty(Recipe recipe) {
    assert(recipe->head == NULL ? recipe->tail == NULL : true);
    return recipe->head == NULL;
}

result_t recipe_push(Recipe recipe, algorithm_t algorithm) {
    if (!recipe) {
        return result_error("Recipe cannot be NULL.");
    }

    precipe_node_t new_node = (precipe_node_t)malloc(sizeof(recipe_node_t));
    if (!new_node) {
        return result_error("Failed to allocate new recipe node.");
    }

    new_node->next = NULL;
    new_node->algorithm = algorithm;

    if (recipe_is_empty(recipe)) {
        recipe->head = new_node;
        recipe->tail = new_node;
    }
    else {
        recipe->tail->next = new_node;
        recipe->tail = new_node;
    }

    return result_ok(NULL);
}

bool recipe_pop(Recipe recipe, algorithm_t* algorithm) {
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

result_t copy_recipe(Recipe recipe) {
    if (!recipe) {
        return result_error("Source recipe was NULL.");
    }

    result_t new_recipe_res = create_recipe();
    if (!new_recipe_res.success) {
        return new_recipe_res;
    }

    Recipe new_recipe = (Recipe)new_recipe_res.data;

    precipe_node_t current = recipe->head;
    while (current) {
        recipe_push(new_recipe, current->algorithm);
    }

    return result_ok(new_recipe);
}

void destroy_recipe(Recipe recipe) {
    if (!recipe) {
        return;
    }

    precipe_node_t node = recipe->head;
    while (node) {
        precipe_node_t next = node->next;
        free(node);
        node = next;
    }

    free(recipe);
}
