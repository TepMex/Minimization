#include <QString>

#define N 2
#define END -99
#define MAX_LENGHT 320
#define MAX_BASE 1500
#define MAX_GROUP 32
#define VARNAMES "abcdefghijklmnopqrstuvwxyz"


QString quine_start(int s1[], int s0[]);
int arrlen(int* arr);
void get_fictive(int* s1, int* s0, int* dest);
int cmpfunc (const void * a, const void * b);
int max(int a, int b);
int base2(int arg);
int arr_contains(int* arr, int val);
void group_from_int(int arg, int base, int* dest);
int get_group_num(int* arr);
int get_difference(int* s1, int* s2);
QString minimize(void);
void print_set(int* set);
int get_max_group_num(int base);
int get_set_from_num(int group, int index,int allsets[][MAX_LENGHT], int* dest);
int get_weight(int* set);
int intpow(int num, int pow);
int weights_contains(int* weights,int weight, int max);
int get_min_group_num(int* els);
int set_covers(int* set, int* worksets);
int cmp_sets_by_cover(const void * a, const void * b);
int is_covered(int* set,int workset);
int is_repeat(int allsets[][MAX_LENGHT], int len, int nset, int* worksets);
QString print_implicant(int* impl);
