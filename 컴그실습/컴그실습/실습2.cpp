#include <glut.h>
#include <ctime>
#include <stdlib.h>

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
int randEven();

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(reshape); // �ٽ� �׸��� �Լ��� ���� 
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // �������� 'Magenta' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	int num = randEven();
	int numX = 800 / num;
	int numY = 600 / num;
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < num; ++j)
		{
			if (i % 2 ==j % 2)
			{
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				glRectf(i*numX, j * numY, i*numX + numX, j * numY + numY);
			}
			else
			{
				glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
				glRectf(i*numX, j * numY, i*numX + numX, j * numY + numY);
			}
		}
	}
	

	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

int randEven()
{
	srand((unsigned)time(NULL));
	int Even = ((rand() % 10) + 1) * 2;
	return Even;
}