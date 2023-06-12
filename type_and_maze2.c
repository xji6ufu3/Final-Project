#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <conio.h>

#define NUM_MENU 20

#define ROWS 19 //邊長
#define COLS 19
#define TIME 30 //遊戲時間秒數

#define DEBUG 1
#define SPACE '0'
#define WALL '1'
#define PLAYER '2'
#define CHANCE '3'
#define DOOR '4'

typedef struct{
    char word[100];
}string;

struct node_ty{
    int menu_code;
    string name;
    float price;
    int time;
    int num_ingredient;
    string ingredient;
    struct node_ty* next;
};

struct node{
    int x;
    int y;
    struct node *next;
    struct node *prior;
};

/*global variables*/
string people[100];
struct node_ty menu[NUM_MENU];
struct node_ty* dish[100];

/*functions declare*/
//type
void convert_letters(struct node_ty* first, int num_dish);//轉換食材字母大小寫(for 困難模式)
void read_and_store_the_menu();//存取菜單
void read_order(int *num_people);//讀取訂單
void ask_hard_mode(int* hard);//是否挑戰困難模式
void make_order(int num_dish, int witch_people);//製作訂單
void output_1(struct node_ty* now_dish, int limit_time);//叫他要幹嘛的輸出
void input_and_judge(struct node_ty* now_dish, int* succeed, int hard, int limit_time);//輸入並判斷結果
void output_2(int succeed, struct node_ty* now_dish, struct node_ty* first, struct node_ty* front_dish);//輸出結果
void delete_dish(struct node_ty** first, struct node_ty** now_dish, struct node_ty** front_dish);//如果做錯菜要把菜丟掉
void calculate_money(struct node_ty* first, float* month_earn, int possible_ending, int found_money, int hard);//算錢
void store_data(float month_earn, int total_dish);//把這個月賺的錢存到file裡
//maze
void add_to_list(struct node *tail, int x, int y);//新增走過哪些路
void pop_back(struct node *tail);//刪掉死路
void direction(char maze[ROWS][COLS], struct node *list, struct node *tail, int count);//創造地圖
void chance_card(int num, int *possible_ending, int *found_money);//機會命運可能的結果
void player(char maze[ROWS][COLS], int *x, int *y, int *possible_ending, int *found_money);//玩家部分
void printf_Maze(char maze[ROWS][COLS]);//印玩家走後的地圖
void countdown(int seconds);//時間倒數
void whether_continue();//要繼續嗎?


/*main*/
int main(){
    int num_people=0;
    int hard=0;//困難模式 成功的話最後錢會2倍
    float month_earn=0;
    int total_dish

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
	    int limit_time;
	    limit_time=(now_dish->num_ingredient)*3;
	    if(hard) limit_time+=now_dish->num_ingredient;

            output_1(now_dish, limit_time);
            input_and_judge(now_dish, &succeed, hard, limit_time);
            output_2(succeed, now_dish, first, front_dish);

            now_dish=now_dish->next;
            printf("\n");
        }

    /**迷宮**/
        printf("It's time to deliver !!!!\n\n");

        time_t startTime, endTime;
        int seconds;//秒數
        int possible_ending = 2;//送成功或失敗的變數
        int found_money = 0;//若在機會卡中撿到錢，則變數變1

        int x = 1, y = 1;//角色的位置，從(1,1)開始走
        char maze[ROWS][COLS];
        int count = 1;

        srand( time(0) );//亂數生成

        struct node *head = (struct node*)malloc(sizeof(struct node));
        struct node *tail = (struct node*)malloc(sizeof(struct node));
        head->prior = NULL;
        head->next = tail;
        tail->prior = head;
        tail->next = NULL;

        add_to_list(tail, 1, 1);// 從(1,1)開始
        struct node *list = head->next;

        for(int i=0; i<ROWS; i++){//生成原始地圖
            for(int j=0; j<COLS; j++){
                if(i==0 || i==ROWS-1 || j==0 || j==COLS-1 || i%2==0 || j%2==0)
                    maze[i][j] = '1';
                else
                    maze[i][j] = '0';
            }
        }

        direction(maze, list, tail, count);//創建隨機地圖
        maze[ROWS-2][COLS-2] = DOOR;//終點

        for(int i=0; i<ROWS; i++){
            for(int j=0; j<COLS; j++){
                if(maze[i][j] == '1'){
                    maze[i][j] = WALL;//把死路換成O
                }
                else if(maze[i][j] == '2'){
                    maze[i][j] = SPACE;//把活路換成.
                }
            }
        }
        maze[1][1] = PLAYER;

        for(int i=0; i<ROWS; i++){//印出地圖
            for(int j=0; j<COLS; j++){
                if(j == COLS-1)
                    printf("%c\n", maze[i][j]);
                else
                    printf("%c", maze[i][j]);
            }
        }

        //遊戲開始
        printf("You only have %d seconds!\nUse the arrow key on the keyboard.\n", TIME);
        for(int i=3; i>=1; i--){//倒數計時3秒鐘
            printf("%d\n",i);
            sleep(1);
        }
        printf("START!\n");
        time(&startTime);
        while(1){
            player(maze, &x, &y, &possible_ending, &found_money);
            if(possible_ending == 1 || possible_ending == 0){
                break;
            }
            printf_Maze(maze);
            time(&endTime);
            if(difftime(endTime, startTime) >= TIME){//若遊玩時間大於30秒，遊戲停止
                printf("Time is up!");
                possible_ending = 0;//沒有完成遊戲
                break;
            }
        }
        //迷宮結束
        calculate_money(first, &month_earn, possible_ending, found_money, hard);

    }
    store_data(month_earn, total_dish);
    whether_continue();
	
    return 0;
}

/*functions for type*/
void read_and_store_the_menu(){
    
    FILE *f_menu=fopen("menu.txt", "r");
    if (f_menu == NULL) {
	    printf("Can't open %s\n", "menu.txt");
	    exit;
    }

    for(int i=0; i<NUM_MENU; i++){
        // fscanf(f_menu, "%d %s %f %d %d %s",
        //     &menu[i].menu_code, menu[i].name.word, &menu[i].price, &menu[i].time, &menu[i].num_ingredient, menu[i].ingredient.word);
        char str[200], *p;
        fgets(str,200,f_menu);
        strtok(str," \n");
        menu[i].menu_code = i+1;
        strcpy(menu[i].name.word,strtok(NULL," \n"));
        menu[i].price = atof(strtok(NULL," \n"));
        menu[i].time = atoi(strtok(NULL," \n"));
        strcpy(menu[i].ingredient.word,strtok(NULL," \n"));
        int len=strlen(menu[i].ingredient.word);
        menu[i].num_ingredient = 1;
        for(int j=0; j<len; j++){
            if(menu[i].ingredient.word[j]==','){
                menu[i].ingredient.word[j]=' ';
                menu[i].num_ingredient++;
            }
        }
        #if DEBUG
        printf( "%d %s %f %d %d %s\n",
            menu[i].menu_code, menu[i].name.word, menu[i].price, menu[i].time, menu[i].num_ingredient, menu[i].ingredient.word);
        #endif
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

void output_1(struct node_ty* now_dish, int limit_time)
{
    printf("Let cook %s !!\n", now_dish->name.word);
    printf("Type \"");
    printf("%s", now_dish->ingredient.word);
    printf("\" in %d seconds\n", limit_time);
    for(int i=3; i>=1; i--){//倒數計時3秒鐘
        printf("%d ",i);
        sleep(1);
    }
    printf("\nSTART!\n");
}

void input_and_judge(struct node_ty* now_dish, int* succeed, int hard, int limit_time)
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
    else if(*succeed==1 && gap>limit_time) *succeed=3;//超時
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
        //printf("%.2f ", money);
        first=temp->next;
        free(temp);
    }
    //printf("\nbefore=%.2f\n", month_earn);

    //再處理加成
    //printf("possible_ending=%d found_money=%d hard=%d\n", possible_ending, found_money, hard);

    if(possible_ending) money*=1.1;
    else money/=2;

    if(found_money) money+=10;
    if(hard) money*=2;

    //加進這個月的總金額裡
    *(month_earn)+=money;
    //printf("after=%.2f", *month_earn);
}

void store_data(float month_earn, int total_dish)
{
    FILE* f_after_game=fopen("after_game.txt", "w");
    fprintf(f_after_game, "%.2f %d", month_earn, total_dish);

    fclose(f_after_game);
}

/*functions for maze*/
void add_to_list(struct node *tail, int x, int y){//新增走過哪些路
    struct node *pre_node = tail->prior; //找到目前最後節點

    struct node *new_node = malloc(sizeof(struct node)); //分配新節點
    new_node->x = x;
    new_node->y = y;

    //連接起來
    pre_node->next = new_node;
    new_node->prior = pre_node;

    new_node->next = tail;
    tail->prior = new_node;

    return;
}

void pop_back(struct node *tail){//刪掉死路
    struct node *del_node = tail->prior;
    struct node *pre_node = del_node->prior;

    pre_node->next = tail;
    tail->prior = pre_node;

    free(del_node);
    return;
}

void direction(char maze[ROWS][COLS], struct node *list, struct node *tail, int count){//創造地圖
    while(1){

        int num = rand() % 4 + 1;

        //死路
        if(maze[list->x + 2][list->y] != '0' && maze[list->x - 2][list->y] != '0' && maze[list->x][list->y + 2] != '0' && maze[list->x][list->y - 2] != '0'){
            if(count == 1)//在第一個死路設置命運機會,可能是加錢、被狗追、直接到終點...
                maze[list->x][list->y] = CHANCE;
            count++;

            list = list->prior;//若是死路的話，往前一格
            pop_back(tail);

            if(list->x == 1 && list->y == 1)//如果回到原點，迷宮即生成完畢
                return;

            continue;
        }

        if(num == 1 && maze[list->x - 2][list->y] == '0'){//上
            maze[list->x - 1][list->y] = '2';
            maze[list->x - 2][list->y] = '2';
            add_to_list(tail, (list->x) - 2, list->y);
            list = list->next;
        }
        else if(num == 2 && maze[list->x + 2][list->y] == '0'){//下
            maze[list->x + 1][list->y] = '2';
            maze[list->x + 2][list->y] = '2';
            add_to_list(tail, (list->x) + 2, list->y);
            list = list->next;
        }
        else if(num == 3 && maze[list->x][list->y - 2] == '0'){//左
            maze[list->x][list->y - 1] = '2';
            maze[list->x][list->y - 2] = '2';
            add_to_list(tail, list->x, (list->y) - 2);
            list = list->next;
        }
        else if(num == 4 && maze[list->x][list->y + 2] == '0'){//右
            maze[list->x][list->y + 1] = '2';
            maze[list->x][list->y + 2] = '2';
            add_to_list(tail, list->x, (list->y) + 2);
            list = list->next;
        }
    }
}

void chance_card(int num, int *possible_ending, int *found_money){//機會命運可能的結果
    if(num == 1){
        *found_money = 1;
        printf("You picked up 10 dollars!\n");
    }
    else if(num == 2){
        *possible_ending = 0;
        printf("The order failed because you were chased by a dog!\n");
        return;
    }
    else if(num == 3){
        *possible_ending = 1;
        printf("You coincidentally met the customer on the way, so the order is completed!\n");
        return;
    }
    printf("\n");
}

void player(char maze[ROWS][COLS], int *x, int *y, int *possible_ending, int *found_money){//玩家部分
    int num = rand() % 3 + 1; //命運機會的隨機數
    int ch;
    ch=getch();
    switch(ch){
        case 0xE0:
            switch(ch=getch()){
                case 72: //上
                    if(maze[*x-1][*y] == DOOR){//若到達終點，遊戲結束
                        *possible_ending = 1;
                        *x -= 1;
                    }
                    else if(maze[*x-1][*y] == CHANCE){//若遇到機會卡的話
                        chance_card(num, possible_ending, found_money);
                        maze[*x][*y] = SPACE;
                        *x -= 1;
                        maze[*x][*y] = PLAYER;
                    }
                    else if(maze[*x-1][*y] == WALL)//如果是死路的話，地圖不變
                        printf("This is a dead end!\n");
                    else{//往上走
                        maze[*x][*y] = SPACE;
                        *x -= 1;
                        maze[*x][*y] = PLAYER;
                    }
                    break;
                case 80:  //下
                    if(maze[*x+1][*y] == DOOR){//若到達終點，遊戲結束
                        *possible_ending = 1;
                        *x += 1;
                    }
                    else if(maze[*x+1][*y] == CHANCE){//若遇到機會卡的話
                        chance_card(num, possible_ending, found_money);
                        maze[*x][*y] = SPACE;
                        *x += 1;
                        maze[*x][*y] = PLAYER;
                    }
                    else if(maze[*x+1][*y] == WALL)
                        printf("This is a dead end!\n");
                    else{
                        maze[*x][*y] = SPACE;
                        *x += 1;
                        maze[*x][*y] = PLAYER;
                    }
                    break;
                case 75:  //左
                    if(maze[*x][*y-1] == DOOR){//若到達終點，遊戲結束
                        *possible_ending = 1;
                        *y -= 1;
                    }
                    else if(maze[*x][*y-1] == CHANCE){//若遇到機會卡的話
                        chance_card(num, possible_ending, found_money);
                        maze[*x][*y] = SPACE;
                        *y -= 1;
                        maze[*x][*y] = PLAYER;
                    }
                    else if(maze[*x][*y-1] == WALL)
                        printf("This is a dead end!\n");
                    else{
                        maze[*x][*y] = SPACE;
                        *y -= 1;
                        maze[*x][*y] = PLAYER;
                    }
                    break;
                case 77:  //右
                    if(maze[*x][*y+1] == DOOR){//若到達終點，遊戲結束
                        *possible_ending = 1;
                        *y += 1;
                    }
                    else if(maze[*x][*y+1] == CHANCE){//若遇到機會卡的話
                        chance_card(num, possible_ending, found_money);
                        maze[*x][*y] = SPACE;
                        *y += 1;
                        maze[*x][*y] = PLAYER;
                    }
                    else if(maze[*x][*y+1] == WALL)
                        printf("This is a dead end!\n");
                    else{
                        maze[*x][*y] = SPACE;
                        *y += 1;
                        maze[*x][*y] = PLAYER;
                    }
                    break;
            }
            break;
    }
}

void printf_Maze(char maze[ROWS][COLS]){//印玩家走後的地圖
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLS; j++){
            if(j == COLS-1)
                printf("%c\n", maze[i][j]);
            else
                printf("%c", maze[i][j]);
        }
    }
}

void countdown(int seconds) {//時間倒數
    while (seconds > 0) {
        sleep(1);
        seconds--;
    }
    exit(0);
}

void whether_continue()
{
    char choose[3];
    //int choose;

    while(1){
        printf("Do you want to continue ????\n");
        printf("Y/N:");
        fgets(choose, 3, stdin);

        choose[2]='\0';
        choose[0]=tolower(choose[0]);

        if(choose[0]=='y'){
            system("start cmd.exe /K front.exe");
            break;
        }
        else if(choose[0]=='n'){
            system("start cmd.exe /K bigbigstage.exe");
            break;
        }
        else{
            printf("invalid input !!!!\n");
        }
    }
}
