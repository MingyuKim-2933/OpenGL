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

//������ ������ ����ϴ� �ݹ� �Լ�
void Render()
{
    //���� ���۸� ���� ���� �����Ѵ�.
    glClearColor(1.0, 1.0, 1.0, 0.0); //0~1.0

    //���� ���۸� �����
    glClear(GL_COLOR_BUFFER_BIT);


    // ���������� �����Ѵ�.
    glMatrixMode(GL_PROJECTION); //���� ����� ������ķ� �����Ѵ�.
    glLoadIdentity(); //���õ� ��������� ������ķ� �ʱ�ȭ�Ѵ�.
    gluOrtho2D(-10, 10, -10, 10); //��ǥ���� ������ �����Ѵ�. 

    glMatrixMode(GL_MODELVIEW); // ���� ����� �𵨺� ��ķ� �����Ѵ�.
    glRotated(angle, 0.0, 1.0, 0.0);
    glColor3d(0.0, 0.0, 0.8); //�׸� ������ �� ����

    //�� �ﰢ����
    glBegin(GL_TRIANGLES); // ���� ����
    {
        glVertex2d(0.0, 0.0);
        glColor3d(0.8, 0.8, 0.8); //�׶��̼�
        glVertex2d(2.0, 0.0);
        glVertex2d(1.0, 1.3);
    }
    glEnd();

    //��
    glColor3d(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    {
        glVertex2d(0.1, 0.0);
        glVertex2d(0.1, -1.3);
        glVertex2d(1.9, -1.3);
        glVertex2d(1.9, 0.0);
    }
    glEnd();

    //â��
    glColor3d(0, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex2d(1.3, -0.4);
        glVertex2d(1.3, -0.7);
        glVertex2d(1.7, -0.7);
        glVertex2d(1.7, -0.4);
    }
    glEnd();

    //â�� �׶��̼�
    glColor3d(1, 1, 1);
    glBegin(GL_TRIANGLES);
    {
        glVertex2d(1.3, -0.4);
        glVertex2d(1.7, -0.5);
        glVertex2d(1.5, -0.4);
    }
    glEnd();

    //����
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

    glBegin(GL_QUADS); //UFO ��
    {
        glColor3d(1, 1, 1); //�׶��̼�
        glVertex2d(-4, 5);
        glColor3d(1, 1, 0.6);
        glVertex2d(-5, 0);
        glVertex2d(-2, 0);
        glColor3d(1, 1, 1); //�׶��̼�
        glVertex2d(-3, 5);
    }
    glEnd();

    glColor3d(1, 0.5, 0);
    glBegin(GL_POLYGON); // �¾�
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = rad * cos(angle)+5;
        double y = rad * sin(angle)+5;
        glVertex2f(x, y);
    }
    glEnd();

    //���α׸���(���� �� ����)
    glBegin(GL_LINES); //�޺� ��
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

    glColor3d(0.7, 0.7, 0.7); //UFO��
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 0.3) * cos(angle) -3;
        double y = (rad - 0.3) * sin(angle) +5;
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); //UFO Ÿ��
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 0.2) * cos(angle+0.7) - 3.2;
        double y = (rad - 0.2) * sin(angle) + 4.8;
        glVertex2f(x, y);
    }
    glEnd();

    //UFO â��
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

    glColor3d(0.3, 0, 0);//���� �� �ٲٱ�
    glBegin(GL_POLYGON);//�ܰ��� �� ��
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 1) * cos(angle) - 2.9;
        double y = (rad - 1) * sin(angle) - 0.8;
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_POLYGON); //�ܰ��� ���� ��
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 1) * cos(angle) - 3.7;
        double y = (rad - 1) * sin(angle) - 0.8;
        glVertex2f(x, y);
    }
    glEnd();

    glColor3d(0.4, 1, 0.4);
    glBegin(GL_QUADS); //�ܰ��� ��
    {
        glVertex2d(-3.48, 1);
        glVertex2d(-4.28, -0.7);
        glVertex2d(-2.28, -0.7);
        glVertex2d(-3.08, 1);
    }
    glEnd();

    glColor3d(0.4, 1, 0.4);
    glBegin(GL_TRIANGLE_FAN); //�ܰ��� �Ӹ�
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad +0.1) * cos(angle+0.5) - 3.3;
        double y = (rad - 0.3) * sin(angle+0.5) +1;
        glVertex2f(x, y);
    }
    glEnd();

    glColor3d(1, 1, 1);
    glBegin(GL_POLYGON);//�ܰ��� �� ����
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 1.1) * cos(angle) - 3.28;
        double y = (rad - 1.1) * sin(angle) + 1;
        glVertex2f(x, y);
    }
    glEnd();

    glColor3d(0, 0, 0);
    glBegin(GL_POLYGON);//�ܰ��� ������
    for (int i = 0; i < 360; i++)
    {
        double angle = i * 3.141592 / 180;
        double x = (rad - 0.9) * cos(angle) - 3.28;
        double y = (rad - 0.9) * sin(angle) + 1;
        glVertex2f(x, y);
    }
    glEnd();

    glColor3d(0.4, 1, 1);

    glBegin(GL_POLYGON); //���̾Ƹ��
    {
        glVertex2d(4, 1.3);
        glVertex2d(5.5, -0.5);
        glVertex2d(7, 1.3);
        glVertex2d(6.3, 2);
        glVertex2d(4.7, 2);
    }
    glEnd();

    glColor3d(0, 0, 0);
    glBegin(GL_LINES); //���̾Ƹ�� ��
    {
        glVertex2d(4, 1.3);
        glVertex2d(7, 1.3);
        glVertex2d(5.5, -0.5);
        glVertex2d(6.3, 2);
        glVertex2d(5.5, -0.5);
        glVertex2d(4.7, 2);
    }
    glEnd();

    //������ ����
    glFinish();
}


void Reshape(int w, int h)
{
    glViewport(0, 0, Width, Height); //1��° ����, 2��° ���ڴ� ������ ��ġ   / 3��° ����, 4��° ���ڴ� ������ ��� ������ ũ��
}

void Keyboard(unsigned char key, int x, int y)
{

}

int main(int argc, char** argv)
{
    // glut �ʱ�ȭ(������ �Ȱ���...)
    glutInit(&argc, argv);

    // Width by Height ũ���� ������ ����
    glutInitWindowSize(Width, Height);

    // �������� ���÷��� ��带 RGB�� ����
    glutInitDisplayMode(GLUT_RGB);

    // ������ ����
    glutCreateWindow("Assignment1");

    // ������ ȭ���� �ٲ� ��, �ڵ����� ȣ��Ǵ� ���÷��� �ݹ��Լ�
    glutDisplayFunc(Render);

    //�������� ũ�Ⱑ ����� ��, �ڵ����� ȣ��Ǵ� �ݹ� �Լ�
    glutReshapeFunc(Reshape);

    glutKeyboardFunc(Keyboard);

    // �޽��� ������ ����
    glutMainLoop();
    return 0;
}