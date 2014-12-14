#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

typedef struct pixel
{
	float x;
	float y;
}pixel;

const float RAD = 3.14159/180;
int width, height, Scale_X, Scale_Y, File_Status, Free_Pixel = 0, Keyboard_Mode = 0, Drag_Index = -1;
float Ball_X = -1.0f, Ball_Y = -1.0f;
FILE *fp;
pixel Active[200];
 
void glCircle(float x, float y, float r)
{
	int i=0;
   	glBegin(GL_LINE_LOOP);
 
	for(; i < 360; i++)
	{
		float degree = i*RAD;
		glVertex2f(x + cos(degree)*r, y + sin(degree)*r);
	}
	glEnd();
}

void glCircleField(float x, float y, float r)
{
	int i=0;
   	glBegin(GL_POLYGON);
 
	for(; i < 360; i++)
	{
		float degree = i*RAD;
		glVertex2f(x + cos(degree)*r, y + sin(degree)*r);
	}
	glEnd();
}

void resetField()
{
	Ball_X = Ball_Y = -1.0f;
	Free_Pixel=0;

	glutPostRedisplay();
}

void fileRead()
{
	int c;
	float x, y;

	resetField();

	fp = fopen("field.txt", "r");
	if(fp)
		File_Status = 1;
	else
		File_Status = 0;

	if(File_Status)
	{
		fscanf(fp, "%f,%f", &Ball_X, &Ball_Y);
		
		while((c = fscanf(fp, "%f,%f", &x, &y))!=EOF)
		{
			Active[Free_Pixel].x = x;
			Active[Free_Pixel].y = y;
			Free_Pixel++;
		}	
		fclose(fp);	
	}
	glutPostRedisplay();
	
}

void fileWrite()
{
	int i=0;
	fp = fopen("field.txt", "w");

	fprintf(fp, "%d,%d\n", (int)Ball_X, (int)Ball_Y);
	for(i=0; i<Free_Pixel; i++)
		fprintf(fp, "%d,%d\n", (int)Active[i].x, (int)Active[i].y);

	fclose(fp);
}

void init()
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void menu(int op) 
{
	Free_Pixel = 11;
	switch(op)
	{
		case 'a':
			Active[0].x = 2.75 * Scale_X;
			Active[0].y = height/2;
			Active[1].x = 20.0 * Scale_X;
			Active[1].y = 24.2 * Scale_Y;
			Active[2].x = Active[1].x;
			Active[2].y = Active[0].y;
			Active[3].x = Active[1].x; 
			Active[3].y = height - Active[1].y;
			Active[4].x = 60.0 * Scale_X;
			Active[4].y = 13.0 * Scale_Y;			
			Active[5].x = Active[4].x;
			Active[5].y = 31.0 * Scale_Y;
			Active[6].x = Active[4].x;
			Active[6].y = Active[0].y;
			Active[7].x = Active[4].x;
			Active[7].y = height - Active[5].y;
			Active[8].x = Active[4].x;
			Active[8].y = height - Active[4].y;
			Active[9].x = 94.0 * Scale_X;
			Active[9].y = 30.0 * Scale_Y;
			Active[10].x = Active[9].x;
			Active[10].y = height - Active[9].y; 
			break;
		case 'b':
			Active[0].x = 2.75 * Scale_X;
			Active[0].y = height/2;
			Active[1].x = 20.0 * Scale_X;
			Active[1].y = 15.0 * Scale_Y;
			Active[2].x = Active[1].x;
			Active[2].y = 40.0 * Scale_Y;
			Active[3].x = Active[1].x; 
			Active[3].y = height - Active[2].y;
			Active[4].x = Active[1].x; 
			Active[4].y = height - Active[1].y;			
			Active[5].x = 60.0 * Scale_X;
			Active[5].y = 24.2 * Scale_Y;
			Active[6].x = Active[5].x;
			Active[6].y = Active[0].y;
			Active[7].x = Active[5].x;
			Active[7].y = height - Active[5].y;
			Active[8].x = 94.0 * Scale_X;
			Active[8].y = Active[5].y;
			Active[9].x = Active[8].x;
			Active[9].y = Active[6].y;
			Active[10].x = Active[8].x;
			Active[10].y = Active[7].y;
			break;
		case 'c':
			Active[0].x = 2.75 * Scale_X;
			Active[0].y = height/2;
			Active[1].x = 20.0 * Scale_X;
			Active[1].y = 15.0 * Scale_Y;
			Active[2].x = Active[1].x;
			Active[2].y = 40.0 * Scale_Y;
			Active[3].x = Active[1].x; 
			Active[3].y = height - Active[2].y;
			Active[4].x = Active[1].x; 
			Active[4].y = height - Active[1].y;			
			Active[5].x = 60.0 * Scale_X;
			Active[5].y = Active[1].y;
			Active[6].x = Active[5].x;
			Active[6].y = Active[2].y;
			Active[7].x = Active[5].x;
			Active[7].y = Active[3].y;
			Active[8].x = Active[5].x;
			Active[8].y = Active[4].y;
			Active[9].x = 94.0 * Scale_X;;
			Active[9].y = 30.0 * Scale_Y;
			Active[10].x = Active[9].x;
			Active[10].y = height - Active[9].y;			
			break;
	}
	glutPostRedisplay();
}

void mouseHandle(int button, int state, int x, int y)
{
	int i, j;
	y = height - y;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(!Keyboard_Mode)
		{
			for(i=0; i<Free_Pixel; i++)
				if(pow(x - Active[i].x,2) + pow(y - Active[i].y,2) < 144) 
					break;	

			if(i==Free_Pixel)
				Drag_Index = -1;
			else
			{
				Drag_Index = i;
				printf("Drag player started\n");
			} 			
		}
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		switch(Keyboard_Mode)
		{
			case 'b':
				Ball_X = x;
				Ball_Y = y;
				printf("Ball location: [%d %d]\n", x, y);				
				break;

			case 'p':
				Active[Free_Pixel].x = x;
				Active[Free_Pixel].y = y;
				Free_Pixel++;
				printf("Player placed: [%d %d]\n", x, y);
				break;

			case 'd':
				for(i=0; i<Free_Pixel; i++)
					if(pow(x - Active[i].x,2) + pow(y - Active[i].y,2) < 144) 
						break;
				
				if(i!=Free_Pixel)
				{
					for(j = i + 1; j < Free_Pixel; i++, j++)
					{
						Active[i].x = Active[j].x;
						Active[i].y = Active[j].y;
					}
					Free_Pixel--;
					printf("Player deleted\n");
				}
				break;
			case 0:
				if(Drag_Index >= 0)
				{
					Active[Drag_Index].x = x;
					Active[Drag_Index].y = y;
					Drag_Index = -1;
					printf("Drag player ended\n");
				}
				break;
		}
		Keyboard_Mode = 0;
		glutPostRedisplay();
	}
}

void mouseMove(int x, int y)
{
	y = height - y;

	if(Drag_Index != -1)
	{
		Active[Drag_Index].x = x;
		Active[Drag_Index].y = y;
		glutPostRedisplay();
	}

}
void displayHandle(void)
{
	float x, y;
	int i;

	glClearColor(0.9f, 0.9f, 0.9f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f,0.5f,0.0f);
	glBegin(GL_POLYGON);
		/******Grass*******/
		glVertex2f(0.0f, 0.0f);
		glVertex2f(width, 0.0f);
		glVertex2f(width, height);
		glVertex2f(0.0f, height);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
		/******Sidelines*****/
		glVertex2f(0.0f, 0.0f);
		glVertex2f(width, 0.0f);
		glVertex2f(width, height);
		glVertex2f(0.0f, height);
	glEnd();

	glBegin(GL_LINES);
		/******Midline******/
		glVertex2f(width/2, 0.0f);
		glVertex2f(width/2, height);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		/******Penalty Area (Left) *****/
		x = Scale_X * 16.5; 
		y = Scale_Y * 24.85;

		glVertex2f(0.0f, y);
		glVertex2f(0.0f, height -y);
		glVertex2f(x, height -y);
		glVertex2f(x ,y);	
	glEnd();

	glBegin(GL_LINE_LOOP);
		/******Penalty Area (Right) *****/
		x = width - x;

		glVertex2f(width, y);
		glVertex2f(width, height -y);
		glVertex2f(x, height -y);
		glVertex2f(x ,y);	
	glEnd();

	glBegin(GL_LINE_LOOP);
		/******Goal Area (Left) *****/
		x = Scale_X * 5.5; 
		y = Scale_Y * 35.85;

		glVertex2f(0.0f, y);
		glVertex2f(0.0f, height -y);
		glVertex2f(x, height -y);
		glVertex2f(x ,y);	
	glEnd();

	glBegin(GL_LINE_LOOP);
		/******Goal Area (Right) *****/
		x = width - x; 

		glVertex2f(width, y);
		glVertex2f(width, height -y);
		glVertex2f(x, height -y);
		glVertex2f(x ,y);	
	glEnd();

	glBegin(GL_LINE_LOOP);
		/******Goal (Left) *****/
		x = Scale_X * 2.44; 
		y = Scale_Y * 41.35;

		glVertex2f(0.0f, y);
		glVertex2f(0.0f, height -y);
		glVertex2f(x, height -y);
		glVertex2f(x ,y);	
	glEnd();

	glBegin(GL_LINE_LOOP);
		/******Goal (Right) *****/
		x = width - x; 

		glVertex2f(width, y);
		glVertex2f(width, height -y);
		glVertex2f(x, height -y);
		glVertex2f(x ,y);	
	glEnd();

	/**********Points in Field*********/
	x = 11*Scale_X;
	y = height/2;
	glCircleField(x , y, 4.0f);
	glCircleField(width / 2,  y, 4.0f);
	glCircleField(width - x,  y, 4.0f);
	
	if(Scale_X < Scale_Y)
		x = Scale_X;
	else
		x = Scale_Y;
	
	/******Corner circles******/
	glCircle(0.0f, 0.0f, x);
	glCircle(0.0f, height, x);
	glCircle(width, height, x);
	glCircle(width, 0.0f, x);

	/*******Mid - circle ******/
	glCircle(width/2, height/2, 9.15 * Scale_Y);


	/*******Player Drawing (if exists) ********/
	glColor3f(0.0f, 0.0f, 0.0f);
	for(i=0; i<Free_Pixel; i++)
		glCircleField(Active[i].x, Active[i].y, 12.0f);	

	/*******Ball Drawing (if exists) ********/
	if(Ball_X>=0)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		glCircleField(Ball_X, Ball_Y, 5.0f);
	}

	glutSwapBuffers();
}

void keyboardSpecial(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_F1:
			resetField();
			printf("Field cleared!\n");
			break;

		case GLUT_KEY_F2:
			fileWrite();
			printf("Field saved!\n");
			break;

		case GLUT_KEY_F3:
			fileRead();
			printf("Field loaded!\n");
			break;
	}
}
void keyboardNormal(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'B' | 'b' :
			printf("Placing ball\n");
			Keyboard_Mode = 'b';
			break;
		case 'P' | 'p' :
			printf("Placing player\n");
			Keyboard_Mode = 'p';
			break;
		case 'D' | 'd' :
			printf("Deleting player\n");
			Keyboard_Mode = 'd';
			break;
	}
}

int main(int argc, char** argv)
{	
	width = atoi(argv[1]);
	height = atoi(argv[2]);

	Scale_X = width / 120;
	Scale_Y = height / 90;	

	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 50);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Ceng477 Fall 2010 - Warmup Prototype [e1560176]");
	glutDisplayFunc(displayHandle);
	glutKeyboardFunc(keyboardNormal);
	glutMouseFunc(mouseHandle);
	glutSpecialFunc(keyboardSpecial);
	glutMotionFunc(mouseMove);

	glutCreateMenu(menu);
	glutAddMenuEntry("3-5-2", 'a');
	glutAddMenuEntry("4-3-3", 'b');
	glutAddMenuEntry("4-4-2", 'c');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	fileRead();
	glutMainLoop();

	return 0;
}
