#include <stdio.h>
#include <stdlib.h>

int *arr = NULL;

int main(int argc, char const *argv[])
{
    int size = 10;

    arr = (int*)malloc(size*sizeof(int));

    for(int i = 0; i < size-3; i++){
        *(arr+i) = i + i*4;
    }
    for(int i = 0; i < size; i++){
        printf("Gia tri %d = %d\n",i , *(arr+i));
    }

    printf("\n\n\n");

    size = 15;
    arr = realloc(arr, size*sizeof(int));
    
    for(int i = 0; i < size; i++){
        printf("Gia tri %d = %d\n",i , *(arr+i));
    }

    free(arr);
    return 0;
}

