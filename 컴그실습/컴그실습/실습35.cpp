#include <glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);


void vLine();

float fMapZ = 0.0;
float vMapX = 0.0;
float vMapY = -15.0;
float fView = 0.0;

GLfloat fog_color[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat density = 0.7;
float start = 25.0;
float end = 35.0;

bool IsFog = true;

void main(int argc, char *argv[]) {
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("4-35"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������ ������ ��ü�� ĥ�ϱ�
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FOG);
	if (IsFog == true)
	{
		glFogf(GL_FOG_MODE, GL_LINEAR);
	}
	else
	{
		glFogf(GL_FOG_MODE, GL_EXP);

	}
	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotated(fMapZ, 0, 0, 1.0);
	glRotated(vMapX, 1.0, 0, 0);
	glRotated(vMapY, 0, 1.0, 0);

	gluLookAt(0, 0, fView, 0, 0, -1, 0, 1, 0);

	glPushMatrix(); //Save
	vLine();
	glPopMatrix();


	glFogfv(GL_FOG_COLOR, fog_color); // fog_color�� �Ȱ��� ���� �ǹ�����.
	glFogf(GL_FOG_START, start); // start�� world coordinate�󿡼� �Ȱ� ���� ��ġ�� �ǹ�����.

	glPushMatrix(); //Save
	glColor3f(1.0, 0.0, 0.0);
	glutSolidCube(100);
	glPopMatrix();

	glPushMatrix(); //Save
	glColor3f(0.0, 0.0, 1.0);
	glTranslated(70, 0, 0);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix(); //Save
	glColor3f(0.0, 1.0, 0.0);
	glTranslated(-70, 0, 0);
	glutSolidCube(50);
	glPopMatrix();

	glFogf(GL_FOG_END, end); // end�� world coordinate�󿡼� �Ȱ� �� ��ġ�� �ǹ�����.
	glFogf(GL_FOG_DENSITY, density); // fog mode�� GL_EXP, GL_EXP2�� ��� �е��� ������ ����

	glPopMatrix();
	//glFlush(); // ȭ�鿡 ����ϱ�
	glutSwapBuffers();     // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value) {
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y) {
	printf("InPut Key = %c\n", key);
	if (key == 'd') {
		density += 1.0;
	}
	else if (key == 'D') {
		density -= 1.0;
	}
	if (key == 'r') {
		vMapY += 1.0;
	}
	if (key == 's') {
		start += 1.0;
	}
	else if (key == 'S') {
		start -= 1.0;
	}
	if (key == 'e') {
		end += 1.0;
	}
	if (key == 'E') {
		end -= 1.0;
	}
	if (key == 'm') {
		IsFog = true;
	}
	if (key == 'M') {
		IsFog = false;
	}
	printf("�Ȱ��� : %f\n", density);
	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		fMapZ -= 3.0;
	}
	if (key == GLUT_KEY_RIGHT) {
		fMapZ += 3.0;
	}
	if (key == GLUT_KEY_DOWN) {
		vMapX += 3.0;
	}
	if (key == GLUT_KEY_UP) {
		vMapX -= 3.0;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		printf("Left = (%d, %d)\n", x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1500.0);

	gluLookAt(0, 0, 500, 0, 0, -1, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
}

void vLine() {
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -100);
	glVertex3f(0, 0, 100);
	glEnd();
}
