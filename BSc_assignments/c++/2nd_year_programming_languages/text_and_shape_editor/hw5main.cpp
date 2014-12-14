#include "hw5.h"

using namespace std;

int main()
{
 Screen s;
 ShapeEditor e("sed");
 s.addEditor(&e);

Rectangle r1(Point(3,-2), Point(5,10));
 Rectangle r2(Point(-6,-3), Point(7,2));
 Triangle t(Point(-6,6), Point(1,6), Point(5,9));
 Circle c(Point(1,4), 3);

 e.addGeometricObject(&r1);
 e.addGeometricObject(&r2);
 e.addGeometricObject(&t);
 e.addGeometricObject(&c);

 r1.setColor(RED);
 r2.setColor(GREEN);
 t.setColor(BLUE);
 c.setColor(CYAN);

 e.draw();
cout << "---1-----" << endl;
 e.pick(Point(-1,4));
 s.send("sed", CUT);
 s.send("sed",COPY);
 s.send("sed",PASTE);
 e.draw(); 

cout << "---2-----" << endl;
 e.pick(Point(0,7));
 e.addGeometricObject(&c);
 s.send("sed",COPY);
 s.send("sed",PASTE);
 e.draw(); cout << "---3-----" << endl;
 r1.move(Point(100,200));
 e.pick(Point(100,200));
 e.cut();
 e.paste();
 e.pick(Point(0,0));
 e.cut();
 e.paste();
 r1.move(Point(4,4));
 e.pick(Point(1,-6));
 e.addGeometricObject(&r1);
 e.deleteObject();

 e.deleteObject();  // en son paste edilen rectangle silindi
 e.pick(Point(1,-6));
 e.deleteObject();
 e.draw(); cout << "---4-----" << endl;
 c.scale(100);
 c.move(Point(0,0));
 e.pick(Point(100,0));
 e.deleteObject();
 e.pick(Point(3.5,4));
 e.deleteObject();
 e.draw(); cout << "---5-----" << endl;
 t.rotate(90,CLOCKWISE);
 t.rotate(90,CLOCKWISE);
 t.rotate(90,CLOCKWISE);
 t.rotate(90,CLOCKWISE);
 e.draw(); cout << "---6-----" << endl;
 r2.rotate(180,ANTICLOCKWISE);
 e.draw(); cout << "---7-----" << endl;
 r2.rotate(-180,CLOCKWISE);
 e.draw(); cout << "---8-----" << endl;
 t.rotate(-47.825,CLOCKWISE);
 e.draw(); cout << "---9-----" << endl;
 t.scale(2);
 e.addGeometricObject(&r1);
 e.addGeometricObject(&c);
 e.draw(); cout << "---10----" << endl;
 s.send("sed", CLOSE);

 return 0;
}
	/*Triangle a(Point(1, 6), Point(-4, 0), Point(0,3));

	/*cout<<a.center->coordx<<","<<a.center->coordy<<endl;
	cout<<a.point1->coordx<<","<<a.point1->coordy<<endl;
	cout<<a.point2->coordx<<","<<a.point2->coordy<<endl;
	cout<<a.point3->coordx<<","<<a.point3->coordy<<endl;
	*//*cout<<a.angle<<endl;
	cout<<a.area()<<endl;
	cout<<a.checkIfInside(Point(0.60457, 4.81368));

/*
	a.move(Point(0,0));
	cout<<a.center->coordx<<","<<a.center->coordy<<endl;
	cout<<a.point1->coordx<<","<<a.point1->coordy<<endl;
	cout<<a.point2->coordx<<","<<a.point2->coordy<<endl;
	cout<<a.point3->coordx<<","<<a.point3->coordy<<endl;
	cout<<a.angle<<endl;
	cout<<a.area()<<endl;

	a.move(Point(1,1));
	cout<<a.center->coordx<<","<<a.center->coordy<<endl;
	cout<<a.point1->coordx<<","<<a.point1->coordy<<endl;
	cout<<a.point2->coordx<<","<<a.point2->coordy<<endl;
	cout<<a.point3->coordx<<","<<a.point3->coordy<<endl;
	cout<<a.angle<<endl;
	cout<<a.area()<<endl;

	Triangle b(Point(0,5), Point(-3,-4), Point(3,-1));
	b.move(Point(1,1));
	b.rotate(-37, CLOCKWISE);
	cout<<b.center->coordx<<","<<b.center->coordy<<endl;
	cout<<b.point1->coordx<<","<<b.point1->coordy<<endl;
	cout<<b.point2->coordx<<","<<b.point2->coordy<<endl;
	cout<<b.point3->coordx<<","<<b.point3->coordy<<endl;
	cout<<b.angle<<endl;
	cout<<b.area()<<endl;
	
	b.scale(1);
	cout<<b.center->coordx<<","<<b.center->coordy<<endl;
	cout<<b.point1->coordx<<","<<b.point1->coordy<<endl;
	cout<<b.point2->coordx<<","<<b.point2->coordy<<endl;
	cout<<b.point3->coordx<<","<<b.point3->coordy<<endl;
	cout<<b.angle<<endl;
	cout<<b.area()<<endl;

	b.scale(3);
	cout<<b.center->coordx<<","<<b.center->coordy<<endl;
	cout<<b.point1->coordx<<","<<b.point1->coordy<<endl;
	cout<<b.point2->coordx<<","<<b.point2->coordy<<endl;
	cout<<b.point3->coordx<<","<<b.point3->coordy<<endl;
	cout<<b.angle<<endl;
	cout<<b.area()<<endl;*/

/*	

	Rectangle a(Point(-3,-4),Point(3,4));

	/*cout<<a.center->coordx<< ","<<a.center->coordy<<endl;
	cout<<a.upperright->coordx<< ","<<a.upperright->coordy<<endl;
	cout<<a.upperleft->coordx<<","<<a.upperleft->coordy<<endl;
	cout<<a.lowerleft->coordx<<","<<a.lowerleft->coordy<<endl;
	cout<<a.lowerright->coordx<<","<<a.lowerright->coordy<<endl;*/
/*	cout<<a.angle<<endl;
	cout<<a.area()<<endl;
		
	cout<<a.checkIfInside(Point(-3,0));



	a.move(Point(-2,-2));*/

/*	cout<<a.center->coordx<< ","<<a.center->coordy<<endl;
	cout<<a.upperright->coordx<< ","<<a.upperright->coordy<<endl;
	cout<<a.upperleft->coordx<<","<<a.upperleft->coordy<<endl;
	cout<<a.lowerleft->coordx<<","<<a.lowerleft->coordy<<endl;
	cout<<a.lowerright->coordx<<","<<a.lowerright->coordy<<endl;*/
/*	cout<<a.angle<<endl;
	cout<<a.area()<<endl;

	a.rotate(-37, CLOCKWISE);

	cout<<a.center->coordx<< ","<<a.center->coordy<<endl;
	cout<<a.upperright->coordx<< ","<<a.upperright->coordy<<endl;
	cout<<a.upperleft->coordx<<","<<a.upperleft->coordy<<endl;
	cout<<a.lowerleft->coordx<<","<<a.lowerleft->coordy<<endl;
	cout<<a.lowerright->coordx<<","<<a.lowerright->coordy<<endl;
	cout<<a.angle<<endl;
	cout<<a.area()<<endl;
	cout<<a.checkIfInside(Point(-3,-4));*/

	

//////////////
	/*a.scale(1);
/*	cout<<a.center->coordx<< ","<<a.center->coordy<<endl;
	cout<<a.upperright->coordx<< ","<<a.upperright->coordy<<endl;
	cout<<a.upperleft->coordx<<","<<a.upperleft->coordy<<endl;
	cout<<a.lowerleft->coordx<<","<<a.lowerleft->coordy<<endl;
	cout<<a.lowerright->coordx<<","<<a.lowerright->coordy<<endl;*/
	/*cout<<a.angle<<endl;
	cout<<a.area()<<endl;

	/*a.scale(3);
	cout<<a.area()<<endl;


/*	Point p1(2,3), p2(0,0) ;
	Circle c(p1, 4), c2(p2, 5.60);


	cout<<c.area()<<endl;
	cout<<c2.area()<<endl;

	cout<<c.checkIfInside(Point(2, 1))<<endl;
	cout<<c2.checkIfInside(Point(-5.60, 0))<<endl;*/

/*	cout<<c.center->coordx<< ","<<c.center->coordy<<"   " <<c.radius <<endl;
	cout<<c2.center->coordx<< ","<<c2.center->coordy<<"   "<<c2.radius<<endl;*/

/*	c.scale(4);
	c2.scale(2);

	/*cout<<c.center->coordx<< ","<<c.center->coordy<<"   " <<c.radius <<endl;
	cout<<c2.center->coordx<< ","<<c2.center->coordy<<"   "<<c2.radius<<endl;*/

/*	c.move(p2);
	c2.move(p1);

	c.rotate(-920, ANTICLOCKWISE);
	c2.rotate(40.5, CLOCKWISE);

	c.rotate(223.9, CLOCKWISE);
	c2.rotate(-409.8, CLOCKWISE);
	
	*/
/*	cout<<c.center->coordx<< ","<<c.center->coordy<<"   " <<c.radius <<"    "<< c.angle<<endl;
	cout<<c2.center->coordx<< ","<<c2.center->coordy<<"   "<<c2.radius<<"     "<<c2.angle<<endl;*/


	/*TextEditor a("rrr");
	cout<<a.getName();	

	/*a.addText("0123");
	a.draw();
	cout<<endl;

	a.addText("45");
	a.draw();
	cout<<endl;
	
	a.cur.moveCursor(4);
	a.draw();
	cout<<endl;

	a.addText("abc");
	a.draw();
	cout<<endl;

	a.cur.moveCursor(9);
	a.draw();
	cout<<endl;

	/*cout<<a.replace("a", "xx");
	a.draw();
	cout<<endl;
	a.replace("a"," ");
	a.draw();
	cout<<endl;
	a.replace("", "kdm");
	a.draw();
	cout<<endl;
	cout<<a.replace("x", "strx");
	a.draw();
	cout<<endl;*/

/*	a.addText("bu yogurdu sarimsaklasak da mi saklasak sarimsaklamasak da mi saklasa");
	cout<<a.replace("da", "brcv");
	a.draw();
	cout<<endl;/*

	cout<<a.replace("sarimsak", "cacik");
	a.draw();
	cout<<endl;

	cout<<a.replace("saklasak", "tt");
	a.draw();

	cout<<endl;
	*/
/*	a.select(4);
	a.copy();
	a.paste();
	a.paste();
	a.draw();
	cout<<endl;

	a.select(-7);
	a.copy();
	a.paste();
	a.paste();
	a.draw();

	a.save();
	cout<<endl;

	a.select(40);
	a.paste();
	a.copy();
	a.paste();
	a.draw();
	cout<<endl;


	a.select(-10);
	a.cut();
	a.cur.moveCursor(7);
	a.paste();
	a.paste();
	a.draw();
	cout<<endl;

	a.select(-34);
	a.cut();
	a.select(100);
	a.paste();

	a.draw();
	cout<<endl;

	a.select(-5);
	//a.select(0);
	a.cut();
	a.cur.moveCursor(0);
	a.paste();

	a.draw();
	//a.save();
	cout<<endl;*/
/*	return 0;
}*/
