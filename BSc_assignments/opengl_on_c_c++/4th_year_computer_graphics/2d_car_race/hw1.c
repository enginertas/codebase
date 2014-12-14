#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define WINDOW_SIZE 800
#define CENTER -400

const float RAD = 3.14159/180;
const float RAD_2 = 2 * 3.14159;
const float GAP_ANGLE = 3.6 * 3.14159/180;
const float ANGLE_DIFF_0 = 2 * 0.000475999;
const float ANGLE_DIFF_1 = 2 * 0.000334212;
const float ANGLE_DIFF_2 = 2 * 0.000257508;

FILE *fp;
char Obstacles[100][3], Car_Transmission = 'N';
int Car_Lane = 156, Car_Speed = 0;
float Car_Angle = 0.0f;

void drawSphere(void)
{
	GLUquadric *quadric = gluNewQuadric();
	gluSphere(quadric , 20 , 50 , 50);
}

void drawCylinder(void)
{
	GLUquadric *quadric = gluNewQuadric();
	gluCylinder(quadric, 10, 0, 40 , 50, 50);
}

void drawCarTire(void)
{
	GLUquadric *quadric = gluNewQuadric();
	gluCylinder(quadric, 10, 10, 40, 50, 50);
}

void drawObstacles()
{
	static int i,j,r_new;
	static float degree;
	glColor3f(1.4f, 0.4f, 0.0f);
	for(i=0, degree = 0; i<100; i++, degree += GAP_ANGLE)
		for(j=0, r_new=165; j<3; j++, r_new += 70)
			if(Obstacles[i][j])
			{
				glPushMatrix();
					glTranslatef(cos(degree)*r_new, sin(degree)*r_new, CENTER);
					glScalef(0.9f, 0.9f,1.5f);
					drawCylinder();
				glPopMatrix();
			}
}

void drawCar()
{
	static int i; 
	static float r, angle;

	r = Car_Lane + 14.0f;
	angle = Car_Angle/RAD;

	/*********** Car Tires - right **********/
	glColor3f(1.2f, 1.2f, 0.6f);
	glPushMatrix();
		glTranslatef(cos(Car_Angle + 0.08f) * r, sin(Car_Angle + 0.08f) * r, CENTER);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(1.0f, 1.0f, 0.2f);
		drawCarTire();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(cos(Car_Angle - 0.08f) * r, sin(Car_Angle - 0.08f) * r, CENTER);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(1.0f, 1.0f, 0.2f);
		drawCarTire();
	glPopMatrix();

	/************ Car Body **********/
	r = r - 14.0f;
	glColor3f(0.0f, 1.2f, 0.0f);
	glPushMatrix();
		glTranslatef(cos(Car_Angle) * r, sin(Car_Angle) * r, CENTER);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glScalef(0.5f, 1.8f, 0.4f);
		drawSphere();
	glPopMatrix();

	/************ Spoiler ******************/
	glColor3f(1.2f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(cos(Car_Angle) * r, sin(Car_Angle) * r, CENTER);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, -36.0f, 0.0f);
			glVertex3f(0.0f, -36.0f, 27.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();
	glPopMatrix();

	/*********** Car Tires - left **********/
	r = r - 12.0f;
	glColor3f(1.2f, 1.2f, 0.6f);
	glPushMatrix();
		glTranslatef(cos(Car_Angle + 0.08f) * r, sin(Car_Angle + 0.08f) * r, CENTER);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(1.0f, 1.0f, 0.2f);
		drawCarTire();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(cos(Car_Angle - 0.08f) * r, sin(Car_Angle - 0.08f) * r, CENTER);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(1.0f, 1.0f, 0.2f);
		drawCarTire();
	glPopMatrix();
	

}
void drawSpeedIndicator()
{
	int i;
	static float degree;
	char speed[15];

	degree = -abs(Car_Speed) * 0.75 + 217.5f;

	glColor3f(1.2f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, CENTER);
		glRotatef(degree, 0, 0, 1);			
		glRotatef(90.0, 0, 1, 0);
		glScalef(0.5f, 0.5f, 2.5f);
		drawCylinder();
	glPopMatrix();

	glColor3f(0.8f, 1.2f, 1.2f);
	glPushMatrix();
		glTranslatef(0.0f, -50.0f, CENTER);
		glBegin(GL_POLYGON);
			glVertex3f(-15.0f, 12.0f, 0.0f);
			glVertex3f(-15.0f, -12.0f, 0.0f);
			glVertex3f(15.0f, -12.0f, 0.0f);
			glVertex3f(15.0f, 12.0f, 0.0f);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -80.0f, CENTER);
		glBegin(GL_POLYGON);
			glVertex3f(-50.0f, 12.0f, 0.0f);
			glVertex3f(-50.0f, -12.0f, 0.0f);
			glVertex3f(50.0f, -12.0f, 0.0f);
			glVertex3f(50.0f, 12.0f, 0.0f);
		glEnd();
	glPopMatrix();

	sprintf(speed, "%c", Car_Transmission);
	glPushMatrix();
		glTranslatef(-10.0f, -118.0f, CENTER);
		glRasterPos3f(0.0f, 0.0f, CENTER);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, speed);		
	glPopMatrix();
	
	sprintf(speed, "%d kmh", abs(Car_Speed));
	glPushMatrix();
		glTranslatef(-90.0f, -178.0f, CENTER);
		glRasterPos3f(0.0f, 0.0f, CENTER);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, speed);		
	glPopMatrix();

	glColor3f(0.6f, 0.4f, 0.2f);
	degree = 217.5f;
	for(i=0; i<=17; degree -= 15, i++)
	{
		glPushMatrix();
			glTranslatef(cos(degree*RAD) * 100, sin(degree*RAD) * 100, CENTER);
			glRotatef(degree, 0, 0, 1);
			glBegin(GL_POLYGON);
				glVertex3f(0.0f, 1.0f, 0.0f);
				glVertex3f(0.0f, -1.0f, 0.0f);
				glVertex3f(25.0f, -1.0f, 0.0f);
				glVertex3f(25.0f, 1.0f, 0.0f);			
			glEnd();
		glPopMatrix();
	}

}

void displayHandle(void)
{
	static GLUquadricObj *disk_quad;
	static float degree = 0;
	static int i;

	disk_quad = gluNewQuadric();
	gluQuadricNormals (disk_quad, GLU_TRUE);
	gluQuadricTexture (disk_quad, GLU_TRUE);
	
	glClearColor(0.9f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
	
	glPushMatrix();

		/************* Race Pist *************/
		glColor3f(0.2f, 0.4f, 0.6f);
		glTranslatef(0.0f,0.0f,CENTER);
		gluDisk(disk_quad, 130.0, 340.0, 100, 1);

		/************ Start Fields ***********/		
		glColor3f(1.2f, 1.2f, 0.0f);
		gluPartialDisk(disk_quad, 130.0, 340.0, 100, 1, 84.0, 6.0);
		glColor3f(1.0f, 1.0f, 1.0f);
		gluPartialDisk(disk_quad, 130.0, 340.0, 100, 1, 90.0, 4.0);

		/************* Road Lines ************/
		glColor3f(1.4f, 1.4f, 1.4f);
		for(i=0, degree = 0; i<48; i+=2, degree += 15.0)
			gluPartialDisk(disk_quad, 198.5, 201.5, 100, 1, degree, 7.5);

		for(i=0, degree = 0; i<60; i+=2, degree += 12.0)
			gluPartialDisk(disk_quad, 268.5, 271.5, 100, 1, degree, 6.0);

		/******* Speed Indicator Field ******/
		glColor3f(0.4f, 1.2f, 0.4f);
		gluDisk(disk_quad, 0, 130.0, 100, 1);

	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
	drawObstacles();
	drawCar();
		
	glDisable(GL_DEPTH_TEST);
	drawSpeedIndicator();	

	glutSwapBuffers();
}

void keyboardHandle(unsigned char key, int x, int y)
{
	if(key == 'q' | key == 'Q')
		exit(0);
}

void keyboardSpecial(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			if(Car_Speed < 340)
			{
				switch(Car_Transmission)
				{
					case 'N':
						Car_Speed += 6;
						break;
					case '1':
						Car_Speed += 6;
						break;
					case '2':
						Car_Speed += 5;
						break;
					case '3':
						Car_Speed += 4;
						break;
					case '4':
						Car_Speed += 3;
						break;
					case '5':
						Car_Speed += 2;
						break;
					case '6':
						Car_Speed += 1;
						break;
					case 'R':
						Car_Speed += 8;
						if(Car_Speed>0)
							Car_Speed = 0;
				}
				if(Car_Speed < 0)
					Car_Transmission = 'R';
				else if(!Car_Speed)
					Car_Transmission = 'N';
				else if(Car_Speed<70)
					Car_Transmission = '1';
				else if(Car_Speed<130)
					Car_Transmission = '2';
				else if(Car_Speed<180)
					Car_Transmission = '3';
				else if(Car_Speed<230)
					Car_Transmission = '4';
				else if(Car_Speed<270)
					Car_Transmission = '5';
				else
					Car_Transmission = '6';
			}
			break;

		case GLUT_KEY_DOWN:
			if(Car_Speed > -70)
			{
				switch(Car_Transmission)
				{
					case 'N':
						Car_Speed -= 4;
						break;
					case 'R':
						Car_Speed -= 2;
						break;
					default:
						Car_Speed -= 8;
						if(Car_Speed<0)
							Car_Speed = 0;					
				}
				if(Car_Speed < 0)
					Car_Transmission = 'R';
				else if(!Car_Speed)
					Car_Transmission = 'N';
				else if(Car_Speed<70)
					Car_Transmission = '1';
				else if(Car_Speed<130)
					Car_Transmission = '2';
				else if(Car_Speed<180)
					Car_Transmission = '3';
				else if(Car_Speed<230)
					Car_Transmission = '4';
				else if(Car_Speed<270)
					Car_Transmission = '5';
				else
					Car_Transmission = '6';
			}
			break;

		case GLUT_KEY_LEFT:
			if(Car_Lane>156)
				if(Car_Speed)
				{
					if(Car_Speed < 50 && Car_Speed > -50)
						Car_Lane -=1;
					else
						Car_Lane -=2;
				}
			break;
		
		case GLUT_KEY_RIGHT:
			if(Car_Lane<314)
				if(Car_Speed)
				{
					if(Car_Speed < 50 && Car_Speed > -50)
						Car_Lane +=1;
					else
						Car_Lane +=2;
				}
			break;	
	}
}

void init(void)
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
	gluPerspective(90,1,1,1000000);
 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,1000,0,0,0,0,0,0,-1);
}

void fileRead(void)
{
	char ch, i, j;	
	fp = fopen("METU_F1_2010.txt", "r");
	if(!fp)
		return ;
	for(i=0; fscanf(fp,"%c",&ch )!=EOF && i<100; i++)
		for(j=0; j<3; j++)
		{
			if(ch=='X')
				Obstacles[i][j] = 1;
			else
				Obstacles[i][j] = 0;	
			fscanf(fp,"%c",&ch);
		}
	
	fclose(fp);
}

void moveCar()
{
	Car_Angle += Car_Speed * RAD * 9/Car_Lane;

	if(Car_Angle >= RAD_2)
		Car_Angle -= RAD_2;
	if(Car_Angle <0)
		Car_Angle += RAD_2;	
}

void carTimer(int x)
{
	moveCar();
	glutPostRedisplay();
	glutTimerFunc(25, carTimer, 0);
}
int main(int argc, char** argv)
{
	int i;
	for(i=0; i<100; i++)
		Obstacles[i][0] = Obstacles[i][1] = Obstacles[i][2] = 0;
	
	fileRead();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(70, 40);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("Engin Ertas Araba Uygulamasi");
	glutDisplayFunc(displayHandle);
	glutKeyboardFunc(keyboardHandle);
	glutSpecialFunc(keyboardSpecial);

	init();
	glutTimerFunc(0, carTimer ,0);
	glutMainLoop();

	return 0;
}
