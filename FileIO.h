#ifndef FILEIO
#define FILEIO

#define RECORD_NAME "recording.txt"
#define RECORD_NAME_TEMP "recording_temp.txt"
typedef struct list_t{
    int number; // the order of order
    double price;
    struct list_t *prior, *next; // doubly linked list
    char meal[]; // store meal codes ranged from 'a' to 'z' to string
} list_t; // list_t store the order information
void free_list(list_t *ptr);
void del_record(int number);
int delete(list_t **list, int number);

#endif