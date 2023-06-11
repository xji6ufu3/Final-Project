#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define MAXLEN_WORD 20
#define NUM_MENU 20

//#define HARD 0 //困難模式:食材會變換大小寫且嚴格比對

typedef struct{
    char word[MAXLEN_WORD];
}string;

struct node_ty{
    int menu_code;
    string name;
    double price;
    int time;
    int num_ingredient;
    string ingredient;
    struct node_ty* next;
};

/*global variables*/
string people[100];
struct node_ty menu[NUM_MENU];
struct node_ty* dish[100];

/*functions declare*/
void convert_letters(struct node_ty* first, int num_dish);
void read_and_store_the_menu();
void read_order(int *num_people);
void ask_hard_mode(int* hard);
void make_order(int num_dish, int witch_people);
void output_1(struct node_ty* now_dish);
void input_and_judge(struct node_ty* now_dish, int* succeed, int hard);
void output_2(int succeed, struct node_ty* now_dish, struct node_ty* first, struct node_ty* front_dish);
void delete_dish(struct node_ty** first, struct node_ty** now_dish, struct node_ty** front_dish);
//void store_data(struct node_ty* first);

/*比上一個版本新增的函式*/
void calculate_money(struct node_ty* first, float* month_earn, int possible_ending, int found_money, int hard)
{
    //先把總金額結算好
    float money=0;
    struct node_ty* temp;
    while(first!=NULL){
        temp=first;
        //printf("%d", first->menu_code);
        //fprintf(f_cook, "%d", first->menu_code);
        money+=temp->price;
        printf("%f ", money);
        first=temp->next;
        free(temp);
    }
    printf("\nbefore=%f\n", *month_earn);

    //再處理加成
    printf("possible_ending=%d found_money=%d hard=%d\n", possible_ending, found_money, hard);

    if(possible_ending) money*=1.1;
    else money/=2;

    if(found_money) money+=10;
    if(hard) money*=2;

    //加進這個月的總金額裡
    *(month_earn)+=money;
    printf("after=%f", month_earn);
}

void store_data(float month_earn)
{
    FILE* f_after_game=fopen("after_game.txt", "w");
    fprintf(f_after_game, "%f", month_earn);

    fclose(f_after_game);
}


/*main*/
int main(){
    float month_earn=0;
    int num_people=0;
    int hard=0;

    read_and_store_the_menu();
    read_order(&num_people);

    ask_hard_mode(&hard);

    for(int witch_people=0; witch_people<num_people; witch_people++)
    {
        int num_dish=strlen(people[witch_people].word);//一個人的訂單有幾樣菜要做

        make_order(num_dish, witch_people);
        struct node_ty* first=dish[0];
        struct node_ty* now_dish=first;
        struct node_ty* front_dish=first;

        if(hard){
            convert_letters(first, num_dish);//變換大小寫
        }

        for(int i=0; i<num_dish; i++){
            int succeed=1;

            output_1(now_dish);
            input_and_judge(now_dish, &succeed, hard);
            output_2(succeed, now_dish, first, front_dish);

            now_dish=now_dish->next;
            printf("\n");
        }

        //store_data(month_earn);


        printf("GO TO MAZE!!!!\n\n");
        /**先假裝這裡有迷宮**/
        int possible_ending=1, found_money=0;
        calculate_money(first, &month_earn, possible_ending, found_money, hard);

    }
    store_data(month_earn);

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

void ask_hard_mode(int* hard)
{
    char choose[3];
    //int choose;

    while(1){
        printf("Play in HARD MODE ?\n");
        printf("Y/N:");
        fgets(choose, 3, stdin);

        choose[2]='\0';
        choose[0]=tolower(choose[0]);

        if(choose[0]=='y'){
            *hard=1;
            break;
        }
        else if(choose[0]=='n'){
            break;
        }
        else{
            printf("invalid input !!!!\n");
        }
    }

}

void make_order(int num_dish, int witch_people)
{
    //malloc dish 的空間
    for(int i=0; i<num_dish; i++){
        dish[i]=malloc(sizeof(struct node_ty));
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

void convert_letters(struct node_ty* first, int num_dish)
{
    struct node_ty* temp_dish=first;
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

void output_1(struct node_ty* now_dish)
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

void input_and_judge(struct node_ty* now_dish, int* succeed, int hard)
{

    clock_t start, end, gap;

    /*input*/
    start=clock();
    char input_ingredient[1000];
    //scanf(" ");
    fgets(input_ingredient, 1000, stdin);
    end=clock();

    //printf("%s", input_ingredient);

    /*judge whether succeed*/
    gap=(end-start)/CLOCKS_PER_SEC;
    int len=strlen(input_ingredient);
    input_ingredient[len-1]='\0';

    if(!hard){
        for(int i=0; i<strlen(input_ingredient); i++){
            input_ingredient[i]=tolower(input_ingredient[i]);
            now_dish->ingredient.word[i]=tolower(now_dish->ingredient.word[i]);
        }
    }

    char* com1=input_ingredient;
    char* com2=now_dish->ingredient.word;
    int compare=strcmp(com1, com2);

    if(compare!=0) *succeed=2;//錯字
    else if(*succeed==1 && gap>10) *succeed=3;//超時
}

void output_2(int succeed, struct node_ty* now_dish, struct node_ty* first, struct node_ty* front_dish)
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

void delete_dish(struct node_ty** first, struct node_ty** now_dish, struct node_ty** front_dish)
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

/*void store_data(struct node_ty* first)
{
    FILE* f_cook=fopen("cook.txt", "w");

    struct node_ty* temp;
    while(first!=NULL){
        temp=first;
        //printf("%d", first->menu_code);
        fprintf(f_cook, "%d", first->menu_code);
        first=first->next;
        free(temp);
    }

    fclose(f_cook);
}*/


