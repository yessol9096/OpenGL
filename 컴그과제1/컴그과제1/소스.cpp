#include <glut.h>
#include <iostream>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;


GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void TimerFunc(int value);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);

float angle = 0.0;
bool rotateX = false;
bool rotateY = false;
bool rotateZ = false;
bool rotate = false;
bool newrectangle = false;
bool Cut = false;
bool Disappear = false;
bool Animation = false;
bool MouseUp = false;
bool collision_move = false;
float collision_x;
float num = 0;

float scale = 1.0f;
float transX = 0.0f;

const int INSIDE = 0; 
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

enum class Dir {
	 Right	// 오른쪽으로
	, Left	// 왼쪽으로
	, Down	// 떨어지기
	, Stop
	, Cover_stop
	, c_Right	// 오른쪽으로
	, c_Left	// 왼쪽으로
};

enum class Wave {
	Up,
	Down
};

struct M_xy {
	float x;
	float y;
}m_xy[2];

float Calculation(float y)
{
	float x = ((y - m_xy[0].y) * ((m_xy[1].x - m_xy[0].x ) / (m_xy[1].y - m_xy[0].y) ) + m_xy[0].x) ;
	return x ;
}

float Calculation2(float x0, float y0, float x1, float y1, float y)
{
	float x = ((y - y0) * ((x1 - x0) / (y1 - y0)) + x0);
	return x;
}
bool compare(float upX , float downX, int rx1, int ry1, int rx2, int ry2, int rx3, int ry3, int rx4, int ry4)
{
	float left = (upX - rx2) + (downX - rx1);
	float right = (rx3 - upX) + (rx4 - downX);

	if (left > right)
		return true;
	else
		return false;
}


int Collision(float left1, float right1, float top1, float bottom1, float left2, float right2, float top2, float bottom2)
{
	if (left1 < right2 && top1 < bottom2 && right1 > left2 && bottom1 > top2 )
	{
		if (left1 < left2) return 2;
		else if (right1 > right2) return 3;
		else
		return 1;
	}
	else return 4;
}




class Rectangle {
public:
	GLfloat rx1 = 0;
	GLfloat rx2 = 0;
	GLfloat rx3 = 0;
	GLfloat rx4 = 0;
	GLfloat ry1 = 0;
	GLfloat ry2 = 0;
	GLfloat ry3 = 0;
	GLfloat ry4 = 0;
	GLfloat moveX = 0;
	GLfloat moveY = 0;

	Dir dir = Dir::Right;
	bool Disappear = false;
	void set(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) 
	{ 
		rx1 = x1; rx2 = x2; rx3 = x3; rx4 = x4; 
		ry1 = y1; ry2 = y2; ry3 = y3; ry4 = y4;
	}
	void setX(float x)
	{
		rx1 = rx1 + x; rx2 = rx2 + x; rx3 = rx3 + x; rx4 = rx4 + x;
	}
	void drawline()
	{
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(rx1 - 3.0f + moveX, ry1 - 3.0f + moveY, 0.0);
		glVertex3f(rx2 - 3.0f + moveX, ry2 + 3.0f + moveY, 0.0);
		glVertex3f(rx3 + 3.0f + moveX, ry3 + 3.0f + moveY, 0.0);
		glVertex3f(rx4 + 3.0f + moveX, ry4 - 3.0f + moveY, 0.0);
		glEnd();
	}
	void draw()
	{
				glBegin(GL_POLYGON);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f(rx1 + moveX, ry1 + moveY, 0.0);
				glVertex3f(rx2 + moveX, ry2 + moveY, 0.0);
				glVertex3f(rx3 + moveX, ry3 + moveY, 0.0);
				glVertex3f(rx4 + moveX, ry4 + moveY, 0.0);
				glEnd();
	}
	

	void move()
	{
		if (dir == Dir::Down) { moveY += 18; if (moveY > 300 && Disappear == false) dir = Dir::Stop; }
		else if (dir == Dir::Right) { moveX += 15;  if (moveX > 800 - 140 && Disappear == false) dir = Dir::Left; }
		else if (dir == Dir::Left) { moveX -= 15;  if (moveX < 140 && Disappear == false) dir = Dir::Right; }
		else if (dir == Dir::Stop) { moveY = 300;}
		else if (dir == Dir::Cover_stop) { moveY = 230; }
	}

	void collision_move(Dir dir, float basketX)
	{
		if (dir == Dir::Right ) { if (basketX == 50) moveX -= 25; else moveX += (25); }
		else if (dir == Dir::Left) { if (basketX == 550) moveX += 25; else moveX -= (25); }
	}

}rectangle, small;

int clliping_check(float boundaryL, float boundaryR, float boundaryT, float boundaryB, float px, float py)
{
	int position = 0;
	if (px < boundaryL)								position += LEFT;
	else if (px > boundaryR)						position += RIGHT;
	else if (boundaryL < px && px < boundaryR)		position += INSIDE;

	if (py > boundaryB)								position += BOTTOM;
	else if (py < boundaryT)						position += TOP;
	else if (boundaryT < py && py < boundaryB)		position += INSIDE;

	return position;
};

void clliping(float boundaryL, float boundaryR, float boundaryT, float boundaryB, float Sx1, float Sy1, float Ex1, float Ey1, float Sx2, float Sy2, float Ex2, float Ey2)
{
	int startBit1 = clliping_check(boundaryL, boundaryR, boundaryT, boundaryB, Sx1, Sy1);
	int EndBit1 = clliping_check(boundaryL, boundaryR, boundaryT, boundaryB, Ex1, Ey1);

	int startBit2 = clliping_check(boundaryL, boundaryR, boundaryT, boundaryB, Sx2, Sy2);
	int EndBit2 = clliping_check(boundaryL, boundaryR, boundaryT, boundaryB, Ex2, Ey2);

	if ((startBit1 + EndBit1) == 0 && (startBit2 + EndBit2) == 0)
	{
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(small.rx1 - 3.0f + small.moveX, small.ry1 - 3.0f + small.moveY, 0.0);
		glVertex3f(small.rx2 - 3.0f + small.moveX, small.ry2 + 3.0f + small.moveY, 0.0);
		glVertex3f(small.rx3 + 3.0f + small.moveX, small.ry3 + 3.0f + small.moveY, 0.0);
		glVertex3f(small.rx4 + 3.0f + small.moveX, small.ry4 - 3.0f + small.moveY, 0.0);
		glEnd();
		cout << "1" << endl;
	}
	else if ((startBit1 == 0 && EndBit1 != 0) || (EndBit1 == 0 && startBit1 != 0))
	{
		// 한쪽은 경계안에 한쪽은 바깥쪽 
		// 계산 해서 그리기 
		float new_x1 = Calculation2(Sx1 , Sy1, Ex1 , Ey1, boundaryT);
		float new_x2 = Calculation2(Sx2 , Sy2, Ex2, Ey2, boundaryT);

		glBegin(GL_POLYGON);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(new_x1 - 3 , boundaryT - 3  , 0.0);
		glVertex3f(small.rx2 - 3 + small.moveX, small.ry2 +3  + small.moveY, 0.0);
		glVertex3f(small.rx3 +3  + small.moveX, small.ry3 +3 + small.moveY, 0.0);
		glVertex3f(new_x2+3, boundaryT-3  , 0.0);
		glEnd();
	}

	else if (startBit1 != 0 && EndBit1 != 0 )
	{
		if ((startBit1 & EndBit1) != 0)
		{
			// 안그림
		}
		else if ((startBit1 & EndBit1) == 0)
		{
			// 계산해서 그리기
			float new_x1 = Calculation2(Sx1, Sy1, Ex1, Ey1, boundaryT);
			float new_x2 = Calculation2(Sx2, Sy2, Ex2, Ey2, boundaryT);

			glBegin(GL_POLYGON);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(new_x1 - 3.0f + small.moveX, boundaryT - 3.0f + small.moveY, 0.0);
			glVertex3f(small.rx2 - 3.0f + small.moveX, small.ry2 + 3.0f + small.moveY, 0.0);
			glVertex3f(small.rx3 + 3.0f + small.moveX, small.ry3 + 3.0f + small.moveY, 0.0);
			glVertex3f(new_x2 + 3.0f + small.moveX, boundaryT - 3.0f + small.moveY, 0.0);
			glEnd();

		}
	}

}
class Basket {
public:
	GLfloat bx1 = 0;
	GLfloat bx2 = 0;
	GLfloat bx3 = 200;
	GLfloat bx4 = 200;
	GLfloat by1 = 400;
	GLfloat by2 = 500;
	GLfloat by3 = 500;
	GLfloat by4 = 400;

	GLfloat wx1 = 5;
	GLfloat wx2 = 5;
	GLfloat wx3 = 195;
	GLfloat wx4 = 195;
	GLfloat wy1 = 395;
	GLfloat wy2 = 495;
	GLfloat wy3 = 495;
	GLfloat wy4 = 395;
	GLfloat moveX = 0;
	GLfloat moveY = 0;

	Wave w = Wave::Up;
	Dir dir = Dir::Right;

	
	void draw()
	{
		glBegin(GL_LINE_STRIP);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(bx1 + moveX, by1 ,0.0);
		glVertex3f(bx2 + moveX, by2 , 0.0);
		glVertex3f(bx3 + moveX, by3 , 0.0);
		glVertex3f(bx4 + moveX, by4, 0.0);
		glEnd();
		
	}

	void drawWave()
	{
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(wx1 + moveX, wy1 + moveY, 0.0);
		glVertex3f(wx2 + moveX, wy2, 0.0);
		glVertex3f(wx3 + moveX, wy3, 0.0);
		glVertex3f(wx4 + moveX, wy4 + moveY, 0.0);
		glEnd();
	}

	void move()
	{
		if (dir == Dir::Right) { moveX += 25;  if (moveX == 550 ) dir = Dir::Left; }
		else if (dir == Dir::Left) { moveX -= 25;  if (moveX == 50 ) dir = Dir::Right; }

		if (w == Wave::Up) { moveY = 50; w = Wave::Down; }
		else if (w == Wave::Down) { moveY = 30; w = Wave::Up; }
	}
}basket;

void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(100, TimerFunc, 1);
	glutTimerFunc(600, TimerFunc, 2);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(reshape); // 다시 그리기 함수의 지정 
	glutMainLoop();
}
// 윈도우 출력 함수

GLvoid drawScene(GLvoid)
{
	srand(time(NULL));
	int randNumX = (rand() % 20 + 1);
	int randNumY = (rand() % 20 + 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLoadIdentity();
	int c_menu;
	if (newrectangle == true) { 
		rectangle.set(-(80 + randNumX), 110 - randNumY, -(80 + randNumX), 170 + randNumY, 80 + randNumX, 170 + randNumY, 80 + randNumX, 110 - randNumY);
		small.set(0,0,0,0,0,0,0,0);
		collision_move = false;
		rectangle.Disappear = false;
		small.dir = rectangle.dir;
		m_xy[0].x = 0; m_xy[0].y = 0;
		m_xy[1].x = 0; m_xy[1].y = 0;
		rectangle.moveX = 0;
		rectangle.moveY = 0;
		small.moveX = 120;
		small.moveY = 0;
		newrectangle = false; }
	else if (Cut == true)
	{
		rectangle.Disappear = true;
		float upX = (Calculation(rectangle.ry1));
		float downX = (Calculation(rectangle.ry2));
		small.dir = Dir::Down; 
		if (compare(upX, downX, rectangle.rx1, rectangle.ry1, rectangle.rx2, rectangle.ry2, rectangle.rx3, rectangle.ry3, rectangle.rx4, rectangle.ry4) == true)
		{
			small.set(upX +5, rectangle.ry1, downX +5, rectangle.ry2, rectangle.rx3 , rectangle.ry3, rectangle.rx4 , rectangle.ry4);
			rectangle.set(rectangle.rx1, rectangle.ry1, rectangle.rx2, rectangle.ry2, downX, rectangle.ry3, upX, rectangle.ry4);
		}
		else
		{
			small.set(rectangle.rx1, rectangle.ry1, rectangle.rx2, rectangle.ry2, downX, rectangle.ry3, upX, rectangle.ry4);
			rectangle.set(upX, rectangle.ry1, downX, rectangle.ry2, rectangle.rx3, rectangle.ry3, rectangle.rx4, rectangle.ry4);
		}
		Cut = false;
	}
	basket.draw();
	basket.drawWave();
	rectangle.drawline();
	rectangle.draw(); 
	//// 대각선 그리기
	if (newrectangle != true)
	{
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(m_xy[0].x + rectangle.moveX, m_xy[0].y);
		glVertex2f(m_xy[1].x + rectangle.moveX, m_xy[1].y);
		glEnd();
	}
		c_menu = Collision(small.rx1 + small.moveX, small.rx3 + small.moveX, small.ry1 + small.moveY, small.ry3 + small.moveY, basket.wx1 + basket.moveX, basket.wx3 + basket.moveX, 400, 500);
		if ( c_menu == 1)
		{
			small.Disappear = false;
			if (small.dir == Dir::Stop)
			{
				collision_move = true;
			}
		}
		else if (c_menu == 2) { 
			small.Disappear = false; small.dir = Dir::Cover_stop; 
			if (small.dir == Dir::Cover_stop)
		{
			collision_move = true;
		}
		}
		else if (c_menu == 3) {
			small.Disappear = false; small.dir = Dir::Cover_stop;
			if (small.dir == Dir::Cover_stop)
			{
				collision_move = true;
			}
		}
		else if (c_menu == 4)
			small.Disappear = true;
	small.drawline();
	if(c_menu == 1)
	clliping(basket.wx1 + basket.moveX, basket.wx4 + basket.moveX, basket.wy1 + basket.moveY, basket.wy2 + basket.moveY, small.rx1 + small.moveX, small.ry1 + small.moveY, small.rx2 + small.moveX, small.ry2 + small.moveY, small.rx4 + small.moveX, small.ry4 + small.moveY, small.rx3 + small.moveX, small.ry3 + small.moveY);
	small.draw(); 
	glutSwapBuffers();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
	if (key == 'q' || key == 'Q') {
		exit(0);
	}
	else if (key == 'r' || key == 'R') {
		newrectangle = true;
	}
	glutPostRedisplay();
}


void TimerFunc(int value)
{
	if (value == 1)
	{
		rectangle.move();
		small.move();
		if((small.dir != Dir::Stop && small.dir != Dir::Cover_stop)&& small.dir != Dir::Down)small.moveX = rectangle.moveX;

		glutTimerFunc(100, TimerFunc, 1);
	}
	if (value == 2)
	{
		basket.move();
		if (collision_move == true && (small.dir == Dir::Stop || small.dir == Dir::Cover_stop))small.collision_move(basket.dir, basket.moveX);
		glutTimerFunc(600, TimerFunc, 2);
	}
	glutPostRedisplay();
};

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		m_xy[0].x = x - rectangle.moveX;
		m_xy[0].y = y;
		MouseUp = false;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		m_xy[1].x = x - rectangle.moveX;
		m_xy[1].y = y;
		Cut = true;
		MouseUp = true; 
	}
}

void Motion(int x, int y)
{
	m_xy[1].x = x - rectangle.moveX;
	m_xy[1].y = y;
	glutPostRedisplay();
}