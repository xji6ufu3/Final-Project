#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "history_record.h"

int num_func()
{
    int num, num_cur;
    FILE *f_count;
    f_count = fopen("counting.txt", "r");
    if (f_count == NULL)
    {
        printf("Failed to open the file.\n");
        return 0;
    }
    while (fscanf(f_count, "%d", &num) == 1)
        num_cur = num;

    fclose(f_count);
    return num;
}

//  紀錄當次金錢與時間
int record(float a, int b, char word[10]) // 錢, 幾道菜, 結局代碼(A or B or C)
{
    time_t current_time;
    struct tm *local_time;
    char time_str[100];

    current_time = time(NULL);             // 取得現在時間
    local_time = localtime(&current_time); // 轉換成本地時區
    strftime(time_str, sizeof(time_str), "%Y/%m/%d %H:%M:%S", local_time);

    FILE *f_record;
    f_record = fopen("record_input.txt", "a");

    if (f_record == NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }

    fprintf(f_record, "%s   Earn : $%05.1f    Dishes : %02d    Ending : %s\n", time_str, a, b, word);
    fclose(f_record);

    return 0;
}

//  顯示近期十筆紀錄
int history_show(int num) //  玩過幾次
{
    char line[10][100];

    FILE *f_show;
    f_show = fopen("record_input.txt", "r");

    if (f_show == NULL)
    {
        printf("Can't open the file.\n");
        exit;
    }

    fseek(f_show, 0, SEEK_END); // 定位到文件的最後

    if (num < 10)
    {
        for (int i = 0; i < num; i++)
        {
            fseek(f_show, (i + 1) * (-66), SEEK_CUR);
            fgets(line[i], sizeof(line[i]), f_show);
        }

        printf("===================  Here's your history records ===================\n\n");
        for (int i = 0; i < num; i++)
            printf("%d. %s", i, line[i]);
        printf("\n===================================================================\n");
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            fseek(f_show, (i + 1) * (-66), SEEK_CUR);
            fgets(line[i], sizeof(line[i]), f_show);
        }

        printf("===================  Here's your history records ===================\n\n");
        for (int i = 0; i < 10; i++)
            printf("%d. %s", i, line[i]);
        printf("\n===================================================================\n");
    }

    fclose(f_show);

    return 0;
}

//  要多設一個變數記錄玩過幾次 num
int restart(int num)
{
    int ans, a, b, choice; // 選項, 錢, 幾道菜, 選擇
    if (num > 0)
    {
        printf("[0]   Start a new game.\n");
        printf("[1]   Continue on previous record\n");
        scanf("%d", &ans);

        if (ans == 0)
        {
            a = 0; // 錢從0開始算
            b = 0; // 幾道菜從0開始算
            return 0;
        }
        else if (ans == 1)
        {
            history_show(num);
            printf("Choose a record that you want to continue with: ");
            scanf("%d", &choice);
            his_search(choice, num);
        }
    }
    else
        return 0;
}

//  用來儲存讀取歷史紀錄的變數，可能要另外放在主程式裡?
typedef struct
{
    int earn;
    int dishes;
} values;

// 讀取歷史紀錄  然後回傳earn跟dishes
int his_search(int choice, int num)
{
    values result;
    char timestamp[20];
    float earn;
    int dishes;

    int n = 0;
    char line[100];
    FILE *f_choice = fopen("record_input.txt", "r");
    fseek(f_choice, 0, SEEK_END); // 定位到文件的最後
    if (num < 10)
    {
        while (n < num - (choice + 1))
        {
            fseek(f_choice, -66, SEEK_CUR);
            fgets(line, sizeof(line), f_choice);
            n++;
        }
    }
    else
    {
        while (n < 10 - (choice + 1))
        {
            fseek(f_choice, -66, SEEK_CUR);
            fgets(line, sizeof(line), f_choice);
            n++;
        }
    }
    sscanf(line, "%s Earn : $%f Dishes : %d", timestamp, result.earn, result.dishes);
    fclose(f_choice);
    return 0;
    //  取值的部分要寫result.earn跟result.dishes
}

//  這個main是我拿來測試檔案亂設的變數，不要管它
int main()
{
    int b;
    int num;
    num = num_func();
    char word[10] = "a"; // 結局ABC
    for (int i = 1, j = 1; i < 5; i++, j++)
    {
        if (i == 10)
        {
            i -= 1;
            j -= 1;
            record(i, j, word);
            break;
        }
        record(i, j, word);
    }

    restart(num);
    return 0;
}

//  這整份應該是會放在整個程式的尾巴
//  幫我存一個txt檔，在每次結束的時候次數都加一，然後存數字進去
//  因為我要讀那個num，感謝，有問題再問我。