#include "FileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "count.h"
void free_list(list_t *ptr){
    list_t *priptr;
    while(ptr != NULL){
        priptr = ptr;
        ptr = ptr->next;
        free(priptr);
    }
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
int delete(list_t **list, int number){
    list_t *priptr, *nextptr, *ptr = *list;
    if(number <= 0 || ptr == NULL){
        puts("end delete()");
        return 1;
    }
    while(ptr->next != NULL) ptr = ptr->next;
    while(ptr != NULL){
        if(ptr->number == number){
            if(ptr->prior == NULL && ptr->next == NULL){
                *list = NULL;
            } else if(ptr->prior == NULL){
                (ptr->next)->prior = NULL;
                *list = ptr->next;
            } else if(ptr->next == NULL){
                (ptr->prior)->next = NULL;
                *list = ptr->prior;
            } else{
                ptr->prior->next = ptr->next;
                ptr->next->prior = ptr->prior;
            }
            free(ptr);
            del_record(number);
            return 1;
        }
        ptr = ptr->prior;
    }
    printf("wrong, can't found %d order.\n",number);
    return 0;
}
void traverse(list_t *list){
    if(list == NULL){
        puts("there is not any order.");
        return;
    }
    puts("----------------");
    while(list != NULL) list = list->prior;
    while(list != NULL){
        printf(
            "num: %d\n"
            "meal code: %s\n",list->number,list->meal);
            printf("meal name: %s",menu[list->meal[0]-'a'].name);
            for(int j = 1; j < strlen(list->meal); j++) printf(" %s",menu[list->meal[j]-'a'].name);
            printf(
            "\nprice: %.2lf\n"
            "----------------\n",list->price);
    }
}