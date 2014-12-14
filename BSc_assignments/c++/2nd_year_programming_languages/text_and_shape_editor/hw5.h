#ifndef _HW5_H_
#define _HW5_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

enum Event {COPY, CUT, PASTE, SAVE, CLOSE, DELETE };
enum Direction {CLOCKWISE, ANTICLOCKWISE};
enum Color {WHITE,RED,BLUE,GREEN,MAGENTA,CYAN,YELLOW,PINK,BROWN,ORANGE};

struct Point 		/***ok***/
{
	double coordx;
	double coordy;
	Point (double a, double b) {coordx=a; coordy=b;}
};

struct Pack
{
	Point *center;
	double angle;
	Color color;
	Point *p1;
	Point *p2;
	Point *p3;
};

struct Error 		/***ok***/
{
	const char *mess;
	Error(const char *p) { mess=p;}
};

class Editor /******works*********/  
{
	protected:
		char *editorName;
	public :
		Editor();
		virtual void save()=0;
		virtual void copy()=0;
  		virtual void cut()=0;
  		virtual void paste()=0;
  		virtual void deleteObject()=0;
  		virtual void draw()=0;
  		virtual void handle(Event)=0;
		virtual void reset()=0;
		char* getName();
};

class Cursor		/****works****/
{
	private:
		int pos;
		Editor *t;
	public:
		Cursor(int a=0);
		void moveCursor(int);
		int getCursor();
		void setPoint(Editor* n);
};

class TextEditor : public Editor
{					/****works properly**/
	private:
		Cursor cur;
		vector<char> text;		
		int start, end;
	public:
		TextEditor(char *);
		
		void addText(char *);
		char * replace(char *, char*);
		void select(int);
		void reset();
		
		void save();
		void copy();
  		void cut();
  		void paste();
  		void deleteObject();
  		void draw();
  		void handle(Event);
};

class GeometricObject		/****works properly*******/
{
	protected:
		Point *center;
		double angle;
		Color color;
		
	public:
		GeometricObject();
		virtual GeometricObject* copy()= 0;
		virtual double area()=0;
		virtual void scale(int scalefactor)=0;
		virtual void move(Point)=0;
		virtual void rotate(double, Direction) { };
		virtual bool checkIfInside(Point)=0;
		void setColor(Color);
		virtual Pack draw()=0;
};

class Circle : public GeometricObject
{					/***********works properly************/
	private:
		double radius;
	public:
		GeometricObject* copy();
		Circle(Point, double);
		Circle (const Circle &ref);
		double area();
		void scale(int);
		void move(Point);
		void rotate(double, Direction);
		bool checkIfInside(Point);
		Pack draw();
};

class Rectangle : public GeometricObject
{
	private:				/*******works properly*********/
		Point *upperright;
		Point *upperleft;
		Point *lowerleft;
		Point *lowerright;	
	public:
		GeometricObject* copy();		
		Rectangle(Point, Point);
		Rectangle(const Rectangle &ref);
		double area();
		void scale(int);
		void move(Point);
		void rotate(double, Direction);
		bool checkIfInside(Point);
		Pack draw();
};

class Triangle : public GeometricObject
{						/********works properly**********/
	private:
		Point *point1,*point2,*point3;
	public:
		GeometricObject* copy();
		Triangle(const Triangle &ref);
		Triangle(Point, Point, Point);
		double area();
		void scale(int);
		void move(Point);
		void rotate(double, Direction);
		bool checkIfInside(Point);
		Pack draw();
};

class ShapeEditor : public Editor
{
	private:
		vector<GeometricObject *> objs;
		GeometricObject *picked;
		int index;
	public:
		ShapeEditor(char *);
		void addGeometricObject(GeometricObject *);
		GeometricObject* pick(Point);
		void save();
		void copy();
  		void cut();
  		void paste();
  		void deleteObject();
  		void draw();
  		void handle(Event);
		void reset();
};

class Screen		/************/
{
	private:
		vector<Editor *> editors;
	public:
		Screen();
		void addEditor(Editor *);
		void removeEditor(char *);
		void send(char *, Event);
};
#endif

