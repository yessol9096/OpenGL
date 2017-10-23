#include <glut.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>

#define width 20
#define height 20

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunc(int value);

int num = 0;
int m_num = 0;
enum class Dir {
	Right	
	, Left	
	, Down	
	, UP
	, Stop
};
class Rectangle {
public:
	int x{};
	int y{};
	int move{};
	int fix_x;
	int fix_y;
	Dir dir = Dir::Stop;

	GLvoid draw(GLvoid) {
		if (y != 0) 
		{
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex2i(x - width, y - height); //v1
			glVertex2i(x - width, y + height); //v2
			glVertex2i(x + width, y + height); //v3
			glVertex2i(x + width, y - height); //v4
			glEnd();
			glutPostRedisplay();
		}
	}

	void Move() {
		if (move == 1) 
		{
			if (dir == Dir::Right)
			{
				x += 5;
				if (x > 790)
				{
					dir = Dir::Down;
				}
			}
			else if (dir == Dir::Down)
			{
				y += 5;
				if (y > 590) dir = Dir::Left;
			}
			else if (dir == Dir::Left)
			{
				x -= 5;
				if (x < fix_x) dir = Dir::UP;
			}
			else if (dir == Dir::UP)
			{
				y -= 5;
				if (y < fix_y) dir = Dir::Stop;
			}
			else if (dir == Dir::Stop)
				move = 0;
		}
	}
};

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
	glutTimerFunc(2000, TimerFunc, 1);
	glutTimerFunc(10, TimerFunc, 2);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

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
		if (rects[m_num].move == 1)
		{
			rects[m_num].move = 0;
		}
		else if (rects[m_num].move == 0)
		{
			rects[m_num].move = 1;
		}
		std::cout << x << ", " << y << "num:" << num << std::endl;
	}

	glutPostRedisplay();
}

void TimerFunc(int value)
{
	if (value == 1 && num < 10)
	{
		rects[num].x = rand() % 750;
		rects[num].y = rand() % 550;
		rects[num].fix_x = rects[num].x;
		rects[num].fix_y = rects[num].y;
		++num;
		glutPostRedisplay();
		glutTimerFunc(2000, TimerFunc, 1);
	}
	if (value == 2)
	{
		if (rects[m_num].dir == Dir::Stop && rects[m_num].move == 0)
		{
			rects[m_num].dir = Dir::Right;
			rects[m_num].move = 1;
		}
		else if (rects[m_num].dir == Dir::Stop && rects[m_num].move == 1)
		{
			rects[m_num].move = 0;
			++m_num;
		}
		rects[m_num].Move();
		glutPostRedisplay();
		glutTimerFunc(10, TimerFunc, 2);
	}
};