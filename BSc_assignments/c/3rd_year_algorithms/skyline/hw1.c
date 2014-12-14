#include <stdio.h>

void *malloc(size_t size);
void free(void* x);

typedef struct build
{
	unsigned left;
	unsigned height;
	unsigned right;
}build;

typedef struct skynode
{
	unsigned coord;
	unsigned height;
	struct skynode *next;
} skynode;

int No_of_Buildings;
build* Buildings = NULL;

skynode* merge(skynode *skyline1, skynode *skyline2)
{
	unsigned h1 = 0, h2 = 0 , hl = 0;
	skynode *old, *new, *new_skyline;	
	
	new = new_skyline = (skynode*)malloc(sizeof(skynode));
	new -> coord = 0;
	new -> height = 0;
	new -> next = NULL;

	old = skyline1;
	skyline1 = skyline1 -> next;
	free(old);
	old = skyline2;
	skyline2 = skyline2 -> next;
	free(old);	
	
	while(skyline1 && skyline2)
	{
		if(skyline1->coord < skyline2->coord)
		{
			h1 = skyline1 -> height;
			if(h1)
			{
				if(h1 >= h2 && h1 != hl)
				{
					new -> next = (skynode*)malloc(sizeof(skynode));
					new = new -> next;
					
					new -> coord = skyline1 -> coord;
					new -> height = h1;
					new -> next = NULL;

					hl = h1;
				}
				else if(h2 > h1 && h2 != hl)		
				{
					new -> next = (skynode*)malloc(sizeof(skynode));
					new = new -> next;
					
					new -> coord = skyline1 -> coord;
					new -> height = h2;
					new -> next = NULL;

					hl = h2;	
				}
			}
			else if(h2 && h2!=hl)
			{
				new -> next = (skynode*)malloc(sizeof(skynode));
				new = new -> next;

				new -> coord = skyline1 -> coord;
				new -> height = h2;
				new -> next = NULL;
				
				hl = h2;				
			}
			else if(!h2)
			{
				new -> next = (skynode*)malloc(sizeof(skynode));
				new = new -> next;

				new -> coord = skyline1->coord;
				new -> height = 0;
				new -> next = NULL;
				
				hl = 0;
			}
			old = skyline1;
			skyline1 = skyline1 -> next;
			free(old);
		}
		else if(skyline1->coord > skyline2->coord)
		{
			h2 = skyline2 -> height;
			if(h2)
			{
				if(h2 >= h1 && h2 != hl)
				{
					new -> next = (skynode*)malloc(sizeof(skynode));
					new = new -> next;
					
					new -> coord = skyline2 -> coord;
					new -> height = h2;
					new -> next = NULL;

					hl = h2;
				}
				else if(h1 > h2 && h1 != hl)		
				{
					new -> next = (skynode*)malloc(sizeof(skynode));
					new = new -> next;
					
					new -> coord = skyline2 -> coord;
					new -> height = h1;
					new -> next = NULL;

					hl = h1;	
				}
			}
			else if(h1 && h1!= hl)
			{
				new -> next = (skynode*)malloc(sizeof(skynode));
				new = new -> next;

				new -> coord = skyline2 -> coord;
				new -> height = h1;
				new -> next = NULL;
				
				hl = h1;				
			}
			else if(!h1)
			{
				new -> next = (skynode*)malloc(sizeof(skynode));
				new = new -> next;

				new -> coord = skyline2->coord;
				new -> height = 0;
				new -> next = NULL;
				
				hl = 0;
			}	
			old = skyline2;
			skyline2 = skyline2 -> next;
			free(old);
		}
		else
		{
			h1 = skyline1 -> height;
			h2 = skyline2 -> height;

			if(h1>=h2 && h1!=hl)
			{
				new -> next = (skynode*)malloc(sizeof(skynode));
				new = new -> next;
					
				new -> coord = skyline1 -> coord;
				new -> height = h1;
				new -> next = NULL;

				hl = h1;
			}
			else if(h1<h2 && h2!=hl)
			{
				new -> next = (skynode*)malloc(sizeof(skynode));
				new = new -> next;
					
				new -> coord = skyline2 -> coord;
				new -> height = h2;
				new -> next = NULL;

				hl = h2;
			}
			old = skyline1;
			skyline1 = skyline1 -> next;
			free(old);

			old = skyline2;
			skyline2 = skyline2 -> next;
			free(old);
		}
	}
	while(skyline1)
	{
		h1 = skyline1 -> height;
		if(h1!=hl)
		{
			new -> next = (skynode*)malloc(sizeof(skynode));
			new = new -> next;
					
			new -> coord = skyline1 -> coord;
			new -> height = h1;
			new -> next = NULL;

			hl = h1;
		}
		old = skyline1;
		skyline1 = skyline1 -> next;
		free(old);	
	}
	while(skyline2)
	{
		h2 = skyline2 -> height;
		if(h2!=hl)
		{
			new -> next = (skynode*)malloc(sizeof(skynode));
			new = new -> next;
					
			new -> coord = skyline2 -> coord;
			new -> height = h2;
			new -> next = NULL;

			hl = h2;
		}
		old = skyline2;
		skyline2 = skyline2 -> next;
		free(old);	
	}
	return new_skyline;
}
skynode* calculateSkyline(int first_el, int last_el)
{
	int x;
	skynode *s1, *s2;

	if(first_el==last_el)
	{
		s1 = (skynode*)malloc(sizeof(skynode));
		s1 -> coord = Buildings[first_el].left;
		s1 -> height = Buildings[first_el].height;

		s2 = (skynode*)malloc(sizeof(skynode));
		s2 -> coord = Buildings[first_el].right;
		s2 -> height = 0;
		s2 -> next = NULL;

		s1 -> next = s2;

		s2 = (skynode*)malloc(sizeof(skynode));
		s2 -> coord = 0;
		s2 -> height = 0;
		s2 -> next = s1;

		return s2;
	}
	x = (first_el + last_el)/2;
	s1 = calculateSkyline(first_el, x);
	s2 = calculateSkyline(x+1, last_el);
	return merge(s1, s2);
}

int main(void)
{
	int i;
	skynode* skyline, *old; 	

	scanf("%d", &No_of_Buildings);
	Buildings = (build*)malloc(sizeof(build)*No_of_Buildings);
	
	for(i=0; i<No_of_Buildings; i++)
		scanf("%d %d %d", &Buildings[i].left, &Buildings[i].height, &Buildings[i].right);

	skyline = calculateSkyline(0, No_of_Buildings-1);
	old = skyline;
	skyline = skyline -> next;
	free(old);

	for(i=0, old = skyline; old; old = old -> next, i++);
	printf("%d\n", i);

	while(skyline)
	{
		printf("%u %u\n", skyline ->coord, skyline -> height);
		old = skyline;
		skyline = skyline -> next;
		free(old);
	}
	free(Buildings);
	return 0;
}
