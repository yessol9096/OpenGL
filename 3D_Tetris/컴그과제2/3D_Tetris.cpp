// 3D_Tetris.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "GameFramework.h"
#include <iostream>

CGameFramework fw;

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(600, 800);
	glutCreateWindow("3D_Tetris");

	fw.Init();
	fw.FrameAdvance();
	glutMainLoop();
    return 0;
}

