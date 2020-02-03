/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <bits/stdc++.h>
using namespace std;

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

static void resize(int width, int height){
	const float ar = (float) width / (float) height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-320, 319, -240, 239, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;
}

int findZone (int x0, int y0, int x1, int y1) {
	int dx = x1 - x0, dy = y1 - y0;
	if (dx >= 0 and dy >= 0) {
		if (dx >= dy) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else if (dx < 0 and dy >= 0) {
		if (-dx >= dy) {
			return 3;
		}
		else {
			return 2;
		}
	}
	else if (dx < 0 and dy < 0) {
		if (-dx >= -dy) {
			return 4;
		}
		else {
			return 5;
		}
	}
	else {
		if (dx >= -dy) {
			return 7;
		}
		else {
			return 6;
		}
	}
}

void drawPixel (int x, int y, int zone) {
	switch (zone) {
		case 0:
			glColor3d(1,0,0);
			glVertex2i(x, y);
			break;
		case 1:
			glColor3d(0,1,0);
			glVertex2i(y, x);
			break;
		case 2:
			glColor3d(0,0,1);
			glVertex2i(-y, x);
			break;
		case 3:
			glColor3d(1,1,0);
			glVertex2i(-x, y);
			break;
		case 4:
			glColor3d(1,0,1);
			glVertex2i(-x, -y);
			break;
		case 5:
			glColor3d(1,1,1);
			glVertex2i(-y, -x);
			break;
		case 6:
			glColor3d(0,1,1);
			glVertex2i(y, -x);
			break;
		case 7:
			glColor3d(1,1,.25);
			glVertex2i(x, -y);
			break;
	}
}

void drawLine0 (int x0, int y0, int x1, int y1, int zone) {
	int dx = x1 - x0, dy = y1 - y0;
	int x = x0, y = y0, d = 2 * dy - dx;
	int de = 2 * dy, dne = 2 * (dy - dx);
	while (x <= x1) {
		drawPixel (x, y, zone);
		if (d < 0) {
			++x;
			d += de;
		}
		else {
			++x, ++y;
			d += dne;
		}
	}
}

void drawLine (int x0, int y0, int x1, int y1) {
	int zone = findZone(x0, y0, x1, y1);
	//printf("zone = %d\n", zone);
	switch (zone) {
		case 0:
			drawLine0(x0, y0, x1, y1, zone);
			break;
		case 1:
			drawLine0(y0, x0, y1, x1, zone);
			break;
		case 2:
			drawLine0(y0, -x0, y1, -x1, zone);
			break;
		case 3:
			drawLine0(-x0, y0, -x1, y1, zone);
			break;
		case 4:
			drawLine0(-x0, -y0, -x1, -y1, zone);
			break;
		case 5:
			drawLine0(-y0, -x0, -y1, -x1, zone);
			break;
		case 6:
			drawLine0(-y0, x0, -y1, x1, zone);
			break;
		case 7:
			drawLine0(x0, -y0, x1, -y1, zone);
			break;
	}
}

int call;
int x_0, x_1, y_0, y_1;

void myMouse (int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON and state == GLUT_UP) {
		if (call % 2 == 0) {
			x_0 = x - 320, y_0 = y - 240;
			y_0 *= -1;
		}
		else if (call % 2 == 1) {
			x_1 = x - 320, y_1 = y - 240;
			y_1 *= -1;
		}
		printf("%d %d\n", x, y);
		if (call % 2 == 1) {
			printf("zone = %d\n", findZone(x_0, y_0, x_1, y_1));
		}
		++call;
	}
}

static void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1,1,1);
	glBegin(GL_LINES);
	glVertex2i(-320, 0);
	glVertex2i(319, 0);
	glVertex2i(0, -240);
	glVertex2i(0, 239);
	glEnd();


	glBegin(GL_POINTS);

	glutMouseFunc(myMouse);
	glutMouseFunc(myMouse);
	if (call % 2 == 0) {
		drawLine(x_0, y_0, x_1, y_1);
	}

	glEnd();
	glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27 :
		case 'q':
			exit(0);
			break;

		case '+':
			slices++;
			stacks++;
			break;

		case '-':
			if (slices>3 && stacks>3)
			{
				slices--;
				stacks--;
			}
			break;
	}

	glutPostRedisplay();
}

static void idle(void)
{
	glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(10,10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Experiment 01");
	
	printf("zone 0 - RED\nzone 1 - GREEN\nzone 2 - BLUE\nzone 3 - YELLOW\nzone 4 - PURPLE\nzone 5 - WHITE\nzone 6 - SKYBLUE\nzone 7 - LIGHT YELLOW\n");
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();

	return EXIT_SUCCESS;
}
