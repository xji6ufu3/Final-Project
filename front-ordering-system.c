#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "count.h"
#include "FileIO.h"
#define LEN 26
#define DEBUG 0
// #define RECORD_NAME "recording.txt"
// #define RECORD_NAME_TEMP "recording_temp.txt"
// typedef struct list_t{
//     int number; // the order of order
//     double price;
//     struct list_t *prior, *next; // doubly linked list
//     char meal[]; // store meal codes ranged from 'a' to 'z' to string
// } list_t; // list_t store the order information
extern int foodnum; // the number of food in the menu
enum state_t{NOTHING,CONTINUE,BREAK};
enum state_t check_meal_code(char str[]);
// void free_list(list_t *ptr);
int cmp(const void *a, const void *b);
// void del_record(int number);
int delete(list_t **list, int number);
int isnumber(char str[]);
int main(){
    int count; // count store the sum of order
    char str[LEN+1], record[36], command[10];
    enum state_t state;
    list_t *list = NULL, *ptr, *prior;
    FILE *frecord = fopen(RECORD_NAME,"a+");
    FILE *fnum = fopen("number.txt","r");
    FILE *fmenu = fopen("menu.txt","r");
    initialMenu(fmenu);
    #if DEBUG
        printMenu();
    #endif
    fclose(fmenu);
    fscanf(fnum,"%d",&count);
    while(count){
        printf("the number in number.txt is not 0.\n"
        "scan command below to continue.\n"
        "0: just continue.\n"
        "1: initialize the number.txt\n"
        "2: exit the program.\n"
        "command: ");
        scanf("%d",&state);
        if(state == NOTHING) break;
        else if(state == CONTINUE){
            fclose(fnum);
            fnum = fopen("number.txt","w");
            fprintf(fnum,"%d",0);
            count = 0;
        }
        else if(state == BREAK) return 0;
        else printf("\nyour input is not 1 or 2.\n"
        "please try again.\n\n");
    }
    setbuf(stdin,NULL); // clear input buffer 
    while(1){
        printf("input the command: ");
        fgets(command,LEN,stdin);
        if(!strcmp(command,"help\n")){
            printf("\nhelp: list all the command that can be used.\n"
            "order: into ordering-food system\n"
            "delete: input the number of order you want to delete.\n"
            "exit: exit the program.\n\n");
        } else if(!strcmp(command,"order\n")){
            while(1){
                printf("input the meal code: ");
                fgets(str,LEN,stdin);
                str[strlen(str)-1] = '\0';
                if(!strlen(str)) {
                    printf("\nempty meal codes!\n"
                    "please try again.\n\n");
                    continue;
                }
                state = check_meal_code(str);
                if(state == BREAK) break;
                else if(state == CONTINUE) continue;
                // sort the meal code and count the total price
                // store the meal codes to the list
                qsort(str,strlen(str),sizeof(char),cmp);
                if(list == NULL){ // if it's first order
                    list = malloc(sizeof(list_t)+strlen(str)+1);
                    list->prior = list->next = NULL;
                } else{
                    list->next = malloc(sizeof(list_t)+strlen(str)+1);
                    prior = list;
                    list = list->next;
                    list->prior = prior;
                    list->next = NULL;
                }
                list->number = ++count;
                strcpy(list->meal,str);
                list->price = count_price(str);
                fprintf(frecord,
                "number: %d\n"
                "meal: %s",list->number,menu[list->meal[0]-'a'].name);
                for(int j = 1; j < strlen(list->meal); j++) fprintf(frecord," %s",menu[list->meal[j]-'a'].name);
                fprintf(frecord,
                "\nprice: %.2lf\n"
                "----------\n",list->price);
            }
        } else if(!strcmp(command,"delete\n")){
            int number;
            while(1){
                printf("delete the number of order: ");
                fgets(str,LEN,stdin);
                str[strlen(str)-1] = '\0';
                if(!isnumber(str)){
                    printf("\nwrong, it is not a digit.\n\n");
                    continue;
                } else{
                    number = atoi(str);
                    printf("detele number %d order\n",number);
                    if(delete(&list,number)) break;
                }
            }
            printf("success to delete.\n");
            fclose(frecord);
            del_record(number);
            frecord = fopen(RECORD_NAME,"a+");
        } else if(!strcmp(command,"exit\n")){
            printf("close the program.\n");
            break;
        } else{
            printf("\n----------\n"
            "wrong command.\n"
            "please try again.\n"
            "----------\n\n");
        }
    }
    fclose(fnum);
    fnum = fopen("number.txt","w");
    fprintf(fnum,"%d",count);
    fclose(fnum);
    fclose(frecord);
    #if DEBUG // check all order in the list
    if(list != NULL){
        puts("----------------");
        ptr = list;
        while(ptr->prior != NULL) ptr = ptr->prior;
        for(; ptr != NULL; ptr = ptr->next){
            printf(
            "num: %d\n"
            "meal code: %s\n",ptr->number,ptr->meal);
            printf("meal name: %s",menu[ptr->meal[0]-'a'].name);
            for(int j = 1; j < strlen(ptr->meal); j++) printf(" %s",menu[ptr->meal[j]-'a'].name);
            printf(
            "\nprice: %.2lf\n"
            "----------------\n",ptr->price);
        }
    }
    #endif
    free_list(list);
    free_menu();
}
enum state_t check_meal_code(char str[]){
    int wrong = 0, len = strlen(str);
    // wrong: whether str contains space or wrong alphabat
    if(!strcmp(str,"0")){ // if the code is 0, break the while loop
        printf("stop input\n");
        return BREAK; // break while loop
    }
    for(int i = 0; i < len; i++){
        if(str[i] == ' '){
            printf("wrong: meal codes can't contain any space.\n");
            wrong = 1;
            break;
        }
    }
    for(int i = 0; i < len; i++){
        if('a' > str[i] || str[i] > 'z'){
            printf("wrong: meal codes only can contain alphabat from a to z.\n");
            wrong = 1;
            break;
        }
    }
    if(wrong) return CONTINUE; // if wrong alphabat or space, return
    for(int i = 0; i < len; i++){
        if(str[i]-'a' >= foodnum){
            printf("wrong: meal code at %d doesn't exist.\n",i+1);
            return CONTINUE;
        }
    }
    return NOTHING;
}
// void free_list(list_t *ptr){
//     list_t *priptr;
//     while(ptr != NULL){
//         priptr = ptr;
//         ptr = ptr->next;
//         free(priptr);
//     }
// }
int cmp(const void *a, const void *b){
    return (*(char*)a - *(char*)b);
}
int delete(list_t **list, int number){
    list_t *priptr, *nextptr, *ptr = *list;
    while(ptr != NULL){
        if(ptr->number == number){
            if(ptr->prior == NULL && ptr->next == NULL){
                *list = NULL;
            } else if(ptr->prior == NULL){
                ptr->next->prior = NULL;
            } else if(ptr->next == NULL){
                ptr->prior->next = NULL;
            } else{
                ptr->prior->next = ptr->next;
                ptr->next->prior = ptr->prior;
            }
            free(ptr);
            return 1;
        }
        ptr = ptr->prior;
    }
    printf("wrong, can't found %d order.\n",number);
    return 0;
}
void del_record(int number){
    char target[20], str[200];
    sprintf(target,"number: %d\n",number);
    FILE *fin = fopen(RECORD_NAME,"r");
    FILE *fout = fopen(RECORD_NAME_TEMP,"w");
    if(fin == NULL || fout == NULL){
        printf("fail to open the file at del_record().\n");
        return;
    }
    while(fgets(str,199,fin) != NULL){
        if(strncmp(str,target,20)) fprintf(fout,"%s",str);
        else break;
    }
    for(int i = 0; i < 3; i++) fgets(str,199,fin);
    while(fgets(str,199,fin) != NULL){
        fprintf(fout,"%s",str);
    }
    fclose(fin);
    fclose(fout);
    remove(RECORD_NAME);
    rename(RECORD_NAME_TEMP,RECORD_NAME);
}
int isnumber(char str[]){
    for(int i = 0; i < strlen(str); i++)
        if(!('0' <= str[i] && str[i] <= '9'))
            return 0;
    return 1;
}