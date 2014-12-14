#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Grid_Size, Extended_Size, Goal_X, Goal_Y;
float Alpha, Gama;
int **Grid, Random_Seed, Max_Direction; 
float **Q[4];

void* malloc(size_t size);
void free(void* p);

int eerand() 
{
	Random_Seed = Random_Seed * 1103515241 + 99989; 
	return (unsigned int)(Random_Seed / 65536) % 32768; 
}
void readFile(void)
{
	int i, j, k, new_x, new_y;
	FILE *fp;

	fp = fopen("input.txt" , "r");
	fscanf(fp, "%d", &Grid_Size);
	Extended_Size = Grid_Size + 2;

	Grid = (int**) malloc(sizeof(int*) * Extended_Size);
	Q[0] = (float **) malloc(sizeof(float*) * Extended_Size);
	Q[1] = (float **) malloc(sizeof(float*) * Extended_Size);
	Q[2] = (float **) malloc(sizeof(float*) * Extended_Size);
	Q[3] = (float **) malloc(sizeof(float*) * Extended_Size);

	for(i = 0; i < Extended_Size; i++)
	{
		Q[0][i] = (float *) malloc(sizeof(float) * Extended_Size);
		Q[1][i] = (float *) malloc(sizeof(float) * Extended_Size);
		Q[2][i] = (float *) malloc(sizeof(float) * Extended_Size);
		Q[3][i] = (float *) malloc(sizeof(float) * Extended_Size);
		Grid[i] = (int *) malloc(sizeof(int) * Extended_Size);

		for(j = 0; j < Extended_Size; j++)
		{
			Grid[i][j] = -1;
			Q[0][i][j] = Q[1][i][j] = Q[2][i][j] = Q[3][i][j] = 0.0f;
		}
	}

	for(i = 1; i <=Grid_Size; i++)
		for(j = 1; j <= Grid_Size; j++)
			Grid[i][j] = 0;

	fscanf(fp, "%f%f%d%d", &Alpha, &Gama, &Goal_X, &Goal_Y);
	while(fscanf(fp, "%d%d", &new_x, &new_y)!=EOF)
		Grid[new_x][new_y] = -1;

	Grid[Goal_X][Goal_Y] = 10;
	fclose(fp);
}
float maxQ(int x, int y)
{
	float max;
	max = Q[0][x][y];
	Max_Direction = '<';

	if (Q[1][x][y] > max)
	{
		max = Q[1][x][y];
		Max_Direction = '^';
	}
	if (Q[2][x][y] > max)
	{
		max = Q[2][x][y];
		Max_Direction = '>';	
	}	
	if (Q[3][x][y] > max)
	{
		max = Q[3][x][y];
		Max_Direction = '|';
	}

	return max;
}
void calculate(float temperature, int tries)
{
	int i, start_x, start_y = 0, direction = 0, c, j, same;
	float max, botz_prob_max, cur;

	Random_Seed = time(NULL);
	for(i = 0; i < tries; i++)
	{
		/***** find an initial state *****/
		do
		{	
			start_x = eerand() % Extended_Size;
			start_y = eerand() % Extended_Size;
		}
		while(Grid[start_x][start_y]);

		/***** consider an arbitrary action *****/
		while(!(start_x == Goal_X && start_y == Goal_Y))
		{
			direction = 0;
			same = 0;
			botz_prob_max = pow(M_E, Q[0][start_x][start_y]/temperature);
			for(j = 1; j < 4; j++)	
			{
				cur = pow(M_E, Q[j][start_x][start_y]/temperature);
				if(cur > botz_prob_max)
				{
					botz_prob_max = cur;
					direction = j;
				}
				else if(cur == botz_prob_max)
					same++;
			}
			if(same > 0)
				direction = eerand() % 4;

			/*printf("%d %d %d %f\n", start_x, start_y, direction, botz_prob_max);*/

			switch(direction)		
			{
				case 0:
					if(start_y == 1 || Grid[start_x][start_y - 1] == -1)
						c = 1;
					else
						c = start_y - 1;

					max = maxQ(start_x, c);
					Q[0][start_x][start_y] = (1 - Alpha) * Q[0][start_x][start_y] + Alpha * (Grid[start_x][c] + max * Gama);
					start_y = c;
					break;

				case 1:	
					if(start_x == 1 || Grid[start_x - 1][start_y] == -1)
						c = 1;
					else 
						c = start_x - 1;

					max = maxQ(c, start_y);
					Q[1][start_x][start_y] = (1 - Alpha) * Q[1][start_x][start_y] + Alpha * (Grid[c][start_y] + max * Gama);
					start_x = c;
					break;

				case 2:	
					if(start_y == Grid_Size || Grid[start_x][start_y + 1] == -1)
						c = start_y;
					else
						c = start_y + 1;

					max = maxQ(start_x, c);
					Q[2][start_x][start_y] = (1 - Alpha) * Q[2][start_x][start_y] + Alpha * (Grid[start_x][c] + max * Gama);
					start_y = c;
					break;

				case 3:
					if(start_x == Grid_Size || Grid[start_x + 1][start_y] == -1)
						c = start_x;
					else
						c = start_x + 1;

					max = maxQ(c, start_y);
					Q[3][start_x][start_y] = (1 - Alpha) * Q[3][start_x][start_y] + Alpha * (Grid[c][start_y] + max * Gama);
					start_x = c;
					break;
			}
		}
	}
}
void writeFile(void)
{
	int i, j;
	FILE *fp;
	fp = fopen("output.txt", "w");
	for(i = 1; i <= Grid_Size; i++)
	{
		for(j = 1; j <= Grid_Size; j++)
		{
			if(Grid[i][j] == -1)
				fprintf(fp, "X ");
			else if(Grid[i][j] == 10)
				fprintf(fp, "G ");
			else
			{
				maxQ(i, j);	
				fprintf(fp, "%c ", Max_Direction);
			}
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

}
void freeSpace(void)
{
	int i;
	for(i = 0; i < Extended_Size; i++)
		free(Grid[i]);
	free(Grid);
}
int main(void)
{
	readFile();
	calculate(4000, 100000);	/**Changeable T and trial values**/
	writeFile();
	freeSpace();
}
