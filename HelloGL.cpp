#include <stdio.h>
#include <freeglut.h>

int Width = 300;
int Height = 300;

double gx = 5.0;
double gy = 5.0;
double angle = 0.0;

//������ ������ ����ϴ� �ݹ� �Լ�
void Render()
{
    //���� ���۸� ���� ���� �����Ѵ�.
    glClearColor(1.0, 1.0, 0.0, 1.0); //0~1.0

    //���� ���۸� �����
    glClear(GL_COLOR_BUFFER_BIT);


    // ���������� �����Ѵ�.
    glMatrixMode(GL_PROJECTION); //���� ����� ������ķ� �����Ѵ�.
    glLoadIdentity(); //���õ� ��������� ������ķ� �ʱ�ȭ�Ѵ�.
    gluOrtho2D(-gx, gx, -gy, gy); //��ǥ���� ������ �����Ѵ�. 

    glMatrixMode(GL_MODELVIEW); // ���� ����� �𵨺� ��ķ� �����Ѵ�.
    glRotated(angle, 0.0, 1.0, 0.0);
    glColor3d(1.0, 0.0, 0.0); //�׸� ������ �� ����
    glBegin(GL_TRIANGLES); // ���� ����
    {
        glColor3d(1.0, 0.0, 0.0); //�׸� ������ �� ����
        glVertex2d(-2.0, -1.0);
        glColor3d(0.0, 1.0, 0.0); //�׸� ������ �� ����
        glVertex2d(2.0, -1.0);
        glColor3d(0.0, 0.0, 1.0); //�׸� ������ �� ����
        glVertex2d(0.0, 3.0);
    }
    glEnd();

    //���α׸���(���� �� ����)
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


    glColor3d(0.0, 0.0, 1.0); //�׸� ������ �� ����
    //���߿� �׷��� ������ �ﰢ�� ���� �׷�����.
    glBegin(GL_TRIANGLES); // ���� ����
    {
        glVertex2d(-2.0, 1.0);
        glVertex2d(0.0, -3.0);
        glVertex2d(2.0, 1.0);
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

    //������ Render() �Լ��� ȣ���Ѵ�.
    glutPostRedisplay();
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
    glutCreateWindow("Hello GL");

    // ������ ȭ���� �ٲ� ��, �ڵ����� ȣ��Ǵ� ���÷��� �ݹ��Լ�
    glutDisplayFunc(Render);

    //�������� ũ�Ⱑ ����� ��, �ڵ����� ȣ��Ǵ� �ݹ� �Լ�
    glutReshapeFunc(Reshape);

    glutKeyboardFunc(Keyboard);

    // �޽��� ������ ����
    glutMainLoop();
    return 0;
}