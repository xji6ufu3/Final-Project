#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

#define ROWS 19 //邊長
#define COLS 19
#define TIME 30 //遊戲時間秒數

struct node{
    int x;
    int y;
    struct node *next;
    struct node *prior;
};

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
                maze[list->x][list->y] = '$';
            count++;

            list = list->prior;//若是死路的話，往前一格
            pop_back(tail);

            if(list->x == 1 && list->y == 1)//如果回到原點，迷宮即生成
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
}
void player(char maze[ROWS][COLS], int *x, int *y, int *possible_ending, int *found_money){//玩家部分
    int num = rand() % 3 + 1; //命運機會的隨機數
    int ch;
    ch=getch();
    switch(ch){
        case 0xE0:
            switch(ch=getch()){
                case 72: //上
                    if(maze[*x-1][*y] == '#'){//若到達終點，遊戲結束
                        *possible_ending = 1;
                        *x -= 1;
                    }
                    else if(maze[*x-1][*y] == '$'){//若遇到機會卡的話
                        chance_card(num, possible_ending, found_money);
                        maze[*x][*y] = '.';
                        *x -= 1;
                        maze[*x][*y] = '*';
                    }
                    else if(maze[*x-1][*y] == 'O')//如果是死路的話，地圖不變
                        printf("This is a dead end!\n");
                    else{//往上走
                        maze[*x][*y] = '.';
                        *x -= 1;
                        maze[*x][*y] = '*';
                    }
                    break;
                case 80:  //下
                    if(maze[*x+1][*y] == '#'){//若到達終點，遊戲結束
                        *possible_ending = 1;
                        *x += 1;
                    }
                    else if(maze[*x+1][*y] == '$'){//若遇到機會卡的話
                        chance_card(num, possible_ending, found_money);
                        maze[*x][*y] = '.';
                        *x += 1;
                        maze[*x][*y] = '*';
                    }
                    else if(maze[*x+1][*y] == 'O')
                        printf("This is a dead end!\n");
                    else{
                        maze[*x][*y] = '.';
                        *x += 1;
                        maze[*x][*y] = '*';
                    }
                    break;
                case 75:  //左
                    if(maze[*x][*y-1] == '#'){//若到達終點，遊戲結束
                        *possible_ending = 1;
                        *y -= 1;
                    }
                    else if(maze[*x][*y-1] == '$'){//若遇到機會卡的話
                        chance_card(num, possible_ending, found_money);
                        maze[*x][*y] = '.';
                        *y -= 1;
                        maze[*x][*y] = '*';
                    }
                    else if(maze[*x][*y-1] == 'O')
                        printf("This is a dead end!\n");
                    else{
                        maze[*x][*y] = '.';
                        *y -= 1;
                        maze[*x][*y] = '*';
                    }
                    break;
                case 77:  //右
                    if(maze[*x][*y+1] == '#'){//若到達終點，遊戲結束
                        *possible_ending = 1;
                        *y += 1;
                    }
                    else if(maze[*x][*y+1] == '$'){//若遇到機會卡的話
                        chance_card(num, possible_ending, found_money);
                        maze[*x][*y] = '.';
                        *y += 1;
                        maze[*x][*y] = '*';
                    }
                    else if(maze[*x][*y+1] == 'O')
                        printf("This is a dead end!\n");
                    else{
                        maze[*x][*y] = '.';
                        *y += 1;
                        maze[*x][*y] = '*';
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

int main(){
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
    maze[1][1] = '*';
    maze[ROWS-2][COLS-2] = '#';//終點

    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLS; j++){
            if(maze[i][j] == '1'){
                maze[i][j] = 'O';//把死路換成O
            }
            else if(maze[i][j] == '2'){
                maze[i][j] = '.';//把活路換成.
            }
        }
    }

    for(int i=0; i<ROWS; i++){//印出地圖
        for(int j=0; j<COLS; j++){
            if(j == COLS-1)
                printf("%c\n", maze[i][j]);
            else    
                printf("%c", maze[i][j]);
        }   
    }

    //遊戲開始
    printf("You only have %d seconds!\n", TIME);
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

}