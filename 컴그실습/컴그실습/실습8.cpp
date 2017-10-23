#include <glut.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>

#define width 20
#define height 20

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void TimerFunc(int value);

int num = 0;
int m_num = 0;

class TargetRectangle {
public:
	int x{};
	int y{};

	GLvoid draw(GLvoid) {
		if (y != 0)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex2i(x - 10, y - 10); //v1
			glVertex2i(x - 10, y + 10); //v2
			glVertex2i(x + 10, y + 10); //v3
			glVertex2i(x + 10, y - 10); //v4
			glEnd();
			glutPostRedisplay();
		}
	}

	int getTagetX()
	{
		return x;
	}
	int getTargetY()
	{
		return y;
	}
};

class Rectangle {
public:
	int x{};
	int y{};
	int move{};

	GLvoid draw(GLvoid) {
		if (y != 0)
		{
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex2i(x - 20, y - 20); //v1
			glVertex2i(x - 20, y + 20); //v2
			glVertex2i(x + 20, y + 20); //v3
			glVertex2i(x + 20, y - 20); //v4
			glEnd();
			glutPostRedisplay();
		}
	}

	void Move(int t_x, int t_y)
	{
		if (x < t_x)
			x += 1;
		else if (x > t_x)
			x -= 1;
		if (y < t_y)
			y += 1;
		else if (y > t_y)
			y -= 1;
	}
};

class TargetRectangle target;
class Rectangle rects[10];

void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(reshape); // 다시 그리기 함수의 지정 
	glutTimerFunc(100, TimerFunc, 1);
	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	target.draw();
	for (int i = 0; i < num; ++i)
	{
		rects[i].draw();
	}

	glFlush();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		target.x = x;
		target.y = y;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{	
		rects[num].x = x;
		rects[num].y = y;
		++num;
	}

	glutPostRedisplay();
}

void Motion(int x, int y)
{
	target.x = x;
	target.y = y;
	glutPostRedisplay();
}

void TimerFunc(int value)
{
	for (int i = 0; i < num ; ++i)
		rects[i].Move(target.getTagetX(), target.getTargetY());
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
};