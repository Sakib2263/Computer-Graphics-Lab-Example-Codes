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

#include <stdlib.h>
#include<bits/stdc++.h>
#include <stdio.h>

using namespace std;
static int slices = 16;
static int stacks = 16;

#define TOP 8
#define BOTTOM 4
#define RIGHT 2
#define LEFT 1
/* GLUT callback Handlers */
int cx0,cx1,cy0,cy1,cnt=0;
int xmax=140,xmin=-140,ymax=100,ymin=-100;
int boundaryx= 140, boundaryy=100;
int width=640,height=480;
int Xmax=boundaryy/2-1;
int Xmin=-boundaryy/2;
int Ymax=boundaryx/2-1;
int Ymin=-boundaryx/2;
int flag1=0,flag2=0,flag=0;

static void resize(int width, int height)
{
   // const float ar = (float) width / (float) height;
     glViewport (0, 0, (GLsizei) width, (GLsizei) height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void drawAxes()
{


        glBegin(GL_LINES);
		glColor3f(0.5, 0.25, 0.75);

        //glVertex2i(Xmin,100);
        //glVertex2i(Xmax,100);
        //glVertex2i(Xmin,-100);
        //glVertex2i(Xmax,-100);
        //glVertex2i(-140,Ymin);
        //glVertex2i(-140,Ymax);
        //glVertex2i(140,Ymin);
        //glVertex2i(140,Ymax);
        
        glVertex2i(boundaryx, height/2-1);
        glVertex2i(boundaryx,-height/2);
        
        glVertex2i(width/2-1,-boundaryy);
        glVertex2i(-width/2,-boundaryy);
        
        glVertex2i(-boundaryx, height/2-1);
        glVertex2i(-boundaryx,-height/2);
        
        glVertex2i(width/2-1,boundaryy);
        glVertex2i(-width/2,boundaryy);
        

        glEnd();
}

void draw8waySyemmtry(int x,int y,int zone)
{
   glBegin(GL_POINTS);
    if(zone==0)
        glVertex2i(x,y);
    else if(zone==1)
        glVertex2i(y,x);
    else if(zone==2)
        glVertex2i(-y,x);
    else if(zone==3)
        glVertex2i(-x,y);
    else if(zone==4)
        glVertex2i(-x,-y);
    else if(zone==5)
        glVertex2i(-y,-x);
    else if(zone==6)
        glVertex2i(y,-x);
    else if(zone==7)
        glVertex2i(x,-y);
    glEnd();

}




int findZone(int x0,int y0,int x1,int y1)
{
    int dx= x1-x0,dy= y1-y0;
    if(dx>=0 && dy>=0)
    {
        if(abs(dx)>abs(dy))return 0;
        else return 1;
    }
    else if(dx<=0 && dy>=0)
    {
        if(abs(dx)>abs(dy))return 3;
        else return 2;
    }
    else if(dx<=0 && dy<=0)
    {
        if(abs(dx)>abs(dy))return 4;
        else return 5;
    }
    else
    {
        if(abs(dx)>abs(dy))return 7;
        else return 6;
    }
}


void drawLine_0(int x0,int y0,int x1,int y1,int zone)
{
    int dx=x1-x0,dy=y1-y0;
    int x,y,d=2*dy-dx;
    int dE=2*dy,dNE=2*(dy-dx);
    x=x0,y=y0;
    draw8waySyemmtry(x,y,zone);
    while(!(x==x1 && y==y1))
    {
        if(d<0)
        {
            x++;
            d+=dE;
        }
        else
        {
            x++,y++;
            d+=dNE;
        }
        draw8waySyemmtry(x,y,zone);
    }
}



void lineDraw(int x0,int y0,int x1,int y1)
{
    int zone=findZone(x0,y0,x1,y1);
    if(zone==0)
    {
        drawLine_0(x0,y0,x1,y1,0);
    }
    else if(zone==1)
    {
        drawLine_0(y0,x0,y1,x1,1);
    }
    else if(zone==2)
    {
        drawLine_0(y0,-x0,y1,-x1,2);
    }
    else if(zone==3)
    {
        drawLine_0(-x0,y0,-x1,y1,3);
    }
     else if(zone==4)
    {
        drawLine_0(-x0,-y0,-x1,-y1,4);
    }
    else if(zone==5)
    {
        drawLine_0(-y0,-x0,-y1,-x1,5);
    }
    else if(zone==6)
    {
        drawLine_0(-y0,+x0,-y1,+x1,6);
    }
    else if(zone==7)
    {
        drawLine_0(x0,-y0,x1,-y1,7);
    }
}


int makeCode(int x,int y)
{
    int code=0;
    if(y>ymax)
    {
        code+=TOP;
    }
    else if(y<ymin)
    {
        code+=BOTTOM;
    }
    if(x>xmax)
    {
        code+=RIGHT;
    }
    else if(x<xmin)
    {
        code+=LEFT;
    }
    return code;
}

void CohenSutherLand(int x0,int y0,int x1,int y1)
{
    int code0,code1, code;
    int x,y;
    code0=makeCode(x0,y0);
    code1=makeCode(x1,y1);
   while(1)
   {
	  
     if(!(code0|code1))
    {
        //completely accepted
		if(!flag){
        printf("Line completely accepted\n");
		flag++;
		}
        glColor3f(1.0,1.0,0.0);
        glPointSize(8);
        glBegin(GL_POINTS);
        glVertex2i(x0,y0);
        glVertex2i(x1,y1);
        glEnd();
        glPointSize(8);
        glPointSize(2);
        glColor3f(1.0,1.0,0.0);
        lineDraw(x0,y0,x1,y1);
        glPointSize(2);

        return;
    }
    else if(code0 & code1)
    {
		 //completely rejected
		if(!flag){
        printf("Line completely rejected\n");
		flag++;
		}
       
        glPointSize(2);
        glColor3f(1.0,0.0,0.0);
        lineDraw(x0,y0,x1,y1);
        glPointSize(2);

     return;
    }
    else
    { //Partially Accepted
		if(!flag){
        printf("Line Partially Accepted!\n");
		flag++;
		}
        if(code0)
        {
            code=code0;
        }
        else
        {
            code=code1;
        }
        if(code & TOP)
        {
            y=ymax;
            x=x0+round((y-y0)*(x1-x0)/(y1-y0));
        }
        else if(code & BOTTOM)
        {
            y=ymin;
            x=x0+round((y-y0)*(x1-x0)/(y1-y0));
        }
        else if(code & LEFT)
        {
            x=xmin;
            y=y0+round((x-x0)*(y1-y0)/(x1-x0));
        }
        else if(code & RIGHT)
        {
            x=xmax;
            y=y0+round((x-x0)*(y1-y0)/(x1-x0));
        }
        if(code==code0)
        {
            glPointSize(2);
            glColor3f(0.5,0.5,0.5);
        lineDraw(x0,y0,x,y);
        glPointSize(2);

            x0=x;
            y0=y;
            code0=makeCode(x0,y0);
        }
       else if(code==code1)
        {
             glColor3f(0.5,0.5,0.5);
        glPointSize(8);
        glBegin(GL_POINTS);
        glVertex2i(x1,y1);
        glVertex2i(x,y);
        glEnd();
        glPointSize(8);
            glPointSize(2);
            glColor3f(0.5,0.5,0.5);
        lineDraw(x1,y1,x,y);
        glPointSize(2);

            x1=x;
            y1=y;
            code1=makeCode(x1,y1);
        }
    }
   }
}
void mouse(int button,int state,int x,int y)
{
   if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
   {
    if(cnt==0 && flag1==0)
    {

        cx0=x-320;
        cy0=239-y;

        cnt++;
        flag1=1;
        flag2=0;
        flag=0;

    }
    else if (cnt==1)
    {

        cx1=x-320;
        cy1=239-y;
        cnt=0;
        flag1=0;
        flag2=1;
        cout<<"Initial Point-> "<<cx0<<" "<<cy0<<endl;
         cout<<"Next Point-> "<<cx1<<" "<<cy1<<endl;

    }
   }

}
static void display(void)
{
    int x = 10, y = 20;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
     glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);
    glEnd();
    drawAxes();
     glutMouseFunc(mouse);
    glBegin(GL_POINTS);
   // glColor3d(0.5,0.5,0.5);

    //glColor3d(.4,.6,.8);
   if(cnt==0 && flag2==1 && flag1==0)
   {
     CohenSutherLand(cx0,cy0,cx1,cy1);
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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Experiment 01");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
