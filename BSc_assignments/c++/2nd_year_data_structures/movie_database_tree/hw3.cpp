#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

typedef struct TreeNode
{
	string name;
	int nodeType;
	vector<struct TreeNode *> edges;
} TreeNode;

typedef struct BiNode
{
	string name;
	struct BiNode *left;
	struct BiNode *right;
	vector<TreeNode *> films;		
	
}BiNode;

TreeNode * root, *searchPointer;
BiNode *rootBST= NULL;
bool isOk=false;
vector<TreeNode *> LastNodes;

/****************search operation in Movie Tree************/
TreeNode *hlpSearch(string x, TreeNode *tp)	//returns upper node of result
{
	TreeNode *subPtr;
	int sizex,i;
		
	if(x==tp->name)		//if element is found
	{
		searchPointer=tp;	//save the place of element
		return tp;		//return itself
	}					
	else if(tp->nodeType)		//if leaf node return null
	{
		sizex=tp->edges.size();
		for(i=0; i<sizex; i++)		//else search the element in nodes in edges
		{
			subPtr=hlpSearch(x,tp->edges[i]);
			if(subPtr)
				if(isOk) 
					return subPtr;		//if upper node is found, return result
				else
				{
					isOk=true;		//if found one is in edges return result as a upper node
					return tp;			
				} 
		}
		
	}	
	return NULL;
}
TreeNode * searchInTree(string x)
{
	isOk=false;		//delete the precedessor result
	return hlpSearch(x, root);	//call helper function
}
/*****************searching in BST***************/
BiNode * searchInBST(string x, BiNode * t)
{
	if(!t)
		return NULL;
	else if(x< t->name)
		return searchInBST(x, t->left);
	else if(x>t->name)
		return searchInBST(x, t->right);
	else
		return t;
}
/******************finding the minimum element***********/
BiNode *minNode( BiNode *t )
{
   if(!t)
       return NULL;
   if(!t->left)
       return t;
   return minNode( t->left );
}
/*********************Add operation of movies*****************/
void addActor(string x, TreeNode *film, BiNode *&t)	//adding an actor to tree
{
	if(!t)		
	{
		t = new BiNode;
		t->name=x;
		(t->films).push_back(film);
		t->left=t->right=NULL;
	}
	else if( x < t->name )
		addActor(x,film,t->left);
	else if( t->name < x )
		addActor(x,film,t->right);
	else
		(t->films).push_back(film);
}

void eliminateNodes(int &tabNo, int &size)
{
	int typeCounter=0;
	while(tabNo<size)
	{
		LastNodes[size]->nodeType=typeCounter;
		if(!typeCounter)
			addActor(LastNodes[size]->name, LastNodes[size-1], rootBST);

		typeCounter++;
		LastNodes.pop_back();
		size--;
	}
	tabNo=0;
}

void addMovies(ifstream &in)
{
	char ch;
	int i,size=0, tabNo=0;
	string opString, buf_String;
	bool isFound=false;
	TreeNode *newRoot=NULL,*tmpRoot=NULL,*newNode=NULL;
	
	in.get(ch);		//get the first character
	
	if(root->edges.empty())		//if edges of root is empty construct a new tree
	{
		while(!in.eof())		//if position is not EOF
		{
			if(ch=='\t')
					tabNo++;	//increase indentity
			else if(ch=='\n')
			{
				eliminateNodes(tabNo,size);	//erase nodes which are completed

				newNode = new TreeNode;		//create a new node
				newNode->name = opString;
								
				LastNodes[size]->edges.push_back(newNode);	//add new created node to LastNodes vector
				LastNodes.push_back(newNode);
				size++;
								
				opString="";
			}
			else if(ch==' ')
				opString+=" ";		//if there is a white space add to String
										
			else
			{
				in.unget();		//if character is taken, give character to buffer, and get the string
				in>>buf_String;
				opString+=buf_String;
			}
			in.get(ch);	//get a new character
		}	
		eliminateNodes(tabNo,size);	//when EOF is taken, delete all LastNodes entries			
	}
	
	else
	{
		vector<TreeNode *> nodesToBeAdded;	//create a new vector to use in addition to the tree
		while(!in.eof())
		{
			if(ch=='\t')		//if tab is taken, increase the indentity
				tabNo++;
			else if(ch=='\n')	
			{
				if(tabNo)		//if input is indented add to LastNodes
				{
					eliminateNodes(tabNo,size);	//pop completed inputs
					
					newNode = new TreeNode;
					newNode->name = opString;
								
					LastNodes[size]->edges.push_back(newNode);	//create a new node and add to the relevant node
					LastNodes.push_back(newNode);
					
				}
				else		//if input is not indented
				{
					tmpRoot=searchInTree(opString);			//search opString in root
					
					if(tmpRoot)			//if entry is found
					{
						isFound=true;			//set isFound as true, and select a new root for addition later
						newRoot=tmpRoot;		
						
						eliminateNodes(tabNo,size);	//pop completed inputs
						LastNodes.push_back(searchPointer);	//add found node to vector to add new elements to tree
					}
					else	//if entry is not found
					{
						eliminateNodes(tabNo,size);	//pop completed inputs
						
						newNode = new TreeNode;		//add new element to vector
						newNode->name = opString;
						
						LastNodes.push_back(newNode);
						nodesToBeAdded.push_back(newNode);		//and the list to be added
						
					}
					
				}
				opString="";
				size++;			//increase the size and empty the opString
				
			}
			else if(ch==' ')
				opString+=" ";		//if space is taken add it to the opString
										
			else
			{				//if character is taken get all string
				in.unget();
				in>>buf_String;
				opString+=buf_String;
			}
			in.get(ch);		//get new character
		}	
		eliminateNodes(tabNo,size);	//pop all inputs in LastNode
				
		if(!isFound) newRoot=root;	//if newroot is not specified assign newRoot to root
		
		size=nodesToBeAdded.size();			
		for(i=0;i<size;i++)					//add nodesToBeAdded to root
			newRoot->edges.push_back(nodesToBeAdded[i]);
				
		nodesToBeAdded.clear();		//clear nodeToBeAdded
		
	}
	LastNodes.erase(LastNodes.begin()+1,LastNodes.end());	//erase apart from root
	in.close();		//close the file
	
}
/********************print movies********************/
void hprtMovies(TreeNode *r, ofstream &outx, int nTab)
{
	int i,s, j;
	string tabString="";
	
	outx<< r->name;	
	
	s=(r->edges).size();
	
	for(j=0;j<nTab;j++)		//adjust the indentity
		tabString+='\t';
		
	nTab++;	
	for(i=0; i<s; i++)		//printing for level-nodes
	{
		outx<<endl;
		
		outx<<tabString;
		
		hprtMovies(r->edges[i], outx, nTab);
	}
}
void printMovies(ofstream &out)		//printing the movies
{
	int i,s;
	s=(root->edges).size();		
	
	for(i=0; i<s; i++)		//writing to file for each tree
	{
		hprtMovies(root->edges[i], out, 1);
		out<<endl;	
	}
	out.close();		//closing the file
}
/******************printing the actors*****************/
void hprtActors(BiNode *t, ofstream &out, int tabNo)
{
	int i,j,sizex;
	string tabString="";
	if (t) {
		sizex=(t->films).size();		
		out<<'+'<< t->name;
		
		for(j=0; j<tabNo; j++)
			tabString+='\t';

		for(i=0;i<sizex;i++)
		{	
			out<<endl;			
			out<<tabString<< (t->films[i])->name;
		}
		tabString+='\t';		
		tabNo++;
		
		if(t->left)
			if(t->right)
			{	
				out<<endl;
				out<<tabString;		
				hprtActors(t->left, out, tabNo);

				out<<endl;
				out<<tabString;
				hprtActors(t->right, out, tabNo);
			}
			else
			{		
				out<<endl;
				out<<tabString;		
				hprtActors(t->left, out, tabNo);
				out<<endl;
				out<<tabString<<'-';
			}
		else if(t->right)
		{	
			out<<endl;
			out<<tabString<<'-';	
			out<<endl;
			out<<tabString;		
			hprtActors(t->right, out, tabNo);
			
		}
		else ;
	}		
}	
void printActors(ofstream &out)
{		
	hprtActors(rootBST, out, 0);
	out<<endl;
	out.close();
}

/*******************listmoviesof operation***********/
void hlpMoviesOf(string x, ofstream &out, BiNode * rootBST)
{
	int i,sizex;	
	if(rootBST)
		if(x==rootBST->name)
		{
			sizex=(rootBST->films).size();
			for(i=0; i<sizex; i++)
			{
				out<<(rootBST->films[i])->name;
				out<<endl;
			}
		}
		else if(x<rootBST->name)
			hlpMoviesOf(x, out, rootBST->left);
		else if(x>rootBST->name)
			hlpMoviesOf(x, out, rootBST->right);
}

void listMoviesOf(string x, ofstream &out)
{
	hlpMoviesOf(x, out, rootBST);
	out.close();

}
/*************ListofCoactors***********************/
void hlpCoactors(string x, ofstream &out, BiNode * rootBST)
{
	int i,sizex, j, sizey;	
	if(rootBST)
		if(x==rootBST->name)
		{
			sizex=(rootBST->films).size();
			for(i=0; i<sizex; i++)
			{
				sizey=(rootBST->films[i])->edges.size();
				for(j=0; j<sizey; j++)
				{
					if(rootBST->name!=((rootBST->films[i])->edges[j])->name)
					{
						out<<((rootBST->films[i])->edges[j])->name;
						out<<endl;
					}
				}
			}
		}
		else if(x<rootBST->name)
			hlpCoactors(x, out, rootBST->left);
		else if(x>rootBST->name)
			hlpCoactors(x, out, rootBST->right);
}

void listCoActors(string x, ofstream &out)
{
	hlpCoactors(x, out, rootBST);
	out.close();
}
/****************removing the actor*************/
void swapActors(BiNode *x, BiNode *y)
{
	BiNode *tmpx=NULL;
	int i,sizex;
	
	tmpx=new BiNode;
	tmpx->name=x->name;
	
	sizex = (x->films).size();
	for(i=0;i<sizex;i++)
		tmpx->films.push_back(x->films[i]);

	x->name=y->name;
	
	x->films.clear();
	sizex=(y->films).size();

	for(i=0;i<sizex;i++)
		x->films.push_back(y->films[i]);
	
	y->name=tmpx->name;
	
	y->films.clear();
	sizex=(tmpx->films).size();

	for(i=0;i<sizex;i++)
		y->films.push_back(tmpx->films[i]);

	delete tmpx;
}
void removeActor(string x, BiNode * & t )
{
	if( t == NULL )
		return;
	if( x < t->name)
		removeActor( x, t->left );
	else if( t->name < x )
		removeActor( x, t->right );
	else if(t->left && t->right) 			//if it has two nodes, swap node with min node
	{		
		swapActors(t, minNode(t->right));
		removeActor(x, t->right);
	}
 	else  				 //if it has one node or any node
	{
		BiNode *oldNode = t;		
		int i,sizex,j, sizey;

		t = t->left ? t->left : t->right;		//adjust new pointer value ->left or right according to existence of node
		sizex=(oldNode->films).size();

		for(i=0;i<sizex;i++)
		{
			sizey=(oldNode->films[i])->edges.size();	//find the relevant movie
			if(sizey==1)					//if movie has only one node delete the movie also
			{
				TreeNode * ttt;				
				ttt=searchInTree((oldNode->films[i])->name);	//find uppernode to delete
								
				sizey=(ttt->edges).size();			
				for(j=0;j<sizey;j++)						//find moviename and delete it from edges
					if(ttt->edges[j]->name==searchPointer->name)
					{
						ttt->edges.erase(ttt->edges.begin()+j, ttt->edges.begin()+j+1);
						delete searchPointer;						
						break ;
					}	
			}
			else			//if movie has more than 1 node
			{
				for(j=0; j<sizey; j++)			
				{
					if((oldNode->films[i])->edges[j]->name==oldNode->name)
					{
						(oldNode->films[i])->edges.erase((oldNode->films[i])->edges.begin()+j, (oldNode->films[i])->edges.begin()+j+1);
						break ;			//only delete actorname from movie
					}
				}
			}			
		}
		delete oldNode;	
	}
}

/*****************removing the node****************/
void helperDeleteNode(TreeNode *t)
{
	int i,sizex;	
	if(t->nodeType==1)		//if node is movie
	{
		int j,sizey;
		BiNode *bp;
		sizex=t->edges.size();

		for(i=0;i<sizex;i++)	
		{
			bp=searchInBST((t->edges[i])->name,rootBST);		//find the actor

			sizey=bp->films.size();
			for(j=0; j<sizey; j++)
			{
				if(t->name==bp->films[j]->name)			//and delete film from list of actor
				{
					bp->films.erase(bp->films.begin()+j , bp->films.begin()+j+1);
					break;
				}
			}

		}

	}
	else		//if a classification name
	{
		sizex=t->edges.size();			//delete the other nodes
		for(i=0; i<sizex; i++)
			helperDeleteNode(t->edges[i]);
	}
	delete t;
}


void deleteNode(string x)
{
	TreeNode *upperNode;
	int i, sizex;

	upperNode=searchInTree(x);	//find the node and uppernode	
		
	sizex=upperNode->edges.size();		
	for(i=0; i<sizex; i++)
		if(upperNode->edges[i]->name==x)
		{
			upperNode->edges.erase(upperNode->edges.begin()+i, upperNode->edges.begin()+i+1);	//delete node from edges of uppernode
			helperDeleteNode(searchPointer);							//and delete the rest
			break;
		}
}

/******************input function: main*****************/

int main(void)
{
	string inpString, file;
	ifstream input;
	ofstream output;
	char c;
	
	root=new TreeNode;		//assign root
	root->name="";
	root->nodeType=-1;
	LastNodes.push_back(root);	//and push to LastNodes
	
	cin>>inpString;	//Take first string: it must be a command
		
	while(inpString!="End")		//while inpString is not End
	{	
		if(inpString=="Addmovies")
		{
			cin>>inpString;
			input.open(inpString.c_str());
			addMovies(input);						
		}
		else if(inpString=="Printmovies")
		{
			cin>>inpString;
			output.open (inpString.c_str(),ios_base::app);
			printMovies(output);
		}
		else if(inpString=="Printactors")
		{
			cin>>inpString;
			output.open (inpString.c_str(),ios_base::app);
			printActors(output);
		}
		
		else if(inpString=="Listcoactors")
		{
			cin>>inpString;			
			cin>>file;
			cin.get(c);
			while(c!='\n')
			{
				if(c!=' ')
				{
					cin.unget();
					inpString+= " " + file;					
					cin>>file;				
				}
				cin.get(c);
			}
			output.open (file.c_str(),ios_base::app);
			listCoActors(inpString,output);
			inpString="";
			file="";
		}

		else if(inpString=="Listmoviesof")
		{
			cin>>inpString;			
			cin>>file;
			cin.get(c);
			while(c!='\n')
			{
				if(c!=' ')
				{
					cin.unget();
					inpString+= " " + file;					
					cin>>file;				
				}
				cin.get(c);
			}
			output.open (file.c_str(),ios_base::app);
			listMoviesOf(inpString,output);
			inpString="";
			file="";
		}
		else if(inpString=="Deletenode")
		{
			cin>>inpString;			
			cin.get(c);
			while(c!='\n')
			{
				if(c!=' ')
				{
					cin.unget();
					cin>>file;
					inpString+= " " + file;					
				}
				cin.get(c);
			}
			deleteNode(inpString);
			inpString="";
			file="";
		}
		else if(inpString=="Deleteactor")
		{
			cin>>inpString;			
			cin.get(c);
			while(c!='\n')
			{
				if(c!=' ')
				{
					cin.unget();
					cin>>file;					
					inpString+= " " + file;					
				}
				cin.get(c);
			}
			removeActor(inpString,rootBST);
			inpString="";
			file="";		
		}
		cin>>inpString;		//take a new character
	}
}
