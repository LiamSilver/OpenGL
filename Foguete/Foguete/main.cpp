#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

float largura = 50;
float altura = 50;
float angle = 90;

void inicializa()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void desenhaFoguete(){

     glColor3f(0.0f, 0.0f, 1.0f);



}

void desenha(){
     glClear(GL_COLOR_BUFFER_BIT);
     glViewport(0, 0, largura, altura);
     desenhaFoguete();


}
int main(void)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Foguete");

    glutDisplayFunc(desenha)
    inicializa();

    glutMainLoop();

}
