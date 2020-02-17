#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string>
#include <math.h>
#include <algorithm>
#define BASE_SPEED 0
#define GRAVITY 0.1

using namespace std;

static int slices = 16;
static int stacks = 16;
bool check;
int xx = 0, r = 50, yy=188;
double speed = BASE_SPEED;

/* GLUT callback Handlers */
void draw8way(int x, int y, int a, int b){
    glVertex2i(x+a, y+b); 
    glVertex2i(y+a, x+b); 
    glVertex2i(-y+a, x+b); 
    glVertex2i(-x+a, y+b); 
    glVertex2i(-x+a, -y+b);
    glVertex2i(-y+a, -x+b);
    glVertex2i(y+a, -x+b); 
    glVertex2i(x+a, -y+b); 
}

void draw4way(int x, int y, int a, int b){
    glVertex2i(x+a, y+b); 
    glVertex2i(x+a, -y+b); 
    glVertex2i(-x+a, y+b); 
    glVertex2i(-x+a, -y+b); 
}

void drawcircle(int x0, int y0, int r){
    int x=0;
    int y=r;
    int d = 5 - 4*r;
    draw8way(x, y, x0, y0);
    while(x<y){
        if(d<0){
            d+=8*x+12;
            x++;
        }
        else{
            d+=8*x-8*y+20;
            x++;
            y--;
        }
        draw8way(x, y, x0, y0);
    }
}

void drawellipse(int x0, int y0, int a, int b){
    int x = 0;
    int y = b;
    double d = b*b - (a*a*b) + (0.25*a*a);
    draw4way(x, y, x0, y0);
    while(a*a*(2*y-1)>2*b*b*(x+1)){
        if(d < 0){ //dE
            d+=(2*x+3)*b*b;
            x++;
        }
        else{ //dSE
            d+=b*b*(2*x+3)+(2-2*y)*a*a;
            x++;
            y--;
        }
        draw4way(x, y, x0, y0);
    }

    while(y>0){
        if(d>0){ //dS
            d+=a*a*(3-2*y);
            y--;
        }
        else{ //dSE
            d+= b*b*(2*x+2) + a*a*(3-2*y);
            x++;
            y--;
        }
        draw4way(x, y, x0, y0);
    }
}

void draw_sponge(){
    glEnd();
    int x = 0, y = -190;
    int a = r, b = r;
    for(int i=0;i<10; i++){
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
        drawellipse(x,y,a,b);
        a+=5;
        b = (r*r)/a;
        y = -240+b;
        glEnd();
        glutSwapBuffers();
    }
    for(int i=0;i<10; i++){
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
        drawellipse(x,y,a,b);
        a-=5;
        b = (r*r)/a;
        y = -240+b;
        glEnd();
        glutSwapBuffers();
    }
    glBegin(GL_POINTS);
}

static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    // glVertex2i(-320, 0);
    // glVertex2i(319, 0);
    // glVertex2i(0, -240);
    // glVertex2i(0, 239);
    glEnd();
    glBegin(GL_POINTS);
    //write your code here
    if(yy+r<=238 && yy-r>=-238){
        drawcircle(xx,yy,r);
        yy-=speed;
        speed+=GRAVITY;
    }
    else{
        draw_sponge();
        speed-=GRAVITY;
        speed = -speed;
        yy-=speed;
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

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Circle bounce");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
