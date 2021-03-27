#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack
{
    unsigned int length;
    int *content;
} Stack;

extern Stack *s;

Stack *init(unsigned int capacity)
{
    Stack *new = (Stack *)malloc(sizeof(Stack));
    new->length = 0;
    new->content = (int *)malloc(capacity * sizeof(int));
    return new;
}

void push(char c)
{
    s->content[s->length++] = c;
}

unsigned int len()
{
    return s->length;
}

char pop()
{
    if (len(s) > 0)
    {
        return s->content[(s->length--) - 1];
    }
    return '&';
}

char peek()
{
    return s->content[s->length - 1];
}

void peekAll()
{
    for (int i = 0; i < s->length; i++)
    {
        printf("%c", *(s->content + i));
    }
    printf("\n");
}
