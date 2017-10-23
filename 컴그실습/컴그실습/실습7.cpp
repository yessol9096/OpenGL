#include <glut.h>
#include <iostream>
#include <stdlib.h>

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void TimerFunc(int value);

class Circle {
public:
	int x;
	int y;
	int r = 20;
	int move;
	int big;
	GLvoid draw(GLvoid) {
		if (move == 1) {
			for (int j = 0; j <= 360; ++j) {
				glBegin(GL_POINTS);
				glVertex2i(x + r*cos((j / 180.0)*3.14), y + r * sin((j / 180.0)*3.14)); //v2
				glEnd();
			}
		}
	}

	void Move() {
		if (move == 1)
		{
			r += 10;
			if (r > 400 && big == 1)
				move = 0;
			else if (r > 400)
				r = 20;
				
		}
	}

};
class Circle cir[10];
int num{};
void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름)
	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene); // 출력 함수의 지정

	glutTimerFunc(100, TimerFunc, 1);
	glutReshapeFunc(reshape); // 다시 그리기 함수의 지정 
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(1, 0, 0, 0);
	for (int i = 0; i < 10; ++i) {
		cir[i].draw();
	}

	glutPostRedisplay();
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
		cir[num].x = x;
		cir[num].y = y;
		cir[num].move = 1;
		cir[num].big = rand() % 2;
		std::cout << x << ", " << y << "num:" << num << std::endl;
		num++;
		num = num % 10;
	}
}

void TimerFunc(int value)
{
	for (int i = 0; i < 10; ++i)
	{
			cir[i].Move();
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
};