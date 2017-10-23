#include <glut.h>
#include <ctime>
#include <stdlib.h>

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
int randEven();

void main(int argc, char *argv[])
{
	//초기화 함수들 
	srand((unsigned)time(NULL));

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT); 

	GLint p1[2] = { 0, -150 };
	GLint p2[2] = { 600, -150 };
	GLint p3[2] = { 0, -300 };
	GLint p4[2] = { 600, -300 };
	GLint p5[2] = { 200, 0 };
	GLint p6[2] = { 200, -450 };
	GLint p7[2] = { 400, 0 };
	GLint p8[2] = { 400, -450 };

	
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2iv(p1);
		glVertex2iv(p2);
		glVertex2iv(p3);
		glVertex2iv(p4);
		glVertex2iv(p5);
		glVertex2iv(p6);
		glVertex2iv(p7);
		glVertex2iv(p8);
	glEnd();
	
	int figure = rand()%4 + 1;

	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			figure++;
			if (figure == 5)figure = 1;
			glColor4f(0.0f, 0.0f, 1.0f, 0.0f);

			if (figure % 4 + 1 == 1)
			{
				GLint f1[2] = { i * 200 + 10 , -(j * 150 + 10)  };
				GLint f2[2] = { i * 200 + 150, -(j * 150 + 130 )};
				glBegin(GL_LINE_STRIP);
					glVertex2iv(f1);
					glVertex2iv(f2);
				glEnd();
			}
			else if (figure % 4 + 1 == 2)
			{
				GLint f1[2] = { i * 200 + 20, -(j * 150 + 20) };
				GLint f2[2] = { i * 200 + 100, -(j * 150 + 130 )};
				GLint f3[2] = { i * 200 + 180, -(j * 150 + 20) };
				glBegin(GL_TRIANGLES);
					glVertex2iv(f1);
					glVertex2iv(f2);
					glVertex2iv(f3);
				glEnd();
			}
			else if (figure % 4 + 1 == 3)
			{
				GLint f1[2] = { i * 200 + 20, -(j * 150 + 20) };
				GLint f2[2] = { i * 200 + 20, -(j * 150 + 130) };
				GLint f3[2] = { i * 200 + 180, -(j * 150 + 20) };
				GLint f4[2] = { i * 200 + 180, -(j * 150 + 130) };
				glBegin(GL_POLYGON);
					glVertex2iv(f2);
					glVertex2iv(f1);
					glVertex2iv(f3);
					glVertex2iv(f4);
				glEnd();
			}
			else if (figure % 4 + 1 == 4)
			{
				GLint f1[2] = { i * 200 + 30, -(j * 150 + 20) };
				GLint f2[2] = { i * 200 + 10, -(j * 150 + 70) };
				GLint f5[2] = { i * 200 + 110, -(j * 150 + 130) };
				GLint f3[2] = { i * 200 + 170, -(j * 150 + 70) };
				GLint f4[2] = { i * 200 + 150, -(j * 150 + 20) };
				glBegin(GL_POLYGON);
					glVertex2iv(f1);
					glVertex2iv(f2);
					glVertex2iv(f5);
					glVertex2iv(f3);
					glVertex2iv(f4);
				glEnd();
			}
		}
		figure = figure + 2;
	}


	glFlush(); // 화면에 출력하기
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 600, 0, -450, -1.0, 1.0);
}
