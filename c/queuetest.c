
#include "queue.h"

int main(int argc, char const *argv[])
{
    Node *list = newEmptyQueue();
    int diez = 62;
    int veinte = 20;
    printf("%p\n", list->next);
    list->value = &diez;
    dispList(list);

    appendQueue(list, &veinte);
    int cuarenta = 40;
    appendQueue(list, &cuarenta);
    dispList(list);

    popQueue(list);
    printf("Last %d\n", *(int *)lastElementQueue(list));
    dispList(list);

    printf("%p\n", list);
    list = pushQueue(list, &cuarenta);
    printf("%p\n", list);
    printf("%p\n", list->next);
    printf("Last %d\n", *(int *)lastElementQueue(list));
    printf("first %d\n", *(int *)list->value);
    dispList(list);

    printf("%d\n", lengthQueue(list));
    for (int i = 0; i < lengthQueue(list); i++)
    {
        printf("%d-th: %d\n", i, *(int *)nthElementQueue(list, i));
    }

    list = shiftQueue(list);
    dispList(list);

    freeQueue(list);


    return 0;
}
