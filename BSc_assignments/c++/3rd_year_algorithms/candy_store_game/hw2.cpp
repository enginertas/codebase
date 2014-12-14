/****	Engin Ertaş
	1560176
	Algo Homework 2 ***/

#include <iostream>
#include <queue>
#include <fstream>
#include <vector> ///////////

int query(int size, int* kind);
int guess(int k);

using namespace std;

/**************************************************************/
vector<int> *mergeSort(int low, int high, int* t_array, int* c_box)
{
	int mid, i, j, size_x, size_y;
	vector<int> *new_vector, *merged1, *merged2;
	
	new_vector = new vector<int>;
	
	if(low == high)
	{
		new_vector->push_back(t_array[low]);
		return new_vector;
	}

	mid = (low + high)/2;
	merged1 = mergeSort(low, mid, t_array, c_box);
	merged2 = mergeSort(mid + 1, high, t_array, c_box);
	size_x = merged1->size();
	size_y = merged2->size();

	for(i=0, j=0 ; i<size_x && j<size_y;)
	{
		if(c_box[merged1->at(i)] >= c_box[merged2->at(j)])
		{
			new_vector->push_back(merged1->at(i));
			i++;
		}
		else
		{
			new_vector->push_back(merged2->at(j));
			j++;
		}
	}
	for(;i<size_x; i++)
		new_vector -> push_back(merged1->at(i));
	
	for(;j<size_y; j++)
		new_vector -> push_back(merged2->at(j));

	delete merged1;
	delete merged2;
	return new_vector;
}

void mainMerge(int low, int high, int *t_array, int *c_box)
{
	int i, size;	
	vector<int> *merged;
	merged = mergeSort(low, high, t_array, c_box);
	size = merged->size();

	for(i=0; i<size; i++)
		t_array[i] = merged -> at(i);

	delete merged;
}
/***********************************************/

void play(void)
{	
	int *candy_box, *types, *new_kind = NULL;
	int no_of_types, size_of_available, new_size, i, j, mid, iter, total, no_of_free_types, last_type;
	ifstream input_file;
	vector<int> search_vector;

	input_file.open("hw2.inp", ifstream::in);

	input_file >> no_of_types;			//getting the number of types
	candy_box = new int[no_of_types + 1];		//creating arrays
	types = new int[no_of_types];

	for(i=1, j=0; i<=no_of_types; i++, j++)		
	{
		input_file >> candy_box[i];	//getting the number of candies for each type
		types[j] = i;	
	}

	while(1)			//loop until candies finish
	{
		for(i=1, size_of_available=0; i<=no_of_types; i++)	//traverse all types
			if(candy_box[i])				//if number of candies of i-th type is not 0,
			{
				types[size_of_available] = i;		//push i to array
				size_of_available++;			//increase the number of available types
			}

		if(!size_of_available)		//if no available types exist, terminate the prog
			break;

		mainMerge(0, size_of_available-1, types, candy_box);

		search_vector.clear();
		for(i=0; i<size_of_available; i++)
			for(j = candy_box[types[i]]; j>0 ; j--)
				search_vector.push_back(types[i]);
		

		size_of_available = search_vector.size();
		for(i=0, j=size_of_available-1, last_type = 0; i!=j;)
		{
			mid = (i + j) / 2;
			new_size = mid - i + 1;
			no_of_free_types = 0;

			for(iter = i; iter <= j; iter++)
				if(search_vector.at(iter) != last_type)
				{
					last_type = search_vector.at(iter);
					no_of_free_types++;
				}

			if(no_of_free_types<=1)
				break;

			last_type=0;
			no_of_free_types = 0;

			for(iter = i; iter <= mid; iter++)
				if(search_vector.at(iter) != last_type)
				{
					last_type = search_vector.at(iter);
					no_of_free_types++;
				}

			new_kind = new int[new_size];
			for(iter = i; iter <= mid; iter++)
				new_kind[iter-i] = search_vector.at(iter);
		
			if(query(new_size, new_kind))
			{
				if(no_of_free_types <=1)					
					break;
				else
					j = mid;		
			}
			else
			{
				for(iter = mid + 1; iter<=j && search_vector.at(iter) == last_type; iter++);

				i = iter;
				no_of_free_types = 0;				

				for(; iter <= j; iter++)
					if(search_vector.at(iter) != last_type)
					{
						last_type = search_vector.at(iter);
						no_of_free_types++;
					}

				if(no_of_free_types<=1)
				{		
					i = j;			
					break;
				}
			}
			delete [] new_kind;
		}

		guess(search_vector.at(i));		//assert the type of candy, and continue
		candy_box[search_vector.at(i)]--;
	}
	search_vector.clear();
	delete [] candy_box;		//free the arrays, and close the file
	delete [] types;
	input_file.close();
}
