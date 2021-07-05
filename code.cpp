#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

GLfloat light = 0.25;
GLfloat screen = 0.0;
int situation = 0;

void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void idle(void);
void display(void);
void lightMaterial(void);
void buildWall(void);
void buildLamp(void);
void buildDesk(void);
void buildSeat(void);
void buildBooks(void);
void buildLaptop(void);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(600, 600);

	glutCreateWindow("My Room");

	glClearColor(0, 0, 0, 1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1, 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'1': // laptop power on
		situation = 1;
		break;
	case'2': // laptop power off
		situation = 2;
		break;
	case'3': // turn on the lamp
		situation = 3;
		break;
	case'4': // turn off the lamp
		situation = 4;
		break;
	default:
		printf("error\n");
	}
}

void idle(void)
{
	if (situation == 1) {
		if (screen <= 1.0) {
			Sleep(10);
			screen += 0.01;
		}
	}
	if (situation == 2) {
		if (screen >= 0.0) {
			Sleep(10);
			screen -= 0.01;
		}
	}
	if (situation == 3) {
		light = 0.25;
	}
	if (situation == 4) {
		light = 0.0;
	}
	glutPostRedisplay();
}

void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();

	lightMaterial();

	glTranslatef(0.0, 0.0, 1);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	buildWall();
	
	buildLamp();

	buildDesk();

	buildSeat();

	buildBooks();

	buildLaptop();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void lightMaterial(void)
{
	GLfloat light0position[] = { 0.0, 100.0, -300.0, 1.0 };
	GLfloat light0ambient[] = { 0.2, 0.2, 0.2, 0.3f };
	GLfloat light0diffuse[] = { 1.0, 1.0, 1.0, 0.3 };

	glLightfv(GL_LIGHT0, GL_POSITION, light0position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0diffuse);

	GLfloat light1position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light1_mat1[] = { 0.1, 0.1, 0.1, 0.3 };
	GLfloat light1_diff[] = { 0.1, 0.1, 0.1, 0.3 };

	glLightfv(GL_LIGHT1, GL_POSITION, light1position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_mat1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);

	GLfloat material[] = { light, light, light, 1.0 };

	glMaterialfv(GL_FRONT, GL_EMISSION, material);
}

void buildWall(void)
{
	// back wall
	glColor3f(1.0, 1.0, 0.9);
	glBegin(GL_QUADS);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glEnd();

	// top wall
	glColor3f(1.0, 1.0, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(1, 1, 0.0);
	glVertex3f(-1, 1, 0.0);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glEnd();

	// ground
	glColor3f(1.0, 1.0, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(1, -1, 0.0);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 0.0);
	glEnd();

	// left wall
	glColor3f(1.0, 1.0, 0.7);
	glBegin(GL_QUADS);
	glVertex3f(-1, -1, 0.0);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 0.0);
	glEnd();

	// right wall
	glColor3f(1.0, 1.0, 0.7);
	glBegin(GL_QUADS);
	glVertex3f(1, -1, 0.0);
	glVertex3f(1, 1, 0.0);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glEnd();
}

void buildLamp(void)
{
	// lamp holder
	glColor3f(0.55, 0.27, 0.07);
	glPushMatrix();
	glTranslatef(0.0, 0.99, -0.4);
	glScalef(0.6, 0.02, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();

	// lamp bulb
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.96, -0.4);
	glScalef(0.4, 0.06, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();
}

void buildDesk(void)
{
	glColor3f(0.9, 0.8, 0.4);

	// middle
	glPushMatrix();
	glTranslatef(0.0, -0.2, -0.7);
	glScalef(1.6, 0.02, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	
	// top
	glPushMatrix();
	glTranslatef(0.0, 0.3, -0.7);
	glScalef(1.6, 0.02, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	
	// right
	glPushMatrix();
	glTranslatef(0.8, -0.25, -0.7);
	glScalef(0.02, 1.5, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	// left
	glPushMatrix();
	glTranslatef(-0.8, -0.25, -0.7);
	glScalef(0.02, 1.5, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	// back
	glPushMatrix();
	glTranslatef(0.0, -0.25, -0.7);
	glScalef(1.64, 1.5, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();

	// cabinet
	glPushMatrix();
	glTranslatef(-0.5, -0.6, -0.7);
	glScalef(0.6, 0.8, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3f(0.55, 0.27, 0.07);
	glPushMatrix();
	glTranslatef(-0.25, -0.6, -0.5);
	glScalef(0.02, 0.06, 0.04);
	glutSolidCube(1.0);
	glPopMatrix();
}

void buildSeat(void)
{
	// top
	glColor3f(0.7, 0.8, 0.4);
	glPushMatrix();
	glTranslatef(0.3, -0.5, -0.5);
	glScalef(0.4, 0.04, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();

	// legs
	glPushMatrix();
	glTranslatef(0.49, -0.75, -0.31);
	glScalef(0.02, 0.5, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.49, -0.75, -0.49);
	glScalef(0.02, 0.5, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.11, -0.75, -0.31);
	glScalef(0.02, 0.5, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.11, -0.75, -0.49);
	glScalef(0.02, 0.5, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();
}

void buildBooks(void)
{
	glColor3f(0.5, 0.5, 0.0);
	glPushMatrix();
	glTranslatef(0.76, 0.45, -0.6);
	glScalef(0.04, 0.3, 0.15);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3f(0.5, 0.0, 0.5);
	glPushMatrix();
	glTranslatef(0.7, 0.4, -0.6);
	glScalef(0.08, 0.2, 0.12);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3f(0.0, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(0.64, 0.43, -0.6);
	glScalef(0.02, 0.26, 0.15);
	glutSolidCube(1.0);
	glPopMatrix();
}

void buildLaptop(void)
{
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.3, -0.16, -0.45);
	glScalef(0.4, 0.02, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3f(0.0, 0.0, screen);
	glPushMatrix();
	glTranslatef(0.3, -0.05, -0.56);
	glScalef(0.4, 0.2, 0.02);
	glutSolidCube(1.0);
	glPopMatrix();
}

