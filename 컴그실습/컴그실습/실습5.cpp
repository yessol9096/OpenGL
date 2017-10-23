#include <glut.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>


GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void TimerFunc(int value);
void MenuFunc(int button);
void Keyboard(unsigned char key, int x, int y);

enum class Dir {
	Right_Up	// ������ �밢�� ����
	, Right_Down	// ������ �밢�� �Ʒ���
	, Left_Down	// ���� �밢�� �Ʒ���
	, Left_UP		// ���� �밢�� ����
};

int num = 0;
int height = 20;
int width = 20;

class Rectangle {
public:
	int x;
	int y;
	int move;
	int speed;
	int fig;
	int r = 20;
	Dir direction;
	GLvoid draw(GLvoid) {
		if (fig == 1)
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
		else if (fig == 2)
		{
			for (int j = 0; j <= 360; ++j) {
				glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
				glBegin(GL_POINTS);
				glVertex2i(x + r*cos((j / 180.0)*3.14), y + r * sin((j / 180.0)*3.14)); //v2
				glEnd();
			}
		}
	}

	void Move()
	{
		for (int i = 0; i < num; ++i)
		{
			if (direction == Dir::Right_Up )
			{
				x += speed;
				y -= speed;
				if (x > 750 || y < 1)
				{
					direction = Dir::Left_UP;
				}
			}
			else if (direction == Dir::Right_Down)
			{
				x += speed;
				y += speed;
				if (x > 750 || y > 590)
				{
					direction = Dir::Right_Up;
				}
			}
			else if (direction == Dir::Left_Down)
			{
				x -= speed;
				y += speed;
				if (x < 1 || y > 590)
				{
					direction = Dir::Right_Down;
				}
			}
			if (direction == Dir::Left_UP)
			{
				x -= speed;
				y -= speed;
				if (x < 1 || y < 1)
				{
					direction = Dir::Left_Down;
				}
			}
		}
	}
};

class Rectangle rects[10];

void main(int argc, char *argv[])
{
	int Mainmenu;
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example"); // ������ ���� (������ �̸�)
	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�

	glutTimerFunc(300, TimerFunc, 1);
	Mainmenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("�簢��", 1);
	glutAddMenuEntry("��", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutReshapeFunc(reshape); // �ٽ� �׸��� �Լ��� ���� 
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(1, 0, 0, 0);
	for (int i = 0; i < 10; ++i) {
		rects[i].draw();
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
		rects[num].x = x;
		rects[num].y = y;
		rects[num].speed = (rand() % 8) + 5;
		rects[num].direction = Dir(rand()%4);
		rects[num].move = 1;
		std::cout << x << ", " << y << "num:" << num << std::endl;
		++num;
		num = num % 10;
	}

	glutPostRedisplay();
}

void TimerFunc(int value)
{
	for (int i = 0; i < 10; ++i)
		rects[i].Move();
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
};


void MenuFunc(int button) {
	switch (button) {
	case 1:
		for (int i = 0; i < 10; ++i) rects[i].fig = 1;
		break;
	case 2:
		for (int i = 0; i < 10; ++i) rects[i].fig = 2;
		break;
	}
	glutPostRedisplay();
};


void Keyboard(unsigned char key, int x, int y) {
	for (int i = 0; i < 10; ++i)
	{
		if (key == 'w')rects[i].speed += 5;
		else if (key == 's' && rects[i].speed > 10) rects[i].speed -= 5;
	}
}