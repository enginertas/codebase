#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <string>
#include <netinet/in.h> 
#include <sys/socket.h>

using namespace std;

int Port_Number, Max_Clients, No_of_Stocks, *Free_Stocks, History[10][3], Cur_Cli = 0;
string* Stock_Names;
float **Stock_Prices, Money = 0.0f;
pthread_mutex_t mutex, conn_lock;

void addHistory(int event, int s_id, int amount)
{
	int i, j;
	for(i = 8, j = 9; i >= 0; i--, j--)
	{
		History[j][0] = History[i][0];
		History[j][1] = History[i][1];
		History[j][2] = History[i][2];
	}
	History[0][0] = event;
	History[0][1] = s_id;
	History[0][2] = amount;
}
void readStocks()
{
	int i, j;
	ifstream in;
	in.open("stocks.txt", ifstream::in);

	in >> No_of_Stocks;
	Stock_Names = new string[No_of_Stocks];
	Free_Stocks = new int[No_of_Stocks];
	Stock_Prices = new float*[No_of_Stocks];

	for(i = 0; i < No_of_Stocks; i++)	
	{
		Stock_Prices[i] = new float[15];
		in >> Stock_Names[i];
		in >> Free_Stocks[i];
		for (j = 0; j < 15; j++)
			in >> Stock_Prices[i][j];
	}
	in.close();

	for(i = 0; i < 10; i++)
		History[i][0] = History[i][1] = History[i][2] = 0;
}
void listHistory(int client_id)
{
	int i, co;
	char out[60], buff[5];
	
	pthread_mutex_lock(&mutex);	
	if(!History[0][0])
	{
		out[0] = '\0';
		send(client_id, out, strlen(out), MSG_EOR);
	}
	for(i = 0; i < 10; i++)
	{
		if(History[i][0] == 1)
			strcpy(buff, "BUY");
		else if(History[i][0])
			strcpy(buff, "SELL");
		else
			break;
		
		sprintf(out, "%s %s %d\n", buff, Stock_Names[History[i][1]].c_str(), History[i][2]);
		send(client_id, out, strlen(out), MSG_EOR);
	}	
	pthread_mutex_unlock(&mutex);
}
void listRSI(int client_id)
{
	int i, j;
	float avg_gain, avg_loss, rsi, t;
	char out[100];
	
	for(i = 0; i < No_of_Stocks; i++)
	{
		avg_gain = 0;
		avg_loss = 0;
		for(j = 0; j < 14; j++)
		{
			t = Stock_Prices[i][j] - Stock_Prices[i][j+1];
			if(t < 0)
				avg_loss -= t;
			else
				avg_gain += t;		
		}
		if(avg_loss == 0)
			rsi = 100.0f;
		else 
		{
			avg_gain/=14;
			avg_loss/=14;		
			rsi = 100 - 100/(1 + avg_gain/avg_loss);

		}
		sprintf(out, "%s %.2f\n", Stock_Names[i].c_str(), rsi);
		send(client_id, out, strlen(out), MSG_EOR);
	}
}
void listMarket(int client_id)
{
	int i, j;
	char out[60];

	pthread_mutex_lock(&mutex);

	sprintf(out, "%.2f\n", Money);
	send(client_id, out, strlen(out), MSG_EOR);
	for(i = 0; i < No_of_Stocks; i++)
	{
		sprintf(out, "%s %d ", Stock_Names[i].c_str(), Free_Stocks[i]);
		send(client_id, out, strlen(out), MSG_EOR);
		for(j = 0; j< 15; j++)
		{
			sprintf(out, "%.2f ", Stock_Prices[i][j]);
			send(client_id, out, strlen(out), MSG_EOR);
		}
		sprintf(out, "\n");
		send(client_id, out, strlen(out), MSG_EOR);
	}
	pthread_mutex_unlock(&mutex);
}
void listMe(int client_id, float &acc, int* stocks)
{
	int i, j;
	char out[60];

	pthread_mutex_lock(&mutex);

	sprintf(out, "%.2f\n", acc);
	send(client_id, out, strlen(out), MSG_EOR);
	for(i = 0; i < No_of_Stocks; i++)
	{
		if(stocks[i])
		{
			sprintf(out, "%s %d ", Stock_Names[i].c_str(), stocks[i]);
			send(client_id, out, strlen(out), MSG_EOR);
			for(j = 0; j< 15; j++)
			{
				sprintf(out, "%.2f ", Stock_Prices[i][j]);
				send(client_id, out, strlen(out), MSG_EOR);
			}
			sprintf(out, "\n");
			send(client_id, out, strlen(out), MSG_EOR);
		}
	}
	pthread_mutex_unlock(&mutex);
}
void buy(int client_id, float &acc, int* stocks, int s_id, int no)
{
	char out[60] = "OK\n";
	float total_price;

	pthread_mutex_lock(&mutex);

	total_price = Stock_Prices[s_id][0] * no;
	if (total_price <= acc && no <= Free_Stocks[s_id])
	{
		acc -= total_price;
		Money += total_price;

		Free_Stocks[s_id] -= no;
		stocks[s_id] += no;

		addHistory(1, s_id, no);	
	}
	else if(no > Free_Stocks[s_id])
		sprintf(out, "Not enough stocks: %s\n", Stock_Names[s_id].c_str());	
	else
		sprintf(out, "Not enough money\n");

	send(client_id, out, strlen(out), MSG_EOR);
	pthread_mutex_unlock(&mutex);
}
void sell(int client_id, float &acc, int *stocks, int s_id, int no)
{
	char out[60] = "OK\n";
	float total_price;
	
	pthread_mutex_lock(&mutex);

	total_price = Stock_Prices[s_id][0] * no;
	if (no <= stocks[s_id])
	{
		acc += total_price;
		Money -= total_price;
		if(Money < 0)
			Money = +0.0f;

		Free_Stocks[s_id] += no;
		stocks[s_id] -= no;
		addHistory(2, s_id, no);	
	}
	else
		sprintf(out, "Not enough stocks: %s\n", Stock_Names[s_id].c_str());	


	send(client_id, out, strlen(out), MSG_EOR);
	pthread_mutex_unlock(&mutex);
}
void* commClient(void *param)
{
	char in[100], out[100];
	ssize_t ret_value;
	int client_id, i, ref, order = 0, stock_id = -1, len, j;
	float Account = 2000.0f;
	int *own_stocks;
	
	client_id = atoi((char*)param);
	own_stocks = new int[No_of_Stocks];
	for(i = 0; i < No_of_Stocks; i++)
		own_stocks[i] = 0;

	while(true)
	{
		ret_value = recv(client_id, in, 99, 0);
		if(ret_value > 1)
		{
			in[ret_value - 2] = '\0';
			if(!strcmp(in, "EXIT"))
			{	
				shutdown(client_id, SHUT_RDWR);
				pthread_mutex_lock(&conn_lock);
				Cur_Cli--;
				pthread_mutex_unlock(&conn_lock);				
				pthread_exit(NULL);					
			}
			else if(!strcmp(in, "HIST"))
				listHistory(client_id);
			else if(!strcmp(in, "RSI"))
				listRSI(client_id);
			else if(!strcmp(in, "LISTMARKET"))
				listMarket(client_id);
			else if(!strcmp(in, "LISTME"))
				listMe(client_id, Account, own_stocks);
			else
			{
				len = ret_value - 1;
				/******* Acquiring first word *******/
				for(i = 0; i < len; i++)	
				{
					if(in[i] == ' ' || in[i] == '\t')
					{
						in[i] = '\0';
						break;
					}
				}
				if(i == len)		// If array is not suitable to parse, continue
					continue;
				ref = i + 1;
				/******* Acquring second word *******/
				for(i = ref; i < len; i++)
				{
					if(in[i] == ' ' || in[i] == '\t')
					{
						in[i] = '\0';
						break;
					}
				}
				if(i == len)		// If array is not suitable to parse, continue
					continue;

				/******** Searching stock database *******/
				for(j = 0; j < No_of_Stocks; j++)
				{
					if(!strcmp(&in[ref], Stock_Names[j].c_str()))
					{
						stock_id = j;
						break;
					}
				}
				if(j == No_of_Stocks)	//If stock is not found, return an error message
				{
					sprintf(out, "The stock cannot be found: %s\n", &in[ref]);
					send(client_id, out, strlen(out), MSG_EOR);	
					continue;
				}
				ref = i + 1;
				/******** Getting the amount and directing******/
				order = atoi(&in[ref]);							
				if(!strcmp(in, "SELL"))
					sell(client_id, Account, own_stocks, stock_id, order);
				else if(!strcmp(in, "BUY"))
					buy(client_id, Account, own_stocks, stock_id, order);
			}
		}
	}
}
void listenClients()
{
	pthread_t *new_thread;
	int sock, new_client, new_thread_id;
	socklen_t addr_len;
	struct sockaddr_in server_addr, client_addr;
	char buffer[10];
	
	server_addr.sin_family= AF_INET;
	server_addr.sin_addr.s_addr= INADDR_ANY;
	server_addr.sin_port = htons(Port_Number);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));
	listen(sock, 100);
	addr_len = sizeof(client_addr);

	while(1)
	{	
		new_client = accept(sock, (struct sockaddr *)&client_addr, &addr_len);

		pthread_mutex_lock(&conn_lock);
		Cur_Cli++;
		if(Cur_Cli > Max_Clients)
		{
			shutdown(new_client, SHUT_RDWR);
			Cur_Cli --;
		}		
		pthread_mutex_unlock(&conn_lock);

		new_thread = new pthread_t();
		sprintf(buffer, "%d", new_client);
		new_thread_id = pthread_create(new_thread, NULL, commClient, buffer);
	}
}
void freeAll()
{
	int i;
	delete [] Stock_Names;
	delete [] Free_Stocks;
	for(i = 0; i < No_of_Stocks; i++)
		delete [] Stock_Prices[i];
	delete [] Stock_Prices;
}
int main(int argc, char* argv[])
{
	Port_Number = atoi(argv[1]);
	Max_Clients = atoi(argv[2]);
	readStocks();
	listenClients();
	freeAll();
	return 0;
}
