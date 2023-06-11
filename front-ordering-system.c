#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "count.h"
#include "FileIO.h"
#define LEN 26
#define DEBUG 0
extern int foodnum; // the number of food in the menu
enum state_t{NOTHING,CONTINUE,BREAK};
enum state_t check_meal_code(char str[]);
int cmp(const void *a, const void *b);
int main(){
    int count; // count store the sum of order
    char str[LEN+1], record[36], command[10];
    enum state_t state;
    list_t *list = NULL, *ptr, *prior;
    FILE *frecord = fopen(RECORD_NAME,"a+");
    FILE *fnum = fopen("number.txt","r");
    FILE *fmenu = fopen("menu.txt","r");
    FILE *forder = fopen("order.txt","w");
    initialMenu(fmenu);
    #if DEBUG
        printMenu();
    #endif
    fclose(fmenu);
    fscanf(fnum,"%d",&count);
    if(count){
        printf("the number in number.txt is not 0.\n"
            "scan command below to continue.\n"
            "0: just continue.\n"
            "1: initialize the number.txt\n"
            "2: exit the program.\n");
        while(1){
            printf("command: ");
            scanf("%1d",&state);
            if(state == NOTHING) break;
            else if(state == CONTINUE){
                fclose(fnum);
                fnum = fopen("number.txt","w");
                fprintf(fnum,"%d",0);
                count = 0;
                break;
            }
            else if(state == BREAK) return 0;
            else printf("\nyour input is not 1 or 2.\n"
            "please try again.\n\n");
        }
    }
    if(fgetc(frecord) != EOF){
        printf("the recording.txt is not empty.\n"
        "scan command below to continue.\n"
        "0: just continue.\n"
        "1: initialize the recording.txt\n"
        "2: exit the program.\n");
        while(1){
            printf("command: ");
            scanf("%1d",&state);
            if(state == NOTHING) break;
            else if(state == CONTINUE){
                fclose(frecord);
                frecord = fopen(RECORD_NAME,"w");
                break;
            }
            else if(state == BREAK) return 0;
            else printf("\nyour input is not 1 or 2.\n"
            "please try again.\n\n");
        }
    }
    setbuf(stdin,NULL); // clear input buffer 
    while(1){
        printf("input the command: ");
        fgets(command,LEN,stdin);
        if(!strcmp(command,"help\n")){
            printf("\nhelp: list all the command that can be used.\n"
            "order: into ordering-food system\n"
            "delete: input the number of order you want to delete.\n"
            "traverse: print all orders.\n"
            "search: input the number of order, print the order detail.\n"
            "sort: sort the order of order with number, price, or waiting time.\n"
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
                    while(list->next != NULL) list = list->next;
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
                puts("----------------");
                fprintf(forder,"%s\n",list->meal);
                print_order(list);
            }
        } else if(!strcmp(command,"delete\n")){
            int number;
            while(1){
                printf("delete the number of order (exit 0): ");
                fgets(str,LEN,stdin);
                str[strlen(str)-1] = '\0';
                if(!isnumber(str)){
                    printf("\nwrong, it is not a digit.\n\n");
                    continue;
                } else{
                    number = atoi(str);
                    fclose(frecord);
                    if(delete(&list,number)) break;
                    frecord = fopen(RECORD_NAME,"a+");
                }
            }
            fclose(frecord);
            // del_record(number);
            frecord = fopen(RECORD_NAME,"a+");
        } else if(!strcmp(command,"traverse\n")){
            traverse(list);
        } else if(!strcmp(command,"search\n")){
            while(1){
                printf("the number of order (exit 0): ");
                int number;
                fgets(str,LEN,stdin);
                str[strlen(str)-1] = '\0';
                if(!isnumber(str)){
                    printf("\nwrong, it is not a digit.\n\n");
                    continue;
                } else{
                    number = atoi(str);
                    if(search(list,number)) break;
                }
            }
        } else if(!strcmp(command,"sort\n")){
            char oper[10];
            while(1){
                printf("sort by what (number, price, exit): ");
                fgets(oper,9,stdin);
                oper[strlen(oper)-1] = '\0';
                if(!strcmp(oper,"number") || !strcmp(oper,"price") || !strcmp(oper,"exit"))
                    break;
                else printf("wrong, please try again.\n");
            }
            if(!strcmp(oper,"exit")) continue;
            fclose(frecord);
            list = sort(list,oper);
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
    fclose(forder);
    #if DEBUG // check all order in the list
    if(list != NULL){
        puts("----------------");
        ptr = list;
        while(ptr->prior != NULL) ptr = ptr->prior;
        for(; ptr != NULL; ptr = ptr->next){
            print_order(ptr);
        }
    }
    #endif
    free_list(list);
    free_menu();
    
    system("start cmd.exe /K type_and_maze2.exe");
    return 0;
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
int cmp(const void *a, const void *b){
    return (*(char*)a - *(char*)b);
}