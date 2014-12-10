#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/******************Type Definitions******************/
int depth1,depth2,divide=1;

typedef struct pixel
{
	int red;
	int green;
	int blue;
}pixel;

class Image
{	
	private:	
		pixel pict[512][512];
	public:
		Image();
		~Image();
		void operate(int opNo, int rowSt, int rowFn, int colSt, int colFn);
		void changeHalves(int rowSt,int rowFn,int colSt,int colFn);
		void verticalMirror(int rowSt,int rowFn,int colSt,int colFn);
		void rotate(int rowSt,int rowFn,int colSt,int colFn);
		void invertColor(int rowSt,int rowFn,int colSt,int colFn);
		void imageCopy(Image & ref);
		int getRed(int x, int y);
		int getGreen(int x, int y);
		int getBlue(int x, int y);
		void placeToArray(ifstream & input);
		void writeImage(ofstream & output);
};

class Stack
{
	private:
		typedef struct stackNode
		{
			int opType;
			Image intImage;
			struct stackNode * next;
		}stackNode;
		stackNode * topStack;
	public:
		Stack(Image & ref);
		~Stack();
		bool isEmpty();
		bool isEqual(Image & ref);
		void pop();
		void push(int opNo);
		int retrieveNo();
		void part1(Image & rr, int opNo);
};

/*******************Class Implementations************************/
/*******Image******/
Image::Image(){}

Image::~Image(){}

void Image::operate(int opNo, int rowSt, int rowFn, int colSt, int colFn)
{
	switch(opNo)
	{
		case 1:
			changeHalves(rowSt,rowFn,colSt, colFn);
			break;
		case 2:
			verticalMirror(rowSt,rowFn,colSt, colFn	);
			break;
		case 3:
			rotate(rowSt, rowFn, colSt, colFn);
			break;
		case 4:
			invertColor(rowSt, rowFn, colSt, colFn);
			break;
	}
}

void Image::changeHalves(int rowSt,int rowFn,int colSt,int colFn)
{
	int rowToMiddle,last1, start2, temp,i,j,row1,row2;

	last1=(rowSt+rowFn)/2;		//finding last row of 1st half
	start2=last1+1;      		//finding first row of 2nd half
	rowToMiddle=last1-rowSt;	//finding the number of rows will be seeked.	
	
	for(i=0; i<=rowToMiddle; i++)
	{
		row1=rowSt+i;		//setting 1st row
		row2=start2+i;		//setting 2nd row

		for(j=colSt;j<=colFn;j++)
		{
			temp=pict[row1][j].red;				//changing red values
			pict[row1][j].red=pict[row2][j].red;
			pict[row2][j].red=temp;

			temp=pict[row1][j].green;			//changing green values
			pict[row1][j].green=pict[row2][j].green;
			pict[row2][j].green=temp;
			
			temp=pict[row1][j].blue;			//changing blue values
			pict[row1][j].blue=pict[row2][j].blue;
			pict[row2][j].blue=temp;
		}		
	}
}

void Image::verticalMirror(int rowSt,int rowFn,int colSt,int colFn)
{
	int colToMiddle,temp,i,j,col1,col2;

	colToMiddle=(colSt+colFn)/2-colSt;	//finding the number of coloumn pairs to be changed
	
	for(j=0; j<=colToMiddle; j++)
	{
		col1=colSt+j;		//setting first coloumn
		col2=colFn-j;		//setting mirror coloumn
		
		for(i=rowSt;i<=rowFn;i++)
		{
			temp=pict[i][col1].red;				//changing red values
			pict[i][col1].red=pict[i][col2].red;
			pict[i][col2].red=temp;

			temp=pict[i][col1].green;			//changing green values
			pict[i][col1].green=pict[i][col2].green;
			pict[i][col2].green=temp;
			
			temp=pict[i][col1].blue;			//changing blue values
			pict[i][col1].blue=pict[i][col2].blue;
			pict[i][col2].blue=temp;
		}		
	}
}

void Image::rotate(int rowSt, int rowFn, int colSt, int colFn)
{
	int i,j, temp, last1,start2;

	last1=(rowSt+rowFn)/2;		//setting last of first rows
	start2=last1+1;			//setting first of second rows

	for(i=rowSt; i<=last1; i++)
		for(j=colSt ; j<=colFn; j++)
		{
			temp=pict[i][j].red;			//R<-G<-B rotation
			pict[i][j].red=pict[i][j].green;
			pict[i][j].green=pict[i][j].blue;
			pict[i][j].blue=temp;
		}
	for(i=start2; i<=rowFn; i++)
		for(j=colSt ; j<=colFn; j++)
		{
			temp=pict[i][j].blue;			//B<-G<-R rotation
			pict[i][j].blue=pict[i][j].green;
			pict[i][j].green=pict[i][j].red;
			pict[i][j].red=temp;
		}
}

void Image::invertColor(int rowSt,int rowFn, int colSt, int colFn)
{
	int i, j, lastRow1, startRow2, lastCol1, startCol2;

	lastRow1=(rowSt+rowFn)/2;	//setting last of first rows
	startRow2= lastRow1+1;		//setting first of last rows

	lastCol1=(colSt+colFn)/2;	//setting last of first coloumns
	startCol2=lastCol1+1;		//setting first of last coloumns

	for(i=rowSt; i<=lastRow1; i++)
		for(j=colSt ; j<=lastCol1; j++)
		{
			pict[i][j].red=depth1-pict[i][j].red;		//Inverting by subtracting from 255
			pict[i][j].green=depth1-pict[i][j].green;
			pict[i][j].blue=depth1-pict[i][j].blue;
		}
	for(i=startRow2; i<=rowFn; i++)
		for(j=startCol2 ; j<=colFn; j++)
		{
			pict[i][j].red=depth1-pict[i][j].red;		//Inverting by subtracting from 255
			pict[i][j].green=depth1-pict[i][j].green;
			pict[i][j].blue=depth1-pict[i][j].blue;
		}
}

void Image::imageCopy(Image & ref)
{
	int i,j;

	for(i=0;i<512;i++)
		for(j=0; j<512;j++)		//deep copy of image
		{
			pict[i][j].red = ref.getRed(i,j);
			pict[i][j].green = ref.getGreen(i,j);
			pict[i][j].blue = ref.getBlue(i,j);
		}
}

int Image::getRed(int x, int y)
{	
	return pict[x][y].red;
}

int Image::getGreen(int x, int y)
{	
	return pict[x][y].green;
}

int Image::getBlue(int x, int y)
{	
	return pict[x][y].blue;
}

void Image::placeToArray(ifstream & input)
{
	string str;
	int i,j;

	input>>str; input>>depth1; input>>depth1; input>>depth1;		//taking 4 irrelevant input	
	
	for(i=0;i<512;i++)
		for(j=0;j<512;j++)
		{
			input>>pict[i][j].red;		//retrieving the color codes
			input>>pict[i][j].green;
			input>>pict[i][j].blue;
	 	}
	input.close();				//closing the file
}

void Image::writeImage(ofstream &output)
{
	int i,j;	

	output<<"P3"<<endl;		//writing type size and color depth
	output<<512<<'\t'<<512<<endl;
	output<<depth1<<endl;
	
	for(i=0;i<512;i++)
	{
		for(j=0;j<512;j++)
		{
			output<<pict[i][j].red<<'\t';		//writing color codes
			output<<pict[i][j].green<<'\t';
			output<<pict[i][j].blue<<'\t';
	 	}
		output<<endl;					//ending the line
	}
	output.close();						//closing the file
}
/*******************Stack*******************/
Stack::Stack(Image & ref)
{
	topStack=new stackNode;
	topStack->opType=-1;			//showing end of operations
	(topStack->intImage).imageCopy(ref);	//deep copy of image
	topStack->next=NULL;
}

Stack::~Stack()
{
	while(!isEmpty())	//while stack is not empty
		pop();		//delete all nodes
			
	delete topStack;	//delete the first node

}
bool Stack::isEmpty()
{
	return topStack->next==NULL;

}

bool Stack::isEqual(Image & ref)		
{
	int i,j;

	for(i=0;i<512;i++)
		for(j=0;j<512;j++)			//only one inequality is sufficient
		{	if((ref.getRed(i,j)!=(topStack->intImage).getRed(i,j))  ||
				(ref.getGreen(i,j)!=(topStack->intImage).getGreen(i,j)) ||
					(ref.getBlue(i,j)!=(topStack->intImage).getBlue(i,j)))

				return false;

		}
	return true;	//if equality exist return true
}

void Stack::pop()
{	
	stackNode *oldNode;
	
	oldNode=topStack;		//advancing topStack and selecting old node
	topStack=topStack->next;

	delete oldNode;
	divide/=2;		//decreasing region size

}

void Stack::push(int opNo)
{
	stackNode * newNode;
	
	newNode=new stackNode;		//allocating space for new node
	newNode->opType=opNo;		//setting operation to be done
	
	newNode->next=topStack;	
	
	(newNode->intImage).imageCopy(topStack->intImage);	//copying the image	
	part1(newNode->intImage,opNo);			//applying all operations required	
	
	topStack=newNode;					//setting topStack to newNode	
}	

int Stack::retrieveNo()
{
	return topStack->opType;
}

void Stack::part1(Image & rr, int opNo)
{
	int rowStart,rowEnd, colStart, colEnd,period,nextRow,nextCol;

	period=512/divide;				//calculating the period			
	for(rowStart=0;rowStart<512;rowStart=nextRow)
	{
		nextRow=rowStart+period;		//setting the next start
		rowEnd=nextRow-1;			//setting the end of the rows
			
		for(colStart=0;colStart<512;colStart=nextCol)
		{
			nextCol=colStart+period;	//setting the next start	
			colEnd=nextCol-1;		//setting end of rows
			rr.operate(opNo, rowStart, rowEnd, colStart, colEnd);	//callng appropriate func.
		}
	}
	divide*=2;	//incresing number of fields for next time
}

/****************helper functions****************/
void part1(Image & rr, int opNo)
{
	int rowStart,rowEnd, colStart, colEnd,period,nextRow,nextCol;

	period=512/divide;				//calculating the period			
	for(rowStart=0;rowStart<512;rowStart=nextRow)
	{
		nextRow=rowStart+period;		//setting the next start
		rowEnd=nextRow-1;			//setting the end of the rows
			
		for(colStart=0;colStart<512;colStart=nextCol)
		{
			nextCol=colStart+period;	//setting the next start	
			colEnd=nextCol-1;		//setting end of rows
			rr.operate(opNo, rowStart, rowEnd, colStart, colEnd);	//callng appropriate func.
		}
	}
	divide*=2;	//incresing number of fields for next time
}

/*****************main:function body***********************/
int main(int argc, char *argv[])
{
	int mode,no,c;
	string inputFile, outputFile;
	Image firstImage;	

	mode=atoi(argv[1]);		//taking first 3 input
	inputFile=argv[2];
	outputFile=argv[3];
	
	ifstream in(inputFile.c_str());		//opening file to input
	firstImage.placeToArray(in);
	
	if(mode==1)
	{
		cin>>no;	//getting the first operation no
		while(no!=-1)
		{
			part1(firstImage, no);
			cin>>no;			//getting new character
		}
		ofstream out(outputFile.c_str());	//opening file to output
		firstImage.writeImage(out);	//writing the image to the file
	}	
	
	else
	{
		int opArray[9],length=0,iop;

		depth2=atoi(argv[4]);		//getting depth for second operation		
		
		ifstream end(outputFile.c_str());	//getting string to open file for reading
		
		Image endImage;			//getting 2nd image
		endImage.placeToArray(end);	
		
		Stack operations(firstImage);		//operation stack is defined and first image is loaded
		
		while(!operations.isEqual(endImage))
		{
			if(length<depth2)	//if we have more choice to push more push
			{
				operations.push(1);
				length++;
			}
			else				//if we don't have
			{
				c=operations.retrieveNo();
				if(c<4)				//if we have choice in same depth:: try
				{
					operations.pop();	//backtrack
					operations.push(c+1);
				}
				else
				{
					while(c==4)			//if we don't have any choice pop until finding new choice
					{
						operations.pop();		//backtrack
						length--;
						c=operations.retrieveNo();
					}
					operations.pop();		//after finding, change!!
					operations.push(c+1);
				}
			}
		}
		for(iop=0;(c=operations.retrieveNo())!=-1;iop++)		//printing the sequence 
		{
			operations.pop();
			opArray[iop]=c;
		}
				
		iop--;
		for(;iop>=0;iop--)
			cout<<opArray[iop]<<" ";		
		
		
	}	
}



