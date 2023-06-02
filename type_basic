#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN_WORD 20
#define MAX_INGREDIENT 10
#define MAX_ORDER 5

typedef struct{
    char word[MAXLEN_WORD];
}string;

struct node{
    string dish;
    string ingredient[MAX_INGREDIENT];
    int num_ingredient;
    int price;
    struct node* next;
};

/*確定該筆訂單(linked list)裡有幾道菜*/
int how_many_order(struct node* first){
    if(first==NULL) return 0;
    int ans=0;
    while(first!=NULL){
        ans++;
        first=first->next;
    }
    return ans;
}

int how_many_ingredient(struct node* temp_order){
    return temp_order->num_ingredient;
}

int main(){
    /*先隨便變個菜單*/
    struct node menu[]={
        {.dish.word="one", .ingredient={"tomato", "egg"}, .num_ingredient=2, .price=50, .next=NULL},
        {.dish.word="two", .ingredient={"banana"}, .num_ingredient=1, .price=30, .next=NULL}
    };

    /*變出訂單*/
    struct node* order[MAX_ORDER];
    for(int i=0; i<MAX_ORDER; i++){
        order[i]=malloc(sizeof(struct node));
        order[i]->next=NULL;
    }
    *(order[0])=menu[1];
    *(order[1])=menu[0];
    order[0]->next=order[1];

    /*start*/
    struct node* first=order[0];
    int num_order=how_many_order(first);
    struct node* temp_order=first;//暫存，紀錄位置用

    for(int i=0; i<num_order; i++){
        int num_ingredient=how_many_ingredient(temp_order);
        int succeed=1;
        clock_t start, end, gap;

        /*output*/
        printf("Let cook %s !!\n", temp_order->dish.word);
        printf("Type \" ");

        for(int i=0; i<num_ingredient; i++){
            printf("%s ", temp_order->ingredient[i].word);
        }
        printf("\" in 10 seconds\n");

        /*input*/
        start=clock();
        string input_ingredient[MAX_INGREDIENT];
        for(int i=0; i<num_ingredient; i++){
            scanf("%s", input_ingredient[i].word);
        }
        end=clock();

        /*judge whether succeed*/
        gap=(end-start)/CLOCKS_PER_SEC;
        //printf("%d", gap);
        for(int i=0; i<num_ingredient; i++){
            char* com1=input_ingredient[i].word;
            char* com2=temp_order->ingredient[i].word;
            int compare=strcmp(com1, com2);

            if(compare!=0) succeed=2;//錯字
        }
        if(succeed==1 && gap>10) succeed=3;//超時

        /*output*/
        switch(succeed){
        case 1:
            printf("Congratulation! You have successfully cooked %s\n", temp_order->dish.word);
            break;

        case 2:
            printf("Sorry,You put wrong ingredient in %s"
                   "you fail to cook this order :(\n", temp_order->dish.word);
            //delete this dish from linked list
            break;

        case 3:
            printf("You cooked too slowly! %s was on fire!!\n", temp_order->dish.word);
            //delete this dish from linked list
            break;
        }

        temp_order=temp_order->next;
        printf("\n");
    }

    return 0;
}
