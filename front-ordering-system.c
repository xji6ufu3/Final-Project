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
enum state_t{NOTHING,CONTINUE,BREAK};
enum state_t check_meal_code(char str[]);
double price[LEN] = {1,2,3,4,5};
double count_price(char str[]);
char *meal_name[LEN] = {"salads","hamberger","soup","tea","ice cream"};
void free_list(list_t *ptr);
int cmp(const void *a, const void *b){
    return (*(char*)a - *(char*)b);
}
int main(){
    int count; // count store the sum of order
    char str[LEN+1], record[36];
    enum state_t state;
    list_t *list = NULL, *ptr, *prior; // the beginning of the list
    FILE *frecord = fopen("recording.txt","a+");
    FILE *fnum = fopen("number.txt","r");
    fscanf(fnum,"%d",&count);
    while(count){
        printf("the number in number.txt is not 0.\n"
        "scan command below to continue.\n"
        "1: initialize the number.txt\n"
        "2: exit the program.\n"
        "command: ");
        scanf("%d",&state);
        if(state == CONTINUE){
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
        if(count == 0){ // if it's first order
            list = malloc(sizeof(list_t)+strlen(str)+1);
            ptr = list;
            list->prior = list->next = NULL;
        }
        else{ // not first order
            ptr->next = malloc(sizeof(list_t)+strlen(str)+1);
            prior = ptr;
            ptr = ptr->next;
            ptr->prior = prior;
            ptr->next = NULL;
        }
        ptr->number = ++count;
        strcpy(ptr->meal,str);
        ptr->price = count_price(str);
    }
    fclose(fnum);
    fnum = fopen("number.txt","w");
    fprintf(fnum,"%d",count);
    fclose(fnum);
    fclose(frecord);
    #if DEBUG // check all order in the list
    ptr = list;
    for(int i = 0; i < count; i++){
        if(i == 0) puts("----------------");
        printf(
        "num: %d\n"
        "meal code: %s\n",ptr->number,ptr->meal);
        printf("meal name: %s",meal_name[ptr->meal[0]-'a']);
        for(int j = 1; j < strlen(ptr->meal); j++) printf(" %s",meal_name[ptr->meal[j]-'a']);
        printf(
        "\nprice: %.2lf\n"
        "----------------\n",ptr->price);
        ptr = ptr->next;
    }
    #endif
    free_list(list);
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
        if(meal_name[str[i]-'a'] == NULL){
            printf("wrong: meal code at %d doesn't exist.\n",i+1);
            return CONTINUE;
        }
    }
    return NOTHING;
}
double count_price(char str[]){
    double sum = 0;
    int len = strlen(str), j;
    for(int i = 0; i < len; i++){
        j = str[i] - 'a';
        sum += price[j];
    }
    // printf("sum: %d.\n",sum);
    return sum;
}
void free_list(list_t *ptr){
    list_t *priptr;
    while(ptr != NULL){
        priptr = ptr;
        ptr = ptr->next;
        free(priptr);
    }
}