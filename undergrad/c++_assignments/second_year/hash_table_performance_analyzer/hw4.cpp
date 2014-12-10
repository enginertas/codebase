#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

unsigned A,B,C,D,E,wordCount=0;

typedef struct hashWord
{
	string wordName;
	unsigned startPos;
	unsigned endPos;
	unsigned startWord;
	unsigned endWord;
	unsigned referenceNo;
} hashWord;

/**************class definition*******************/
class HashTable
{
	private:
		int funcType;
		int probType;
		int tableSize;
		hashWord * table;

		unsigned func1(string x);
		unsigned func2(string x);

	public:
		HashTable(int pType, int fType, int tSize);
		~HashTable();
		void placeToTable(string x, int linePos, int wordPos);
		void makeQuery(string x);
		double calcAverage(void);
};

/*******************class implementation**********/
HashTable::HashTable(int pType, int fType, int tSize):probType(pType), funcType(fType), tableSize(tSize)
{
	table= new hashWord[tableSize];
}

HashTable::~HashTable()
{
	delete [] table;
}

void HashTable::placeToTable(string x, int linePos, int wordPos)
{
	int place,i;

	if(funcType==1)			//determining first array to place
		place=func1(x);
	else
		place=func2(x);

	//searching empty node
	if(probType==1)			//if linear probing is active go one by one
		while(table[place].referenceNo && table[place].wordName!=x)	//loop until finding empty cell or the cell with same name
			place= (place + 1) % tableSize;

	else			//else go quadratic
		for(i=1;table[place].referenceNo && table[place].wordName!=x;i+=2) //loop until finding empty cell or the cell with same name
			place= (place + i) %tableSize;

	if(!table[place].referenceNo)		//if empty cell is found
	{
		table[place].wordName=x;
		table[place].startPos = table[place].endPos = linePos;		//set the start and end positions same
		table[place].startWord = table[place].endWord = wordPos;
		table[place].referenceNo=1;
	}
	else		//if cell with the same name is found
	{
		table[place].endPos=linePos;		//update last line and word positions
		table[place].endWord=wordPos;
		table[place].referenceNo++;		//update reference numbers
	}
}

unsigned HashTable::func1(string x)
{
	unsigned place=0, i ,length;

	length=x.length();
	for(i=0; i<length; i++)
		place=((place<<A) + (place>>B) + ((unsigned)x[i] % C)) & 0xFFFFFFFF;

	return place%tableSize;
}

unsigned HashTable::func2(string x)
{
	unsigned place=1, i , length;

	length=x.length();
	for(i=0; i<length; i++)
		place=(place * ((unsigned)x[i] % D) + E) & 0xFFFFFFFF;

	return place%=tableSize; 
}

double HashTable::calcAverage(void)
{
	int totalProbes=0, i, j, place;
	wordCount=0;		//reseting the wordCount

	if(funcType==1)
	{
		if(probType==1)
		{
			for(i=0; i<tableSize; i++)
				if(table[i].referenceNo)	//if word is found in cell
				{
					place=func1(table[i].wordName);
					totalProbes++;

					for(;table[place].wordName != table[i].wordName; totalProbes++)	//loop until finding the cell with same name
						place= (place + 1) % tableSize;

					wordCount++;
				}
		}
		else
		{
			for(i=0; i<tableSize; i++)
				if(table[i].referenceNo)	//if word is found in cell
				{
					place=func1(table[i].wordName);
					totalProbes++;

					for(j=1;table[place].wordName != table[i].wordName; j+=2) //loop until finding the cell with same name
					{
						place= (place + j) % tableSize;
						totalProbes++;
					}
					wordCount++;
				}
		}
	}
	else if(probType==1)
	{
		for(i=0; i<tableSize; i++)
			if(table[i].referenceNo)	//if word is found in cell
			{
				place=func2(table[i].wordName);
				totalProbes++;

				for(;table[place].wordName != table[i].wordName; totalProbes++)	//loop until finding the cell with same name
					place= (place + 1) % tableSize;

				wordCount++;
			}
	}
	else
	{
		for(i=0; i<tableSize; i++)
			if(table[i].referenceNo)	//if word is found in cell
			{
				place=func2(table[i].wordName);
				totalProbes++;

				for(j=1;table[place].wordName != table[i].wordName; j+=2) //loop until finding the cell with same name
				{
					place= (place + j) % tableSize;
					totalProbes++;
				}
				wordCount++;
			}
	}
	return (double)totalProbes/wordCount;	//find the average
}

void HashTable::makeQuery(string x)
{
	int i, place;

	if(funcType==1)			//determining first place to look
		place=func1(x);
	else
		place=func2(x);

	if(probType==1)		//if linear probing is active go one by one
		while(table[place].wordName != x)	//loop until finding the cell with same name
			place= (place + 1) % tableSize;

	else		//else go quadratic
		for(i=1;table[place].wordName != x; i+=2) //loop until finding the cell with same name
			place= (place + i) % tableSize;

	cout<<table[place].wordName<<' '<<table[place].startPos<<':'<<table[place].startWord<<' ';
	cout<<table[place].endPos<<':'<<table[place].endWord<<' '<<table[place].referenceNo;
	cout<<endl;
}

/************helper function**************//***reading from input file****/
void readInput(ifstream &in, HashTable &linear1, HashTable &quadratic1, HashTable &linear2, HashTable &quadratic2)
{
	char ch;
	int i, lineCount=1, wordInLine=1, sizex;
	string query;
	vector<char> conjunctions;

	in.get(ch);
	while(!in.eof())		//while eof is not reached, loop
	{
		if(isspace(ch))
		{
			if(ch=='\n')
			{	
				if(query!="")
				{
					linear1.placeToTable(query,lineCount,wordInLine);
					quadratic1.placeToTable(query,lineCount,wordInLine);
					linear2.placeToTable(query,lineCount,wordInLine);
					quadratic2.placeToTable(query,lineCount,wordInLine);

					conjunctions.clear();	//clear the conjunctions
					query="";		//set query to null
				}
				wordInLine=1;		//set the position of the word to start
				lineCount++;		//increase the line position
			}
			else if(query!="")
			{
				linear1.placeToTable(query,lineCount,wordInLine);
				quadratic1.placeToTable(query,lineCount,wordInLine);
				linear2.placeToTable(query,lineCount,wordInLine);
				quadratic2.placeToTable(query,lineCount,wordInLine);

				wordInLine++;		//get the position of the word in the line
				query="";		//set query to null
				conjunctions.clear();	//clear the conjunctions
			}
		}

		else if(ch=='.'||ch==','||ch==':'||ch==';'||ch=='?'||ch=='\''||ch=='!'||ch=='\"'||ch=='('||ch==')')
		{
			if(query!="")
				conjunctions.push_back(ch);	//add conjuctions to vector
		}
		else
		{
			sizex=conjunctions.size();

			for(i=0;i<sizex; i++)
				query+=conjunctions[i];

			conjunctions.clear();		//clear the conjuctions
			query+=ch;		//update the string
		}
		in.get(ch);		//take a new character
	}
	in.close();		//closing the file
}

int main(int argc, char *argv[])
{
	ifstream input;
	string query;
	unsigned argcx,tsize,i;
	double l1,l2,q1,q2;

	input.open(argv[1]);	//opening the book
	tsize=atoi(argv[2]);
	A=atoi(argv[3]);
	B=atoi(argv[4]);
	C=atoi(argv[5]);
	D=atoi(argv[6]);
	E=atoi(argv[7]);

	HashTable linear1(1,1,tsize), quadratic1(2,1,tsize), linear2(1,2,tsize), quadratic2(2,2,tsize);	//creating 4 hash tables
	readInput(input, linear1, quadratic1, linear2, quadratic2);

	/***printing the average results*********/
	l1=linear1.calcAverage();
	q1=quadratic1.calcAverage();
	l2=linear2.calcAverage();
	q2=quadratic2.calcAverage();	

	cout<<wordCount<<" unique words"<<endl;
	cout<<"Linear Probing, Hash#1: "<<l1 <<endl;
	cout<<"Quadratic Probing, Hash#1: "<< q1 <<endl;
	cout<<"Linear Probing, Hash#2: "<< l2 <<endl;
	cout<<"Quadratic Probing, Hash#2: "<< q2 <<endl;

	/*****printing the queries*********/
	argcx=argc;
	for(i=8; i<argcx ; i++)
	{
		query=argv[i];
		linear1.makeQuery(query);
	}
	return 0;
}
