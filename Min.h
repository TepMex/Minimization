#define N 2
#define END -99
#define MAX_LENGHT 320
#define MAX_BASE 1500
#define MAX_GROUP 32


int arrlen(int*);
void get_fictive(int*, int*, int*);
int cmpfunc(const void *, const void *);
int max(int, int);
int base2(int);
int arr_contains(int*, int);
void group_from_int(int,int,int*);
int get_group_num(int*);
int get_difference(int*, int*);
void minimize(void);
void print_set(int*);
int get_max_group_num(int);
int get_set_from_num(int, int,int[][MAX_LENGHT],int*);
