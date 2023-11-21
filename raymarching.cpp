#include <glut.h>

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_POINTS);
    glVertex3f(-0.5,-0.5,0.0);
    glVertex3f(0.0,0.5,0.0);
    glVertex3f(0.5,-0.5,0.0);
    glVertex3f(0.5,0,0.0);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {

    // инициализация
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("Урок 1");

    // регистрация обратных вызовов
    glutDisplayFunc(renderScene);

    // Основной цикл GLUT
    glutMainLoop();

    return 1;
}