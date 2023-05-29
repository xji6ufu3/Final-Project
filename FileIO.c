#include "FileIO.h"
#include <stdio.h>
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