#include <glut.h>
#include <iostream>
#include <cmath>

#define pi 3.1415927

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void TimerFunc(int value);
void Keyboard(unsigned char key, int x, int y);

float scale = 1.0f;
float transX = 0.0f;
float transY = 0.0f;
int road = 0;

enum class Dir {
	Next
	, Up	// 오른쪽 대각선 위로
	, Down	// 오른쪽 대각선 아래로
};

class figure {
public:
	float x1 = 0, y1 = 50, z1 = 0;
	float x2 = -25, y2 = 0, z2=0;
	float x3=25, y3=0, z3=0;
	float r_x = 0;
	float r_y = 0;
	float size = 20;
	int fig;

	void draw() 
	{
		glPushMatrix();
		glColor3f(0.0, 1.0, 1.0);
		if (fig == 0)
		{
			glBegin(GL_TRIANGLES);
			glVertex3f(x1, y1, z1); // v1 
			glVertex3f(x2, y2, z2); // v2 
			glVertex3f(x3, y3, z3); // v3 
			glEnd();
		}
		else if (fig == 1)
		{
			glBegin(GL_POLYGON);
			glVertex2i(r_x - size, r_y - size); //v1
			glVertex2i(r_x - size, r_y + size); //v2
			glVertex2i(r_x + size, r_y + size); //v3
			glVertex2i(r_x + size, r_y - size); //v4
			glEnd();
		}
		glPopMatrix();
	}

}fig;

class Sin_graph {
public:
	GLfloat x = -300;
	GLfloat y = 0;
	GLfloat size = 60;
	void draw()
	{
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i <= 500; ++i) {
			x = -300 + i;
			y = size * sin(((float)x / 60)*pi);	
			glVertex3f(x, y, 0.0);
		}
		glEnd();
		glPopMatrix();
	}

}s_graph;

class Spring {
public:
	GLfloat x = -300;
	GLfloat y = 0;
	GLfloat r = 35;
	Dir dir = Dir::Down;
	
	void draw()
	{
		glPushMatrix();
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 15; i++)
		{
			for (int j = 145; j <= 420; ++j)
			{
				glColor3f(1.0, 1.0, 1.0);
				glVertex2i(x + r*cos((j / 180.0)*pi), y + r * sin((j / 180.0)*pi)); //v2
			}
			x += 40;
		}
		if (x > 160) x = -300;
		glEnd();
		glPopMatrix();
	}

	void move()
	{
		if (dir == Dir::Down)
		{
			for (int j = 145; j <= 420; ++j)
			{
				transX = (transX + r*cos((j / 180.0)*pi));
				transY = transY + r * sin((j / 180.0)*pi); //v2
			}
			dir = Dir::Next;
		}
		else if (dir == Dir::Next)
		{
			transX += 40; dir = Dir::Down;
		}
		if (transX > 160) transX = -300;
	}
}spring;

class Circle {
public:
	int x = 0;
	int y = 0;
	int r = 100;
	int move;
	int big;
	GLvoid draw(GLvoid) {
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
			for (int j = 0; j <= 360; ++j) {
				glBegin(GL_POINTS);
				glVertex2i(x + r*cos((j / 180.0)*pi), y + r * sin((j / 180.0)*pi)); //v2
				glEnd();
			}
		glPopMatrix();
		}

}circle;

void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(300, TimerFunc, 1);
	glutKeyboardFunc(Keyboard);
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
	
	if (road == 0) circle.draw();
	else if (road == 1) s_graph.draw();
	else if (road == 2) spring.draw();

	glScalef(scale, scale, 1.0);
	glTranslatef(transX, transY, 0);
	fig.draw();
	

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
	if (key == 't' || key == 'T') {
		fig.fig = 0;
	}
	else if (key == 'r' || key == 'R') {
		fig.fig = 1;
	}
	if (key == '0') {
		road = 0;
	}
	else if (key == '1') {
		road = 1;
	}
	else if (key == '2') {
		road = 2;
	}
	glutPostRedisplay();
}

int j = 0;
float k = 0;
int n = -300;
Dir dir = Dir::Down;

void TimerFunc(int value)
{
	// 커졌다 작아졌다
	if (scale == 1.0f)
	{
		scale += 0.2f;
		if (road == 0)
		{
			transX = 60 * cos((j / 180.0)*pi);
			transY = 60 * sin((j / 180.0)*pi);
		}
		else if (road == 1)
		{
			transX = -300 + j;
			transY = 60 * sin(((float)transX / 60)*pi);
		}
		else if (road == 2)
		{
			transX = -300;
		}
	}
	else
	{
		scale -= 0.2f;
		if (road == 0)
		{
			transX = 100 * cos((j / 180.0)*pi);
			transY = 100 * sin((j / 180.0)*pi);
		}
		else if (road == 1)
		{
			transX = -300 + j;
			transY = 60 * sin(((float)transX / 60)*pi);
		}
		else if (road == 2)
		{
			transX = -300;
		}
	}
	if (j > 500) j = 0;
		j+=10;
	if (road == 2) k += 0.1;
	glutPostRedisplay();
	glutTimerFunc(300, TimerFunc, 1);
};
