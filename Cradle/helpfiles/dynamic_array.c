#include <stdio.h>
#include <stdlib.h>

typedef struct IntArray arr;
int push(int usrdata, arr *s1);
int init(arr *s1, int cap);

struct IntArray {
    int* data;
    int size;
    int capacity;
};

int main() {
    //init
    arr s1;
    init(&s1, 4);

    int usrdata[] = {1,2,3,4,5,6,7,8}; //testing

    //push
    int len = sizeof(usrdata)/sizeof(usrdata[0]);
    for (int i = 0; i < len; i++) {
        if (push(usrdata[i], &s1) != 0) {
            printf("not enough memory\n");
            free(s1.data);
            return 2;
        }
    }

    //print
    for (int i = 0; i < s1.size; i++) {
        printf("%d\n", s1.data[i]); 
    }

    printf("capacity: %d\nsize: %d\n", s1.capacity, s1.size); //testing

    free(s1.data); //free
}

int push(int usrdata, arr *s1) {
    if (s1->capacity == s1->size) {
        int *tmp;
        tmp = realloc(s1->data, sizeof(*s1->data) * s1->capacity * 2);
        if (tmp == NULL) {return 2;}
        s1->capacity = s1->capacity * 2;
        s1->data = tmp;
    }

    s1->data[s1->size++] = usrdata;
    return 0;
}

int init(arr *s1, int cap) {
    s1->size = 0;
    s1->capacity = cap;
    s1->data = malloc(sizeof(*s1->data) * s1->capacity);
    if (s1->data == NULL) {
        printf("not enough memory\n");
        return 1;
    }

    return 0;
}