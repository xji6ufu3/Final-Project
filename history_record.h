#ifndef history_record_h
#define history_record_h

int num_func();
int record(float a, int b, char word[10]); // 錢, 幾道菜, 結局代碼(A or B or C)
int history_show(int num);                 //  玩過幾次
int restart(int num);
int his_search(int choice, int num);

#endif