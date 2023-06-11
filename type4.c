#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define MAXLEN_WORD 20
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

/*global variables*/
string people[100];
struct node menu[NUM_MENU];
struct node* dish[100];

/*functions declare*/
void convert_letters(struct node* first, int num_dish);
void read_and_store_the_menu();
void read_order(int *num_people);
void make_order(int num_dish, int witch_people);
void output_1(struct node* now_dish);
void input_and_judge(struct node* now_dish, int* succeed);
void output_2(int succeed, struct node* now_dish, struct node* first, struct node* front_dish);
void delete_dish(struct node** first, struct node** now_dish, struct node** front_dish);
void store_data(struct node* first);

/*main*/
int main(){
    int num_people=0;

    read_and_store_the_menu();
    read_order(&num_people);

    for(int witch_people=0; witch_people<num_people; witch_people++)
    {
        int num_dish=strlen(people[witch_people].word);//一個人的訂單有幾樣菜要做

        make_order(num_dish, witch_people);
        struct node* first=dish[0];
        struct node* now_dish=first;
        struct node* front_dish=first;

        #if HARD
        convert_letters(first, num_dish);//變換大小寫
        #endif // HARD

        for(int i=0; i<num_dish; i++){
            int succeed=1;

            output_1(now_dish);
            input_and_judge(now_dish, &succeed);
            output_2(succeed, now_dish, first, front_dish);

            now_dish=now_dish->next;
            printf("\n");
        }

        store_data(first);

        /**迷宮**/
        printf("GO TO MAZE!!!!\n\n");
    }

    return 0;
}

/*functions*/
void read_and_store_the_menu()
{
    FILE *f_menu=fopen("menu.txt", "r");
    if (f_menu == NULL) {
	    printf("Can't open %s\n", "menu.txt");
	    exit;
    }

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
}

void read_order(int *num_people)
{
    //我先把只有寫上訂單編號的那個檔案叫order
    FILE* f_order=fopen("order.txt", "r");
    if (f_order == NULL) {
	    printf("Can't open %s\n", "order.txt");
	    exit;
    }

    char temp[100];
    while (fgets(temp, 100, f_order) != NULL) {
        strcpy(people[*num_people].word, temp);
        int len=strlen(people[*num_people].word);

        if(people[*num_people].word[len-1]=='\n'){
            people[*num_people].word[len-1]='\0';
        }
        (*num_people)++;
    }

    fclose(f_order);
}

void make_order(int num_dish, int witch_people)
{
    //malloc dish 的空間
    for(int i=0; i<num_dish; i++){
        dish[i]=malloc(sizeof(struct node));
        dish[i]->next=NULL;
    }

    //處理訂單
    for(int i=0; i<num_dish; i++){
        int tingyi=(int)(people[witch_people].word[i])-'a';

        for(int j=0; j<NUM_MENU; j++){
            if(tingyi==j){
                *(dish[i])=menu[j];
                dish[i]->next = dish[i+1];
            }
        }
    }
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

void output_1(struct node* now_dish)
{
    printf("Let cook %s !!\n", now_dish->name.word);
    printf("Type \"");
    printf("%s", now_dish->ingredient.word);
    printf("\" in 10 seconds\n");
    for(int i=3; i>=1; i--){//倒數計時3秒鐘
        printf("%d ",i);
        sleep(1);
    }
    printf("\nSTART!\n");
}

void input_and_judge(struct node* now_dish, int* succeed)
{

    clock_t start, end, gap;

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
        now_dish->ingredient.word[i]=tolower(now_dish->ingredient.word[i]);
    }
    #endif

    char* com1=input_ingredient;
    char* com2=now_dish->ingredient.word;
    int compare=strcmp(com1, com2);

    if(compare!=0) *succeed=2;//錯字
    else if(*succeed==1 && gap>10) *succeed=3;//超時
}

void output_2(int succeed, struct node* now_dish, struct node* first, struct node* front_dish)
{
    switch(succeed){
    case 1:
        printf("Congratulation! You have successfully cooked %s\n", now_dish->name.word);
        now_dish=now_dish->next;
        break;

    case 2:
        printf("Sorry,You put wrong ingredient in %s, "
                "you fail to cook this dish :(\n", now_dish->name.word);
        //delete this dish from linked list
        delete_dish(&first, &now_dish, &front_dish);
        break;

    case 3:
        printf("You cooked too slowly! %s was on fire!!\n", now_dish->name.word);
        //delete this dish from linked list
        delete_dish(&first, &now_dish, &front_dish);
        break;
    }
}

void delete_dish(struct node** first, struct node** now_dish, struct node** front_dish)
{
    if(*now_dish==*first){
        *first=(*first)->next;
        free(*now_dish);
        *now_dish=*first;
        *front_dish=*first;
    }

    else{
        (*front_dish)->next=(*now_dish)->next;
        free(*now_dish);
        *now_dish=(*front_dish)->next;
    }
}

void store_data(struct node* first)
{
    FILE* f_cook=fopen("cook.txt", "w");

    struct node* temp;
    while(first!=NULL){
        temp=first;
        //printf("%d", first->menu_code);
        fprintf(f_cook, "%d", first->menu_code);
        first=first->next;
        free(temp);
    }

    fclose(f_cook);
}
