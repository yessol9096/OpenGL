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
	, Right_Up	// 오른쪽 대각선 위로
	, Right_Down	// 오른쪽 대각선 아래로
	, Left_Down	// 왼쪽 대각선 아래로
	, Left_UP		// 왼쪽 대각선 위로
	, Stop
};

class Boundary {
public:

	GLvoid draw(GLvoid) {
		{
			glColor4f(0.1f, 0.0f, 0.1f, 1.0f);
			glBegin(GL_POLYGON);
			glVertex2i(100, 100); //v1
			glVertex2i(100, 500); //v2
			glVertex2i(700, 500); //v3
			glVertex2i(700, 100); //v4
			glEnd();
			glutPostRedisplay();
		}
	}
};

class Circle {
public:
	int x;
	int y;
	int r = 40;
	int move;
	int speed;
	Dir dir;
	GLvoid draw(GLvoid) {
		if (move == 1) {
			for (int j = 0; j <= 360; ++j) {
				glBegin(GL_POINTS);
				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
				glVertex2i(x + r*cos((j / 180.0)*3.14), y + r * sin((j / 180.0)*3.14)); //v2
				glEnd();
			}
		}
	}

	void Move() {
		if (move == 1)
		{
			if (r > 5)
				r -= 2;
			if (dir == Dir::Down) { y += speed; }
			else if (dir == Dir::Left) { x -= speed; }
			else if (dir == Dir::Left_Down) { y += speed; x -= speed; }
			else if (dir == Dir::UP) { y -= speed; }
			else if (dir == Dir::Left_UP) { x -= speed; y -= speed; }
			else if (dir == Dir::Right) { x += speed; }
			else if (dir == Dir::Right_Down) { x += speed; y += speed; }
			else if (dir == Dir::Right_Up) { x += speed; y -= speed; }
			else if (dir == Dir::Stop) { move = 0; }
			if (x < 110 || x > 710 || y < 110 || y > 510 )dir = Dir::Stop;
		}
	}

};
class Circle cir[20];
class Boundary boundary;


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
	glutMouseFunc(Mouse);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	boundary.draw();
	for (int i = 0; i < 20; ++i)
	{
		cir[i].draw();
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

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x > 110 && x < 710 && y > 110 && y < 510)
	{
			cir[num].x = x;
			cir[num].y = y;
			cir[num].move = 1;
			cir[num].dir = Dir(rand() % 8);
			cir[num].speed = (rand() % 30) + 5;
			++num;
			num = num % 21;
	}

	glutPostRedisplay();
}

void TimerFunc(int value)
{
	for (int i = 0; i < 20; ++i)
	{
		cir[i].Move();
		if (cir[i].move == 0) cir[i].r = 30;
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
};