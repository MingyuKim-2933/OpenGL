#include <stdio.h>
#include <freeglut.h>
#include <math.h>

int Width = 800;
int Height = 800;
int gx = 10;
int gy = 10;
double angle = 0.0;
double rad = 0.8;
int mp = 1000;

//윈도우 렌더링 담당하는 콜백 함수
void Render()
{
    //색상 버퍼를 지울 색을 지정한다.
    glClearColor(1.0, 1.0, 1.0, 0.0); //0~1.0

    //색상 버퍼를 지운다
    glClear(GL_COLOR_BUFFER_BIT);


    // 관측영역을 지정한다.
    glMatrixMode(GL_PROJECTION); //현재 행렬을 투영행렬로 선택한다.
    glLoadIdentity(); //선택된 투영행렬을 단위행렬로 초기화한다.
    gluOrtho2D(-10, 10, -10, 10); //좌표계의 영역을 지정한다. 

    glMatrixMode(GL_MODELVIEW); // 현재 행렬을 모델뷰 행렬로 선택한다.
    glRotated(angle, 0.0, 1.0, 0.0);
    glColor3d(0.0, 0.0, 0.8); //그릴 도형의 색 지정

    //집 삼각지붕
    glBegin(GL_TRIANGLES); // 도형 지정
    {
        glVertex2d(0.0, 0.0);
        glColor3d(0.8, 0.8, 0.8); //그라데이션
        glVertex2d(2.0, 0.0);
        glVertex2d(1.0, 1.3);
    }
    glEnd();

    //집
    glColor3d(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    {
        glVertex2d(0.1, 0.0);
        glVertex2d(0.1, -1.3);
        glVertex2d(1.9, -1.3);
        glVertex2d(1.9, 0.0);
    }
    glEnd();

    //창문
    glColor3d(0, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex2d(1.3, -0.4);
        glVertex2d(1.3, -0.7);
        glVertex2d(1.7, -0.7);
        glVertex2d(1.7, -0.4);
    }
    glEnd();

    //창문 그라데이션
    glColor3d(1, 1, 1);
    glBegin(GL_TRIANGLES);
    {
        glVertex2d(1.3, -0.4);
        glVertex2d(1.7, -0.5);
        glVertex2d(1.5, -0.4);
    }
    glEnd();

    //도로
    glColor3d(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    {
        glVertex2d(-10, -7.0);
        glVertex2d(-10, -8.0);
        glVertex2d(10, -8.0);
        glVertex2d(10, -7.0);

        glVertex2d(-10, -5.8);
        glVertex2d(-10, -6.8);
        glVertex2d(10, -6.8);
        glVertex2d(10, -5.8);

        glColor3d(1, 1, 0);
        glVertex2d(-10, -7.0);
        glVertex2d(-10, -6.8);
        glVertex2d(10, -6.8);
        glVertex2d(10, -7.0);
    }
    glEnd();

    glColor3d(1, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex2d(-8, -7.4);
        glVertex2d(-8, -7.6);
        glVertex2d(-7, -7.6);
        glVertex2d(-7, -7.4);

        glVertex2d(-5, -7.4);
        glVertex2d(-5, -7.6);
        glVertex2d(-4, -7.6);
        glVertex2d(-4, -7.4);

        glVertex2d(-2, -7.4);
        glVertex2d(-2, -7.6);
        glVertex2d(-1, -7.6);
        glVertex2d(-1, -7.4);

        glVertex2d(1, -7.4);
        glVertex2d(1, -7.6);
        glVertex2d(2, -7.6);
        glVertex2d(2, -7.4);

        glVertex2d(4, -7.4);
        glVertex2d(4, -7.6);
        glVertex2d(5, -7.6);
        glVertex2d(5, -7.4);

        glVertex2d(7, -7.4);
        glVertex2d(7, -7.6);
        glVertex2d(8, -7.6);
        glVertex2d(8, -7.4);
        
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glVertex2d(-8, -6.2);
        glVertex2d(-8, -6.4);
        glVertex2d(-7, -6.4);
        glVertex2d(-7, -6.2);

        glVertex2d(-5, -6.2);
        glVertex2d(-5, -6.4);
        glVertex2d(-4, -6.4);
        glVertex2d(-4, -6.2);

        glVertex2d(-2, -6.2);
        glVertex2d(-2, -6.4);
        glVertex2d(-1, -6.4);
        glVertex2d(-1, -6.2);

        glVertex2d(1, -6.2);
        glVertex2d(1, -6.4);
        glVertex2d(2, -6.4);
        glVertex2d(2, -6.2);

        glVertex2d(4, -6.2);
        glVertex2d(4, -6.4);
        glVertex2d(5, -6.4);
        glVertex2d(5, -6.2);

        glVertex2d(7, -6.2);
        glVertex2d(7, -6.4);
        glVertex2d(8, -6.4);
        glVertex2d(8, -6.2);

    }
    glEnd();

    glBegin(GL_QUADS); //UFO 빛
    {
        glColor3d(1, 1, 1); //그라데이션
        glVertex2d(-4, 5);
        glColor3d(1, 1, 0.6);
        glVertex2d(-5, 0);
        glVertex2d(-2, 0);
        glColor3d(1, 1, 1); //그라데이션
        glVertex2d(-3, 5);
    }
    glEnd();

    glColor3d(1, 0.5, 0);
    glBegin(GL_POLYGON); // 태양
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = rad * cos(angle)+5;
        double y = rad * sin(angle)+5;
        glVertex2f(x, y);
    }
    glEnd();

    //라인그리기(여러 개 가능)
    glBegin(GL_LINES); //햇빛 선
    {
        glVertex2d(6.0, 5.0);
        glVertex2d(7.0, 5.0);

        glVertex2d(3.0, 5.0);
        glVertex2d(4.0, 5.0);

        glVertex2d(5.0, 3.0);
        glVertex2d(5.0, 4.0);

        glVertex2d(5.0, 6.0);
        glVertex2d(5.0, 7.0);

        glVertex2d(5.8, 5.8);
        glVertex2d(6.5, 6.5);

        glVertex2d(4.2, 5.8);
        glVertex2d(3.5, 6.5);

        glVertex2d(4.2, 4.2);
        glVertex2d(3.5, 3.5);

        glVertex2d(5.8, 4.2);
        glVertex2d(6.5, 3.5);
    }
    glEnd();

    glColor3d(0.7, 0.7, 0.7); //UFO원
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 0.3) * cos(angle) -3;
        double y = (rad - 0.3) * sin(angle) +5;
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); //UFO 타원
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 0.2) * cos(angle+0.7) - 3.2;
        double y = (rad - 0.2) * sin(angle) + 4.8;
        glVertex2f(x, y);
    }
    glEnd();

    //UFO 창문
    glColor3d(0.5, 1, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 90; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 0.3) * cos(angle) - 3.1;
        double y = (rad - 0.2) * sin(angle) + 4.8;
        glVertex2f(x, y);
    }
    glEnd();

    glColor3d(0.3, 0, 0);//발의 색 바꾸기
    glBegin(GL_POLYGON);//외계인 왼 발
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 1) * cos(angle) - 2.9;
        double y = (rad - 1) * sin(angle) - 0.8;
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_POLYGON); //외계인 오른 발
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 1) * cos(angle) - 3.7;
        double y = (rad - 1) * sin(angle) - 0.8;
        glVertex2f(x, y);
    }
    glEnd();

    glColor3d(0.4, 1, 0.4);
    glBegin(GL_QUADS); //외계인 몸
    {
        glVertex2d(-3.48, 1);
        glVertex2d(-4.28, -0.7);
        glVertex2d(-2.28, -0.7);
        glVertex2d(-3.08, 1);
    }
    glEnd();

    glColor3d(0.4, 1, 0.4);
    glBegin(GL_TRIANGLE_FAN); //외계인 머리
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad +0.1) * cos(angle+0.5) - 3.3;
        double y = (rad - 0.3) * sin(angle+0.5) +1;
        glVertex2f(x, y);
    }
    glEnd();

    glColor3d(1, 1, 1);
    glBegin(GL_POLYGON);//외계인 눈 흰자
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 1.1) * cos(angle) - 3.28;
        double y = (rad - 1.1) * sin(angle) + 1;
        glVertex2f(x, y);
    }
    glEnd();

    glColor3d(0, 0, 0);
    glBegin(GL_POLYGON);//외계인 눈동자
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 0.9) * cos(angle) - 3.28;
        double y = (rad - 0.9) * sin(angle) + 1;
        glVertex2f(x, y);
    }
    glEnd();

    glColor3d(0.4, 1, 1);

    glBegin(GL_POLYGON); //다이아몬드
    {
        glVertex2d(4, 1.3);
        glVertex2d(5.5, -0.5);
        glVertex2d(7, 1.3);
        glVertex2d(6.3, 2);
        glVertex2d(4.7, 2);
    }
    glEnd();

    glColor3d(0, 0, 0);
    glBegin(GL_LINES); //다이아몬드 선
    {
        glVertex2d(4, 1.3);
        glVertex2d(7, 1.3);
        glVertex2d(5.5, -0.5);
        glVertex2d(6.3, 2);
        glVertex2d(5.5, -0.5);
        glVertex2d(4.7, 2);
    }
    glEnd();

    //렌더링 종료
    glFinish();
}


void Reshape(int w, int h)
{
    glViewport(0, 0, Width, Height); //1번째 인자, 2번째 인자는 도형의 위치   / 3번째 인자, 4번째 인자는 도형을 띄울 공간의 크기
}

void Keyboard(unsigned char key, int x, int y)
{

}

int main(int argc, char** argv)
{
    // glut 초기화(무조건 똑같이...)
    glutInit(&argc, argv);

    // Width by Height 크기의 윈도우 지정
    glutInitWindowSize(Width, Height);

    // 윈도우의 디스플레이 모드를 RGB로 설정
    glutInitDisplayMode(GLUT_RGB);

    // 윈도우 생성
    glutCreateWindow("Assignment1");

    // 윈도우 화면이 바뀔 때, 자동으로 호출되는 디스플레이 콜백함수
    glutDisplayFunc(Render);

    //윈도우의 크기가 변경될 때, 자동으로 호출되는 콜백 함수
    glutReshapeFunc(Reshape);

    glutKeyboardFunc(Keyboard);

    // 메시지 루프로 진입
    glutMainLoop();
    return 0;
}