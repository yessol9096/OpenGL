#include <glut.h>

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);

void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGBA ); // 디스플레이 모드 설정 
	glutInitWindowPosition ( 100, 100 ); // 윈도우의 위치지정 
	glutInitWindowSize ( 800, 600 ); // 윈도우의 크기 지정 
	glutCreateWindow ( "Example" ); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc (drawScene); // 출력 함수의 지정
	glutReshapeFunc(reshape); // 다시 그리기 함수의 지정 
	glutMainLoop ();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'Magenta' 로 지정 
	glClear ( GL_COLOR_BUFFER_BIT ); // 설정된 색으로 전체를 칠하기
	
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 'Magenta' 로 지정 
	glRectf(-400.0, 100.0, -200.0, 300.0);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glRectf(200.0, 100.0, 400.0, 300.0);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glRectf(-400.0, -300.0, -200.0, -100.0);

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glRectf(200.0, -300.0, 400.0, -100.0);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRectf(-100.0, -50, 100, 50);

	glFlush(); // 화면에 출력하기
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}
