#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define MAXLEN_WORD 20
#define MAX_INGREDIENT 10
#define MAX_DISH 5
#define NUM_MENU 20

#define HARD 0 //困難模式:食材會變換大小寫且嚴格比對

typedef struct{
    char word[MAXLEN_WORD];
}string;

struct node{
    int menu_code;
    string name;
    double price;
    int time;
    int num_ingredient;
    string ingredient;
    struct node* next;
};

int how_many_dish(struct node* first)
{
    if(first==NULL) return 0;
    int ans=0;
    while(first!=NULL){
        ans++;
        first=first->next;
    }
    return ans;
}

void convert_letters(struct node* first, int num_dish)
{
    struct node* temp_dish=first;
    srand(time(NULL));

    for(int i=0; i<num_dish; i++){

        int len=strlen(temp_dish->ingredient.word);
        for(int j=0; j<len; j++){
                int x=rand()%2;

                if(temp_dish->ingredient.word[j]!=' '){
                    if(x) temp_dish->ingredient.word[j]=toupper(temp_dish->ingredient.word[j]);
                    else temp_dish->ingredient.word[j]=tolower(temp_dish->ingredient.word[j]);
                }
        }
        temp_dish=temp_dish->next;
    }
}

int main(){

    /*讀取菜單並儲存*/
    FILE *f_menu=fopen("menu.txt", "r");
    if (f_menu == NULL) {
	    printf("Can't open %s\n", "menu.txt");
	    exit;
    }

    struct node menu[NUM_MENU];
    for(int i=0; i<NUM_MENU; i++){
        fscanf(f_menu, "%d %s %f %d %d %s",
            &menu[i].menu_code, menu[i].name.word, &menu[i].price, &menu[i].time, &menu[i].num_ingredient, menu[i].ingredient.word);

        int len=strlen(menu[i].ingredient.word);
        for(int j=0; j<len; j++){
            if(menu[i].ingredient.word[j]==','){
                menu[i].ingredient.word[j]=' ';
            }
        }
        menu[i].next=NULL;
    }
    fclose(f_menu);

    /*變出訂單*/
    struct node* dish[MAX_DISH];
    for(int i=0; i<MAX_DISH; i++){
        dish[i]=malloc(sizeof(struct node));
        dish[i]->next=NULL;
    }
    *(dish[0])=menu[3];
    *(dish[1])=menu[0];
    dish[0]->next=dish[1];

    /*讀取訂單並儲存*/
    FILE* f_order=fopen("order.txt", "r");

    /*start*/
    struct node* first=dish[0];
    int num_dish=how_many_dish(first);
    struct node* temp_dish=first;//暫存，紀錄位置用

    #if HARD
    convert_letters(first, num_dish);//變換大小寫
    #endif // HARD

    for(int i=0; i<num_dish; i++){
        //int num_ingredient=how_many_ingredient(temp_dish);
        int succeed=1;
        clock_t start, end, gap;

        /*output*/
        printf("Let cook %s !!\n", temp_dish->name.word);
        printf("Type \"");
        printf("%s", temp_dish->ingredient.word);
        printf("\" in 10 seconds\n");
        for(int i=3; i>=1; i--){//倒數計時3秒鐘
            printf("%d ",i);
            sleep(1);
        }
        printf("\nSTART!\n");

        /*input*/
        start=clock();
        char input_ingredient[1000];
        fgets(input_ingredient, 1000, stdin);
        end=clock();

        /*judge whether succeed*/
        gap=(end-start)/CLOCKS_PER_SEC;
        int len=strlen(input_ingredient);
        input_ingredient[len-1]='\0';

        #if !HARD
        for(int i=0; i<strlen(input_ingredient); i++){
            input_ingredient[i]=tolower(input_ingredient[i]);
            temp_dish->ingredient.word[i]=tolower(temp_dish->ingredient.word[i]);
        }
        #endif

        char* com1=input_ingredient;
        char* com2=temp_dish->ingredient.word;
        int compare=strcmp(com1, com2);

        if(compare!=0) succeed=2;//錯字
        else if(succeed==1 && gap>10) succeed=3;//超時

        /*output*/
        switch(succeed){
        case 1:
            printf("Congratulation! You have successfully cooked %s\n", temp_dish->name.word);
            break;

        case 2:
            printf("Sorry,You put wrong ingredient in %s"
                   "you fail to cook this dish :(\n", temp_dish->name.word);
            //delete this dish from linked list
            break;

        case 3:
            printf("You cooked too slowly! %s was on fire!!\n", temp_dish->name.word);
            //delete this dish from linked list
            break;
        }

        temp_dish=temp_dish->next;
        printf("\n");
    }

    return 0;
}
