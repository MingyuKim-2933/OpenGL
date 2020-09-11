#include <stdio.h>
#include <freeglut.h>

int Width = 300;
int Height = 300;

double gx = 5.0;
double gy = 5.0;
double angle = 0.0;

//윈도우 렌더링 담당하는 콜백 함수
void Render()
{
    //색상 버퍼를 지울 색을 지정한다.
    glClearColor(1.0, 1.0, 0.0, 1.0); //0~1.0

    //색상 버퍼를 지운다
    glClear(GL_COLOR_BUFFER_BIT);


    // 관측영역을 지정한다.
    glMatrixMode(GL_PROJECTION); //현재 행렬을 투영행렬로 선택한다.
    glLoadIdentity(); //선택된 투영행렬을 단위행렬로 초기화한다.
    gluOrtho2D(-gx, gx, -gy, gy); //좌표계의 영역을 지정한다. 

    glMatrixMode(GL_MODELVIEW); // 현재 행렬을 모델뷰 행렬로 선택한다.
    glRotated(angle, 0.0, 1.0, 0.0);
    glColor3d(1.0, 0.0, 0.0); //그릴 도형의 색 지정
    glBegin(GL_TRIANGLES); // 도형 지정
    {
        glColor3d(1.0, 0.0, 0.0); //그릴 도형의 색 지정
        glVertex2d(-2.0, -1.0);
        glColor3d(0.0, 1.0, 0.0); //그릴 도형의 색 지정
        glVertex2d(2.0, -1.0);
        glColor3d(0.0, 0.0, 1.0); //그릴 도형의 색 지정
        glVertex2d(0.0, 3.0);
    }
    glEnd();

    //라인그리기(여러 개 가능)
    glBegin(GL_LINES);
    {
        glColor3d(0.0, 1.0, 0.0);
        glVertex2d(-100.0, 0.0);
        glVertex2d(100.0, 0.0);

        glColor3d(0.0, 0.0, 1.0);
        glVertex2d(0.0, -100.0);
        glVertex2d(0.0, 100.0);
    }
    glEnd();


    glColor3d(0.0, 0.0, 1.0); //그릴 도형의 색 지정
    //나중에 그려서 빨간색 삼각형 위에 그려진다.
    glBegin(GL_TRIANGLES); // 도형 지정
    {
        glVertex2d(-2.0, 1.0);
        glVertex2d(0.0, -3.0);
        glVertex2d(2.0, 1.0);
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
    if (key == '1')
    {
        gx *= 2.0;
        gy *= 2.0;
    }
    if (key == '2')
    {
        gx /= 2.0;
        gy /= 2.0;
    }
    if (key == '3')
    {
        angle += 5.0;
    }

    //강제로 Render() 함수를 호출한다.
    glutPostRedisplay();
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
    glutCreateWindow("Hello GL");

    // 윈도우 화면이 바뀔 때, 자동으로 호출되는 디스플레이 콜백함수
    glutDisplayFunc(Render);

    //윈도우의 크기가 변경될 때, 자동으로 호출되는 콜백 함수
    glutReshapeFunc(Reshape);

    glutKeyboardFunc(Keyboard);

    // 메시지 루프로 진입
    glutMainLoop();
    return 0;
}