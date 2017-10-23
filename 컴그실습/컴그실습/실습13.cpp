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
	Right
	,Up	// 오른쪽 대각선 위로
	,Down	// 오른쪽 대각선 아래로
};
class BigTriangle {
	float x1 = 0, y1 = 0, z1 = 0;
	float x2 = 0, y2 = 0, z2 = 0;
	float x3 = 0, y3 = 0, z3 = 0;
public:
	void set(float x_1, float y_1, float z_1, float x_2, float y_2, float z_2, float x_3, float y_3, float z_3)
	{
		x1 = x_1; x2 = x_2; x3 = x_3; y1 = y_1, y2 = y_2, y3 = y_3, z1 = z_1, z2 = z_2, z3 = z_3;
	}
	void draw() {
		glPushMatrix();
		glColor3f(0.0, 1.0, 1.0);
		{
			glBegin(GL_LINE_STRIP);
			glVertex3f(x1, y1, z1); // v1 
			glVertex3f(x2, y2, z2); // v2 
			glVertex3f(x3, y3, z3); // v3 
			glVertex3f(x1, y1, z1); // v1 
			glEnd();
		}
		glPopMatrix();
	}
};

class SmallTriangle {
public:
	float x1 = 0, y1 = 40, z1 = 0;
	float x2 = -20, y2 = 0, z2 = 0;
	float x3 = 20, y3 = 0, z3 = 0;
	float transX = 0, transY = 0, transZ = 0;
	Dir dir = Dir::Down;
public:
	void draw() 
	{
		glPushMatrix();
		glTranslatef(transX, transY, transZ);
		glColor3f(0.0, 1.0, 1.0);
		{
			glBegin(GL_LINE_STRIP);
			glVertex3f(x1, y1, z1); // v1 
			glVertex3f(x2, y2, z2); // v2 
			glVertex3f(x3, y3, z3); // v3 
			glVertex3f(x1, y1, z1); // v1 
			glEnd();
		}
		glPopMatrix();
	}
	void move1()
	{
		if (dir == Dir::Down)
		{
			transX -= 10;
			transY = 2*transX + 100;
			if (transX < -100 && transY < 0) dir = Dir::Right;
		}
		else if (dir == Dir::Right)
		{
			transX += 10;
			if (transX > 100) dir = Dir::Up;
		}
		else if (dir == Dir::Up)
		{
			transX -= 10;
			transY = -2 * transX + 100;
			if (transY > 100 && transX < 0) dir = Dir::Down;
		}
	}

	void move2()
	{
		if (dir == Dir::Down)
		{
			transZ -= 10;
			transY = 2 * transZ + 100;
			if (transZ < -100 && transY < 0) dir = Dir::Right;
		}
		else if (dir == Dir::Right)
		{
			transZ += 10;
			if (transZ > 100) dir = Dir::Up;
		}
		else if (dir == Dir::Up)
		{
			transZ -= 10;
			transY = -2 * transZ + 100;
			if (transY > 100 && transZ < 0) dir = Dir::Down;
		}
	}
}small1, small2;


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
	small1.transX = 0, small1.transY = 100, small1.transZ = 0;
	small2.transX = 0, small2.transY = 100, small2.transZ = 0;
}
// 윈도우 출력 함수
bool rotateY = false;
int angle = 0;
GLvoid drawScene(GLvoid)
{
	BigTriangle xyTri;
	BigTriangle yzTri;
	xyTri.set(0, 100, 0, -100, -100, 0, 100, -100, 0);
	yzTri.set(0, 100, 0, 0, -100, -100, 0, -100, 100);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	// 좌표축
	if (rotateY == true)glRotatef(angle, 0, 1, 0);
	xyTri.draw();
	yzTri.draw();
	small1.draw();
	small2.draw();


	glutSwapBuffers();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-400.0, 400.0, -300.0, 300.0, -300.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
	if (key == 'y' || key == 'Y') {
		if(rotateY == false)	rotateY = true;
		else rotateY = false;
	}
	glutPostRedisplay();
}

void TimerFunc(int value)
{
	angle += 10;
	small1.move1();
	small2.move2();
	
	glutPostRedisplay();
	glutTimerFunc(300, TimerFunc, 1);
};
