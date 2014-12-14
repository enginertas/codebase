#include <stdio.h>

#define INF 2147483647
#define NA -1

void* malloc(size_t size);
void free(void *p);

int ***Building[4];
int Cube_Dim, Start_Floor, Start_NS, Start_EW;
int End_Floor, End_NS, End_EW;

void readInput()
{
	int a, i, j, k, no_of_danger, floor, ns, ew;

	scanf("%d", &Cube_Dim);
	for(a = 0; a < 4; a++)
	{
		Building[a] = (int***) malloc(sizeof(int**) * Cube_Dim);
		for(i=0; i<Cube_Dim; i++)
		{
			Building[a][i] = (int**) malloc(sizeof(int*)*Cube_Dim);
			for(j=0; j<Cube_Dim; j++)
				Building[a][i][j] = (int*) malloc(sizeof(int)*Cube_Dim);
		}
	}
	for(a=0; a<4; a++)
		for(i=0; i<Cube_Dim; i++)
			for(j=0; j<Cube_Dim; j++)	
				for(k=0; k<Cube_Dim; k++)
					Building[a][i][j][k] = INF;
	
	scanf("%d %d %d", &Start_Floor, &Start_NS, &Start_EW);
	scanf("%d %d %d", &End_Floor, &End_NS, &End_EW);
	Start_Floor--, Start_NS--, Start_EW--;
	End_Floor--, End_NS--, End_EW--;
	Building[0][Start_Floor][Start_NS][Start_EW]= 0;

	scanf("%d", &no_of_danger);
	for(i=0; i<no_of_danger; i++)
	{
		scanf("%d %d %d", &floor, &ns, &ew);
		floor--, ns--, ew--;
		j = Cube_Dim - ns - 1;
		k = Cube_Dim - ew - 1;

		Building[0][floor][ns][ew]= NA;
		Building[1][floor][k][ns] = NA;
		Building[2][floor][j][k]  = NA;
		Building[3][floor][ew][j] = NA;
	}
}

void opInterFloor(int angle, int floor, int ns, int ew)
{
	int j, k, distance, new_dist, rotate_value, new_angle;
	distance = Building[angle][floor][ns][ew];

	if(Building[angle][floor][ns][ew] != INF && Building[angle][floor][ns][ew] != NA)
	{
		/********* Between the floor's rooms in the same angle ********/
		new_dist = distance + 1;
		k = ew - 1;
		if(k != -1 && Building[angle][floor][ns][k] > new_dist)
		{
			Building[angle][floor][ns][k] = new_dist;
			opInterFloor(angle, floor, ns, k);
		}

		k = ew + 1;
		if(k != Cube_Dim && Building[angle][floor][ns][k] > new_dist)
		{
			Building[angle][floor][ns][k] = new_dist;
			opInterFloor(angle, floor, ns, k);
		}

		j = ns - 1;
		if(j != -1 && Building[angle][floor][j][ew] > new_dist)
		{
			Building[angle][floor][j][ew] = new_dist;
			opInterFloor(angle, floor, j, ew);
		}

		j = ns + 1;
		if(j != Cube_Dim && Building[angle][floor][j][ew] > new_dist)
		{
			Building[angle][floor][j][ew] = new_dist;
			opInterFloor(angle, floor, j, ew);
		}
		/*********** Between the same floor's rooms having different angles ************/
		j = Cube_Dim - ns - 1;
		k = Cube_Dim - ew - 1;
		rotate_value = Cube_Dim - floor;
		
		new_angle = (angle + 1) % 4;
		new_dist = distance + rotate_value;
		if(Building[new_angle][floor][k][ns] > new_dist)
		{
			Building[new_angle][floor][k][ns] = new_dist;
			if(angle > new_angle)
				opInterFloor(new_angle, floor, k, ns);
		}

		new_angle = (angle + 3) % 4;
		if(Building[new_angle][floor][ew][j] > new_dist)
		{
			Building[new_angle][floor][ew][j] = new_dist;
			if(angle > new_angle)
				opInterFloor(new_angle, floor, ew, j);
		}

		new_angle = (angle + 2) % 4;
		new_dist += rotate_value;
		if(Building[new_angle][floor][j][k] > new_dist)
		{
			Building[new_angle][floor][j][k] = new_dist;
			if(angle > new_angle)
				opInterFloor(new_angle, floor, j, k);
		}

		/********** The rooms of upper floor **********/
		rotate_value--;
		new_dist = distance + 1;
		floor++;
		if(Building[0][floor][ns][ew] > new_dist)
			Building[0][floor][ns][ew] = new_dist;

		new_dist += rotate_value;
		if(Building[1][floor][ns][ew] > new_dist)
			Building[1][floor][ns][ew] = new_dist;

		if(Building[3][floor][ns][ew] > new_dist)
			Building[3][floor][ns][ew] = new_dist;

		new_dist += rotate_value;
		if(Building[2][floor][ns][ew] > new_dist)
			Building[2][floor][ns][ew] = new_dist;
	}
}
void opUpperFloor(int ns, int ew)
{
	int j, k, distance;
	distance = Building[0][End_Floor][ns][ew];

	if(distance != INF && distance != NA)
	{
		distance ++;
		k = ew - 1;
		if(k != -1 && Building[0][End_Floor][ns][k] > distance)
		{
			Building[0][End_Floor][ns][k] = distance;
			opUpperFloor(ns, k);
		}

		k = ew + 1;
		if(k != Cube_Dim && Building[0][End_Floor][ns][k] > distance)
		{
			Building[0][End_Floor][ns][k] = distance;
			opUpperFloor(ns, k);
		}

		j = ns - 1;
		if(j != -1 && Building[0][End_Floor][j][ew] > distance)
		{
			Building[0][End_Floor][j][ew] = distance;
			opUpperFloor(j, ew);
		}

		j = ns + 1;
		if(j != Cube_Dim && Building[0][End_Floor][j][ew] > distance)
		{
			Building[0][End_Floor][j][ew] = distance;
			opUpperFloor(j, ew);
		}
	}
}
void findShortestPath()
{
	int ang, fl, ns, ew, min, j, k;
	for(fl = Start_Floor; fl < End_Floor; fl++)
		for(ang=0; ang<4 ; ang++)
			for(ns = 0; ns<Cube_Dim ; ns++)
				for(ew=0; ew<Cube_Dim; ew++)
					opInterFloor(ang, fl, ns, ew);
	for(ns =0; ns<Cube_Dim; ns++)
	{
		j = Cube_Dim - ns - 1;		
		for(ew=0; ew<Cube_Dim; ew++)
		{
			k = Cube_Dim - ew - 1;
			min = Building[0][fl][ns][ew];
			
			if(Building[1][fl][k][ns] < min)
				min = Building[1][fl][k][ns];

			if(Building[2][fl][j][k] < min)
				min = Building[2][fl][j][k];

			if(Building[3][fl][ew][j] < min)
				min = Building[3][fl][ew][j];

			Building[0][fl][ns][ew] = min;
		}
	}
	for(ns = 0; ns < Cube_Dim; ns++)
		for(ew = 0; ew < Cube_Dim; ew++)
			opUpperFloor(ns, ew);
	printf("%d\n", Building[0][End_Floor][End_NS][End_EW]);
}
void freeSpace(void)
{
	int a, i, j, k, min;
	for(i=0; i<End_Floor; i++)
	{
		for(j=Cube_Dim-1; j>= 0; j--)
		{
			for(k=0; k<Cube_Dim; k++)
			{
				min = INF;
				if(Building[0][i][j][k] == NA)
					printf("X");
				else
					min = Building[0][i][j][k];

				if(Building[1][i][j][k] !=NA && Building[1][i][j][k] < min)
					min = Building[1][i][j][k];

				if(Building[2][i][j][k] !=NA && Building[2][i][j][k] < min)
					min = Building[2][i][j][k];

				if(Building[3][i][j][k] !=NA && Building[3][i][j][k] < min)
					min = Building[3][i][j][k];

				if(min == INF)
					printf("INF\t");
				else
					printf("%d\t", min);
			}
			printf("\n");
		}
		printf("--------------\n");
	}
	for(j=Cube_Dim-1; j>=0; j--)
	{
		for(k=0; k<Cube_Dim; k++)
		{
			if(Building[0][i][j][k] == NA)
				printf("X\t");
			else if(Building[0][i][j][k] == INF)
				printf("INF\t");
			else
				printf("%d\t", Building[0][i][j][k]);
		}
		printf("\n");
	}

	for(a=0; a<4; a++)
	{
		for(i=0; i<Cube_Dim; i++)
		{
			for(j=0; j<Cube_Dim; j++)
				free(Building[a][i][j]);
			free(Building[a][i]);
		}
		free(Building[a]);
	}
}
int main(void)
{
	readInput();
	findShortestPath();
	freeSpace();
	return 0;
}
