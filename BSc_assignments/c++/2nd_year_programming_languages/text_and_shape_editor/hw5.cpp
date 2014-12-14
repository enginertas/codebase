#include "hw5.h"

#define PI 3.14

char *selected=NULL;
Event lastEventText, lastEventShape=DELETE;
GeometricObject *picked=NULL;

/********************Auxillary Helper Functions*******************/
bool mystrcmp(char *str1, char *str2)		/****working properly****/
{
	if(*str1)
		if(*str2)
			if(*str1==*str2)
			{
				str1++;
				str2++;
				return mystrcmp(str1,str2);
			}
			else
				return true;
		else
			return true;
	else
		if(*str2)
			return true;
		else
			return false;

}

int mystrlen(char *str)
{
	if(*str)
		return mystrlen(++str) +1;
	else
		return 0;
}

void mystrcpy(char *&str1, char *str2)
{
	char *p;

	p = new char[mystrlen(str2)+1];		/************deleting old string************/
	str1=p;	

	for(; *str2!='\0'; p++, str2++)
		*p=*str2;
	*p='\0';
}

double mod(double x)
{				/******works properly********/
	while(x<0)
		x+=360;

	while(x>=360)
		x-=360;

	return x;
}

bool checkslopes(double m1x, double m1y, double m2x, double m2y, double px, double py)
{
	double m1, m2 , n, r;

	if(!m1x)
		if(m1y<0)
			if(!px)
				if(py<=0)
					return true;
				else
					return false;
			else
			{
				n=py/px;
				m2= m2y/m2x;
				return n <= m2;
			}				
		else
			if(!px)
				if(py>=0)
					return true;
				else
					return false;
			else
			{
				n=py/px;
				m2= m2y/m2x;
				return n<=m2;
			}
	else if(!m2x)
		if(m2y<0)
			if(!px)
				if(py<=0)
					return true;
				else
					return false;
			else
			{
				n=py/px;
				m1=m1y/m1x;
				return n>=m1;

			}
			
		else
			if(!px)
				if(py>=0)
					return true;
				else
					return false;
			else
			{
				n=py/px;
				m2= m2y/m2x;
				return n>=m1;
			}
	else
	{
		m1= m1y/m1x;
		m2= m2y/m2x;
		
		if(!py)
			py=1e-20;

		n=py/px;

		if(m1<0)
			n*=-1;

		if(n<0)
			return n<=m2;

		else if(n>0)
			return n>=m1;
		else
			return n>=m1;
	}
	
	
}

double cross(Point p1, Point p2)
{
	return p1.coordx * p2.coordy - p2.coordx * p1.coordy;
}

bool both(Point p1, Point p2, Point a, Point b)
{
	double r1, r2;
	Point w(0,0);

	w.coordx=b.coordx-a.coordx;
	w.coordy=b.coordy-a.coordy;

	r1= cross (w , Point(p1.coordx-a.coordx, p1.coordy-a.coordy));
	r2= cross (w , Point(p2.coordx-a.coordx, p2.coordy-a.coordy));

	return (r1*r2>-1e-10);
}

string colorWriter(int x)
{
	switch(x)
	{
		case 0:
			return "WHITE";
			break;

		case 1:
			return "RED";
			break;

		case 2:
			return "BLUE";
			break;


		case 3:
			return "GREEN";
			break;
			
		case 4:
			return "MAGENTA";
			break;
		
		case 5:
			return "CYAN";
			break;

		case 6:
			return "YELLOW";
			break;

		case 7:
			return "PINK";
			break;

		case 8:
			return "BROWN";
			break;
		case 9:
			return "ORANGE";
			break;
	}
}

/********************Implementation of Cursor*********************/
Cursor::Cursor(int a)			/*****working******/
{
	pos=a;
}

void Cursor::moveCursor(int newPos)
{
	pos=newPos;
	t->reset();
}

int Cursor::getCursor()
{
	return pos;
}

void Cursor::setPoint(Editor* n)
{
	t=n;
}

/*******************Implementation of TextEditor******************/
TextEditor::TextEditor(char *name)	/**********works properly******/
{
	mystrcpy(editorName, name);
	start=end=-1;	
	text.push_back('\0');
	cur.setPoint(this);
}

void TextEditor::reset()
{				/***********works properly**********/
	start=end=-1;
}
void TextEditor::addText(char *str)
{					/*********works properly*****/
	int pos;

	pos= cur.getCursor();
	while(*str!='\0')
		text.insert(text.begin() + pos++, *(str++));
	
	cur.moveCursor(pos);
}

char * TextEditor::replace(char * st1, char* st2)
{						/***works properly********/
	bool isFound=false;
	int i=0,j=0,x;
	char *q;

	if(st1=='\0')
		return NULL;
	else
	{
		q=st1;
			
		while(text[j]!='\0')
		{
			if(text[j++]==*(q++))
				if(*q=='\0')
				{
					isFound=true;
					text.erase(text.begin()+i, text.begin()+j);
					cur.moveCursor(i);
					addText(st2);
					i=j=cur.getCursor();
					q=st1;
				}
				else ;
			else
			{
				q=st1;		
				i=j;
			}
		}
		if(isFound)
		{
			mystrcpy(q, st2);
			return q;
		}
		else
			return NULL;
	}

}

void TextEditor::select(int c)
{				/******works properly*********/
	int pos,size,r;
	pos=cur.getCursor();
	size=text.size()-1;

	r=pos;
	if(c>0)
	{	
		pos+=c;
		if(pos>size)
			pos=size;
		
		cur.moveCursor(pos);
		start=r;		
		end=pos;
	}
	else if(c<0)
	{
		pos+=c;
		if(pos<0)
			pos=0;

		cur.moveCursor(pos);
		end=r;
		start=pos;
	}
	else
		start=end=-1;
}

void TextEditor::save()
{				/****works properly****/
	ofstream out(editorName);
	int i, pos, size;

	pos= cur.getCursor();

	for(i=0;i<pos; i++)
		out<<text[i];

	out<<'^';
	
	while(text[i]!='\0')
		out<<text[i++];
	
	out.close();
}

void TextEditor::copy()
{				/***works properly***/
	int pos, i=0, j, r;
	
	delete selected;
	lastEventText= COPY;	

	if(start==-1)
		selected=NULL;
		
	else
	{	
		selected=new char[end-start+1];
		
		for(j=start; j<end; i++,j++)
			selected[i]=text[j];

		selected[i]='\0';
	}
}

void TextEditor::cut()
{			/***************works properly*********/
	int pos, i=0, j, r;
	
	delete selected;	
	lastEventText= CUT;	

	if(start==-1)
		selected=NULL;
	
	else
	{
		selected=new char[end-start+1];

		for(j=start; j<end; i++,j++)
			selected[i]=text[j];

		selected[i]='\0';
		deleteObject();
	}
}

void TextEditor::paste()
{				/*********works properly***********/
	if(selected)
	{
		addText(selected);
		if(lastEventText!=COPY)
		{
			delete selected;	
			selected=NULL;
		}	
	}
	else ;
}
void TextEditor::deleteObject()
{
	lastEventText= CUT;
	text.erase(text.begin()+start, text.begin()+end);
	cur.moveCursor(start);
}

void TextEditor::draw()
{			/********works properly********/
	int i, pos;

	pos= cur.getCursor();

	for(i=0;i<pos; i++)
		cout<<text[i];

	cout<<'^';
	
	while(text[i]!='\0')
		cout<<text[i++];
}

void TextEditor::handle(Event e)
{
	switch(e)
	{
		case COPY:
			copy();
			break;

		case CUT:
			cut();			
			break;

		case PASTE:
			paste();
			break;

		case SAVE:
			save();
			break;

		case CLOSE:
			save();
			break;

		case DELETE:
			deleteObject();
			break;
	}
}
/************************Implementation of GeometricObject******/
GeometricObject::GeometricObject()
{
	color=WHITE;
	angle=0.0;
}

void GeometricObject::setColor(Color c)
{
	color=c;
}

/************************Implementation of Circle***************/
Circle::Circle(Point p, double radius)
:radius(radius)
{
	center= new Point(p.coordx,p.coordy);
}

double Circle::area()
{
	return radius * PI* PI;
}

void Circle::scale(int scalefactor)
{
	radius*= scalefactor;

}
void Circle::move(Point p)
{
	delete center;
	center=new Point(p.coordx, p.coordy);
}
void Circle::rotate(double a, Direction d)
{
	if(d==CLOCKWISE)
		angle= mod (angle - a);	
	
	else
		angle= mod (angle + a);
}
bool Circle::checkIfInside(Point p)
{
	return (pow(radius,2)) - pow((p.coordx - center->coordx),2) - pow((p.coordy - center->coordy),2) > - 1e-10;
}

Pack Circle::draw()
{
	Pack a;

	a.color=color;
	a.center=center;
	a.angle=radius;
	a.p1=NULL;
	a.p2=NULL;
	a.p3=NULL;

	return a;
}

GeometricObject* Circle::copy()
{
	GeometricObject* p;
	p = new Circle(*this);
	return p;
}

Circle::Circle(const Circle &ref)
{
	radius=ref.radius;
	center= new Point(ref.center->coordx , ref.center->coordy);
	angle =ref.angle;
	color=ref.color;
}
/************************Implementation of Rectangle************/
Rectangle::Rectangle(Point p1, Point p2)
{
	lowerleft= new Point(p1.coordx, p1.coordy);
	upperright= new Point(p2.coordx, p2.coordy);
	
	lowerright=new Point(p2.coordx, p1.coordy);
	upperleft= new Point(p1.coordx, p2.coordy);

	center = new Point((p1.coordx + p2.coordx)/2 , (p1.coordy + p2.coordy)/2);
}

Rectangle::Rectangle(const Rectangle &ref)
{
	center= new Point(ref.center->coordx , ref.center->coordy);
	angle =ref.angle;
	color=ref.color;
	upperright= new Point(ref.upperright->coordx, ref.upperright->coordy);
	upperleft=  new Point(ref.upperleft->coordx , ref.upperleft->coordy);
	lowerleft=  new Point(ref.lowerleft->coordx , ref.lowerleft->coordy);
	lowerright= new Point(ref.lowerright->coordx , ref.lowerright->coordy);
}

double Rectangle::area()
{
	double r1, r2;

	r1 = sqrt(pow(lowerright->coordx - lowerleft->coordx, 2) + pow(lowerright->coordy - lowerleft->coordy, 2));
	r2 = sqrt(pow(lowerright->coordx - upperright->coordx,2) + pow(lowerright->coordy - upperright->coordy, 2));

	return r1*r2;
}
void Rectangle::scale(int scalefactor)
{
	if(center->coordx > lowerleft->coordx)	
		lowerleft->coordx = lowerleft->coordx - (scalefactor-1)* (center->coordx - lowerleft->coordx);
	else
		lowerleft->coordx = lowerleft->coordx + (scalefactor-1)* (lowerleft->coordx - center->coordx);

	if(center->coordy > lowerleft->coordy)	
		lowerleft->coordy = lowerleft->coordy - (scalefactor-1)* (center->coordy - lowerleft->coordy);
	else
		lowerleft->coordy = lowerleft->coordy + (scalefactor-1)* (lowerleft->coordy - center->coordy);

	if(center->coordx > lowerright->coordx)	
		lowerright->coordx = lowerright->coordx - (scalefactor-1)* (center->coordx - lowerright->coordx);
	else
		lowerright->coordx = lowerright->coordx + (scalefactor-1)* (lowerright->coordx - center->coordx);

	if(center->coordy > lowerright->coordy)	
		lowerright->coordy = lowerright->coordy - (scalefactor-1)* (center->coordy - lowerright->coordy);
	else
		lowerright->coordy = lowerright->coordy + (scalefactor-1)* (lowerright->coordy - center->coordy);

	if(center->coordx > upperleft->coordx)	
		upperleft->coordx = upperleft->coordx - (scalefactor-1)* (center->coordx - upperleft->coordx);
	else
		upperleft->coordx = upperleft->coordx + (scalefactor-1)* (upperleft->coordx - center->coordx);

	if(center->coordy > upperleft->coordy)	
		upperleft->coordy = upperleft->coordy - (scalefactor-1)* (center->coordy - upperleft->coordy);
	else
		upperleft->coordy = upperleft->coordy + (scalefactor-1)* (upperleft->coordy - center->coordy);

	if(center->coordx > upperright->coordx)	
		upperright->coordx = upperright->coordx - (scalefactor-1)* (center->coordx - upperright->coordx);
	else
		upperright->coordx = upperright->coordx + (scalefactor-1)* (upperright->coordx - center->coordx);

	if(center->coordy > upperright->coordy)	
		upperright->coordy = upperright->coordy - (scalefactor-1)* (center->coordy - upperright->coordy);
	else
		upperright->coordy = upperright->coordy + (scalefactor-1)* (upperright->coordy - center->coordy);

}
void Rectangle::move(Point p)
{
	double scalex, scaley;

	scalex= p.coordx - center->coordx;
	scaley= p.coordy - center->coordy;

	center->coordx= p.coordx;
	center->coordy= p.coordy;

	lowerleft->coordx += scalex;
	lowerleft->coordy += scaley;
	
	lowerright->coordx += scalex;
	lowerright->coordy += scaley;

	upperright->coordx += scalex;
	upperright->coordy += scaley;

	upperleft->coordx += scalex;
	upperleft->coordy += scaley;
}

void Rectangle::rotate(double a, Direction d)
{
	double coordx, coordy;
	double newx, newy, t ,cosx, sinx;
	
	coordx=center->coordx;
	coordy=center->coordy;
	
	if(d==CLOCKWISE)
		a*=-1;

	t=a;
	a*=(PI/180);
	cosx= cos(a);
	sinx= sin(a);


	move(Point(0,0));

	newx = lowerleft->coordx * cosx - lowerleft->coordy * sinx;
	newy = lowerleft->coordx * sinx + lowerleft->coordy * cosx;
	lowerleft->coordx = newx;
	lowerleft->coordy = newy;

	newx = lowerright->coordx * cosx - lowerright->coordy * sinx;
	newy = lowerright->coordx * sinx + lowerright->coordy * cosx;
	lowerright->coordx = newx;
	lowerright->coordy = newy;

	newx = upperleft->coordx * cosx - upperleft->coordy * sinx;
	newy = upperleft->coordx * sinx + upperleft->coordy * cosx;
	upperleft->coordx = newx;
	upperleft->coordy = newy;

	newx = upperright->coordx * cosx - upperright->coordy * sinx;
	newy = upperright->coordx * sinx + upperright->coordy * cosx;
	upperright->coordx = newx;
	upperright->coordy = newy;

	move(Point(coordx, coordy));

	angle= mod (angle + t);
}

bool Rectangle::checkIfInside(Point p)
{
	bool a=true;
	double m1x, m1y, m2x, m2y, px, py;

	m1x= upperleft->coordx - upperright->coordx;
	m1y= upperleft->coordy - upperright->coordy;
	m2x= lowerright->coordx - upperright->coordx;
	m2y= lowerright->coordy - upperright->coordy;
	px= p.coordx- upperright->coordx;
	py= p.coordy- upperright->coordy; 

	a = a && checkslopes(m1x, m1y, m2x, m2y, px, py);

	m1x= lowerleft->coordx - upperleft->coordx;
	m1y= lowerleft->coordy - upperleft->coordy;
	m2x= upperright->coordx - upperleft->coordx;
	m2y= upperright->coordy - upperleft->coordy;
	px= p.coordx- upperleft->coordx;
	py= p.coordy- upperleft->coordy; 
	
	a = a && checkslopes(m1x, m1y, m2x, m2y, px, py);

	m1x= lowerright->coordx - lowerleft->coordx;
	m1y= lowerright->coordy - lowerleft->coordy;
	m2x= upperleft->coordx - lowerleft->coordx;
	m2y= upperleft->coordy - lowerleft->coordy;
	px= p.coordx- lowerleft->coordx;
	py= p.coordy- lowerleft->coordy; 
	
	a = a && checkslopes(m1x, m1y, m2x, m2y, px, py);

	m1x= upperright->coordx - lowerright->coordx;
	m1y= upperright->coordy - lowerright->coordy;
	m2x= lowerleft->coordx - lowerright->coordx;
	m2y= lowerleft->coordy - lowerright->coordy;
	px= p.coordx- lowerright->coordx;
	py= p.coordy- lowerright->coordy; 

	a = a && checkslopes(m1x, m1y, m2x, m2y, px, py);

	return a;
}

Pack Rectangle::draw()
{
	Pack a;

	a.center = new Point(center->coordx, center->coordy);
	a.angle=angle;
	a.p1= new Point(lowerleft->coordx, lowerleft->coordy);
	a.color=color;
	a.p2 = new Point(upperright->coordx, upperright->coordy);
	a.p3 = NULL;

	return a;
}

GeometricObject* Rectangle::copy()
{
	GeometricObject* p;
	p = new Rectangle(*this);
	return p;
}
/************************Implementation of TextEditor***********/
Triangle::Triangle(Point p1, Point p2, Point p3)
{
	point1= new Point(p1.coordx, p1.coordy);
	point2= new Point(p2.coordx, p2.coordy);
	point3= new Point(p3.coordx, p3.coordy);

	center = new Point((p1.coordx + p2.coordx + p3.coordx)/3, (p1.coordy + p2.coordy + p3.coordy)/3);
}

Triangle::Triangle(const Triangle &ref)
{
	center= new Point(ref.center->coordx , ref.center->coordy);
	angle =ref.angle;
	color=ref.color;
	point1= new Point(ref.point1->coordx, ref.point1->coordy);
	point2=  new Point(ref.point2->coordx , ref.point2->coordy);
	point3=  new Point(ref.point3->coordx , ref.point3->coordy);
}

double Triangle::area()
{
	double u, a, b, c;
	
	a= sqrt(pow((point1->coordx - point2->coordx),2) + pow((point1->coordy - point2->coordy),2));
	b= sqrt(pow((point1->coordx - point3->coordx),2) + pow((point1->coordy - point3->coordy),2));
	c= sqrt(pow((point2->coordx - point3->coordx),2) + pow((point2->coordy - point3->coordy),2));

	u= (a+b+c)/2;

	return sqrt(u* (u-a) * (u-b) * (u-c));
}

void Triangle::scale(int scalefactor)
{
	if(center->coordx > point1->coordx)	
		point1->coordx = point1->coordx - (scalefactor-1)* (center->coordx - point1->coordx);
	else
		point1->coordx = point1->coordx + (scalefactor-1)* (point1->coordx - center->coordx);

	if(center->coordy > point1->coordy)	
		point1->coordy = point1->coordy - (scalefactor-1)* (center->coordy - point1->coordy);
	else
		point1->coordy = point1->coordy + (scalefactor-1)* (point1->coordy - center->coordy);

	if(center->coordx > point2->coordx)	
		point2->coordx = point2->coordx - (scalefactor-1)* (center->coordx - point2->coordx);
	else
		point2->coordx = point2->coordx + (scalefactor-1)* (point2->coordx - center->coordx);

	if(center->coordy > point2->coordy)	
		point2->coordy = point2->coordy - (scalefactor-1)* (center->coordy - point2->coordy);
	else
		point2->coordy = point2->coordy + (scalefactor-1)* (point2->coordy - center->coordy);

	if(center->coordx > point3->coordx)	
		point3->coordx = point3->coordx - (scalefactor-1)* (center->coordx - point3->coordx);
	else
		point3->coordx = point3->coordx + (scalefactor-1)* (point3->coordx - center->coordx);

	if(center->coordy > point3->coordy)	
		point3->coordy = point3->coordy - (scalefactor-1)* (center->coordy - point3->coordy);
	else
		point3->coordy = point3->coordy + (scalefactor-1)* (point3->coordy - center->coordy);
}
void Triangle::move(Point p)
{
	double scalex, scaley;

	scalex= p.coordx - center->coordx;
	scaley= p.coordy - center->coordy;

	center->coordx= p.coordx;
	center->coordy= p.coordy;

	point1->coordx += scalex;
	point1->coordy += scaley;
	
	point2->coordx += scalex;
	point2->coordy += scaley;

	point3->coordx += scalex;
	point3->coordy += scaley;
}

void Triangle::rotate(double a, Direction d)
{
	double coordx, coordy;
	double newx, newy, t ,cosx, sinx;
	
	coordx=center->coordx;
	coordy=center->coordy;
	
	if(d==CLOCKWISE)
		a*=-1;

	t=a;
	a*=(PI/180);
	cosx= cos(a);
	sinx= sin(a);

	move(Point(0,0));

	newx = point1->coordx * cosx - point1->coordy * sinx;
	newy = point1->coordx * sinx + point1->coordy * cosx;
	point1->coordx = newx;
	point1->coordy = newy;

	newx = point2->coordx * cosx - point2->coordy * sinx;
	newy = point2->coordx * sinx + point2->coordy * cosx;
	point2->coordx = newx;
	point2->coordy = newy;

	newx = point3->coordx * cosx - point3->coordy * sinx;
	newy = point3->coordx * sinx + point3->coordy * cosx;
	point3->coordx = newx;
	point3->coordy = newy;

	move(Point(coordx, coordy));
	angle= mod (angle + t);
}
bool Triangle::checkIfInside(Point p)
{
	return both(p, *point1, *point2, *point3) && both(p, *point2 , *point1, *point3) && both(p, *point3, *point1, *point2);
}
Pack Triangle::draw()
{
	Pack a;

	a.center = new Point(center->coordx, center->coordy);
	a.angle=angle;
	a.p1 = new Point(point1->coordx, point1->coordy);
	a.color=color;
	a.p2 = new Point(point2->coordx, point2->coordy);
	a.p3 = new Point(point3->coordx, point3->coordy);

	return a;
}

GeometricObject* Triangle::copy()
{
	GeometricObject* p;
	p = new Triangle(*this);
	return p;
}
/************************Implementation of ShapeEditor**********/
ShapeEditor::ShapeEditor(char *name)
{
	mystrcpy(editorName,name);
}

void ShapeEditor::addGeometricObject(GeometricObject *obj)
{
	objs.push_back(obj);
	picked=NULL;
	index=-1;
	
}

GeometricObject* ShapeEditor::pick(Point p)
{
	int i=-1,size;
	bool x;	

	size=objs.size();
	for(i=0; i<size; i++)
	{
		if(objs[i]->checkIfInside(p))
		{	
			index=i;
			x=true;
		}
	}

	if(i==-1)
		return picked=NULL;
	else
		return objs[index];
}

void ShapeEditor::save()
{
	int i, size;
	Pack a;
	ofstream out(editorName);

	size=objs.size();

	for(i=0;i<size;i++)
	{
		a = objs[i]-> draw();
		
		if(a.p3)
		{
			out<<"Triangle ";
			out<<"(" << a.center->coordx << "," <<a.center->coordy <<") ";
			out<<a.angle<<" ";
			out<<colorWriter(a.color)<<" ";
			out<<"(" << a.p1->coordx << "," <<a.p1-> coordy << ") ";
			out<<"(" << a.p2->coordx << "," <<a.p2-> coordy << ") ";
			out<<"(" << a.p3->coordx << "," <<a.p3-> coordy << ") ";
			out<<endl;
		}		
		else if(a.p2)
		{
			out<<"Rectangle ";
			out<<"(" << a.center->coordx << "," <<a.center->coordy <<") ";
			out<<a.angle<<" ";			
			out<<colorWriter(a.color)<<" ";
			out<<"(" << a.p1->coordx << "," <<a.p1-> coordy << ") ";
			out<<"(" << a.p2->coordx << "," <<a.p2-> coordy << ") ";
			out<<endl;
		}
		else
		{
			out<<"Circle ";
			out<<"(" << a.center->coordx << "," <<a.center->coordy <<") ";
			out<<colorWriter(a.color)<<" ";
			out<<a.angle;
			out<<endl;
		}
	}
	out.close();
}
void ShapeEditor::copy()
{
	if (index!=-1)
		picked= objs[index]->copy();
	else
		picked=NULL;
	
	lastEventShape=COPY;
}
void ShapeEditor::cut()
{
	if(index!=-1)
	{	
		picked=objs[index]->copy();
		objs.erase(objs.begin()+index, objs.begin() +index+1);
		index=-1;
	}		
	lastEventShape=CUT;
		
}
void ShapeEditor::paste()
{
	if(picked!=NULL)
	{
		picked->move(Point(0,0));
		objs.push_back(picked);
	}
	if(lastEventShape!=COPY)
	{
		picked=NULL;
	}

	index=-1;
}
void ShapeEditor::deleteObject()
{
	if(index!=-1)
	{
		objs.erase(objs.begin()+index, objs.begin() +index+1);
	}	
	lastEventShape=DELETE;
	picked=NULL;
	index=-1;
}
void ShapeEditor::draw()
{
	int i, size;
	Pack a;

	size=objs.size();

	for(i=0;i<size;i++)
	{
		a = objs[i]-> draw();

		if(a.p3)
		{
			cout<<"Triangle ";
			cout<<"(" << a.center->coordx << "," <<a.center->coordy <<") ";
			cout<<a.angle<<" ";
			cout<<colorWriter(a.color)<<" ";
			cout<<"(" << a.p1->coordx << "," <<a.p1-> coordy << ") ";
			cout<<"(" << a.p2->coordx << "," <<a.p2-> coordy << ") ";
			cout<<"(" << a.p3->coordx << "," <<a.p3-> coordy << ") ";
			cout<<endl;
		}		
		else if(a.p2)
		{
			cout<<"Rectangle ";
			cout<<"(" << a.center->coordx << "," <<a.center->coordy <<") ";
			cout<<a.angle<<" ";			
			cout<<colorWriter(a.color)<<" ";
			cout<<"(" << a.p1->coordx << "," <<a.p1-> coordy << ") ";
			cout<<"(" << a.p2->coordx << "," <<a.p2-> coordy << ") ";
			cout<<endl;
		}
		else
		{
			cout<<"Circle ";
			cout<<"(" << a.center->coordx << "," <<a.center->coordy <<") ";
			cout<<colorWriter(a.color)<<" ";
			cout<<a.angle;
			cout<<endl;
		}
	}
}
void ShapeEditor::handle(Event e)
{
	switch(e)
	{
		case COPY:
			copy();
			break;

		case CUT:
			cut();			
			break;

		case PASTE:
			paste();
			break;

		case SAVE:
			save();
			break;

		case CLOSE:
			save();
			break;

		case DELETE:
			deleteObject();
			break;
	}
}

void ShapeEditor::reset()
{
}

/************************Implementation of Editor***************/
char* Editor::getName()
{
	char *x;

	mystrcpy(x,editorName);
	return x;
}

Editor::Editor()
{
}

/********************Implementation of Screen*********************/
Screen::Screen()
{};

void Screen::addEditor(Editor * edt)
{
	int i, size;

	size = editors.size();

	for(i=0;i<size&&strcmp(editors[i]->getName(), edt->getName()); i++);

	if(i==size || !size)
		editors.push_back(edt);
	else
		throw Error("Error in Creating the Editor");
}

void Screen::removeEditor(char * remName)
{
	int i, size, r;
	size=editors.size();
	for(i=0;strcmp(editors[i]->getName(), remName)&&i<size; i++);

	if(i==size)
		throw Error("Error: Editor is not found");
	else
		editors.erase(editors.begin() + i, editors.begin() + i + 1);
	
}

void Screen::send(char *name, Event e)
{
	int i, size, r;
	size=editors.size();
	for(i=0;strcmp(editors[i]->getName(), name)&&i<size; i++);

	if(i==size)
		throw Error("Error: Editor is not found");
	else 
		editors[i]->handle(e);
}

