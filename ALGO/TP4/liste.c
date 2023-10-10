#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct stack_node {
    int data;
    struct stack_node *next;
};
struct stack {
    struct stack_node *first;
};

void stack_create(struct stack *self){
    assert(self!=NULL);
    self->first=NULL;
}

bool stack_is_empty(const struct stack *self){
    if (self-> first !=NULL){
        return false;
    }
    return true;
}

void stack_push(struct stack *self, int data){
    struct stack_node *s=malloc(sizeof(struct stack_node));
    if(s == NULL){
        printf("Erreur d'allocation mémoire");
        return;
    }
    s->data = data;
    s->next = self->first;
    self->first = s;
}

int stack_top(const struct stack *self){
    return self->first->data;
}


void stack_pop(struct stack *self){
    struct stack_node *p = self->first;
    self->first= self->first->next;
    free(p);
}

void stack_destroy(struct stack *self){
    while(self->first !=NULL){
        stack_pop(self);
    }
}





int main() {

    struct stack s;
    stack_create(&s);
    bool t;
    t = stack_is_empty(&s);
    printf("%i \n",t);
    stack_push(&s,8);
    stack_push(&s,0);
    stack_push(&s,1);
    stack_push(&s,12);
    stack_push(&s,4);

    t = stack_is_empty(&s);
    printf("%i \n",t);

    int p = stack_top(&s);
    printf("%d \n",p);

    stack_pop(&s);
    p = stack_top(&s);
    printf("%d \n",p);

    stack_destroy(&s);
    t = stack_is_empty(&s);
    printf("%i \n",t);

    return 0;
}
