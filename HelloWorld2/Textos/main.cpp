
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

int win = 50;
float largura;
float altura;
float aspecto;
float angle = 1;
char texto[10];

void idle(){
    glutPostRedisplay();
}

void desenhaTexto(char *string){

    glPushMatrix();
        glRasterPos2f(-10,-40);

    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);

    //glScalef(2.0f,2.0f,0.0f);
    glPopMatrix();
}

void alteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;

    if (w == 0)
        w = 1;
    largura = w/2;
    altura = h;
    aspecto = (float) largura/altura;


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-win*aspecto, win*aspecto, -win, win);
}


void desenhaCasa(){
    glColor3f(0.0f, 0.0f, 1.0f);

	glPushMatrix();
	//glRotatef(angle++, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);

	glVertex2f(-15.0f, -15.0f);
	glVertex2f(-15.0f, 5.0f);
	glVertex2f(15.0f, 5.0f);
	glVertex2f(15.0f, -15.0f);

	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glVertex2f(-4.0f, -14.5f);
	glVertex2f(-4.0f, 0.0f);
	glVertex2f(4.0f, 0.0f);
	glVertex2f(4.0f, -14.5f);

	glVertex2f(7.0f, -5.0f);
	glVertex2f(7.0f, -1.0f);
	glVertex2f(13.0f, -1.0f);
	glVertex2f(13.0f, -5.0f);

	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_LINES);

	glVertex2f(7.0f, -3.0f);
	glVertex2f(13.0f, -3.0f);
	glVertex2f(10.0f, -1.0f);
	glVertex2f(10.0f, -5.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);

	glVertex2f(-15.0f, 5.0f);
	glVertex2f(0.0f, 17.0f);
	glVertex2f(15.0f, 5.0f);


	glEnd();

    glPopMatrix();
}

void fazMoldura(){
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-win*aspecto, -win);
        glVertex2f(-win*aspecto, win);
        glVertex2f(win*aspecto, win);
        glVertex2f(win*aspecto, -win);
    glEnd();
    glLineWidth(1);
}
void desenha()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, largura, altura);

    //glTranslatef(10.0f, 10.0f,0.0f);
    desenhaCasa();
    fazMoldura();
    desenhaTexto(texto);

    glViewport(largura, 0, largura, altura);


    desenhaCasa();
    fazMoldura();

	glFlush();
}

void inicializa()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void moveMouse(int x, int y){


    sprintf(texto,"(%d,%d)",x,y);
    glutPostRedisplay();
}

void desenha1(){

float ang;

glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0f, 1.0f, 1.0f);

glPointSize(5.0f);

glBegin(GL_POINTS);

for(ang=0; ang<2*M_PI; ang+= M_PI/7)
    glVertex2f(20*cos(ang), 20*sin(ang));


glEnd();

glFlush();

}


int main(void)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Primeiro Programa");

    glutDisplayFunc(desenha);
    //glutDisplayFunc(desenha1);
    inicializa();
    glutReshapeFunc(alteraTamanhoJanela);

    glutPassiveMotionFunc(moveMouse);

    //glutTimerFunc(33, timer,1);
    glutMainLoop();

}




