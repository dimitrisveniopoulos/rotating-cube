#include <GL/glut.h>
#include <GL/glu.h>

const int a = 6;
const int b = 90;
const int vx = 1;
const int vy = 0;
const int vz = 1;
float theta = 1;
float s = 1;
int f = 1;
int flag = 1;

void initialize()
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(400,50);
    glutInitWindowSize(700,700);
    glutCreateWindow ("Rotating Cube");
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50,-150,150);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}


void display()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    if (flag)
    {
        glTranslatef(0,0,-b);
        glRotatef(theta,vx,vy,vz);
        glScalef(s,s,s);
        glTranslatef(0,0,b);
    }
    else
    {
        glTranslatef(0,0,-8*b/10);
        glRotatef(theta,vx,vy,vz);
        glTranslatef(0,0,8*b/10);

        glTranslatef(0,0,-b);
        glScalef(s,s,s);
        glTranslatef(0,0,b);
    }

    glTranslatef(0,0,-b);

    // front side
    glPushMatrix();
    glColor3ub(0, 255, 0);
    glTranslatef(0,0,a/2);
    glScalef(a/2,a/2,1);
    glTranslatef(0,0,-1);
    glCallList(1);
    glPopMatrix();

    // back side
    glPushMatrix();
    glColor3ub(0, 0, 255);
    glTranslatef(0,0,-a/2);
    glScalef(a/2,a/2,1);
    glTranslatef(0,0,-1);
    glCallList(1);
    glPopMatrix();

    // right side
    glPushMatrix();
    glColor3ub(255, 0, 0);
    glTranslatef(a/2,0,0);
    glRotatef(90, 0, 1, 0);
    glScalef(a/2,a/2,1);
    glTranslatef(0,0,-1);
    glCallList(1);
    glPopMatrix();

    // left side
    glPushMatrix();
    glColor3ub(255, 255, 0);
    glTranslatef(-a/2,0,0);
    glRotatef(90,0,1,0);
    glScalef(a/2,a/2,1);
    glTranslatef(0,0,-1);
    glCallList(1);
    glPopMatrix();

    // top side
    glPushMatrix();
    glColor3ub(255,0,127);
    glTranslatef(0,a/2,0);
    glRotatef(90,1,0,0);
    glScalef(a/2,a/2,1);
    glTranslatef(0,0,-1);
    glCallList(1);
    glPopMatrix();

    // bottom side
    glPushMatrix();
    glColor3f(0, 255, 255);
    glTranslatef(0,-a/2,0);
    glRotatef(90,1,0,0);
    glScalef(a/2,a/2,1);
    glTranslatef(0,0,-1);
    glCallList(1);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void idle()
{
    theta += 0.2;
    if (s >= 3)
        f = -1;
    else if (s <= 1)
        f = 1;
    s += f * 0.002;
    glutPostRedisplay();
}

void menu(int id){

    if (id == 1)
        exit(0);
    else if (id == 2)
        flag = 1;
    else if (id == 3)
        flag = 0;

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    initialize();

    glNewList(1,GL_COMPILE);
    glBegin(GL_POLYGON);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glEnd();
    glEndList();

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutCreateMenu(menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutAddMenuEntry("Quit", 1);
    glutAddMenuEntry("(0,0,-b)", 2);
    glutAddMenuEntry("(0,0,-8b/10)", 3);

    glutMainLoop();

    return 0;
}
