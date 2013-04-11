#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Min.h"

int set0[MAX_LENGHT] = {2,7,9,13,15,END};
int set1[MAX_LENGHT] = {0,1,3,5,8,END};
int setF[MAX_LENGHT];
int base;
int max_group_num;

int main(int argc, char** argv)
{
	get_fictive(set1,set0,setF);
	minimize();
	return 0;
}

int arrlen(int* arr)
{
	int i=0;
	while(arr[i] != END)
	{
		i++;
	}
	return i;
}

void get_fictive(int* s1, int* s0, int* dest)
{
	
	int fict[MAX_LENGHT];
	
	qsort(s1,arrlen(s1),sizeof(int),cmpfunc);
	qsort(s0,arrlen(s1),sizeof(int),cmpfunc);
	
	
	
	int max_num = max(s1[0],s0[0]);
	base = base2(max_num);
	max_group_num = get_max_group_num(base);
	
	int i = 0;
	int n = 0;
	
	while(i<base)
	{
		if(!arr_contains(s1,i) && !arr_contains(s0,i))
		{
			fict[n++] = i;
		}
		i++;
	}
	
	fict[n] = END;
	
	memcpy(dest,fict,sizeof(fict));
}

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)b - *(int*)a );
}

int max(int a, int b)
{
	if((a-b) > 0)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int base2(int arg)
{
	int i = 1;
	while(arg+1 > (i *= 2))
	{
	}
	return i;
}

int arr_contains(int* arr, int val)
{
	int i=0;
	
	while(i<arrlen(arr))
	{
		if(arr[i] == val)
		{ 
			return 1;
		}
		i++;
	}
	
	return 0;
}

void group_from_int(int arg, int base, int* dest)
{
	int set[MAX_LENGHT];
	base /= 2;
	
	int n = 0;	
	while(base != 0)
	{
		set[n++] = arg/base;
		arg = arg%base;
		base /= 2;
	}
	set[n] = END;
	memcpy(dest,set,sizeof(set));
	
}

int get_group_num(int* arr)
{
	int len = arrlen(arr);
	int i = 0;
	int num = 0;
	while(i<len)
	{
		if(arr[i] == 1)
		{
			num++;
		}
		i++;
	}
	return num;
}

int get_difference(int* s1, int* s2)
{
	
	int len;
	
	if((len = arrlen(s1)) != arrlen(s2))
	{
		printf("Error: different sizes of collections");
		return -2;
	}
	
	int i=0;
	int diff=0;
	int index = -1;
	while(i<len)
	{
		if(s1[i] != s2[i])
		{
			diff++;
			index = i;
		}
		i++;
	}
	
	if(diff == 1)
	{
		return index;
	}
	else
	{
		return -1;
	}
}

void minimize()
{
	int len1 = arrlen(set1);
	int lenF = arrlen(setF);
	
	int allsets[MAX_LENGHT][MAX_LENGHT];
	int newsets[MAX_LENGHT][MAX_LENGHT];
	int cover_table[len1+lenF][MAX_LENGHT];
	int el_in_grpn[MAX_GROUP];
	int marks[MAX_LENGHT];
	
	int j=0;
	
	int allsets_lenght = 0;
	
	int is_changes = 0;
	int newsets_pointer = 0;
	int cover_table_pointer = 0;
	while(j<MAX_GROUP)
	{
		el_in_grpn[j]=0;
		j++;
	}
	
	int i=0;
	int ind = 0;
	
	while(i<len1)
	{
		group_from_int(set1[i],base,allsets[ind]);
		el_in_grpn[get_group_num(allsets[ind])]++;
		ind++;
		i++;
	}
	allsets_lenght += i;
	i = 0;
	while(i<lenF)
	{
		group_from_int(setF[i],base,allsets[ind]);
		el_in_grpn[get_group_num(allsets[ind])]++;
		ind++;
		i++;
	}
	allsets_lenght += i;
	//printf("%i %i %i %i \n",el_in_grpn[0],el_in_grpn[1],el_in_grpn[2],el_in_grpn[3]);
	do
	{
		is_changes = 0;
		newsets_pointer = 0;
		i=0;
		//int y = 0;
		
		int l = 0;
		while(l<MAX_LENGHT)
		{
			marks[l] = 0;
			l++;
		}
		
		while(i<(max_group_num-1))
		{
			j = 0;
			while(j<el_in_grpn[i])
			{
				int k=0;
				int s1[MAX_LENGHT];
				int s1_index = -1;
				s1_index = get_set_from_num(i,j,allsets,s1);
				if(s1_index < 0)
				{
					printf("Error: no sets found for group: %i, index: %i",i,j);
				}
				
				while(k<el_in_grpn[i+1])
				{
					int s2[MAX_LENGHT];
					int s2_index = -1;
					
					if((s2_index = get_set_from_num(i+1,k,allsets,s2)) < 0)
					{
						printf("Error: no sets found for group: %i, index: %i",i+1,k);
					}
					

					int diff_ind;
					if((diff_ind = get_difference(s1,s2)) >= 0)
					{
						s2[diff_ind] = N;
						memcpy(newsets[newsets_pointer],s2,sizeof(s2));
						newsets_pointer++;
						marks[s1_index] = 1;
						marks[s2_index] = 1;
						is_changes = 1;
						print_set(s2);
					}
					else
					{
						//printf(" %i \n",diff_ind);
					}
					k++;
					
				}
				j++;
			}
			i++;
		}
		//y++;
		//printf("\n===%i===\n", arrlen(newsets[0]));
		//print_set(newsets[0]);
		int np = 0;
		while(np++<allsets_lenght)
		{
			if(marks[np])
			{
				continue;
			}
			else
			{
				memcpy(cover_table[cover_table_pointer++], allsets[np],sizeof(allsets[np]));
				//printf("==%i==\n",marks[np]);
				//print_set(allsets[np]);
			}
		}
		
		memcpy(allsets,newsets,sizeof(newsets));
		//print_set(newsets[0]);
		allsets_lenght = newsets_pointer;
		max_group_num = max_group_num -1;
		
		int peka = 0;
		while(peka<MAX_GROUP)
		{
			el_in_grpn[peka] = 0;
			peka++;
		}
		
		int grpn=0;
		while(grpn<allsets_lenght)
		{
			el_in_grpn[get_group_num(allsets[grpn])]++;
			grpn++;
		}
		
	} while(is_changes);
	
	i=0;
	while(i<cover_table_pointer)
	{
		//print_set(cover_table[i]);
		i++;
	}
	
}
void print_set(int* set)
{
	int len = arrlen(set);
	int i = 0;
	while(i<len)
	{
		if(set[i] == N)
		{
			printf("-");
		}
		else
		{
			printf("%i",set[i]);
		}

		i++;
	}
	printf("\n");
}

int get_max_group_num(int base)
{
	int result = 0;
	while(base != 1)
	{
		result++;
		base /= 2;
	}
	return result;
}

int get_set_from_num(int group, int index,int allsets[][MAX_LENGHT], int* dest)
{
	int i = 0;
	int ind = 0;
	while(i<(base*2))
	{
		if(get_group_num(allsets[i]) == group)
		{
			if(ind == index)
			{
				memcpy(dest,allsets[i],sizeof(allsets[i]));
				return i;
			}
			else
			{
				ind++;
			}
		}
		i++;
	}
	return -1;
	
}
