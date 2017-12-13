#include <glut.h> 
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#define PI 3.141592


void SetupRC();
void DrawScene();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void SpecialKeyboard(int key, int x, int y);
void UpdateCam();
int culling = 1;
int shading = 1;
int depth = 1;
float open_up;
float move_x;
float move_y;

float move_fx;
float move_fz;
float open_front;
float move_z;
bool Open_front = false;
bool Open_up = false;
GLdouble cyRotate = 0.5;
GLdouble cxRotate = 0.0;
GLdouble czRotate = 0.0;

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint texture_object[6];
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);



void main()
{
	// 윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("Points Drawing");

	// 상태 변수 초기화 함수
	SetupRC();

	// 필요한 콜백 함수 설정
	glutDisplayFunc(DrawScene); // 출력 콜백 함수
	glutReshapeFunc(Reshape); // 다시 그리기 콜백 함수
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutSpecialFunc(SpecialKeyboard);
	glutTimerFunc(100, TimerFunction, 1); // 타이머 콜백 함수
	glutMainLoop(); // 이벤트 루프 실행하기
}

void SetupRC() {
	glGenTextures(2, texture_object);

	// 1
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	pBytes = LoadDIBitmap("1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 2
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	pBytes = LoadDIBitmap("2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);

}
int rotateX = 0;
//-------------------------------------------------------------------------------------------------------------------------
// 렌더링을 위한 디스플레이 콜백 함수: 모든 그리기 명령은 이 함수에서 대부분 처리 함
void DrawScene()
{
	UpdateCam();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기


	glPushMatrix();
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);	// 컬링제거
	//glShadeModel(GL_SMOOTH); // 또는 glShadeModel (GL_FLAT)

	glPushMatrix();
	glRotatef(30, 1.0, 0.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(rotateX, 0.0, 1.0, 0.0);

	if (culling == 1) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	if (shading == 1) {
		glShadeModel(GL_SMOOTH); // 또는 glShadeModel (GL_FLAT)
	}
	else {
		glShadeModel(GL_FLAT);
	}

	if (depth == 1) {
		glEnable(GL_DEPTH_TEST);
	}

	else {
		glDisable(GL_DEPTH_TEST);
	}

	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);		// 옆면
	
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-50.0, 50.0, 50.0);   //1

	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-50.0, -50.0, 50.0);   //2

	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(50.0, -50.0, 50.0);   //3

	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(50.0, 50.0, 50.0);   //4

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);		// 오른쪽 옆면
	
	glTexCoord2d(0.0f, 1.0f);

	glVertex3f(50.0, 50.0, 50.0);   //4

	glTexCoord2d(0.0f, 0.0f);

	glVertex3f(50.0, -50.0, 50.0);   //3

	glTexCoord2d(1.0f, 0.0f);

	glVertex3f(50.0, -50.0, -50.0);   //7

	glTexCoord2d(1.0f, 1.0f);

	glVertex3f(50.0, 50.0, -50.0);   //6

	glEnd();




	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);		// 앞면

	glTexCoord2d(0.0f, 1.0f);

	glVertex3f(-50.0, 50.0, -50.0);   //5

	glTexCoord2d(0.0f, 0.0f);

	glVertex3f(50.0, 50.0, -50.0);   //6

	glTexCoord2d(1.0f, 0.0f);

	glVertex3f(50.0, -50.0, -50.0);   //7

	glTexCoord2d(1.0f, 1.0f);

	glVertex3f(-50.0, -50.0, -50.0);   //8

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);		// 왼쪽면
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-50.0, 50.0, 50.0);   //1

	glTexCoord2d(0.0f, 0.0f);

	glVertex3f(-50.0, 50.0, -50.0);   //5

	glTexCoord2d(1.0f, 0.0f);

	glVertex3f(-50.0, -50.0, -50.0);   //8

	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-50.0, -50.0, 50.0);   //2

	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);		// 윗면

	glTexCoord2d(0.0f, 1.0f);

	glVertex3f(-50.0, 50.0, -50.0);   //1

	glTexCoord2d(0.0f, 0.0f);

	glVertex3f(-50.0, 50.0, 50.0);   //4

	glTexCoord2d(1.0f, 0.0f);

	glVertex3f(50.0, 50.0, 50.0);   //5

	glTexCoord2d(1.0f, 1.0f);

	glVertex3f(50.0, 50.0, -50.0);   //6

	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);		// 아랫면

	glTexCoord2d(0.0f, 1.0f);

	glVertex3f(-50.0, -50.0, 50.0);   //2

	glTexCoord2d(0.0f, 0.0f);

	glVertex3f(-50.0, -50.0, -50.0);   //8

	glTexCoord2d(1.0f, 0.0f);

	glVertex3f(50.0, -50.0, -50.0);   //7

	glTexCoord2d(1.0f, 1.0f);

	glVertex3f(50.0, -50.0, 50.0);   //3
	glEnd();

	glPopMatrix();
	glPopMatrix();
	//glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); // 결과 출력
}

void Reshape(int w, int h)
{
	// 뷰포트 변환 설정: 출력 화면 결정
	glViewport(0, 0, w, h);
	// 클리핑 변환 설정: 출력하고자 하는 공간 결정
	// 아래 3줄은 투영을 설정하는 함수
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 원근 투영을 사용하는 경우:
	gluPerspective(60.0, 600 / 400, 1.0, 1000.0);
	//glTranslatef(0.0, 0.0, -300.0);
	//glOrtho (0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장


	gluLookAt(0, 0, 500, 0, 0, -1, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'c' || key == 'C') {
		if (culling == 0)culling = 1;
		else if (culling == 1)culling = 0;
	}
	else if (key == 's' || key == 'S') {
		if (shading == 0)shading = 1;
		else if (shading == 1)shading = 0;
	}
	else if (key == 'd' || key == 'D') {
		if (depth == 0)depth = 1;
		else if (depth == 1)depth = 0;
	}
	else if (key == 'u') {
		if (Open_up == false) Open_up = true;
		else if (Open_up == true)Open_up = false;
	}
	else if (key == 'f') {
		if (Open_front == false) Open_front = true;
		else if (Open_front == true)Open_front = false;
	}
	else if (key == 'x') {
		if (cyRotate<1) cyRotate += 0.1;
	}
	else if (key == 'X') {
		if (cyRotate>-1) cyRotate -= 0.1;
	}
	else if (key == 'y') {
		if (cxRotate<1) cxRotate += 0.1;
	}
	else if (key == 'Y') {
		if (cxRotate>-1) cxRotate -= 0.1;
	}
	else if (key == 'z') {
		czRotate += 1;
	}
	else if (key == 'Z') {
		czRotate -= 1;
	}
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	rotateX += 10;
	if (Open_up == true && open_up < 40) { move_x = open_up * 0.6; open_up += 0.5; move_y = open_up*1.0; }
	else if (Open_up == false && open_up != 0) {
		move_x = open_up * 0.6; open_up -= 0.5; move_y = open_up*1.0;
	}
	if (Open_front == true && open_front > -40) { move_fx = open_front * 0.6; open_front -= 0.5; move_fz = open_front * 1.0; }
	else if (Open_front == false && open_front != 0) {
		move_fx = open_front * 0.6; open_front += 0.5; move_fz = open_front * 1.0;
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void SpecialKeyboard(int key, int x, int y) {

	glutPostRedisplay();
}

void UpdateCam() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 원근 투영을 사용하는 경우:
	gluPerspective(60.0, 600 / 400, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장

	glRotatef(czRotate, 0, 0, 1);
	gluLookAt
	(
		cxRotate, cyRotate, 0,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0
	);
	glRotatef(-czRotate, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}



GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인핚다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 갂다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 핛당을 핚다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 핛당핚다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장핚다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}