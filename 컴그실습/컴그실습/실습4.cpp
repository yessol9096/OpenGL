#include <glut.h>
#include <iostream>
GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void TimerFunc(int value);

struct location {
	int x;
	int y;
};
struct location fig[10]{};

int num = 0;
int height = 10;
int width = 50;

void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름)
	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene); // 출력 함수의 지정

	glutTimerFunc(300, TimerFunc, 1);
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
		glBegin(GL_POLYGON);
		glVertex2i(fig[i].x - width, fig[i].y - height); //v1
		glVertex2i(fig[i].x - width, fig[i].y + height); //v2
		glVertex2i(fig[i].x + width, fig[i].y + height); //v3
		glVertex2i(fig[i].x + width, fig[i].y - height); //v4
		glEnd();
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
		fig[num].x = x;
		fig[num].y = y;
		std::cout << x << ", " << y << "num:" << num << std::endl;
		num++;
		if (num > 9) num = 0;
	}
}

void TimerFunc(int value)
{
	int next;
	if (value == 1) next = 2;
	else next = 1;

	if (value == 1) {
		for (int i = 0; i < num + 1; ++i)
		{
			width = 10;
			height = 50;
		}
	}
	else
	{
		for (int i = 0; i < num + 1; ++i)
			width = 50;
		height = 10;
	}

	glutPostRedisplay();
	glutTimerFunc(300, TimerFunc, next);
};