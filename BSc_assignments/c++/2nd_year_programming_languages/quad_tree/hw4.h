#ifndef _HW_H_
#define _HW_H_

#include <iostream>

using namespace std;

struct Point {
	int coordx;
	int coordy;
	Point (int a, int b)
	{
		coordx=a;
		coordy=b;
	}
};


struct Error {
	const char *mess;
	Error(const char *p) {mess=p;}
};

class QuadTree 
{
	private:
		QuadTree* upperleft;
		QuadTree* upperright;
		QuadTree* lowerleft;
		QuadTree* lowerright;
		Point* point1;
		Point* point2;
		int type;
		
		QuadTree* getUpperLeft();
		QuadTree* getUpperRight();
		QuadTree* getLowerLeft();
		QuadTree* getLowerRight();
		QuadTree* newTree (int t, int p1x, int p1y, int p2x, int p2y, QuadTree *ul=NULL, QuadTree *ur=NULL, QuadTree *ll=NULL, QuadTree *lr=NULL);
		Point getPoint1();
		Point getPoint2();
		friend ostream& printhlp(ostream & , const QuadTree &, int, int);

	public:
		QuadTree(int);
		QuadTree(const QuadTree &);
		~QuadTree();
		QuadTree & insertNode (Point, Point);
		QuadTree & deleteNode (Point, Point);
		QuadTree operator- (const QuadTree &);
		QuadTree operator+ (const QuadTree &);
		QuadTree operator* (const QuadTree &);
		QuadTree & operator= (const QuadTree &);
		QuadTree operator~ ();
		
		friend ostream& operator<<(ostream &, const QuadTree &) ;
};

ostream& operator<<(ostream &, const QuadTree &) ;
#endif
