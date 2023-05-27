#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

/*static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}
*/
static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    if (tree == NULL) //Si el arbol es vacio se cumple la invariante
    {
        return true;
    }else
    if (tree->left != NULL && !elem_less(tree->left->elem, tree->elem))/*Si el elemento de la izquierda es no nulo
    y ese elemento es mayor que el elemento de arriba no se cumple la invariante */
    {
        return false;
    }else
    if (tree->right != NULL && !elem_less(tree->elem, tree->right->elem))/*Si el elemento de la derecha es no nulo
    y ese elemento es menor que el elemento de arriba no se cumple la invariante */
    {
        return false;
    }
    return invrep(tree->left) && invrep(tree->right); //Retorno la llamada recursiva de la funcion inv
}

abb abb_empty(void) {
    abb tree;
    tree = NULL; //Creo un arbol vacio, es decir apuntando a null el puntero inicial del arbol
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree == NULL)
    {
        struct _s_abb *new_node=malloc(sizeof(struct _s_abb));
        new_node -> elem = e;
        new_node -> left = NULL;
        new_node -> right = NULL;
        tree = new_node;
    } else if (e < tree -> elem) {
        tree -> left = abb_add(tree -> left,e);
    } else if (e > tree -> elem) {
        tree -> right = abb_add(tree -> right,e); 
    }
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));
    is_empty = (tree==NULL);
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    if (tree == NULL) //Si el arbol es nulo, el elemento no existe
    {
        exists = false;
    } else { //Si el arbol es no nulo, reviso si el elemento esta en la raiz y si esta existe
        if (tree -> elem == e) {
            exists = true;
        } else if (e < tree -> elem){ //Si no esta y es menor a la raiz, busco en la izquierda
            exists = abb_exists(tree -> left,e);
        } else if (e > tree -> elem){ //Si no esta y es mayor a la raiz, busco en la derecha
            exists = abb_exists(tree -> right,e);
        }
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (tree != NULL) //Si es arbol no vacio, significa que hay un nodo, aumento el tamaño en 1
    {
        length += 1;
        length += abb_length(tree -> left); //Repito con la parte derecha del arbol
        length += abb_length(tree -> right);//Repito con la parte izquierda del arbol
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    /*
     * Needs implementation
     */
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree -> elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb aux = tree;
    while (aux -> right != NULL)
    {
        aux = aux -> right;
    }
    max_e = aux -> elem;
    free(aux);
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb aux = tree;
    while (aux -> left != NULL)
    {
        aux = aux -> left;
    }
    min_e = aux -> elem;
    free(aux);
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (tree != NULL)
    {
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree);
    }
    assert(tree == NULL);
    return tree;
}

