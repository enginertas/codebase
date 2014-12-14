//============================================================================
// Name        : ceng477_circuitGenerator.cpp
// Author      : rusen
// Version     :
// Copyright   : most rights not reserved
// Description : Input generator for ceng477 2010 HW1, The Racer
//============================================================================

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <math.h>
#include <cstdlib>

#define NUMBER_OF_TYPES 3

#define CLEAR 0
#define OBSTACLE 1
#define ROCKET 2


using namespace std;

int orientation=0;
int pathLength;

int main(int argc, char * argv[]) {

	//get path length as input.
	pathLength=atoi(argv[1]);

	srand(time(NULL));

	//path will first be written in a string.
	char * path=new char[pathLength*4+1];
	std::ostringstream stream;

	//input file containing circuit for our race.
	ofstream outFile;
	outFile.open("METU_F1_2010.txt",ios_base::out);

	//path is created iteratively by randomly generating each step. However,
	int itr;
	int randomNumber;
	int left=CLEAR,middle=CLEAR,right=CLEAR;

	for(itr=0;itr<5;itr++){
		path[itr*4]	=path[(pathLength-itr)*4-4]='_';
		path[itr*4+1]	=path[(pathLength-itr)*4-3]='_';
		path[itr*4+2]	=path[(pathLength-itr)*4-2]='_';
		path[itr*4+3]	=path[(pathLength-itr)*4-1]='\n';
	}

	for(itr=5;itr<pathLength-5;itr++){

	//	depending on this number, we'll decide whether or not put the obstacle.
		randomNumber=rand()%100;
//		cout<<randomNumber<<endl;

		//Turning right and left. 17 turns right, 19 turns left. almost equal probability.
/*
		if (!(randomNumber%17)&&orientation<2){
			path[itr*4]='/';
			path[itr*4+1]='/';
			path[itr*4+2]='/';
			path[itr*4+3]='\n';

			orientation++;

			continue;
		}
		else if (!(randomNumber%19)&&orientation>-2){
			path[itr*4]=92;		// ascii entry for '\'.
			path[itr*4+1]=92;
			path[itr*4+2]=92;
			path[itr*4+3]='\n';

			orientation--;

			continue;
		}

*/

		//these numbers can be changed, however, their least common multiple should be
		//larger than 100, so that entire road is not blocked by obstacles.

		//We also need to keep track of previously blocked parts of the road at each step.
		//otherwise, we might stuck on the way. left,right and middle variables do just that.

		if (!(randomNumber%6)&&(middle!=OBSTACLE||right!=OBSTACLE)) {

			path[itr*4]='X';
			left=OBSTACLE;
		}
		else{
			path[itr*4]='_';
		}

		if (!(randomNumber%7)&&(left!=OBSTACLE||right!=OBSTACLE) )
		{
			path[itr*4+1]='X';
			middle=OBSTACLE;
		}
		else{
			path[itr*4+1]='_';
		}

		if (!(randomNumber%8)&&(left!=OBSTACLE||middle!=OBSTACLE)){
			path[itr*4+2]='X';
			right=OBSTACLE;
		}
		else{
			path[itr*4+2]='_';
		}

		path[itr*4+3]='\n';
		//make a clearance of the paths, each slice of the road consists of three segments.
		//if there are no obstacles in between, the car can pass from one to another without
		//any problem.

		if (left==CLEAR){
			if (path[itr*4+1]=='_')	{
				middle=CLEAR;
				if (path[itr*4+2]=='_')	right=CLEAR;
			}
		}

		if (middle==CLEAR){
			if (path[itr*4]=='_')	left=CLEAR;
			if (path[itr*4+2]=='_')	right=CLEAR;
		}

		if (right==CLEAR){
			if (path[itr*4+1]=='_')	{
				middle=CLEAR;
				if (path[itr*4]=='_')	left=CLEAR;
			}
		}
		//clear, proceed.

	}

	cout<<path<<endl;

	outFile.write(path,pathLength*4);
	outFile.close();

	return 1;
}



