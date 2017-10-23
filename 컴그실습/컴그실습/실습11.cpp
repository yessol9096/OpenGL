#include <glut.h>
#include <iostream>
#include <cmath>

#define pi 3.1415927

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void TimerFunc(int value);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);


float angle = 0.0;
bool rotateX = false;
bool rotateY = false;
bool rotateZ = false;
bool rotate = false;

bool Animation = false;
float num = 0;

float scale = 1.0f;
float transX = 0.0f;
class Sin_graph {
public:
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat size = 20;
	void draw()
	{
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-150, 120, 0);
		if (rotateX == true) { glRotatef(angle, 1, 0, 0); }
		else if (rotateZ == true)glRotatef(angle, 0, 0, 1);
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i <= 400; ++i) {
			x = i ;
			y = size * sin((((float)x+ num) / 30)*pi) ;
			glVertex3f(x, y, 0.0);
		}
		glEnd();
		glPopMatrix();
	}

}s_graph;

class Cos_graph {
public:
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat size = 20;
	void draw()
	{
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-150, 20, 0);
		if (rotateX == true) { glRotatef(angle, 1, 0, 0); }
		else if (rotateZ == true)glRotatef(angle, 0, 0, 1);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 400; ++i) {
			x =  i;
			y =size * cos((((float)x + num)/ 30)*pi) ;
			glVertex3f(x, y, 0.0);
		}
		glEnd();
		glPopMatrix();
	}
}c_graph;

class Spring {
public:
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat r = 20;
	float red = 1.0;
	float blue = 0;
	void draw()
	{
		glPushMatrix();
		glTranslatef(10, -50, 0);
		if (rotateX == true) { glRotatef(angle, 1, 0, 0); }
		//else if (rotateY == true)glRotatef(angle, 0, 1, 0);
		else if (rotateZ == true)glRotatef(angle, 0, 0, 1);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 23 ; i++)
		{
			for (int j = 145; j <= 420; ++j)
			{
				glColor3f(red, 0.0, blue);
				glVertex2i(x + r*cos((j / 180.0)*pi), y + r * sin((j / 180.0)*pi)); //v2
			}
			x += 21;
			if (Animation == true)red -= 0.01; else red -= (0.1); 
			blue += (0.1);
		}
		if (x > 160) x = -200;
		if (red < 0.0) red = 1;
		if (blue > 1.0) blue = 0;
		glEnd();
		glPopMatrix();
	}
}spring;

class Rectangle {
public:
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat size = 20;
	GLfloat moveX = 0;
	void draw()
	{
		if (x + moveX> -250 && x + moveX < 250)
		{
			glPushMatrix();
			glTranslatef(10 + moveX, -150, 0);
			if (rotateX == true) { glRotatef(angle, 1, 0, 0); }
			else if (rotateZ == true)glRotatef(angle, 0, 0, 1);
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex3f(x - size, y + size, 0.0);
			glVertex3f(x + size, y + size, 0.0);
			glVertex3f(x + size, y - size, 0.0);
			glVertex3f(x - size, y - size, 0.0);
			glEnd();


			glPopMatrix();
		}
	}

	void move()
	{
		moveX -= 2;
	}
}rectangle[30];


void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(100, TimerFunc, 1);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutReshapeFunc(reshape); // 다시 그리기 함수의 지정 
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	// 좌표축
	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, -300.0, 0.0);
		glVertex3f(0.0, 300.0, 0.0);
		glVertex3f(-400.0, 0.0, 0.0);
		glVertex3f(400.0, 0.0, 0.0);
	glEnd();

	
	glScalef(scale, scale, 1.0);
	glTranslatef(transX, 0, 0);
	if (rotateY == true)glRotatef(angle, 0, 1, 0);
	
	s_graph.draw();
	c_graph.draw();
	spring.draw();

	for (int i = 0; i < 20; ++i)
	{
		rectangle[i].x = -200 + (60 * i);
		rectangle[i].draw();
	}

	glutSwapBuffers();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-400.0, 400.0, -300.0, 300.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
	if (key == 'x' || key == 'X') {
		rotateX = true;
		rotateY = false;
		rotateZ = false;
	}
	else if (key == 'y' || key == 'Y') {
		rotateX = false;
		rotateY = true;
		rotateZ = false;

	}
	else if (key == 'z' || key == 'Z') {
		rotateX = false;
		rotateY = false;
		rotateZ = true;
	}
	else if (key == 's') {
		scale -= 0.1;
	}
	else if (key == 'S') {
		scale += 0.1;
	}
	else if (key == 'a') {
		Animation = true;
	}
	else if (key == 'A') {
		Animation = false;
	}
	else if (key == 'i' || key == 'I') {
		transX = 0.0f;
	}
	else if (key == 'q' || key == 'Q') {
		exit(0);
	}
	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		transX -= 5;
	}
	else if (key == GLUT_KEY_RIGHT) {
		transX += 5;
	}
	glutPostRedisplay();
}

void TimerFunc(int value)
{
	angle += 10;
	if (Animation == true) 
	{
		for(int i = 0; i < 30; ++i)
		rectangle[i].move(); 
		num+=2;  };
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
};
