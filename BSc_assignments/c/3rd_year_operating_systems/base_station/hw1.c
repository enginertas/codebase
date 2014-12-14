#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

void* malloc(size_t size);
void free(void* x);
int care1_omit0=0, Signal_Received=0;

int isNotEnd(char *active, int x)/*******If calls still exist, it returns "true"*******/
{
	int i;
	for(i=0;i<x;i++)
		if(active[i])
			break;
	return i!=x;
}
void clearBuffer(char *buff)	/*****clears the buffer*****/
{
	while(*buff)
		*buff='\0';
}
void care()	/*******cares if SIGUSR1 comes*****/
{
	care1_omit0=1;
	Signal_Received=1;
}
void omit()	/*******omits the signal which is sent******/
{
	care1_omit0=0;
	Signal_Received=1;
}
void baseStation(int** to_main, int pid[], int children)	/********Code for base station after fork()*********/
{
	int i, call_time=0, time=0, index=-1, index2;
	char buffer[20], *is_active;

	signal(SIGUSR1, care);		/*********Signal handlers**********/
	signal(SIGUSR2, omit);
	signal(SIGCHLD, care);
	is_active=(char*)malloc(sizeof(char)*children);

	for(i=0; i<children; i++)	/*****Creating checkpoints for each child*****/
		is_active[i]=1;
		
	while(isNotEnd(is_active, children))	/*****If calls still exist, loop until calls are over*****/
	{
		if(call_time)		/*******If base station is busy, continue with this part of code*******/
		{
			for(i=0; i<children; i++)
				if(is_active[i])		
				{
					if(index==i)	/**If user[i] is calling now, send a signal(second)*/
					{
						kill(pid[i],SIGUSR1);
						if(!Signal_Received)
							pause();
						Signal_Received=0;
					}
					else	/*******If user[i] is requesting, reject user[i]*******/
					{
						kill(pid[i],SIGUSR2);					
						if(!Signal_Received)
							pause();
						Signal_Received=0;
						if(care1_omit0)
							printf("time %d user %d rejected\n", time, i);
					}
				}	
		}
		else
		{	
			index2=index;
			if(index!=-1)	/*****If user[index] has no calls, set user inactive*****/
			{
				care1_omit0=0;
				kill(pid[index], SIGUSR2);
				if(!Signal_Received)
					pause();
				Signal_Received=0;
				if(care1_omit0)
					is_active[index]=0;

				index=-1;				
			}
			for(i=0; i<children; i++)
			{
				if(is_active[i]&& i!=index2) 	/**Seek active children apart from last caller**/
				{
					kill(pid[i],SIGUSR1);
					if(!Signal_Received)
						pause();
					Signal_Received=0;
					if(care1_omit0)		/***If user is not sleeping, accept it and break loop***/
					{
						read(to_main[i][0], buffer, 20);;						
						call_time=atoi(buffer);
						index=i;
						printf("time %d user %d accepted for %d seconds\n", time, i, call_time);
						clearBuffer(buffer);
						i++;
						break;
					}
				}
			}
			if(index2>=0&&is_active[index2]) 	/***Control last caller, if it is active***/
			{
				if(index==-1) 	/*If we couldn't find any other user, continue with last caller*/
				{
					kill(pid[index2],SIGUSR1);
					if(!Signal_Received)	/****Wait for "written" signal****/
						pause();
					Signal_Received=0;
					if(care1_omit0)	
					{
						read(to_main[index2][0], buffer, 20);	/***accept it, and break loop***/
						call_time=atoi(buffer);
						index=index2;
						printf("time %d user %d accepted for %d seconds\n", time, index2, call_time);
						clearBuffer(buffer);
					}				
				}
				else	/**If we found new caller, reject old caller**/
				{
					kill(pid[index2],SIGUSR2);					
					if(!Signal_Received)
						pause();
					Signal_Received=0;
					if(care1_omit0)
						printf("time %d user %d rejected\n", time, index2);
				}
			}
			for(;i<children; i++)		/***After accepting, reject other requests***/
			{
				if(is_active[i])
				{
					kill(pid[i],SIGUSR2);
					if(!Signal_Received)
						pause();
					Signal_Received=0;
					if(care1_omit0)					
						printf("time %d user %d rejected\n", time, i);
				}
			}
		}
		time++;
		if(call_time)call_time--;	/***If station is busy, decrease elapsed time***/
		sleep(1);
	}
	free(is_active);
}

void callRespectively(int to_main, int index)
{
	int call_time, no_of_calls, i, sleep_time=0;
	pid_t parent_id;
	FILE *fp, *fout;
	char str[20], ind[3], buffer[20];
	
	signal(SIGUSR1, care);	/****Signal handlers****/
	signal(SIGUSR2, omit);
	parent_id=getppid();

	strcpy(str,"user");		/****Determine input file and open it****/
	sprintf(ind, "%d", index);
	strcat(str, ind);
	strcat(str,".inp");
	fp=fopen(str, "r");
	
	strcpy(str,"user");		/****Determine output file and open it***/
	sprintf(ind, "%d", index);
	strcat(str, ind);
	strcat(str,".out");
	fout=fopen(str, "w");
	
	fscanf(fp, "%d", &no_of_calls);
	for(i=0; i<no_of_calls; i++)	/**Loop until all calls are done!**/
	{	
		fscanf(fp, "%d", &call_time);		
		sprintf(buffer, "%d", call_time);
		while(1)
		{
			if(!Signal_Received)	
			 	pause();
			Signal_Received=0;
			
			if(sleep_time)	/***If process is sleeping, don't start calling***/
			{
				fprintf(fout, "waiting\n");
				kill(parent_id, SIGUSR2);
				sleep_time--;
			}
			else if(care1_omit0)  /***If call is accepted, call the station!***/
			{
				write(to_main, buffer, 20);
				kill(parent_id, SIGUSR1);
				break;
			}
			else	/***If call is not accepted, sleep [1-5] minutes***/
			{
				fprintf(fout, "waiting\n");
				kill(parent_id, SIGUSR1);
				srand(time(NULL)+parent_id+getpid());
				sleep_time=rand()%5;
			}			
		}
		for(care1_omit0=1;1;)	/***If call is continuing, decrease the time***/
		{
			fprintf(fout,"calling\n");
			if(!Signal_Received)
				pause();
			Signal_Received=0;
			if(care1_omit0)		/***If call is continuing, decrease the time***/
			{	
				kill(parent_id, SIGUSR2);
				--call_time;
			}
			else	/***If call is ended, continue with next call***/
			{
				if(i!=no_of_calls)				
					kill(parent_id, SIGUSR2);
				break;
			}	
		}
		clearBuffer(buffer);
	}
	fclose(fp);	/*****close the files*****/
	fclose(fout);
	kill(parent_id, SIGUSR1);
}
int main(int argc, char** argv)
{
	int i, no_of_children, **pipes_to_main, *pid_of_children; 
	size_t size_fd;
	pid_t current_pid;

	no_of_children=atoi(argv[1]);
	size_fd=2*sizeof(int);
	pipes_to_main=(int **)malloc(no_of_children * sizeof(int*));
	pid_of_children=(int*)malloc(no_of_children * sizeof(int));

	for(i=0; i<no_of_children; i++)
	{	
		pipes_to_main[i]=(int*)malloc(size_fd);
		pipe(pipes_to_main[i]);
		current_pid=fork();

		if(current_pid)		/***if it's parent (base station)***/
		{
			pid_of_children[i]=current_pid;
			printf("%d\n", current_pid);
			close(pipes_to_main[i][1]);
		}		
		else			/***if it's child (user)***/
		{
			close(pipes_to_main[i][0]);
			callRespectively(pipes_to_main[i][1], i);
			return 0;
		}
	}
	baseStation(pipes_to_main, pid_of_children, no_of_children);
	return 0;
}
