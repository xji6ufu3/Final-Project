#ifndef COUNT
#define COUNT

#define LEN 26
extern double price[LEN];
double count_price(char str[]);
int foodnum;
void free_menu();
void initialMenu(FILE *fmenu);
void printMenu();
extern struct menu_t{
    double price;
    int time;
    char *name;
    char *ingredients;
} menu[LEN];
int isnumber(char str[]);

#endif