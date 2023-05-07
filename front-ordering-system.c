#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 26
typedef struct{
    int order;
    double price;
    list_t *prior, *next;
    char product[];
} list_t;
int main(){
    
}