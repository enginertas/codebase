#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <fstream>
#include "Object3DS.h"

using namespace std;

const int WINDOW_SIZE = 800;
const int START_ROAD = 0, END_ROAD = 202800, ST_RACE = 1000, EN_RACE = 201800;
const float RAD = 3.14159/180;

char Car_Name[3][25] = {"cars/Mazdo.3ds", "cars/Car (basic).3ds", "cars/Corvette.3ds"};
Object3DS Cars[3];
char Obstacles[1000][5], Cam_Mode = '1', Last_Key_LR = 0, Last_Key_FW = 0;
int Mode = 0, Car_No = 0, Win, Win_Sub, Car_Angle = 0, Ang = 0;
float Car_LR = 0.0f, Car_FW = 200.0f, Car_Speed = 0.0f;
float Camera_X = 0, Camera_Z = 200.0f , Camera_Y[4] = {50.0f, 60.0f, 50.0f, 58.0f};
float Cam_Ref_X = 0, Cam_Ref_Z= 0;

void drawTire(void)
{
	glBegin(GL_POLYGON);
		GLUquadric *quadric = gluNewQuadric();
		gluCylinder(quadric, 12, 12, 10 , 50, 50);
	glEnd();
}
void drawConical(void)
{
	GLUquadric *quadric = gluNewQuadric();
	gluCylinder(quadric, 5, 50, 40 , 50, 50);
}
void drawCylinder(void)
{
	GLUquadric *quadric = gluNewQuadric();
	gluCylinder(quadric, 30, 30, 40 , 50, 50);
}
void drawWall()
{
	glColor3f(1.0f, 0.8f, 0.8f);
	glBegin(GL_POLYGON);
		glVertex3f(-40.0f, 0.0f, 40.0f);
		glVertex3f(-40.0f, 40.0f, 40.0f);
		glVertex3f(40.0f, 40.0f, 40.0f);
		glVertex3f(40.0f, 0.0f, 40.0f);		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-40.0f, 0.0f, -40.0f);
		glVertex3f(-40.0f, 40.0f, -40.0f);
		glVertex3f(40.0f, 40.0f, -40.0f);
		glVertex3f(40.0f, 0.0f, -40.0f);		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-40.0f, 40.0f, 40.0f);
		glVertex3f(-40.0f, 40.0f, -40.0f);
		glVertex3f(-40.0f, 0.0f, -40.0f);
		glVertex3f(-40.0f, 0.0f, 40.0f);		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(40.0f, 40.0f, 40.0f);
		glVertex3f(40.0f, 40.0f, -40.0f);
		glVertex3f(40.0f, 0.0f, -40.0f);
		glVertex3f(40.0f, 0.0f, 40.0f);		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-40.0f, 40.0f, 40.0f);
		glVertex3f(-40.0f, 40.0f, -40.0f);
		glVertex3f(40.0f, 40.0f, -40.0f);
		glVertex3f(40.0f, 40.0f, 40.0f);		
	glEnd();
}
void drawMyCar()
{
	/********** Car Tires ********/
	glPushMatrix();
	if(Mode ==1)
	{
		if(Cam_Mode == '2' || Cam_Mode == '3')
			glTranslatef(190.0f, 0.0f, -4.5f);	
	
	}
	glColor3f(0.3f, 0.3f, 0.3f);
	glPushMatrix();
		glTranslatef(-52.0f, 12.0f, 40.0f);
		glRotatef(180, 0, 1, 0);
		glTranslatef(0.0f, 0.0f, 0.0f);		
		drawTire();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(52.0f, 12.0f, 40.0f);
		glRotatef(180, 0, 1, 0);
		glTranslatef(0.0f, 0.0f, 0.0f);		
		drawTire();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(52.0f, 12.0f, -30.0f);
		drawTire();
	glPopMatrix();
		glPushMatrix();
		glTranslatef(-52.0f, 12.0f, -30.0f);
		drawTire();
	glPopMatrix();
	
	/******** Sub-Platform of Car ****/
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_POLYGON);
		glVertex3f(-66.0f , 10.0f, 30.0f);
		glVertex3f(66.0f , 10.0f, 30.0f);
		glVertex3f(66.0f , 10.0f, -20.0f);
		glVertex3f(-66.0f , 10.0f, -20.0f);	
	glEnd();	
	glBegin(GL_POLYGON);
		glVertex3f(38.0f , 10.0f, 40.0f);
		glVertex3f(-38.0f , 10.0f, 40.0f);
		glVertex3f(-38.0f , 10.0f, -30.0f);	
		glVertex3f(38.0f , 10.0f, -30.0f);
	glEnd();	
	glBegin(GL_POLYGON);
		glVertex3f(84.0f , 10.0f, 40.0f);
		glVertex3f(66.0f , 10.0f, 40.0f);
		glVertex3f(66.0f , 10.0f, -30.0f);	
		glVertex3f(84.0f , 10.0f, -30.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-100.0f , 10.0f, 40.0f);
		glVertex3f(-66.0f , 10.0f, 40.0f);
		glVertex3f(-66.0f , 10.0f, -30.0f);	
		glVertex3f(-100.0f , 10.0f, -30.0f);
	glEnd();

	/********* Top of Car *******/
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3f(-28.0f , 52.0f, 40.0f);
		glVertex3f(36.0f , 52.0f, 40.0f);
		glVertex3f(36.0f , 52.0f, -30.0f);
		glVertex3f(-28.0f , 52.0f, -30.0f);	
	glEnd();
	
	/******** Kaput :) of Car ****/
	glBegin(GL_POLYGON);
		glVertex3f(-60.0f , 28.0f, 40.0f);
		glVertex3f(-100.0f , 27.0f, 40.0f);
		glVertex3f(-100.0f , 27.0f, -30.0f);	
		glVertex3f(-60.0f , 28.0f, -30.0f);	
	glEnd();
	
	/******** Bagaj of Car ********/
	glBegin(GL_POLYGON);
		glVertex3f(54.0f , 28.0f, 40.0f);
		glVertex3f(84.0f , 28.0f, 40.0f);
		glVertex3f(84.0f , 28.0f, -30.0f);	
		glVertex3f(54.0f , 28.0f, -30.0f);	
	glEnd();
	
	/******** First near-side of car ******/
	/***** Over tires****/
	glBegin(GL_POLYGON);
		glVertex3f(84.0f , 28.0f, 40.0f);
		glVertex3f(84.0f , 10.0f, 40.0f);
		glVertex3f(66.0f , 10.0f, 40.0f);	
		glVertex3f(64.0f , 22.0f, 40.0f);	
		glVertex3f(52.0f , 28.0f, 40.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-100.0f , 27.0f, 40.0f);
		glVertex3f(-100.0f , 10.0f, 40.0f);
		glVertex3f(-66.0f , 10.0f, 40.0f);	
		glVertex3f(-64.0f , 24.0f, 40.0f);	
		glVertex3f(-52.0f , 28.0f, 40.0f);		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(38.0f, 28.0f, 40.0f);
		glVertex3f(38.0f, 10.0f, 40.0f);
		glVertex3f(40.0f, 24.0f, 40.0f);		
		glVertex3f(60.0f, 28.0f, 40.0f);		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-38.0f, 28.0f, 40.0f);
		glVertex3f(-38.0f, 10.0f, 40.0f);
		glVertex3f(-40.0f, 24.0f, 40.0f);		
		glVertex3f(-60.0f, 28.0f, 40.0f);
	glEnd();

	/******* Near doors *******/
	glBegin(GL_POLYGON);
		glVertex3f(38.0f, 28.0f, 40.0f);
		glVertex3f(-38.0f, 28.0f, 40.0f);
		glVertex3f(-38.0f, 10.0f, 40.0f);		
		glVertex3f(38.0f, 10.0f, 40.0f);		
	glEnd();
	
	/******** Second Side of Car ******/
	/******* Over Tires *******/
	glBegin(GL_POLYGON);
		glVertex3f(84.0f , 28.0f, -30.0f);
		glVertex3f(84.0f , 10.0f, -30.0f);
		glVertex3f(66.0f , 10.0f, -30.0f);	
		glVertex3f(64.0f , 22.0f, -30.0f);	
		glVertex3f(52.0f , 28.0f, -30.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-100.0f , 27.0f, -30.0f);
		glVertex3f(-100.0f , 10.0f, -30.0f);
		glVertex3f(-66.0f , 10.0f, -30.0f);	
		glVertex3f(-64.0f , 24.0f, -30.0f);	
		glVertex3f(-52.0f , 28.0f, -30.0f);		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-38.0f, 28.0f, -30.0f);
		glVertex3f(-38.0f, 10.0f, -30.0f);
		glVertex3f(-40.0f, 24.0f, -30.0f);		
		glVertex3f(-60.0f, 28.0f, -30.0f);	
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(38.0f, 28.0f, -30.0f);
		glVertex3f(38.0f, 10.0f, -30.0f);
		glVertex3f(40.0f, 24.0f, -30.0f);		
		glVertex3f(60.0f, 28.0f, -30.0f);		
	glEnd();
	
	/****** Near Doors ******/
	glBegin(GL_POLYGON);
		glVertex3f(38.0f, 28.0f, -30.0f);
		glVertex3f(-38.0f, 28.0f, -30.0f);
		glVertex3f(-38.0f, 10.0f, -30.0f);		
		glVertex3f(38.0f, 10.0f, -30.0f);		
	glEnd();
	
	/****** Windows ******/
	glColor3f(0.8f, 0.8f, 0.8f);	
	glBegin(GL_POLYGON);
		glVertex3f(-28.0f , 52.0f, 40.0f);
		glVertex3f(-60.0f , 28.0f, 40.0f);
		glVertex3f(-60.0f , 28.0f, -30.0f);	
		glVertex3f(-28.0f , 52.0f, -30.0f);	
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(36.0f , 52.0f, 40.0f);
		glVertex3f(54.0f , 28.0f, 40.0f);
		glVertex3f(54.0f , 28.0f, -30.0f);	
		glVertex3f(36.0f , 52.0f, -30.0f);	
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-60.0f , 28.0f, 40.0f);
		glVertex3f(-28.0f , 52.0f, 40.0f);
		glVertex3f(36.0f , 52.0f, 40.0f);	
		glVertex3f(54.0f , 28.0f, 40.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-60.0f , 28.0f, -30.0f);
		glVertex3f(-28.0f , 52.0f, -30.0f);
		glVertex3f(36.0f , 52.0f, -30.0f);	
		glVertex3f(54.0f , 28.0f, -30.0f);
	glEnd();
	
	/***** Back and Front of Car ****/
	glColor3f(0.1f, 0.1f, 0.1f);
	glBegin(GL_POLYGON);
		glVertex3f(-100.0f , 27.0f, 40.0f);
		glVertex3f(-100.0f , 10.0f, 40.0f);
		glVertex3f(-100.0f , 10.0f, -30.0f);	
		glVertex3f(-100.0f , 27.0f, -30.0f);	
	glEnd();
	
	glColor3f(0.1f, 0.1f, 0.1f);
	glBegin(GL_POLYGON);
		glVertex3f(84.0f , 28.0f, 40.0f);
		glVertex3f(84.0f , 10.0f, 40.0f);
		glVertex3f(84.0f , 10.0f, -30.0f);	
		glVertex3f(84.0f , 28.0f, -30.0f);	
	glEnd();
	
	/*********Spoiler *******/
	glColor3f(0.4f, 0.4f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3f(80.0f, 28.0f, 33.0f);
		glVertex3f(82.0f, 34.0f, 33.0f);
		glVertex3f(82.0f, 34.0f, 30.0f);
		glVertex3f(80.0f, 28.0f, 30.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(80.0f, 28.0f, -23.0f);
		glVertex3f(82.0f, 34.0f, -23.0f);
		glVertex3f(82.0f, 34.0f, -20.0f);
		glVertex3f(80.0f, 28.0f, -20.0f);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(81.0f, 34.0f, 40.0f);
		glVertex3f(83.0f, 34.0f, 40.0f);
		glVertex3f(83.0f, 34.0f, -30.0f);
		glVertex3f(81.0f, 34.0f, -30.0f);
	glEnd();
	glPopMatrix();
}
void fileRead()
{
	int i;
	ifstream in;

	for(i=0; i<1000; i++)
	{
		Obstacles[i][0] = Obstacles[i][1] = Obstacles[i][2] = '_';
		Obstacles[i][3] = Obstacles[i][4] = '_';
	}
	in.open("METU_F1_2010.txt", ifstream::in);
	for(i=0; i<1000; i++)
	{
		in >> Obstacles[i][0];
		in >> Obstacles[i][1];
		in >> Obstacles[i][2];
		in >> Obstacles[i][3];
		in >> Obstacles[i][4];
	}
	in.close();
}
void carInit()
{
	Cars[0] = Object3DS();
	Cars[1] = Object3DS();	
	Cars[2] = Object3DS();	
	
	Cars[0].Initialize(Car_Name[0]);
	Cars[1].Initialize(Car_Name[1]);
	Cars[2].Initialize(Car_Name[2]);
	
	Cars[2].SetScalar(0.5f);
	Cars[1].SetScalar(30.0f);
	Cars[1].Rotate(0.0f, 90, 0.0f);
}
void rotateCar()
{
	if(Car_No == 1)
		Cars[1].Rotate(0.0f, Ang - 90, 0.0f);
		
	else if(Car_No != 3)
		Cars[Car_No].Rotate(0.0f, Ang, 0.0f);
		
	Ang = (Ang + 1) % 360;
}
void selectCar(int right)
{	
	if(right)
		Car_No = (Car_No + 1) % 4;
	else
		Car_No = (Car_No + 3) % 4;

	glutPostRedisplay();
}
void speedDisplay()
{
	int i;
	float degree;

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	degree = -Car_Speed * 0.75 + 37.5f;
	
	glColor3f(1.4f, 1.4f, 1.4f);
	glPushMatrix();
		glTranslatef(100.0f, 100.0f, 0.0f);
		glRotatef(degree, 0, 0, 1);
		glBegin(GL_TRIANGLES);
			glVertex2f(-70.0f, 0.0f);
			glVertex2f(0.0f, 5.0f);
			glVertex2f(0.0f, -5.0f);
		glEnd();
	glPopMatrix();
	
	degree = 217.5f;
	for(i=0; i<=17; degree -= 15, i++)
	{
		glPushMatrix();
			glTranslatef(100 + cos(degree*RAD) * 70, 100 + sin(degree*RAD) * 70, 0.0f);
			glRotatef(degree, 0, 0, 1);
			glBegin(GL_POLYGON);
				glVertex3f(0.0f, 1.0f, 0.0f);
				glVertex3f(0.0f, -1.0f, 0.0f);
				glVertex3f(25.0f, -1.0f, 0.0f);
				glVertex3f(25.0f, 1.0f, 0.0f);			
			glEnd();
		glPopMatrix();
	}
	glutSwapBuffers();
}
void getCarOrder()
{
	switch(Last_Key_LR)
	{
		case 'L':
			Car_Angle += 3;
			if(Car_Angle == 360)
				Car_Angle = 0;				
			break;
		case 'R':
			Car_Angle -= 3;
			if(Car_Angle == -360)
				Car_Angle = 0;
			break;
	 }
	 switch(Last_Key_FW)
	 {
		case 'U':
			Car_Speed += 5;
			if(Car_Speed >340)
				Car_Speed = 340;
			break;
		case 'D':
			Car_Speed -= 8;
			if(Car_Speed < 0)
				Car_Speed = 0;		
	}
	if(Car_Speed)
	{
		if(Car_LR < -235.0f || Car_LR > 235.0f)
		{
			Car_Speed -= 2.5f;
			if(Car_Speed<0)
				Car_Speed = 0;
		}
		else if(Car_LR < -140.0f || Car_LR > 140.0f)
		{
			Car_Speed -= 1.5f;
			if(Car_Speed<0)
				Car_Speed = 0;
		}
		else
		{
			Car_Speed -= 0.5f;
			if(Car_Speed<0)
				Car_Speed = 0;
		}
	}
}
void moveCar()
{
	float diff_fw, diff_lr;
	diff_fw = Car_Speed * cos(Car_Angle*RAD)* 0.45f;
	diff_lr = Car_Speed * sin(Car_Angle*RAD)* 0.45f;
	
	if((diff_fw > 0 && Car_FW < EN_RACE) || (diff_fw < 0 && Car_FW > ST_RACE))
		Car_FW += diff_fw;
	else
		Car_Speed = 0;
		
	if((diff_lr > 0 && Car_LR < 485) || (diff_lr < 0 && Car_LR > -485))
		Car_LR += diff_lr;
}
void adjustCamera()
{
	float camera_dis;
	switch(Cam_Mode)
	{
		case '1':	
			camera_dis = 200 + 0.4 * Car_Speed;
			Camera_Z = Car_FW - camera_dis * cos(Car_Angle * RAD);
			Camera_X = Car_LR - camera_dis * sin(Car_Angle * RAD);
			break;
		case '2':
			camera_dis = 30;
			Camera_Z = Car_FW + camera_dis * cos(Car_Angle * RAD);
			Camera_X = Car_LR + camera_dis * sin(Car_Angle * RAD);
			Cam_Ref_Z = Car_FW + camera_dis * cos(Car_Angle * RAD) * 2;
			Cam_Ref_X = Car_LR + camera_dis * sin(Car_Angle * RAD) * 2;
			break;
		case '3':
			camera_dis = 200 + 0.4 * Car_Speed;
			Camera_Z = Car_FW + camera_dis * cos(Car_Angle * RAD);
			Camera_X = Car_LR + camera_dis * sin(Car_Angle * RAD);
			break;
	}
}
void glCircleField(float x, float y, float z, float r)
{
	int i=0;
   	glBegin(GL_POLYGON);
 
	for(; i < 360; i++)
	{
		float degree = i*RAD;
		glVertex3f(x + cos(degree)*r, y, z + sin(degree)*r);
	}
	glEnd();
}
void drawEnvironment()
{
	int i, rs, re;
	
	/*********** Grass - Bottom of Box *********/
	glColor3f(0.0f, 0.8f, 0.0f);
	glBegin(GL_POLYGON);
		glVertex3f(-1100, -0.5f, START_ROAD);
		glVertex3f(-1100, -0.5f, END_ROAD);
		glVertex3f(1100, -0.5f, END_ROAD);
		glVertex3f(1100, -0.5f, START_ROAD);
	glEnd();
	
	/********** Roadway *************/
	glColor3f(0.3f, 0.3f, 0.4f);
	glBegin(GL_POLYGON);
		glVertex3f(-150, 0.0f, START_ROAD);
		glVertex3f(-150, 0.0f, END_ROAD);
		glVertex3f(150, 0.0f, END_ROAD);
		glVertex3f(150, 0.0f, START_ROAD);
	glEnd();
	
	/********** Banket **************/
	glColor3f(0.7f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
		glVertex3f(-250, 0.0f, START_ROAD);
		glVertex3f(-250, 0.0f, END_ROAD);
		glVertex3f(-150, 0.0f, END_ROAD);
		glVertex3f(-150, 0.0f, START_ROAD);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(150, 0.0f, START_ROAD);
		glVertex3f(150, 0.0f, END_ROAD);
		glVertex3f(250, 0.0f, END_ROAD);
		glVertex3f(250, 0.0f, START_ROAD);
	glEnd();
	
	/****** End and Start of Box ******/
	glColor3f(0.9f, 0.9f, 0.8f);
	glBegin(GL_POLYGON);
		glVertex3f(-1100, -0.5f, END_ROAD);
		glVertex3f(-1100, 500.0f, END_ROAD);
		glVertex3f(1100, 500.0f, END_ROAD);	
		glVertex3f(1100, -0.5f, END_ROAD);	
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-1100, -0.5f, START_ROAD);
		glVertex3f(-1100, 500.0f, START_ROAD);
		glVertex3f(1100, 500.0f, START_ROAD);	
		glVertex3f(1100, -0.5f, START_ROAD);
	glEnd();
	
	/********** Top of Box *********/
	glColor3f(0.4f, 0.7f, 0.7f);
	glBegin(GL_POLYGON);
		glVertex3f(-1100, 500.0f, END_ROAD);
		glVertex3f(-1100, 500.0f, START_ROAD);
		glVertex3f(1100, 500.0f, START_ROAD);
		glVertex3f(1100, 500.0f, END_ROAD);
	glEnd();
	
	/****** Left and Right of Box *****/
	glBegin(GL_POLYGON);
		glVertex3f(-1100, 500.0f, END_ROAD);
		glVertex3f(-1100, 500.0f, START_ROAD);
		glVertex3f(-1100, -0.5f, START_ROAD);
		glVertex3f(-1100, -0.5f, END_ROAD);	
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(1100, 500.0f, END_ROAD);
		glVertex3f(1100, 500.0f, START_ROAD);
		glVertex3f(1100, -0.5f, START_ROAD);
		glVertex3f(1100, -0.5f, END_ROAD);	
	glEnd();	
	/******** Road Lines ********/
	rs = 0;
	re = 125;
	glColor3f(1.4f, 1.4f, 1.4f);
	for(i=0; i<4000; i++, rs += 250, re+= 250)
	{
		if(re < END_ROAD)
		{
			glBegin(GL_POLYGON);
				glVertex3f(-52.0f, 0.5f, rs);
				glVertex3f(-52.0f, 0.5f, re);
				glVertex3f(-48.0f, 0.5f, re);
				glVertex3f(-48.0f, 0.5f, rs);			
			glEnd();
			glBegin(GL_POLYGON);
				glVertex3f(52.0f, 0.5f, rs);
				glVertex3f(52.0f, 0.5f, re);
				glVertex3f(48.0f, 0.5f, re);
				glVertex3f(48.0f, 0.5f, rs);			
			glEnd();
		}
	}
	/********* Finish Line **********/
	rs = -250;
	re = -230;
	for(i=0; i<25; i++, rs+=20, re+=20)
	{
		if(i%2)
			glColor3f(1.4f, 1.4f, 1.4f);
		else
			glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
			glVertex3f(rs, 0.9f, EN_RACE);
			glVertex3f(rs, 0.9f, EN_RACE + 20);
			glVertex3f(re, 0.9f, EN_RACE + 20);
			glVertex3f(re, 0.9f, EN_RACE);
		glEnd();
		
		if(i%2)
			glColor3f(0.0f, 0.0f, 0.0f);
		else
			glColor3f(1.4f, 1.4f, 1.4f);
		glBegin(GL_POLYGON);
			glVertex3f(rs, 0.9f, EN_RACE + 20);
			glVertex3f(rs, 0.9f, EN_RACE + 40);
			glVertex3f(re, 0.9f, EN_RACE + 40);
			glVertex3f(re, 0.9f, EN_RACE + 20);
		glEnd();
	}
	/****** Start Line *******/
	glColor3f(1.4f,1.4f, 1.4f);
	glBegin(GL_POLYGON);
		glVertex3f(-250, 0.9f, ST_RACE);
		glVertex3f(-250, 0.9f, ST_RACE + 20);
		glVertex3f(250, 0.9f, ST_RACE + 20);
		glVertex3f(250, 0.9f, ST_RACE);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-250, 0.9f, ST_RACE + 200);
		glVertex3f(-250, 0.9f, ST_RACE + 220);
		glVertex3f(250, 0.9f, ST_RACE + 220);
		glVertex3f(250, 0.9f, ST_RACE + 200);
	glEnd();
}
void drawObstacles(void)
{
	int start, end, i, j, coord_x, coord_z;
	start = Car_FW / 200 - 20;
	if(start < 0)
		start = 0;
	
	end = start + 40;
	if(end > 1000)
		end = 1000;
	
	for(i=start; i<end; i++)
	{
		for(j=0; j<5; j++)
		{
			coord_x = j * 100 - 200;
			coord_z = i * 200 + 500;
			switch(Obstacles[i][j])
			{
				case 'T':
					glColor3f(0.4f, 0.4f, 0.3f);
					glPushMatrix();
						glTranslatef(coord_x, 150.0f, coord_z);
						glScalef(0.8f, 5.2f, 0.8f);
						glRotatef(90.0f, 1, 0, 0); 
						glTranslatef(0.0f, 0.0f, 0.0f);
						drawCylinder();			
					glPopMatrix();
					glColor3f(0.0f, 0.6f, 0.0f);
					glPushMatrix();
						glTranslatef(coord_x, 220.0f, coord_z);
						glScalef(1.0f, 3.2f, 1.0f);
						glRotatef(90.0f, 1, 0, 0); 
						glTranslatef(0.0f, 0.0f, 0.0f);
						drawConical();			
					glPopMatrix();					
					break;
				case 'C':
					if(Car_No == 3)
					{
						Cars[2].Render();
						Cars[2].ResetRotation();
						Cars[2].SetPosition(coord_x, 0.0f, coord_z);
					}
					else
					{
						glPushMatrix();
							glTranslatef(coord_x, 0.0f, coord_z);
							glRotatef(270, 0, 1, 0);
							drawMyCar();
						glPopMatrix();
					}
					break;
				case 'W':
					glPushMatrix();
						glTranslatef(coord_x, 0.0f, coord_z);
						drawWall();
					glPopMatrix();
					break;
			}
		}
	}
}
void putCar(void)
{
	switch(Car_No)
	{
		case 0:
			Cars[0].Render();
			Cars[0].Rotate(0.0f, Car_Angle, 0.0f);
			Cars[0].SetPosition(Car_LR, 20.0f, Car_FW);
			break;
		case 1:
			Cars[1].Render();
			Cars[1].Rotate(0.0f, Car_Angle - 90, 0.0f);
			Cars[1].SetPosition(Car_LR, 0.0f, Car_FW);
			break;
		case 2:
			Cars[2].Render();
			Cars[2].SetPosition(Car_LR, -3.0f, Car_FW);
			Cars[2].Rotate(0.0f, Car_Angle, 0.0f);
			break;
		case 3:
			glPushMatrix();
				glTranslatef(Car_LR, 0.0f, Car_FW);
				glRotatef(Car_Angle + 90, 0, 1, 0);
				glTranslatef(0.0f, 0.0f, 0.0f);
				drawMyCar();
			glPopMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			break;
	}
}
void displayHandle(void)
{
	glClearColor(0.9f, 0.95f, 0.95f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	if(Mode)
	{
		glDisable(GL_TEXTURE_2D);
		switch(Cam_Mode)
		{
			case '1':
				gluLookAt(Camera_X, 70, Camera_Z, Car_LR, 0, Car_FW, 0, 1, 0);	
				break;
			case '2':
				gluLookAt(Camera_X, Camera_Y[Car_No], Camera_Z, Cam_Ref_X, 60, Cam_Ref_Z, 0, 1, 0);	
				break;
			case '3':
				gluLookAt(Camera_X, 70, Camera_Z, Car_LR, 0, Car_FW, 0, 1, 0);
				break;			
		}
		drawEnvironment();
		drawObstacles();
		glEnable(GL_TEXTURE_2D);
		moveCar();
		adjustCamera();
		putCar();
	}
	else
	{
		gluLookAt(0, 50, 0, 0, 0, Car_FW, 0, 1, 0);
		glColor3f(0.4f, 0.5f, 0.6f);
		glCircleField(0.0f, 0.0f, 200.0f, 140.0f);
		if(Car_No == 3)
		{
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, Car_FW);
				glRotatef(Ang + 90, 0, 1, 0);
				glTranslatef(0.0f, 0.0f, 0.0f);
				drawMyCar();
			glPopMatrix();
		}
		else
		{
			Cars[Car_No].Render();
			switch(Car_No)
			{
				case 0:
					Cars[Car_No].SetPosition(Car_LR, 20.0f, Car_FW);
					break;
				case 1:
					Cars[Car_No].SetPosition(Car_LR, 0.0f, Car_FW);
					break;
				case 2:
					Cars[Car_No].SetPosition(Car_LR, -3.0f, Car_FW);
					break;		
			}
		}
	}
	glutSwapBuffers();
}
void keyboardHandle(unsigned char key, int x, int y)
{
	if(Mode)
	{
		if(key == '1' || key == '2' || key == '3')
			Cam_Mode = key;
	}
	else
		switch(key)
		{
			case 13:
				Car_Angle = 0;
				Win_Sub = glutCreateSubWindow(Win, 600, 600, 200, 200);
				glutDisplayFunc(speedDisplay);
				glOrtho(0, 200, 0, 200, -10, 10);
				Cars[2].ResetRotation();
				Cars[2].Rotate(0.0f, 90, 0.0f);
				Cars[1].ResetRotation();
				Mode = 1;
				break;			
		}
}
void keyboardSpecial(int key, int x, int y)
{
	if(Mode)
	{
		switch(key)
		{
			case GLUT_KEY_LEFT:
				Last_Key_LR = 'L';
				break;
			case GLUT_KEY_RIGHT:
				Last_Key_LR = 'R';
				break;
			case GLUT_KEY_UP:
				Last_Key_FW = 'U';
				break;
			case GLUT_KEY_DOWN:
				Last_Key_FW = 'D';
				break;	
		}
	}
	else
		switch(key)
		{
			case GLUT_KEY_LEFT:
				selectCar(0);
				break;
			case GLUT_KEY_RIGHT:
				selectCar(1);
				break;
		}
}
void keyboardUp(int key, int x, int y)
{
	if(Mode)
		switch(key)
		{
			case GLUT_KEY_LEFT:
				Last_Key_LR = 0;
				break;
			case GLUT_KEY_RIGHT:
				Last_Key_LR = 0;
				break;
			case GLUT_KEY_UP:
				Last_Key_FW = 0;
				break;
			case GLUT_KEY_DOWN:
				Last_Key_FW = 0;
				break;
		}	
}
void init()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0);
	GLfloat position[] = {-1000.0, 1000.0 , 500.0, 0.0};
	GLfloat blackColor[] = {0.1 , 0.1 , 0.1 , 1.0};
	GLfloat whiteColor[] = {1.0 , 1.0 , 1.0 , 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, blackColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,1,10,1000000);
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 50, 0, 0, 0, 100, 0, 1, 0);	

}
void mainTimer(int x)
{
	if(Mode)
	{
		getCarOrder();
		glutSetWindow(Win);
		glutPostRedisplay();
		glutSetWindow(Win_Sub);
		glutPostRedisplay();	
	}
	else
	{
		rotateCar();
		glutPostRedisplay();
	}
	glutTimerFunc(25, mainTimer, 0);
}
int main(int argc, char **argv)
{
	fileRead();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(70, 40);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	Win = glutCreateWindow("Engin Ertas Araba Yarisi");
	glutDisplayFunc(displayHandle);
	glutKeyboardFunc(keyboardHandle);
	glutSpecialFunc(keyboardSpecial);
	glutSpecialUpFunc(keyboardUp);
	carInit();
	init();
	glutTimerFunc(0, mainTimer ,0);
	glutMainLoop();
	
	return 0;	
}
