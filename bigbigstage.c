#include <stdio.h>
#include <stdlib.h>
#include "history_record.h"
int main()
{
    FILE *usd = f_open("after_game", "r");
    float quantity, usd_money;
    fscanf("usd", "%d %f", &quantity, &usd_money);
    char end[3];

    if (usd_money <= 0)
    {
        // 乞丐
        printf("YOU ARE A LOSER!\nHow did you lose all your money?\nThe restaurant has gone bankrupt! Game over!");
        end[0] = 'A';
    }
    else
    {
        // 兩個結局
        if (usd_money / quantity <= 10)
        {
            printf("wow!It seems like you're a skilled restaurant manager.\nCongratulations on earning the title of 'Street Chef Extraordinaire'!");
            end[0] = 'B';
        }
        else
        {
            printf("Oh my, you're truly a genius at running a restaurant! Congratulations on earning the title of 'Master Chef'!");
            end[0] = 'C';
        }
    }
    fclose(usd);
    record(usd_money, quantity, end);
    counting();
    return 0;
}