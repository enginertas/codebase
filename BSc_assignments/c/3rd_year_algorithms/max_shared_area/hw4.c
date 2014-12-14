#include <stdio.h>

void *malloc(size_t size);
void free(void* p);

/************** New Type Definitions *************/
typedef struct square
{
	int x;
	int y;
	int width;
	int height;
} square;

typedef struct edge
{
	int area;
	int next_id;
	struct edge * next;
} edge;

int No_of_Squares, *Color, *Count, No_of_Count = 0;
edge* Square_Graph;

/************** Helper Functions ******************/
square* readInput()
{
	int i;
	square* sqr;

	scanf("%d", &No_of_Squares);
	sqr = (square*) malloc(sizeof(square) * (No_of_Squares + 1));

	for(i = 1; i<=No_of_Squares; i++)
	{
		scanf("%d",&sqr[i].x);
		scanf("%d",&sqr[i].y);
		scanf("%d",&sqr[i].width);
		scanf("%d",&sqr[i].height);
	}
	return sqr;
}

int calculateSharedArea(square *s1, square *s2)
{
	int start, start1, start2, end, end1, end2, d_x = 0, d_y = 0;

	/********* Finding delta x = end - start difference *********/
	start1 = s1 -> x;
	end1 = start1 + s1 -> width;
	start2 = s2 -> x;
	end2 = start2 + s2 -> width;

	if(start1 > start2)		/***** Pick max start *****/
		start = start1;
	else
		start = start2;

	if(end1 < end2)			/***** Pick min end *****/
		end = end1;
	else
		end = end2;

	if(start < end)
		d_x = end - start;		/***** Calculate delta *****/

	/********* Finding delta y = end - start difference *********/
	start1 = s1 -> y;
	end1 = start1 + s1 -> height;
	start2 = s2 -> y;
	end2 = start2 + s2 -> height;

	if(start1 > start2)
		start = start1;
	else
		start = start2;

	if(end1 < end2)	
		end = end1;
	else
		end = end2;

	if(start < end)
		d_y = end - start;

	/******* If return = 0, there is no shared area *******/

	return d_x * d_y;	
}


edge* constructGraph(square* all_squares)
{
	int i, j, sh_area;
	edge* new_graph, *new_node;

	new_graph = (edge*) malloc(sizeof(edge) * (No_of_Squares + 1));

	for(i=1; i<=No_of_Squares; i++)
	{
		new_graph[i].area = all_squares[i].width * all_squares[i].height;
		new_graph[i].next = NULL;
	}
	for(i=1; i<=No_of_Squares; i++)
	{
		for(j = i+1; j<=No_of_Squares; j++)
			if((sh_area = calculateSharedArea(&all_squares[i], &all_squares[j])))
			{
				/***** If shared area exists, produce two symmetric new nodes *****/
				new_node = (edge*) malloc(sizeof(edge));
				new_node -> area = sh_area;
				new_node -> next_id = j;
				new_node -> next = new_graph[i].next;
				new_graph[i].next = new_node; 

				new_node = (edge*) malloc(sizeof(edge));
				new_node -> area = sh_area;
				new_node -> next_id = i;
				new_node -> next = new_graph[j].next;
				new_graph[j].next = new_node; 
			}
	}
	return new_graph;
}

int dfs(int index)
{
	int total_area;
	edge *p;
	
	Color[index] = 'G';
	Count[index] = 1;
	No_of_Count++;
	total_area = Square_Graph[index].area;

	for(p = Square_Graph[index].next; p; p = p -> next)
	{
		if(Color[p -> next_id] == 'W')
			total_area += dfs(p -> next_id);	
		else if(Color[p -> next_id] == 'G')
			total_area -= p->area;
	}
	Color[index] = 'B';

	return total_area;
}

int findMax()
{
	int i, j, total_area = 0, max_area = 0, max_index = 1;

	Color = malloc(sizeof(int)*(No_of_Squares + 1));
	Count = malloc(sizeof(int)*(No_of_Squares + 1));

	for(i=1; i<= No_of_Squares; i++)
	{
		Color[i] = 'W';
		Count[i] = 0;
	}
	for(i=1; i<=No_of_Squares; i++)
	{
		for(j=1; j<=No_of_Squares; j++)
			Count[j] = 0;
		No_of_Count = 0;

		if(Color[i] == 'W')
			total_area = dfs(i);

		if(total_area > max_area)
		{
			max_area = total_area;
			max_index = i;
		}
	}
	return max_index;
}
void printOut(int index)
{
	int i;
	for(i=1; i<=No_of_Squares; i++)
	{
		Color[i] = 'W';
		Count[i] = 0;	
	}
	No_of_Count = 0;
	printf("%d\n", dfs(index));
	printf("%d\n", No_of_Count);

	for(i=1; i<=No_of_Squares; i++)
		if(Count[i])
			printf("%d ", i);

}
void deAlloc()
{
	int i;
	edge *p;
	for(i=1; i<=No_of_Squares; i++)
		while(Square_Graph[i].next)
		{
			p = Square_Graph[i].next;
			Square_Graph[i].next = p ->next;
			free(p);
		}
	free(Square_Graph);
	free(Color);
	free(Count);
}

/***************** Main function *************/

int main(void)
{
	square* all_squares;

	all_squares = readInput();
	Square_Graph = constructGraph(all_squares);
	free(all_squares);

	printOut(findMax());
	deAlloc();

	return 0;
}
