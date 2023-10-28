#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

float x = 5;
float y = 5;
float angle = 0;
float translacaoX = 0;
float translacaoY = 0;
float stepX = 1;
float stepY = 1;
bool loopFoguete = false;

const int wJanela = 1500;
const int hJanela = 1000;

const float wViewPort = 75;
const float hViewPort = 75;
void inicializa()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void alteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;

    if (w == 0)
        w = 1;

    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w<=h)
        gluOrtho2D(-wViewPort, wViewPort, -hViewPort*h/w, hViewPort*h/w);
    else
        gluOrtho2D(-wViewPort*w/h, wViewPort*w/h,-hViewPort,hViewPort);
}

void bico(){

glColor3f(0.0f,1.0f,0.0f);

glBegin(GL_TRIANGLES);
	glVertex2f(x+x/2,(y*4)+(y/2));
	glVertex2f(x,y*3);
	glVertex2f(x*2,y*3);
glEnd();

}

void corpo(){
    glColor3f(0.0f,0.0f,1.0f);

    glBegin(GL_QUADS);

    glVertex2f(x,y);
    glVertex2f(x,y*3);
    glVertex2f(x*2,y*3);
    glVertex2f(x*2,y);

    glEnd();

}
void asaDireita(){

glColor3f(1.0f,0.0f,0.0f);

    glBegin(GL_TRIANGLES);
    glVertex2f(x*2,y*2);
    glVertex2f(x*2,y);
    glVertex2f(x*3,y);
    glEnd();

}

void asaEsquerda(){
    glBegin(GL_TRIANGLES);
    glVertex2f(-x,y);
    glVertex2f(x,y*2);
    glVertex2f(x,y);
    glEnd();

}
void desenhaFoguete(){

    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    bico();
    corpo();
    asaDireita();
    asaEsquerda();
    glPopMatrix();

    glFlush();


}

void rotacao(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            angle += 90.0f;
        } else if (button == GLUT_RIGHT_BUTTON) {
            angle -= 90.0f;
        }
        glutPostRedisplay();
    }

}

void specialFunc(int key, int a, int b){

switch(key){

case GLUT_KEY_UP:
    translacaoY+= 5;
    break;
case GLUT_KEY_DOWN:
    translacaoY-=5;
    break;
case GLUT_KEY_LEFT:
    translacaoX-=5;
    break;
case GLUT_KEY_RIGHT:
    translacaoX+=5;
}

glutPostRedisplay();
}

void ajusteTranslacao(){
    if (translacaoX < -wViewPort - wViewPort/2) {
        translacaoX = -wViewPort- wViewPort/2;
    } else if (translacaoX > wViewPort + wViewPort/2) {
        translacaoX = wViewPort + wViewPort/2;
    }

    if (translacaoY > hViewPort) {
        translacaoY = hViewPort;
    } else if (translacaoY < -hViewPort) {
        translacaoY = -hViewPort;
    }
}

void ajustePosicao(){
    if (x < -wViewPort - x/2) {
        x = -wViewPort - x/2;
    } else if (x > wViewPort + x/2) {
        x = wViewPort + x/2;
    }

    if (y < -hViewPort) {
        y = -hViewPort;
    } else if (y > hViewPort) {
        y = hViewPort;
    }

}
void desenha(){
     glClear(GL_COLOR_BUFFER_BIT);

     glPushMatrix();


     ajusteTranslacao();
     glTranslatef(translacaoX,translacaoY,0.0f);
     glRotatef(angle,0.0f,0.0f,1.0f);

     ajustePosicao();
     desenhaFoguete();

     glPopMatrix();

}
void anda(int value) {

    if(!loopFoguete)
        return;

    translacaoX += stepX;
    translacaoY += stepY;

    stepX = (translacaoX + stepX > wViewPort+wViewPort/2 || translacaoX + stepX < -wViewPort - wViewPort/2) ? -stepX : stepX;
    stepY = (translacaoY + stepY > hViewPort || translacaoY + stepY < -hViewPort) ? -stepY : stepY;

    translacaoX = (translacaoX > wViewPort+wViewPort/2) ? (wViewPort +wViewPort/2) : (translacaoX < -wViewPort - wViewPort/2) ? (-wViewPort-wViewPort/2) : translacaoX;
    translacaoY = (translacaoY > hViewPort) ? hViewPort : (translacaoY < -hViewPort) ? -hViewPort : translacaoY;

    glutPostRedisplay();
    glutTimerFunc(33, anda, 0);
}
void movimentacao(unsigned char key, int a, int b){

    if(key=='a'){
        loopFoguete = true;
        anda(0);
    }

    if(key=='p'){
        loopFoguete=false;
    }
}
int main(void)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wJanela,hJanela);
    glutCreateWindow("Foguete");

    glutDisplayFunc(desenha);
    inicializa();
    glutReshapeFunc(alteraTamanhoJanela);

    glutMouseFunc(rotacao);
    glutSpecialFunc(specialFunc);

    glutKeyboardFunc(movimentacao);
    glutMainLoop();

}
