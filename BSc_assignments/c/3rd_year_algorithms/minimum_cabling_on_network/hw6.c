#include <stdio.h>

#define INF 2147483647
void* malloc(size_t size);
void free(void* p);

typedef struct node
{
	int start;
	int id;
	float distance;
	struct node *next;
} node;

int No_of_Computers, Degree, No_of_Edges;
int Binary_Heap[15][2], Heap_Size = 0, Cur_Cables[16],In_Queue[16], Parent[16];
node Computers[16];

void readInput(void)
{
	int i, con_st, con_end, dist;
	node *cur_node;

	scanf("%d", &No_of_Computers);
	scanf("%d", &Degree);
	scanf("%d", &No_of_Edges);

	/*************** Initialization ***************/
	for(i = 1; i <= No_of_Computers; i++)
	{
		Computers[i].id = -1;
		Computers[i].distance = -1;
		Computers[i].start = -1;
		Computers[i].next = NULL;
	}

	/************** Initial Graph Set Up **********/
	for(i = 0; i < No_of_Edges; i++)
	{
		scanf("%d %d %d", &con_st, &con_end, &dist);

		cur_node = (node *)malloc(sizeof(node));
		cur_node -> next = Computers[con_st].next;
		cur_node -> distance = dist;
		cur_node -> id = con_end;
		cur_node -> start = dist;
		Computers[con_st].next = cur_node;

		cur_node = (node *)malloc(sizeof(node));
		cur_node -> next = Computers[con_end].next;
		cur_node -> distance = dist;
		cur_node -> id = con_st;
		cur_node -> start = dist;
		Computers[con_end].next = cur_node;
	}
}
void swap(int index1, int index2)
{
	int tmp;
	tmp = Binary_Heap[index1][0];
	Binary_Heap[index1][0] = Binary_Heap[index2][0];
	Binary_Heap[index2][0] = tmp;
	In_Queue[tmp] = index2;
	In_Queue[Binary_Heap[index1][0]] = index1;

	tmp = Binary_Heap[index1][1];
	Binary_Heap[index1][1] = Binary_Heap[index2][1];
	Binary_Heap[index2][1] = tmp;
}
void insertToHeap(int id, int dist)
{
	int i, parent;
	i = Heap_Size;
	parent = i/2;
	Heap_Size++;
	Binary_Heap[i][0] = id;
	Binary_Heap[i][1] = dist;
	In_Queue[id] = i;
	while(i > 0)
		if(Binary_Heap[i][1] < Binary_Heap[parent][1])	
		{
			swap(i, parent);			
			i = i/2;
			parent = parent/2;
		}
		else
			break;
}
int extractMin()
{
	int i = 0, child1 = 1, child2 = 2, min , x;
	min = Binary_Heap[0][0];	
	Heap_Size--;
	x = Binary_Heap[0][0] = Binary_Heap[Heap_Size][0];
	Binary_Heap[0][1] = Binary_Heap[Heap_Size][1];
	In_Queue[x] = 0;
	
	while(i < Heap_Size)
	{
		if(child1 <= Heap_Size && child2 <= Heap_Size)
		{
			if(Binary_Heap[i][1] > Binary_Heap[child1][1])
			{
				if(Binary_Heap[child1][1] <= Binary_Heap[child2][1])
				{
					swap(i, child1);
					i = child1;
				}
				else
				{
					swap(i, child2);
					i = child2;
				}
			}
			else if(Binary_Heap[i][1] > Binary_Heap[child2][1])
			{
				swap(i, child2);
				i = child2;
			}
			else
				break;
		}		
		else if(child1 <= Heap_Size && Binary_Heap[i][1] > Binary_Heap[child1][1])
		{
			swap(i, child1);
			i = child1;
		}
		else
			break;

		child1 = 2*i + 1;
		child2 = 2*i + 2;		
	}
	In_Queue[min] = -1;
	return min;
}
void decreaseKey(int place, int dist)
{
	int parent;
	Binary_Heap[place][1] = dist;
	parent = place / 2;
	while(place > 0)
		if(Binary_Heap[place][1] < Binary_Heap[parent][1])	
		{
			swap(place, parent);	
			place = place/2;
			parent = parent/2;
		}
		else
			break;
}
void penalizeGraph()
{
	int i;
	float max = 0, min = INF, co;
	node *cur;
	for(i = 1; i <= No_of_Computers; i++)
		for(cur = Computers[i].next; cur; cur = cur -> next)
			if(cur -> distance < min)
				min = cur -> distance;

	for(i = 1; i <= No_of_Computers; i++)
		for(cur = Computers[i].next; cur; cur = cur -> next)
			if(cur -> distance > max)
				max = cur -> distance;

	co = max * 0.2 / (max - min);	
	for(i = 1; i <= No_of_Computers; i++)
	{
		for(cur = Computers[i].next; cur; cur = cur ->next)
			if(Cur_Cables[i] && Cur_Cables[cur -> id])
				cur -> distance += 2 * (cur -> distance - min + 0.01) * co;
			else if(Cur_Cables[i] && !Cur_Cables[cur ->id])
				cur -> distance += (cur -> distance - min + 0.01) * co;
	}
}
void findMST()
{
	int i, ax;
	node *cur;
	for(i = 2; i <= No_of_Computers; i++)
	{
		Parent[i] = -1;
		insertToHeap(i, INF);
	}
	Parent[1] = -1;
	insertToHeap(1, 0);

	while(Heap_Size)
	{
		i = extractMin();
		for(cur = Computers[i].next; cur; cur = cur -> next)
		{

/*			for(j = 0; j < No_of_Computers; j++)
				printf("%d,%d\t", Binary_Heap[j][0], Binary_Heap[j][1]);
			printf("\n");*/

			ax = In_Queue[cur->id];
			if(ax != -1 && cur -> distance < Binary_Heap[ax][1])
			{
				Parent[cur->id] = i;
				decreaseKey(ax, cur->distance);				
			}
		}
	}
}
int controlMST()
{
	int i, is_completed = 1;
	static int loop = 0;
	loop++;	
	if(loop == 20000)
		return -1;
	else
	{
		for(i = 2; i <= No_of_Computers; i++)
			if(Parent[i] == -1)
				return -1;

		for(i = 1; i<=No_of_Computers; i++)
			Cur_Cables[i] = 0; 
		for(i = 2; i<=No_of_Computers; i++)
		{
			Cur_Cables[Parent[i]]++;
			Cur_Cables[i]++;
		}

		for(i = 1; i<= No_of_Computers; i++)
		{
			if(Cur_Cables[i] <= Degree)
				Cur_Cables[i] = 0;
			else
				is_completed = 0;
		}
		return is_completed;
	}
}
void returnMinCost()
{
	int i, total = 0;
	node* cur;
	if(controlMST() == 1)
	{
		for(i = 1; i <= No_of_Computers; i++)
			for(cur = Computers[i].next; cur; cur = cur -> next)
				if(Parent[i] == cur ->id)
				{
					//printf("%d -> %d\n", i, cur -> id);
					total += cur -> start;
					break;
				}
		printf("%d", total);
	}
	else
		printf("%d", -1);
}
void freeSpace()
{
	int i;
	node* old;
	for(i = 0; i <= No_of_Computers; i++)
		for(old = Computers[i].next; old; old = Computers[i].next)
		{
			Computers[i].next = old -> next;
			free(old);	
		}
}
int main(void)
{	
	readInput();
	findMST();
	while(!controlMST())
	{
		penalizeGraph();
		findMST();		
	}
	returnMinCost();
	freeSpace();
	return 0;
}
