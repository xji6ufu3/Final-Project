#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "count.h"
#define LEN 26
int foodnum;
struct menu_t menu[LEN];
double price[LEN] = {1,2,3,4,5};
double count_price(char str[]){
    double sum = 0;
    int j;
    for(int i = 0; i < strlen(str); i++){
        j = str[i] - 'a';
        sum += menu[j].price;
    }
    return sum;
}
void free_menu(){
    for(int i = 0; i < foodnum; i++){
        free(menu[i].name);
        free(menu[i].ingredients);
    }
}
void initialMenu(FILE *fmenu){
    int i = 0;
    char str[100];
    char *p;
    while(fgets(str,100,fmenu) != NULL){
        if(atoi(strtok(str," \n")) != i+1){
            printf("wrong order at line %d in the menu.\n",i+1);
            exit(0);
        }
        p = strtok(NULL," \n");
        menu[i].name = malloc(strlen(p)+1);
        strcpy(menu[i].name,p);
        menu[i].price = atof(strtok(NULL," \n"));
        menu[i].time = atoi(strtok(NULL," \n"));
        p = strtok(NULL," \n");
        menu[i].ingredients = malloc(strlen(p)+1);
        strcpy(menu[i].ingredients,p);
        p = strtok(NULL," \n");
        if(p != NULL){
            printf("too many parameter at line %d in menu.\n",i+1);
            exit(0);
        }
        i++;
    }
    foodnum = i;
}
void printMenu(){
    for(int i = 0; i < foodnum; i++){
        printf("-----\n"
        "code: %c\n"
        "name: %s\n"
        "price: %.1lf\n"
        "time: %d\n"
        "ingredients: %s\n",i+'a',menu[i].name,menu[i].price,
        menu[i].time,menu[i].ingredients);
    }
}