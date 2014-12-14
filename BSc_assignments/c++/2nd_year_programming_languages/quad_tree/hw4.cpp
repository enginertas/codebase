/************Implementation of QuadTree***********/
#include "hw4.h"


#define TREE 3
#define FULL 2
#define EMPTY 1
#define NLL 0
/********Helper Functions*************/

ostream& putn(ostream& ost,int n)		//puts tab n times
{
	if(n)
	{
		ost<<'\t';
		putn(ost, n-1);
	}
}

ostream& printhlp(ostream& ost, const QuadTree &q, int a, int n)
{
	switch(q.type)
	{
		case EMPTY:			//if string is NULL, don't print anything
			putn(ost, a);			
			ost<<"(("<< q.point1->coordx << ',' << q.point1->coordy << ')' ;
			ost<<" (";
			ost<<q.point2->coordx << ',' << q.point2->coordy << ')' << ' ' << "Empty" << ')';
			break;
		
		case FULL:		//if FULL, print only a line with points
			putn(ost, a);			
			ost<<"(("<< q.point1->coordx << ',' << q.point1->coordy << ')' ;
			ost<<" (";
			ost<<q.point2->coordx << ',' << q.point2->coordy << ')' << ' ' << "Full" << ')';
			break;

		case TREE:		//If TREE, divide tree to 4
			putn(ost, a);
			ost << '(';
			ost << endl;
			printhlp(ost, *q.upperright, n+1, n+1);
			ost << endl; 
			
			printhlp(ost, *q.upperleft, n+1, n+1);
			if(q.upperleft->type)
				ost << endl; 

			printhlp(ost, *q.lowerleft, n+1, n+1);
			if(q.lowerleft->type)
				ost << endl;			

			printhlp(ost, *q.lowerright, n+1, n+1);
			if(q.lowerright->type)
				ost << endl;
						
			putn(ost, n) << ')';
			break;
		default:
			break;
	}
}


QuadTree * QuadTree::newTree (int t, int p1x, int p1y, int p2x, int p2y, QuadTree *ul, QuadTree *ur, QuadTree *ll, QuadTree *lr)
{
	QuadTree *newQuad;			//Creates a desired QuadTree Node.....
	
	newQuad=new QuadTree(1);
	newQuad->type=t;
	newQuad->point1->coordx=p1x;
	newQuad->point1->coordy=p1y;
	newQuad->point2->coordx=p2x;
	newQuad->point2->coordy=p2y;
	newQuad->upperleft=ul;
	newQuad->upperright=ur;
	newQuad->lowerleft=ll;
	newQuad->lowerright=lr;
	
	return newQuad;

}
ostream& operator<<(ostream& ost, const QuadTree &q)	//sends the string to output stream
{
	printhlp(ost,q,0,0);
}

bool checkIfInside(int x, int y, int border1, int border2)	//checks the intersection of intervals
{
	return ((x>=border1 && x<=border2) ||(y>=border1 && y<=border2) || (border1>=x && border1<=y) || (border2>=x && border2<=y));
}

bool doesInclude(Point p1, Point p2, Point refp1, Point refp2)	//checks if rectangulars intersect
{
	return checkIfInside(p1.coordx, p2.coordx, refp1.coordx, refp2.coordx) && checkIfInside(p1.coordy, p2.coordy, refp1.coordy, refp2.coordy); 
}

/**************Helper Member Functions*****************/
QuadTree* QuadTree::getUpperLeft()		//gives thee upperleft
{
	QuadTree * newQuad;
	int p1x,p1y,p2x,p2y;

	if(type==TREE)
		return upperleft;	
	
	else if(point1->coordx == point2->coordx)	//if points are equal, return NULL
	{	
		newQuad = newTree(NLL, point1->coordx, point1->coordy, point2->coordx, point2->coordy);	
		
	}	
	else 
	{	p1x=point1->coordx;				//if not equal, divide and return
		p1y=(point1->coordy+point2->coordy+1)/2;
		p2x=(point1->coordx+point2->coordx-1)/2;
		p2y=point2->coordy;
		
		newQuad = newTree(type, p1x, p1y, p2x, p2y);
		
	}
	return newQuad;
}

QuadTree* QuadTree::getUpperRight()		//gives thee upperright
{	
	QuadTree * newQuad;
	int p1x,p1y;

	if(type==TREE)				//divide and return
		return upperright;
	else 
	{	p1x=(point1->coordx+point2->coordx+1)/2;
		p1y=(point1->coordy+point2->coordy+1)/2;
				
		newQuad = newTree(type, p1x, p1y, point2->coordx, point2->coordy);
	}
	return newQuad;
}

QuadTree* QuadTree::getLowerLeft()
{						//gives thee lowerleft
	QuadTree * newQuad;
	int p2x,p2y;

	if(type==TREE)				
		return lowerleft;
	
	else if((point1->coordx == point2->coordx)||(point1->coordy == point2->coordy))			//if points are equal, return NULL
			newQuad= newTree(NLL, point1->coordx, point1->coordy, point2->coordx, point2->coordy);
	
	else 
	{	p2x=(point1->coordx+point2->coordx-1)/2;		//if not equal, divide and return
		p2y=(point1->coordy+point2->coordy-1)/2;
		
		newQuad = newTree(type, point1->coordx , point1->coordy , p2x , p2y);
	}
	return newQuad;
}

QuadTree* QuadTree::getLowerRight()
{					//gives thee lowerright
	QuadTree * newQuad;
	int p1x,p1y,p2x,p2y;

	if(type==TREE)
		return lowerright;
	
	else if(point1->coordy == point2->coordy)		//if points are equal, return NULL
		newQuad = newTree(NLL, point1->coordx, point1->coordy, point2->coordx, point2->coordy);
	else 
	{	p1x=(point1->coordx+point2->coordx+1)/2;	//if not equal, divide and return
		p1y=point1->coordy;
		p2x=point2->coordx;
		p2y=(point1->coordy+point2->coordy-1)/2;
		
		newQuad = newTree(type, p1x , p1y , p2x , p2y);
	}
	return newQuad;
}
/********New QuadTree*****************/
QuadTree::QuadTree(int size)
{
	int x;
	x=size-1;
	
	point1 = new Point(0,0);
	point2 = new Point(x,x);
	upperleft = NULL;
	upperright = NULL;
	lowerleft = NULL;
	lowerright = NULL ;
	type= EMPTY;
}

/***********Copy Constructor for QuadTree***************/
QuadTree::QuadTree(const QuadTree & rhs)
{
	if(rhs.type==TREE)
	{
		upperleft = new QuadTree(*rhs.upperleft);
		upperright= new QuadTree(*rhs.upperright);
		lowerleft = new QuadTree(*rhs.lowerleft);
		lowerright= new QuadTree(*rhs.lowerright);
	}
	else
		upperleft = upperright = lowerleft = lowerright = NULL;
	
	type = rhs.type;
	point1= new Point(rhs.point1->coordx , rhs.point1->coordy);
	point2= new Point(rhs.point2->coordx , rhs.point2->coordy);
}

/********Deconstructor for QuadTree**********/
QuadTree::~QuadTree() 
{
	delete point1;
	delete point2;
	if(type==TREE)
	{
		lowerleft->~QuadTree();
		lowerright->~QuadTree();
		upperleft->~QuadTree();
		upperright->~QuadTree();
	}
	lowerleft=lowerright=upperleft=upperright=NULL;
}	

/************InsertNode, insert node and give reference**************/
QuadTree & QuadTree::insertNode (Point p1, Point p2)
{
	if(type!=NLL)
	{
		if((p1.coordy>p2.coordy)&&(p1.coordx>p2.coordx))	//Interchange the points
		{
			int cx, cy;
			cx = p1.coordx;
			cy = p1.coordy;

			p1.coordx=p2.coordx;
			p1.coordy=p2.coordy;
			
			p2.coordx=cx;
			p2.coordy=cy; 	
		}			
		if(doesInclude(*point1, *point2, p1, p2))		//If rectangulars intersect
			if(doesInclude(*point1, *point1, p1, p2) && doesInclude(*point2, *point2, p1, p2))	//If 2nd rectangular covers 1st one
			{
				if(type==TREE)		//empty old ones
				{
					lowerleft->~QuadTree();
					lowerright->~QuadTree();
					upperleft->~QuadTree();
					upperright->~QuadTree();
				}
				lowerleft=lowerright=upperleft=upperright=NULL;
				type=FULL;
			}
			else				//If 2nd doesn't cover divide to 4
			{
				upperleft = &getUpperLeft()->insertNode(p1,p2);
				upperright= &getUpperRight()->insertNode(p1,p2);
				lowerleft = &getLowerLeft()->insertNode(p1,p2);
				lowerright= &getLowerRight()->insertNode(p1,p2);

				if((upperleft->type==NLL||upperleft->type==FULL) && (upperright->type==NLL||upperright->type==FULL) &&
					(lowerleft->type==NLL||lowerleft->type==FULL) && (lowerright->type==NLL||lowerright->type==FULL))
				{
					if(type==TREE)		//empty old ones
					{
						lowerleft->~QuadTree();
						lowerright->~QuadTree();
						upperleft->~QuadTree();
						upperright->~QuadTree();
					}					

					upperleft=upperright=lowerleft=lowerright=NULL;
					type= FULL;
				}
				else
					type = TREE;
			}
	}
	return *this;
}

/*******************deleteNode:Delete and give the reference**********/
QuadTree & QuadTree::deleteNode (Point p1, Point p2)
{
	if(type!=NLL)
	{
		if((p1.coordy>p2.coordy)&&(p1.coordx>p2.coordx))	//Interchange the points
		{
			int cx, cy;
			cx = p1.coordx;
			cy = p1.coordy;

			p1.coordx=p2.coordx;
			p1.coordy=p2.coordy;
			
			p2.coordx=cx;
			p2.coordy=cy; 	
		}			
		if(doesInclude(*point1, *point2, p1, p2))	//If rectangulars intersect
			if(doesInclude(*point1, *point1, p1, p2) && doesInclude(*point2, *point2, p1, p2))//If 2nd rectangular covers 1st one
			{
				if(type==TREE)		//empty old ones
				{
					lowerleft->~QuadTree();
					lowerright->~QuadTree();
					upperleft->~QuadTree();
					upperright->~QuadTree();
				}
				lowerleft=lowerright=upperleft=upperright=NULL;
				type=EMPTY;
			}
			else			//If 2nd doesn't cover divide to 4
			{
				upperleft = &getUpperLeft()->deleteNode(p1,p2);
				upperright= &getUpperRight()->deleteNode(p1,p2);
				lowerleft = &getLowerLeft()->deleteNode(p1,p2);
				lowerright= &getLowerRight()->deleteNode(p1,p2);

				if((upperleft->type==NLL||upperleft->type==EMPTY) && (upperright->type==NLL||upperright->type==EMPTY) &&
					(lowerleft->type==NLL||lowerleft->type==EMPTY) && (lowerright->type==NLL||lowerright->type==EMPTY))
				{
					if(type==TREE)		//empty old ones
					{
						lowerleft->~QuadTree();
						lowerright->~QuadTree();
						upperleft->~QuadTree();
						upperright->~QuadTree();
					}		
					upperleft=upperright=lowerleft=lowerright=NULL;
					type= EMPTY;
				}
				else
					type = TREE;
			}
	}
	return *this;
}

/***********************Union of Trees**********************/
QuadTree QuadTree::operator+ (const QuadTree &rhs)
{
	QuadTree* newQuad;
	int p1x,p1y,p2x,p2y;

	if(point1->coordx==rhs.point1->coordx && point1->coordy==rhs.point1->coordy && point2->coordx==rhs.point2->coordx && point2->coordy==rhs.point2->coordy)
	{
		p1x= point1->coordx;
		p1y= point1->coordy;
		p2x= point2->coordx;
		p2y= point2->coordy;

		switch(type)
		{
			case NLL:
				newQuad = new QuadTree(*this);
				break;
			
			case EMPTY:
				newQuad = new QuadTree(rhs);
				break;

			case FULL:
				newQuad = new QuadTree(*this);
				break;
				
			default:
				if(rhs.type==FULL)
					newQuad = new QuadTree(rhs);
			
				else if(rhs.type==EMPTY)
					newQuad = new QuadTree(*this);

				else
				{						
					QuadTree *a1, *a2, *a3, *a4;
					a1=newTree(-1,0,0,0,0);			//Default values of pointers
					a2=newTree(-1,0,0,0,0);	
					a3=newTree(-1,0,0,0,0);	
					a4=newTree(-1,0,0,0,0);	

					*a1=*upperleft+*rhs.upperleft;		//Assignment
					*a2=*upperright+*rhs.upperright;
					*a3=*lowerleft+*rhs.lowerleft;
					*a4=*lowerright+*rhs.lowerright;
					
					if((a1->type==NLL||a1->type==FULL) && (a2->type==NLL||a2->type==FULL) &&	//Tests if full
						(a3->type==NLL||a3->type==FULL) && (a4->type==NLL||a4->type==FULL))
						newQuad= newTree(FULL,p1x,p1y,p2x,p2y);
					else
						newQuad= newTree(TREE, p1x, p1y, p2x, p2y, a1, a2, a3, a4);
				}					

		}
		return *newQuad;
	}
	else
		throw Error("size mismatch");
}

/*********************Difference of Trees********************/
QuadTree QuadTree::operator- (const QuadTree &rhs)
{
	QuadTree* newQuad;
	int p1x,p1y,p2x,p2y;

	if(point1->coordx==rhs.point1->coordx && point1->coordy==rhs.point1->coordy && point2->coordx==rhs.point2->coordx && point2->coordy==rhs.point2->coordy)
	{
		p1x= point1->coordx;
		p1y= point1->coordy;
		p2x= point2->coordx;
		p2y= point2->coordy;

		switch(type)
		{
			case NLL:
				newQuad = new QuadTree(*this);
				break;
			
			case EMPTY:
				newQuad = new QuadTree(*this);
				break;

			case FULL:
				newQuad = new QuadTree(rhs);
				*newQuad= ~(*newQuad);					
				break;
			
			default:
				if(rhs.type==FULL)
					newQuad = newTree(EMPTY,p1x,p1y,p2x,p2y);
				
				else if(rhs.type==EMPTY)
					newQuad = new QuadTree(*this);

				else
				{						
					QuadTree *a1, *a2, *a3, *a4;
					
					a1=newTree(-1,0,0,0,0);			//Default values of pointers
					a2=newTree(-1,0,0,0,0);	
					a3=newTree(-1,0,0,0,0);	
					a4=newTree(-1,0,0,0,0);	
			
					*a1=*upperleft-*rhs.upperleft;		//Assignment
					*a2=*upperright-*rhs.upperright;
					*a3=*lowerleft-*rhs.lowerleft;
					*a4=*lowerright-*rhs.lowerright;
				
					if((a1->type==NLL||a1->type==EMPTY) && (a2->type==NLL||a2->type==EMPTY) &&	//Tests if empty
						(a3->type==NLL||a3->type==EMPTY) && (a4->type==NLL||a4->type==EMPTY))
						newQuad= newTree(EMPTY,p1x,p1y,p2x,p2y);
					else
						newQuad= newTree(TREE, p1x, p1y, p2x, p2y, a1, a2, a3, a4);	
				}					

		}
		return *newQuad;
	}
	else
		throw Error("size mismatch");	
}

/**************Intersection of trees*****************/
QuadTree QuadTree::operator* (const QuadTree &rhs)
{
	QuadTree* newQuad;
	int p1x,p1y,p2x,p2y;

	if(point1->coordx==rhs.point1->coordx && point1->coordy==rhs.point1->coordy && point2->coordx==rhs.point2->coordx && point2->coordy==rhs.point2->coordy)
	{
		p1x= point1->coordx;
		p1y= point1->coordy;
		p2x= point2->coordx;
		p2y= point2->coordy;

		switch(type)
		{
			case NLL:
				newQuad = new QuadTree(*this);
				break;
			
			case EMPTY:
				newQuad = new QuadTree(*this);
				break;

			case FULL:
				newQuad = new QuadTree(rhs);
				break;
			
			default:
				if(rhs.type==FULL)
					newQuad = new QuadTree(*this);
				
				else if(rhs.type==EMPTY)
					newQuad = new QuadTree(rhs);

				else
				{						
					QuadTree *a1, *a2, *a3, *a4;
						
					a1=newTree(-1,0,0,0,0);			//Default values of pointers
					a2=newTree(-1,0,0,0,0);	
					a3=newTree(-1,0,0,0,0);	
					a4=newTree(-1,0,0,0,0);		

					*a1=*upperleft * *rhs.upperleft;	//Assignment
					*a2=*upperright * *rhs.upperright;
					*a3=*lowerleft * *rhs.lowerleft;
					*a4=*lowerright * *rhs.lowerright;
				
					if((a1->type==NLL||a1->type==EMPTY) && (a2->type==NLL||a2->type==EMPTY) &&	//Tests if empty
						(a3->type==NLL||a3->type==EMPTY) && (a4->type==NLL||a4->type==EMPTY))
						newQuad= newTree(EMPTY,p1x,p1y,p2x,p2y);
					else
						newQuad= newTree(TREE, p1x, p1y, p2x, p2y, a1, a2, a3, a4);	
				}					

		}
		return *newQuad;
	}
	else
		throw Error("size mismatch");	
}

/****************Negating operation function*********************/
QuadTree QuadTree::operator~()
{
	if(type==NLL)
		return QuadTree(*this);
	else if(type==EMPTY)
		return *newTree(FULL, point1->coordx, point1->coordy, point2->coordx, point2->coordy);
	else if(type==FULL)
		return *newTree(EMPTY, point1->coordx, point1->coordy, point2->coordx, point2->coordy);
	else
	{
		QuadTree *a1,*a2,*a3,*a4;
		a1=newTree(-1,0,0,0,0);			//Default values of pointers
		a2=newTree(-1,0,0,0,0);	
		a3=newTree(-1,0,0,0,0);	
		a4=newTree(-1,0,0,0,0);
		
		*a1= ~(*upperleft);		//Assignment
		*a2= ~(*upperright);
		*a3= ~(*lowerleft);
		*a4= ~(*lowerright);	
		
		return *newTree(TREE, point1->coordx, point1->coordy, point2->coordx, point2->coordy, a1, a2, a3, a4);
	}
}

/********************Assignment Operator********************/
QuadTree& QuadTree::operator= (const QuadTree &rhs)
{
	
	delete point1;
	delete point2;
	
	if(type==TREE)		//empty old ones
	{
		lowerleft->~QuadTree();
		lowerright->~QuadTree();
		upperleft->~QuadTree();
		upperright->~QuadTree();
	}		

	if(rhs.type==TREE)
	{							//assign new ones	
		upperleft = new QuadTree(*rhs.upperleft);
		upperright= new QuadTree(*rhs.upperright);
		lowerleft = new QuadTree(*rhs.lowerleft);
		lowerright= new QuadTree(*rhs.lowerright);
	}
	else
		upperleft = upperright = lowerleft = lowerright = NULL;

	type=rhs.type;
	point1= new Point(rhs.point1->coordx , rhs.point1->coordy);
	point2= new Point(rhs.point2->coordx , rhs.point2->coordy);

	return *this;
}


