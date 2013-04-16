#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Min.h"

int set1[MAX_LENGHT] = {1,5,6,END};
int set0[MAX_LENGHT] = {2,3,7,END};
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
		l=0;
		while(l<allsets_lenght)
		{
			//print_set(allsets[l]);
			l++;
		}
		while(i<(max_group_num))
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
						//print_set(s2);
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
		//print_set(newsets[0]);
		int np = 0;
		while(np<allsets_lenght)
		{
			if(marks[np])
			{
			}
			else
			{
				//print_set(allsets[np]);
				//printf("%i === \n",np);
				memcpy(cover_table[cover_table_pointer++], allsets[np],sizeof(allsets[np]));
				//printf("==%i==\n",marks[np]);
				//print_set(allsets[np]);
			}
			np++;
		}
		//printf("==========%i \n",newsets_pointer);
		int h = 0;
		int aind = 0;
		int weights[MAX_LENGHT];
		while(h<MAX_LENGHT)
		{
			weights[h] = -1;
			h++;
		}
		h = 0;
		//printf("-------\n");
		while(h<newsets_pointer)
		{
			int w = get_weight(newsets[h]);
			//printf("==========%i \n",w);
			int contains = weights_contains(weights,w,MAX_LENGHT);
			if(contains)
			{
				//printf("@%i\n",w);
				//print_set(newsets[h]);
			}
			else
			{
				//printf("@@%i\n",w);
				//print_set(newsets[h]);
				weights[aind] = get_weight(newsets[h]);
				memcpy(allsets[aind++],newsets[h],sizeof(newsets[h]));
			}
			h++;
		}
		
		//printf("2==========%i \n",aind);
		//memcpy(allsets,newsets,sizeof(newsets));
		//print_set(newsets[0]);
		allsets_lenght = aind;
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
	
	qsort(cover_table,cover_table_pointer,sizeof(int)*MAX_LENGHT,cmp_sets_by_cover);
	
	int implicants[cover_table_pointer][MAX_LENGHT];
	int impl_pointer = 0;
	int append = cover_table_pointer;
	
	i = 0;
	while(i<cover_table_pointer)
	{
		if(!is_repeat(cover_table, append, i, set1))
		{
			memcpy(implicants[impl_pointer++],cover_table[i],sizeof(cover_table[i]));
			memcpy(cover_table[append++],cover_table[i],sizeof(cover_table[i]));
		}
		i++;
	}
		
	i = 0;
	while(i<impl_pointer)
	{
		printf("(");
		print_implicant(implicants[i]);
		printf(")");
		if(i != impl_pointer - 1)
		{
			printf("+");
		}
		i++;
	}
	printf("\n");
	
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

int get_min_group_num(int* els)
{
	int i = 0;
	while(i<max_group_num)
	{
		if(els[i] != 0)
		{
			break;
		}
		i++;
	}
	return i;
}

int get_weight(int* set)
{
	int len = arrlen(set);
	int i = 0;
	int weight = 0;
	
	while(i<len)
	{
		weight += set[i]*intpow(3,i);
		i++;
	}
	
	return weight;
	
}

int intpow(int num, int pow)
{
	int i = 0;
	int result = 1;
	
	if(num == 0)
	{
		return 0;
	}
	if(num == 1)
	{
		return 1;
	}
	
	while(i<pow)
	{
		result *= num;
		i++;
	}
	return result;
}

int weights_contains(int* weights,int weight, int max)
{
	
	int i = 0;
	while(i<max)
	{
		if(weights[i] == weight)
		{
			return 1;
		}
		i++;
	}
	return 0;
	
}

int set_covers(int* set, int* worksets)
{
	int lenW = arrlen(worksets);
	int lenS = arrlen(set);
	
	int result = 0;
	
	int i = 0;
	while(i<lenW)
	{
		int s[MAX_LENGHT];
		group_from_int(worksets[i],base,s);
		int j = 0;
		int eq = 1;
		while(j<lenS)
		{
			if(set[j] == N)
			{
				s[j] = set[j];
			}
			if(s[j] != set[j])
			{
				eq = 0;
				break;
			}
			j++;
		}
		if(eq)
		{
			result++;
		}
		i++;
	}
	
	return result;
	
}

int cmp_sets_by_cover(const void * a, const void * b)
{
	 return ( set_covers((int*)a,set1) - set_covers((int*)b,set1) );
}

int is_covered(int* set,int workset)
{
	int w[] = {workset,END};
	if(set_covers(set,w))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int is_repeat(int allsets[][MAX_LENGHT], int len, int nset, int* worksets)
{
	int i = 0;
	int lenW = arrlen(worksets);
	int target_sets[MAX_LENGHT];
	int target_pointer = 0;
	
	while(i<lenW)
	{
		if(is_covered(allsets[nset],worksets[i]))
		{
			target_sets[target_pointer++] = worksets[i];
		}
		i++;
	}
	i = 0;
	
	while(i<target_pointer)
	{
		int j = nset+1;
		int complete = 0;
		while(j<len)
		{
			if(is_covered(allsets[j],target_sets[i]))
			{
				complete = 1;
			}
			j++;
		}
		if(!complete)
		{
			return 0;
		}
		i++;
	}
	
	return 1;
}

void print_implicant(int* impl)
{
	int len = arrlen(impl);
	
	int j = 0;
	
	while(j<len)
	{
		if(impl[j] == N)
		{
			j++;
			continue;
		}
		if(impl[j] == 0)
		{
			printf("!");
		}
		printf("%c",VARNAMES[j]);
		j++;
	}
}
