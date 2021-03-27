#include "stack.h"
#include <string.h>

Stack *s;

void push(char c);
unsigned int len();
char pop();
char peek();
void peekAll();

int main(void)
{
    s = init(100);
    char test[] = "Hello C, this is Stack";
    for (int i = 0; i < strlen(test); i++)
    {
        push(test[i]);
    }
    printf("Popped: %c, Length: %d\n", pop(), len());
    peekAll();
    return 0;
}
