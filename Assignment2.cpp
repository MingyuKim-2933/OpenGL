#include <stdio.h>
#include "gl\freeglut.h"

int Width = 800, Height = 800;
GLfloat R = 0.0, G = 0.0, B = 0.0;
GLfloat LineWidth = 1.0;
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

// 콜백 함수 선언
void Display();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void ColorMenu(int id);
void WidthMenu(int id);
void PatternMenu(int id);
void CreateMenu(int id);

int main(int argc, char** argv)
{
	// GLUT 초기화
	glutInit(&argc, argv);

	// 윈도우 크기 및 위치 초기화
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);

	// 디스플레이모드 설정
	glutInitDisplayMode(GLUT_RGBA);



	// 윈도우 생성
	glutCreateWindow("2016113290 김민규");

	// 콜백 함수 등록
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	// 메뉴 생성
	GLint ColorMenuId = glutCreateMenu(ColorMenu);
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);

	GLint WidthMenuId = glutCreateMenu(WidthMenu);
	glutAddMenuEntry("1.0", 0);
	glutAddMenuEntry("3.0", 1);
	glutAddMenuEntry("5.0", 2);

	GLint PatternMenuId = glutCreateMenu(PatternMenu);
	glutAddMenuEntry("Solid", 0);
	glutAddMenuEntry("Dotted", 1);

	GLint CreateMenuId = glutCreateMenu(CreateMenu);
	glutAddSubMenu("Color", ColorMenuId);
	glutAddSubMenu("Width", WidthMenuId);
	glutAddSubMenu("Pattern", PatternMenuId);
	glutAddMenuEntry("Exit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// 메시지 루프 진입
	glutMainLoop();
	return 0;
}

void Display()
{
	

	// 관측 공간을 지정한다.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Width, 0.0, Height);

	glColor3f(R, G, B);
	glLineWidth(LineWidth);
	glBegin(GL_LINES);

	glVertex3f(TopLeftX, TopLeftY, 0.0);
	glVertex3f(BottomRightX, BottomRightY, 0.0);

	glEnd();
	glFinish();
}

void CreateMenu(int id)
{
	if (id == 0) // "Exit" 선택...
		exit(0);
}

void ColorMenu(int id)
{
	if (id == 0) // "Red" 선택...
	{
		R = 1.0;
		G = 0.0;
		B = 0.0;
	}

	else if (id == 1) // "Green" 선택...
	{
		R = 0.0;
		G = 1.0;
		B = 0.0;
	}

	else if (id == 2) // "Blue" 선택...
	{
		R = 0.0;
		G = 0.0;
		B = 1.0;
	}
}

void WidthMenu(int id)
{
	if (id == 0) // "1.0" 선택...
	{
		LineWidth = 1.0;
	}

	else if (id == 1) // "3.0" 선택...
	{
		LineWidth = 3.0;
	}

	else if (id == 2) // "5.0" 선택...
	{
		LineWidth = 5.0;
	}
}

void PatternMenu(int id)
{
	if (id == 0)
	{
		glDisable(GL_LINE_STIPPLE);
	}
	else if (id == 1)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(2, 0x00FF);
	}
}


void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}


void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		TopLeftX = x;
		TopLeftY = Height - y;
	}
	
}

void Motion(int x, int y)
{
	BottomRightX = x;
	BottomRightY = Height - y;
}



