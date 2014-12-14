#include <stdio.h>

void *malloc(size_t t);
void free(void* p);

void swap(unsigned long long *p1, unsigned long long *p2)
{
	unsigned long long int temp;
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

int partition (unsigned long long array[], int left, int right)
{
	int mid, pivot, last_small, last_big;

	mid = (left + right)/2;
	if(array[left] < array[mid])
		if(array[mid] <= array[right])
			pivot = mid;
		else
		{
			if(array[left] < array[right])
				pivot = right;
			else
				pivot = left;
		}
	else
	{
		if(array[left] <= array[right])
			pivot = left;
		else
		{
			if(array[mid] < array[right])
				pivot = right;
			else
				pivot = mid;
		}
	}
	swap(&array[pivot], &array[left]);
	
	for(last_big=left + 1, last_small = left; last_big <= right; last_big++)
		if(array[left] > array[last_big])
		{
			last_small++;
			swap(&array[last_big], &array[last_small]);	
		}

	swap(&array[left], &array[last_small]);
	return last_small;
}

void quickSort(unsigned long long array[], int left, int right)
{
	int mid;
		mid = partition(array, left, right);
		if(mid != left)
			quickSort(array, left, mid - 1);
		if(mid != right)		
			quickSort(array, mid + 1, right);
}

int main(void)
{
	FILE *fp;
	int no_of_integers, i, j, *length_of_ways, cur_length, index, size ,*parents;
	unsigned long long *integers, *new_array;

	fp = fopen("hw3.inp","r");
	fscanf(fp,"%d",&no_of_integers);
	integers = (unsigned long long*) malloc(sizeof(unsigned long long) * no_of_integers);
	parents = (int*) malloc(sizeof(int) * no_of_integers);
	length_of_ways = (int*) malloc(sizeof(int) * no_of_integers);

	for(i=0; i<no_of_integers; i++)
	{
		fscanf(fp, "%llu", &integers[i]);
		parents[i] = 0;
		length_of_ways[i] = 0;
	}
	fclose(fp);
	quickSort(integers, 0, no_of_integers -1);

/************Main part of code ***********/

	for(i=0; i<no_of_integers; i++)
	{
		cur_length = length_of_ways[i] + 1;
		for(j=i+1; j<no_of_integers; j++)
			if(cur_length > length_of_ways[j] && !(integers[j] % integers[i]))
			{
				parents[j] = i;
				length_of_ways[j] = cur_length;
			}			
	}

	for(i=1, cur_length = 0, index = 0; i<no_of_integers; i++)
		if(length_of_ways[i] > cur_length)
		{
			cur_length = length_of_ways[i];
			index = i;
		}
	
	new_array = (unsigned long long*) malloc(sizeof(unsigned long long) * (cur_length +1));
	size = cur_length;
	for(;cur_length>=0; cur_length--)
	{
		new_array[cur_length] = integers[index];
		index = parents[index];
	}

	fp = fopen("hw3.out", "w");
	fprintf(fp, "%d\n", size + 1);
	for(i=0; i< size; i++)
		fprintf(fp, "%llu ", new_array[i]);
	fprintf(fp, "%llu", new_array[size]);
	fclose(fp);
	
	free(new_array);
	free(integers);
	free(parents);
	free(length_of_ways);
	return 0;
}
