#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 26
#define DEBUG 1
typedef struct list_t{
    int number; // the order of order
    double price;
    struct list_t *prior, *next; // doubly linked list
    char meal[]; // store meal codes ranged from 'a' to 'z' to string
} list_t; // list_t store the order information
int main(){
    int count, price = 0; // count store the sum of order
    char str[LEN+1], record[36]; 
    list_t *list = NULL, *ptr, *prior; // the beginning of the list
    FILE *frecord = fopen("recording.txt","a+");
    FILE *fnum = fopen("number.txt","w+");
    fscanf(fnum,"%d",&count);
    while(1){
        printf("input the meal code: ");
        fgets(str,LEN,stdin);
        str[strlen(str)-1] = '\0';
        // if the code is 0, break the while loop
        if(!strcmp(str,"0")) break;
        // sort the meal code and count the total price
        // store the meal codes to the list
        if(count == 0){
            list = malloc(sizeof(list_t)+strlen(str)+1);
            ptr = list;
            list->prior = list->next = NULL;
        }
        else{
            ptr->next = malloc(sizeof(list_t)+strlen(str)+1);
            prior = ptr;
            ptr = ptr->next;
            ptr->prior = prior;
            ptr->next = NULL;
        }
        ptr->number = ++count;
        strcpy(ptr->meal,str);
        ptr->price = price;
    }
    fprintf(fnum,"%d",count);
    fclose(fnum);
    fclose(frecord);
    #if DEBUG
    ptr = list;
    puts("----------------");
    for(int i = 0; i < count; i++){
        printf(
        "num: %d\n"
        "meal: %s\n"
        "price: %d\n"
        "----------------\n",ptr->number,ptr->meal,ptr->price);
        ptr = ptr->next;
    }
    #endif
}