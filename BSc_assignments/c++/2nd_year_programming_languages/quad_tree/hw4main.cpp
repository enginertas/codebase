#include "hw4.h"

int main() {
QuadTree a(200), b(200), c(200);
QuadTree d(10000000);

a.insertNode(Point(10,10),Point(100,100)).insertNode(Point(40,80),Point(190,10));
a.insertNode(Point(10,10),Point(100,123));
b.insertNode(Point(42,10),Point(140,120));
c.insertNode(Point(98,27),Point(198,50));


a=a+b;
a=a-c;
b=a*c;
c=a+~b*~c;

cout << a << '\n' << b << '\n' << c << '\n';

return 0;
}



/*#include "hw4.cpp"
#include <fstream>
#include <string>
int main()
{
/*	QuadTree a(10),b(10),c(10),d(10),e(10),f(10),g(10),h(10),i(10),j(10),k(10),l(10),m(10),n(10),temp(10);
Point p0(2,3),p1(8,9),p2(5,5),p3(8,1),p4(9,8),p5(1,3),p6(4,8),p7(1,2),p8(8,5),p9(9,5),p10(3,3),p11(7,7),p12(1,0),p13(9,1),p14(6,6),p15(6,7);


b=~a;
c.insertNode(p0,p1);
temp=b;
d=temp.deleteNode(p3,p4).deleteNode(p2,p2);
e.insertNode(p5,p6).insertNode(p2,p7).insertNode(p8,p9);     f=(~e).deleteNode(p10,p11).insertNode(p12,p13).insertNode(p14,p15);
g=a-b;
h=b-a;
i=d*e;
j=d+e;
k=d-e;
l=d+e*f-(a*c+c*d+e*f);
m=a*(c-d-e+f);
n=b*(c-d-e+f);

//cout<<"A:"<<endl<<a<<endl;
//cout<<"B:"<<endl<<b<<endl;
//cout<<"C:"<<endl<<c<<endl;
//cout<<"D:"<<endl<<d<<endl;
//cout<<"E:"<<endl<<e<<endl;
//cout<<"F:"<<endl<<f<<endl;
//cout<<"G:"<<endl<<g<<endl;
//cout<<"H:"<<endl<<h<<endl;
//cout<<"I:"<<endl<<i<<endl;
//cout<<"J:"<<endl<<j<<endl;
//cout<<"K:"<<endl<<k<<endl;
//cout<<"L:"<<endl<<l<<endl;
//cout<<"M:"<<endl<<m<<endl;
//cout<<"N:"<<endl<<n<<endl;


/*QuadTree o(10);
Point p16(4,6),p17(0,2),p18(1,1);

o=((~(a-b+c-d+e-f)).insertNode(p13,p18).deleteNode(p16,p17))-e;
cout<<"O:"<<endl<<o<<endl;

 try {
        QuadTree* q = new QuadTree(9);
        QuadTree x(0);
        x = (*q)+c;
        cout<<"X:"<<endl<<x<<endl;
        delete q;
    }
    catch( Error& e) {
        cout<<"X:"<<endl<<e.mess<<endl;
    }

    try {
        QuadTree* q = new QuadTree(9);
        QuadTree* y = new QuadTree(0);
        *y = (*q)*c;
        cout<<"Y:\n"<<*y<<endl;
        delete y; delete q;
    }
    catch( Error& e) {
        cout<<"Y:\n"<<e.mess<<endl;
    }

    try {
        QuadTree* q = new QuadTree(9);
        QuadTree z(0);
        z = (*q)-c;
        cout<<"Z:\n"<<z<<endl;
        delete q;
    }
    catch( Error& e) {
        cout<<"Z:\n"<<e.mess<<endl;
    }*/
/*string x="d.txt";
ofstream out(x.c_str());

QuadTree d(10000),e(10000),f(10000),g(10000);
d.insertNode(Point(4920,6840),Point(7010,9490));
out<<d<<endl;
out.close();
e.insertNode(Point(3105,9380),Point(1295,5845));
out.open("e1.txt");
out<<e<<endl;
out.close();
e.deleteNode(Point(2110,3245),Point(4030,4575));
out.open("e2.txt");
out<<e<<endl;
out.close();
f=d+e;
g=(d-e)*f;

out.open("f.txt");
out<<f<<endl;
out.close();

out.open("g.txt");
out<<g<<endl;
out.close();

}*/
