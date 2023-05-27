#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

struct s_queue {
    unsigned int size;     // Tamaño de la pila
    struct s_node *first;  // Puntero al primer nodo
    struct s_node *last;  // Puntero al ultimo nodo
};

struct s_node {            // Estructura de nodo
    queue_elem elem;       // Elemento del nodo
    struct s_node *next;   // Puntero al siguiente nodo
};

static struct s_node *
create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *
destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool
invrep(queue q) {
    return q != NULL;
}

queue queue_empty(void) {
    queue q = malloc(sizeof(struct s_queue)); // Alojo memoria para el nodo principal
    q -> size = 0;                            // Tamaño inicial en 0
    q -> first = q -> last = NULL;        // Puntero al primer nodo NULL (no existe el primer nodo)
    assert(invrep(q) && queue_is_empty(q));
    return q;
}

queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e); // Crea puntero a un nodo nuevo
    if (q-> first==NULL) {                     // Si el primer nodo no existe lo creo
        q -> first = q -> last = new_node;
    } else {                                  // Si ya existen nodos entonces 
        q -> last -> next = new_node;
        q -> last = new_node;
        q -> size += 1;
    }
    assert(invrep(q) && !queue_is_empty(q) && queue_first(q) == e);
    return q;
}

queue queue_disscard(queue q, unsigned int n) {
    if (n >= q->size) {
        return q;
    }

    if (n == 0) {
        q = queue_dequeue(q);
    } else {
        struct s_node* nodo_prev = q->first;
        for (unsigned int i = 1; i < n; i++) {
            nodo_prev = nodo_prev->next;
        }

        struct s_node* discard_node = nodo_prev->next;
        nodo_prev->next = discard_node->next;

        if (discard_node == q->last) {
            q->last = nodo_prev;
        }

        destroy_node(discard_node);
    }

    q->size--;

    return q;
}



bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->last->elem;
}
unsigned int queue_size(queue q) {
    assert(invrep(q));
    unsigned int size=0;
    size = q -> size;
    return size;
}

queue queue_dequeue(queue q) { 
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->first;
    q -> first = q -> first->next;
    q -> size -= 1;
    killme = destroy_node(killme);
    assert(invrep(q));
    return q;
}

void queue_dump(queue q, FILE *file) {
    file = file==NULL ? stdout: file;
    struct s_node *node=q->first;
    fprintf(file, "[ ");
    while(node!=NULL) {
        fprintf(file, "%d", node->elem);
        node = node->next;
        if (node != NULL) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
}


queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}

