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
    char target[20], str[200], str2[200];
    sprintf(target,"number: %d\n",number);
    FILE *fin = fopen(RECORD_NAME,"r");
    FILE *fout = fopen(RECORD_NAME_TEMP,"w");
    FILE *foin = fopen("order.txt","r");
    FILE *foout = fopen("order-temp.txt","w");
    if(fin == NULL || fout == NULL || foin == NULL || foout == NULL){
        printf("fail to open the file at del_record().\n");
        return;
    }
    int count = 0;
    while(fgets(str,199,fin) != NULL){
        if(strncmp(str,target,20)){
            fprintf(fout,"%s",str);
            if(count % 4 == 0){
                fgets(str2,199,foin);
                fprintf(foout,"%s",str2);
            }
        }
        else break;
        count++;
    }
    for(int i = 0; i < 3; i++) fgets(str,199,fin);
    fgets(str,199,foin);
    count = 0;
    while(fgets(str,199,fin) != NULL){
        fprintf(fout,"%s",str);
        if(count % 4 == 0){
            fgets(str2,199,foin);
            fprintf(foout,"%s",str2);
        }
        count++;
    }
    
    fclose(fin);
    fclose(fout);
    fclose(foin);
    fclose(foout);
    remove(RECORD_NAME);
    rename(RECORD_NAME_TEMP,RECORD_NAME);
    remove("order.txt");
    rename("order-temp.txt","order.txt");
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
            printf("detele number %d order\n",number);
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
    while(list->prior != NULL) list = list->prior;
    while(list != NULL){
        printf(
            "num: %d\n"
            "meal code: %s\n",list->number,list->meal);
            printf("meal name: %s",menu[list->meal[0]-'a'].name);
            for(int j = 1; j < strlen(list->meal); j++) printf(" %s",menu[list->meal[j]-'a'].name);
            printf(
            "\nprice: %.2lf\n"
            "----------------\n",list->price);
        list = list->next;
    }
}
list_t* sort(list_t* head, char oper[]){
    if(head == NULL){
        puts("the order is empty.");
        return NULL;
    }
    while(head->prior != NULL) head = head->prior;
    list_t *cur, *tmp, *tail = NULL;
    if(!strcmp(oper,"number")){
        while(head != tail){
            cur = head;
            while(cur->next != tail){
                if(cur->number > cur->next->number){
                    tmp = cur->next;
                    if(cur->prior != NULL) cur->prior->next = tmp;
                    tmp->prior = cur->prior;
                    cur->next = tmp->next;
                    if(cur->next != NULL) cur->next->prior = cur;
                    cur->prior = tmp;
                    tmp->next = cur;
                    if(cur == head) head = cur->prior;
                } else{
                    cur = cur->next;
                }
            }
            tail = cur;
        }
    }
    else if(!strcmp(oper,"price")){
        while(head != tail){
            cur = head;
            while(cur->next != tail){
                if(cur->price > cur->next->price){
                    tmp = cur->next;
                    if(cur->prior != NULL) cur->prior->next = tmp;
                    tmp->prior = cur->prior;
                    cur->next = tmp->next;
                    if(cur->next != NULL) cur->next->prior = cur;
                    cur->prior = tmp;
                    tmp->next = cur;
                    if(cur == head) head = cur->prior;
                } else{
                    cur = cur->next;
                }
            }
            tail = cur;
        }
    }
    FILE *frecord = fopen(RECORD_NAME,"w");
    while(tail != NULL){
        fprintf(frecord,
            "number: %d\n"
            "meal: %s",
            tail->number,menu[tail->meal[0]-'a'].name);
        for(int j = 1; j < strlen(tail->meal); j++)
            fprintf(frecord," %s",menu[tail->meal[j]-'a'].name);
        fprintf(frecord,
            "\nprice: %.2lf\n"
            "----------\n",
            tail->price);
        tail = tail->next;
    }
    fclose(frecord);
    return head;
}
int search(list_t *list, int number){
    if(list == NULL || number == 0){
        if(list == NULL) printf("the food order is empty.\n");
        else if(number == 0) puts("end search.");
        return 1;
    }
    list_t *ptr = list;
    while(ptr != NULL){
        if(ptr->number == number){
            puts("----------------");
            print_order(ptr);
            return 1;
        }
        ptr = ptr->prior;
    }
    ptr = list->next;
    while(ptr != NULL){
        if(ptr->number == number){
            puts("----------------");
            print_order(ptr);
            return 1;
        }
        ptr = ptr->next;
    }
    printf("not found %d order.\nplease try again.\n",number);
    return 0;
}