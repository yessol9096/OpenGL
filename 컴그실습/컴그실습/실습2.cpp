#include <glut.h>
#include <ctime>
#include <stdlib.h>

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
int randEven();

void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(reshape); // 다시 그리기 함수의 지정 
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'Magenta' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

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
	

	glFlush(); // 화면에 출력하기
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