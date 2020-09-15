#include <stdlib.h>
#include <string.h>
#include <gl/glut.h>
#include <math.h>

int Width = 600, Height = 600;

// Declaration of call back functions
void Render();
void Reshape(int w, int h);

int main(int argc, char **argv)
{
	// Initialize OpenGL.
	glutInit(&argc, argv);

	// Initialize window size and its position when it is created.
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);

	// Initialize OpenGL display modes for double buffering, RGB color, depth buffer enabling.
	glutInitDisplayMode(GLUT_SINGLE);

	// Create OpenGL window.
	glutCreateWindow("A SimpleGL Program");

	// Register call back functions.
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);

	// Enter the message loop.
	glutMainLoop();
	return 0;
}


void Reshape(int w, int h)
{
	// View-port transformation
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}


void SetupViewTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
}

void SetupViewVolume()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Width, 0, Height, -100.0, 100.0);
}

void Render()
{
	// Clear color buffer with specified clear color (R, G, B, A)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Set up view transformation
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, Width, 0.0, Height);

	// Perform modeling transformation
	glMatrixMode(GL_MODELVIEW);

	switch (1)
	{ 
	case 1:
		// Test 1: glColor*(...).
		{
			// Draw a triangle with red color.
			
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2i(150, 200);
			//glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2i(350, 200);
			//glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2i(250, 350);
			glEnd();

			// Draw a triangle with green color.
 			float color[3] = {0.0f, 1.0f, 0.0f};
 			glColor3fv(color);
 			glBegin(GL_TRIANGLES);
 			glVertex2i(150, 300);
 			glVertex2i(250, 150);
 			glVertex2i(350, 300);
 			glEnd();
		}
		break;

	case 2:
		// Test 2: glBlendFunc(...).
		{
			// Draw a triangle with red color.
			glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
			glBegin(GL_TRIANGLES);
			glVertex2i(150, 200);
			glVertex2i(350, 200);
			glVertex2i(250, 350);
			glEnd();

			glEnable(GL_BLEND);
			//glBlendFunc(GL_ONE, GL_ZERO);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Draw a triangle with green color.
			glColor4f(0.0, 1.0, 0.0, 1.0);
			glBegin(GL_TRIANGLES);
			glVertex2i(150, 300);
			glVertex2i(250, 150);
			glVertex2i(350, 300);
			glEnd();

			glDisable(GL_BLEND);
		}
		break;

	case 3:
		// Test 3: glPointSize(...).
		{
			// Set point attributes
			glColor3f(1.0f, 0.0f, 0.0f);
			glPointSize(15.0f);
			
			// Draw points
			glBegin(GL_POINTS);
			glVertex2i(150, 200);
			glVertex2i(350, 200);
			glVertex2i(250, 350);
			glEnd();

			// Set point attributes
			glColor3f(0.0, 1.0, 0.0);
			glPointSize(30.0f);

			// Draw points
			glBegin(GL_POINTS);
			glVertex2i(150, 300);
			glVertex2i(250, 150);
			glVertex2i(350, 300);
			glEnd();
		}
		break;

	case 4:
		// Test 4: glLineWidth(), glLineStipple().
		{
			// Set line attributes
			glColor3f(1.0f, 1.0f, 1.0f);
			glLineWidth(5.0f);

			// Draw a triangle with solid line.
			glBegin(GL_LINE_LOOP);
			glVertex2i(150, 200);
			glVertex2i(350, 200);
			glVertex2i(250, 350);
			glEnd();

			glEnable(GL_LINE_STIPPLE);
			glLineStipple(5, 0xf0f0);
			// Draw a triangle with dot-line.
			glBegin(GL_LINE_LOOP);
			glVertex2i(150, 300);
			glVertex2i(250, 150);
			glVertex2i(350, 300);
			glEnd();
			glDisable(GL_LINE_STIPPLE);
		}
		break;

	case 5:
		// Test 5: glPolygonMode().
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_LINE);

			// Draw a triangle
			glBegin(GL_TRIANGLES);
			glVertex2i(150, 200);
			glVertex2i(350, 200);
			glVertex2i(250, 350);
			glEnd();

			// Draw a triangle
			glBegin(GL_TRIANGLES);
			glVertex2i(150, 300);
			glVertex2i(350, 300);
			glVertex2i(250, 150);
			glEnd();
		}
		break;

	case 6:
		// Test 6: glPolygonStipple().
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			glEnable(GL_POLYGON_STIPPLE);
			GLubyte fly[] = {
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60, 
				0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20, 
				0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
				0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22, 
				0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 
				0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
				0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 
				0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC, 
				0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
				0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0, 
				0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0, 
				0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
				0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08, 
				0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08, 
				0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08};

				glPolygonStipple(fly);
				// Draw a triangle with dot-line.
				glBegin(GL_TRIANGLES);
				glVertex2i(150, 300);
				glVertex2i(250, 150);
				glVertex2i(350, 300);
				glEnd();
				glDisable(GL_POLYGON_STIPPLE);
		}
		break;

	case 7:
		// Test 7: anti-aliasing...
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			glLineWidth(5.0);

			glBegin(GL_LINES);
			for (double theta = 0.0; theta <= 180.0; theta += 10.0)
			{
				double x = 300 + 300 * cos(theta * 3.141592 / 180);
				double y = 300 + 300 * sin(theta * 3.141592 / 180);	
				glVertex3f(300, 300.0, 0.0);
				glVertex3f(x, y, 0.0);
			}
			glEnd();

			glEnable(GL_LINE_SMOOTH);
 			glEnable(GL_BLEND);
 			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_LINES);
			for (double theta = 180.0; theta <= 360.0; theta += 10.0)
			{
				double x = 300 + 300 * cos(theta * 3.141592 / 180);
				double y = 300 + 300 * sin(theta * 3.141592 / 180);	
				glVertex3f(300, 300.0, 0.0);
				glVertex3f(x, y, 0.0);
			}
			glEnd();

			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_BLEND);		

		}
		break;		
	}

	glFinish();
}