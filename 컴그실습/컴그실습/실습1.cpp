#include <glut.h>

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGBA ); // ���÷��� ��� ���� 
	glutInitWindowPosition ( 100, 100 ); // �������� ��ġ���� 
	glutInitWindowSize ( 800, 600 ); // �������� ũ�� ���� 
	glutCreateWindow ( "Example" ); // ������ ���� (������ �̸�) 
	glutDisplayFunc (drawScene); // ��� �Լ��� ����
	glutReshapeFunc(reshape); // �ٽ� �׸��� �Լ��� ���� 
	glutMainLoop ();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // �������� 'Magenta' �� ���� 
	glClear ( GL_COLOR_BUFFER_BIT ); // ������ ������ ��ü�� ĥ�ϱ�
	
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // �������� 'Magenta' �� ���� 
	glRectf(-400.0, 100.0, -200.0, 300.0);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glRectf(200.0, 100.0, 400.0, 300.0);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glRectf(-400.0, -300.0, -200.0, -100.0);

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glRectf(200.0, -300.0, 400.0, -100.0);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRectf(-100.0, -50, 100, 50);

	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}
