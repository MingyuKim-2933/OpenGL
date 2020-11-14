#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "..\usr\include\GL\freeglut.h"
#include <vector>

static int shoulder = 0, elbow = 0;
static float finger = 0;

// ������ ũ��
int Width = 800, Height = 800;



// ��� ������ ���� ������
int ManipulateMode = 0; // 1: ȸ��, 2: �̵�
int StartPt[2];
float Axis[3] = { 1.0, 0.0, 0.0 };
float Angle = 0.0;
float RotMat[16] = { 1, 0, 0, 0,
               0, 1, 0, 0,
               0, 0, 1, 0,
               0, 0, 0, 1 };
float Zoom = -30.0;
float Pan[3] = { 0.0, 0.0, 0.0 };


// �ݹ� �Լ���
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void MouseWheel(int button, int dir, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Render();

// ����� ���� �Լ���
void InitOpenGL();
void GetSphereCoord(int x, int y, float* px, float* py, float* pz);
void RenderFloor();
void RenderRobot();
void drawCube(float sx, float sy, float sz);
void SetupViewVolume();
void SetupViewTransform();
void Sub(double out[3], double a[3], double b[3]);
void Add(double out[3], double a[3], double b[3]);
void Cross(double out[3], double a[3], double b[3]);


void Cross(double out[3], double a[3], double b[3])
{
    out[0] = a[1] * b[2] - a[2] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
}

void Sub(double out[3], double a[3], double b[3])
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

void Add(double out[3], double a[3], double b[3])
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

int main(int argc, char** argv)
{
    // GLUT �ʱ�ȭ(���� Į�����, RBGA, ���̹��� ���)
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    // ������ ����
    glutInitWindowSize(Width, Height);
    glutCreateWindow("3DViewer");

    // OpenGL �ʱ�ȭ
    InitOpenGL();

    // �ݹ��Լ� ���
    glutReshapeFunc(Reshape);
    glutMouseFunc(Mouse);
    glutKeyboardFunc(Keyboard);
    glutMotionFunc(Motion); // ���콺 ��ư ������ ������ ��, �ڵ����� ȣ��Ǵ� �Լ�
    glutMouseWheelFunc(MouseWheel);
    glutDisplayFunc(Render);

    // �޽��� ���� ����
    glutMainLoop();
    return 0;
}


void InitOpenGL()
{
    // ���� �׽�Ʈ�� Ȱ��ȭ
    glEnable(GL_DEPTH_TEST);

    // ���� �� Ȱ��ȭ
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void Render()
{
    // Clear color buffer
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up viewing volume
    SetupViewVolume();

    // Set up viewing transformation
    SetupViewTransform();

    glMatrixMode(GL_MODELVIEW);
    RenderFloor();
    RenderRobot();

    // Swap buffers for double buffering.
    glutSwapBuffers();
}



void RenderRobot()
{
    // ���� �ϼ���.

    //������ �����Ѵ�.
    glShadeModel(GL_FLAT);
    float mat0_ambient[] = { 0.2, 0.2, 0.2 };
    float mat0_diffuse[] = { 0.0, 0.0, 0.0 };
    float mat0_specular[] = { 0.2, 0.2, 0.2 };
    float mat0_shininess = 32;

    GLfloat light0_position[] = { 10.0f, 10.0f, 10.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat0_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat0_shininess);
    glPushMatrix();
    drawCube(10.0f, 1.0f, 10.0f); //�ٴ�

    glShadeModel(GL_SMOOTH);
    float mat0_ambient1[] = { 0.0, 0.0, 0.0 };
    float mat0_diffuse1[] = { 0.0, 0.0, 0.6 };
    float mat0_specular1[] = { 0.2, 0.2, 0.2 };
    float mat0_shininess1 = 128;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat0_ambient1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular1);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat0_shininess1);
    glPushMatrix();
    glTranslatef(0.0, 1.0f, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 1.0, 0.0);
    drawCube(1.0f, 5.0f, 1.0f); //�� ��

    float mat0_ambient2[] = { 0.2, 0.2, 0.2 };
    float mat0_diffuse2[] = { 0.0, 0.6, 0.6 };
    float mat0_specular2[] = { 0.2, 0.2, 0.2 };
    float mat0_shininess2 = 32;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat0_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat0_shininess2);
    glPushMatrix();
    glTranslatef(0.0, 5.0f, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glutSolidSphere(1.0, 100, 100); //��
    
    float mat0_ambient3[] = { 0.2, 0.2, 0.2 };
    float mat0_diffuse3[] = { 0.6, 0.0, 0.0 };
    float mat0_specular3[] = { 0.2, 0.2, 0.2 };
    float mat0_shininess3 = 32;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat0_ambient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular3);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat0_shininess3);
    glPushMatrix();
    drawCube(1.0f, 5.0f, 1.0f); //�� �Ʒ�
   
    glShadeModel(GL_FLAT);
    float mat0_ambient4[] = { 0.0, 0.0, 0.0 };
    float mat0_diffuse4[] = { 0.8, 0.8, 0.0 };
    float mat0_specular4[] = { 0.4, 0.4, 0.0 };
    float mat0_shininess4 = 3;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat0_ambient4);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse4);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular4);
    glMaterialfv(GL_FRONT, GL_SHININESS, &mat0_shininess4);
    glPushMatrix();
    glTranslatef(-0.5 + finger, 5.0, 0.0);
    drawCube(0.1f, 2.0f, 1.0f);
    glPopMatrix();
    //�հ��� 1

    glPushMatrix();
    glTranslatef(0.5 - finger, 5.0, 0.0);
    drawCube(0.1f, 2.0f, 1.0f);
    glPopMatrix();
    //�հ��� 2


    glPopMatrix();//�� �Ʒ�
    glPopMatrix();//��
    glPopMatrix();//�� ��
    glPopMatrix();//�ٴ�

}

void Keyboard(unsigned char key, int x, int y)
{
    // Complete implementation...   

    switch (key) {
    case '1':
        shoulder = (shoulder + 5) % 360;
        break;
    case '2':
        shoulder = (shoulder - 5) % 360;
        break;
    case '3':
        if (elbow >= 125) break;
        elbow = (elbow + 5) % 360;
        break;
    case '4':
        if (elbow <= -125) break;
        elbow = (elbow - 5) % 360;
        break;
    case '5':
        if (finger >= 0.5) break;
        finger = (finger + 0.1);
        break;
    case '6':
        if (finger <= 0.01) break;
        finger = (finger - 0.1);
        break;
    case 27:
        exit(0);
        break;
    default:
        break;

    }
    glutPostRedisplay();
}

void drawCube(float sx, float sy, float sz)
{
    glPushMatrix();
    glTranslatef(0.0, sy * 0.5, 0.0);
    glScalef(sx, sy, sz);
    glutSolidCube(1.0);
    glPopMatrix();
}

void Reshape(int w, int h)
{
    // ����Ʈ ��ȯ
    glViewport(0, 0, w, h);
    Width = w;
    Height = h;
}

void SetupViewVolume()
{
    // ���� ���� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (double)Width / (double)Height, 1.0, 10000.0);
}

void SetupViewTransform()
{
    // �� �� ����� ���� ��ķ� �ʱ�ȭ, M = I
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // �� ��/�ƿ��� ���� ��ȯ, M = I * T_zoom
    glTranslatef(0.0, 0.0, Zoom);

    // ���ο� ȸ���� ����, M = I * T_zoom * R_new
    glRotatef(Angle, Axis[0], Axis[1], Axis[2]);

    // ���� ȸ���� ����, M = I * T_zoom * R_new * R_old   //   R_n .... * R3 * R2 * R1
    glMultMatrixf(RotMat);

    // ȸ�� ��� ����, R_old = R_new * R_old
    glGetFloatv(GL_MODELVIEW_MATRIX, RotMat);
    RotMat[12] = RotMat[13] = RotMat[14] = 0.0;

    // �̵� ��ȯ�� ����, M = I * T_zoom * R_new * R_old * T_pan
    glTranslatef(Pan[0], Pan[1], Pan[2]);
}

void RenderFloor()
{
    glDisable(GL_LIGHTING);
    glColor3f(0.7f, 0.7f, 0.7f);
    for (int x = -10; x <= 10; x++)
    {
        if (x == 0)
            continue;
        glBegin(GL_LINES);
        glVertex3f((float)x, 0.0, -10.0f);
        glVertex3f((float)x, 0.0, 10.0f);
        glVertex3f(-10.0f, 0.0, (float)x);
        glVertex3f(10.0f, 0.0, (float)x);
        glEnd();
    }

    glLineWidth(2.0f);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0, 10.0f);
    glEnd();
    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}

void Mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        StartPt[0] = x;
        StartPt[1] = y;
        if (button == GLUT_LEFT_BUTTON)
            ManipulateMode = 1;   // ȸ��

        if (button == GLUT_RIGHT_BUTTON)
            ManipulateMode = 2;   // �̵�
    }
    if (state == GLUT_UP)
    {
        ManipulateMode = 0;   // ����
        StartPt[0] = StartPt[1] = 0;
        Angle = 0.0;
    }
}

void Motion(int x, int y)
{
    // ȸ����� ȸ�� ���� ���
    if (ManipulateMode == 1)
    {
        // ���� �� ���� ��ǥ ���
        float px, py, pz, qx, qy, qz;
        GetSphereCoord(StartPt[0], StartPt[1], &px, &py, &pz);
        GetSphereCoord(x, y, &qx, &qy, &qz);

        // ȸ�� ��� ���� ���
        Axis[0] = py * qz - pz * qy;
        Axis[1] = pz * qx - px * qz;
        Axis[2] = px * qy - py * qx;
        Angle = 0.0;
        float len = Axis[0] * Axis[0] + Axis[1] * Axis[1] + Axis[2] * Axis[2];
        if (len > 0.0001) // ���� ���� �̻� ó��
            Angle = acos(px * qx + py * qy + pz * qz) * 180.0f / 3.141592f;
    }

    // �̵� ���� ���
    if (ManipulateMode == 2)
    {
        float dx = (float)(x - StartPt[0]) * 0.01f;
        float dy = (float)(StartPt[1] - y) * 0.01f;
        // ȸ�� ��� �� �����
        // R = 0 4 8   invR = 0 1 2
        //     1 5 9          4 5 6    
        //     2 6 10         8 9 10
        // invR * (dx, dy, 0)
        Pan[0] += RotMat[0] * dx + RotMat[1] * dy;
        Pan[1] += RotMat[4] * dx + RotMat[5] * dy;
        Pan[2] += RotMat[8] * dx + RotMat[9] * dy;
    }

    StartPt[0] = x;   // Update startpt as current position
    StartPt[1] = y;
    glutPostRedisplay();
}

/*!
*   \brief ���콺 ��ũ���� ó���ϴ� �ݹ� �Լ�
*
*   \param button[in]   ���콺 ��ư ����(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
*   \param dir[in]      ��ũ���� ����
*   \param x[in]      ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*   \param y[in]      ���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*/
void MouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0)
        Zoom += 1.0;
    else
        Zoom -= 1.0;
    glutPostRedisplay();
}

void GetSphereCoord(int x, int y, float* px, float* py, float* pz)
{
    *px = (2.0f * x - Width) / Width;
    *py = (-2.0f * y + Height) / Height;

    float r = (*px) * (*px) + (*py) * (*py); // �������κ����� �Ÿ� ���
    if (r >= 1.0f)
    {
        *px = *px / sqrt(r);
        *py = *py / sqrt(r);
        *pz = 0.0f;
    }
    else
        *pz = sqrt(1.0f - r);  // �Ϲ����� ���
}
