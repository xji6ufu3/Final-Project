#include <stdio.h>
#include <stdlib.h>
int main(){
    printf("Hello! This is a restaurant management game. First, customers will place their orders, and you'll need to prepare each dish. If you win the typing master challenge, it means you successfully prepared the dish and you'll earn money. If you lose, you won't earn any money. Each customer will also require a delivery, where you'll navigate through a map to earn a bonus. But be careful not to encounter any scary dogs in the neighborhood. Alright, let's start the game!");
    system("star cmd.exe /Ka.exe");
    FILE* usd=f_open("after_game","r");
    float quantity,usd_money;
    fscanf("usd","%d %f",&quantity,&usd_money);
    if(usd_money<=0){
        //乞丐
        printf("YOU ARE A LOSER!\nHow did you lose all your money?\nThe restaurant has gone bankrupt! Game over!");
    }
    else {
        //兩個結局 
        if (usd_money/quantity<=10)
        {
            printf("wow!It seems like you're a skilled restaurant manager.\nCongratulations on earning the title of 'Street Chef Extraordinaire'!");
        }
        else{
            printf("Oh my, you're truly a genius at running a restaurant! Congratulations on earning the title of 'Master Chef'!");
        }
    }
    return 0;
}
