#include <iostream>
#include <vector>
#include <memory>

#include <GL/glut.h>
#include <math.h>

#include "transform.h"
#include "constantes.h"
#include "mathdef.h"

#define EDICAO 0
#define MANIPULACAO 1

#define PI 3.14159f


GLint gJanelaPrincipal = 0;
GLint janelaLargura = 400, janelaAltura = 400;
GLfloat ortho2D_minX = -400.0f, ortho2D_maxX = 400.0f, ortho2D_minY = -400.0f, ortho2D_maxY = 400.0f;
GLfloat orthoLargura = ortho2D_maxX - ortho2D_minX;
GLfloat orthoAltura  = ortho2D_maxY - ortho2D_minY;

float angleX = 0.0;
float angleY = 0.0;
float angleZ = 0.0;

VART::Transform transform;
VART::Point4D eye(20.0f, 20.0f, 20.0f);
VART::Point4D center(0.0f, 0.0f, 0.0f);

void ligarLuz();
void drawCube(GLfloat translacao[], GLfloat escala[], GLfloat angulo[]);

GLfloat translacaoCubo[] = {1.0f, 1.0f, 1.0f};
GLfloat escalaCubo[]     = {2.0f, 2.0f, 2.0f};
GLfloat anguloCubo[]     = {0.0f, 0.0f, 0.0f};
GLfloat translacaoMundo[] = {0.0f, 0.0f, 0.0f};
GLfloat escalaMundo[]     = {1.0f, 1.0f, 1.0f};


void inicializacao(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);

	//ligarLuz();

	//glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);

	transform.MakeIdentity();
}

void exibicaoPrincipal(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.GetX(), eye.GetY(), eye.GetZ(), center.GetX(), center.GetY(), center.GetZ(), 0.0f, 1.0f, 0.0f);
	
	SRU();

	drawCube(translacaoCubo, escalaCubo, anguloCubo);

	// chão
	glPushMatrix();
		glScalef(escalaMundo[0], escalaMundo[1], escalaMundo[2]);
		glTranslated(translacaoMundo[0], translacaoMundo[1], translacaoMundo[2]);
		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f (0.0f, 0.0f,  0.0f);
			glVertex3f(100.0f, 0.0f,  0.0f);
			glVertex3f(100.0f, 0.0f, 100.0f);
			glVertex3f( 0.0f, 0.0f, 100.0f);
		glEnd();
	glPopMatrix();

	///////
	glutSwapBuffers();
}

void drawCube(GLfloat translacao[], GLfloat escala[], GLfloat angle[]) {
	
	//glEnable(GL_LIGHTING);
	glPushMatrix();
		glScalef(escala[0], escala[1], escala[2]);
		glTranslated(translacao[0], translacao[1], translacao[2]);
		glRotatef(angle[2], 0.0f, 0.0f, 1.0f);
		glRotatef(angle[0], 1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);									// Draw A Quad
		glColor3f(0.0f,1.0f,0.0f);						// Set The Color To Green
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Bottom Right Of The Quad (Top)
		glColor3f(1.0f,0.5f,0.0f);						// Set The Color To Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Front)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Front)
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Top Right Of The Quad (Back)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Top Left Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Bottom Left Of The Quad (Back)
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Bottom Right Of The Quad (Back)
		glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Left)
		glColor3f(1.0f,0.0f,1.0f);						// Set The Color To Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Right)
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Right)

	glEnd();	
	glPopMatrix();
	//glDisable(GL_LIGHTING);
}

void ligarLuz() {
	float posLight[] = { 5.0f, 5.0f, 10.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, posLight);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}


void rotateX(GLfloat n) {
	int nn = ((int)n) % 360;
	double angle = (2 * PI / 360) * nn;
	double y = cos(angle);
	double z = sin(angle);
	eye.SetY(y*20);
	eye.SetZ(z*20);
}

void rotateY(GLfloat n) {
	int nn = ((int)n) % 360;
	double angle = (2 * PI / 360) * nn;
	double x = cos(angle);
	double z = sin(angle);
	eye.SetX(x*20);
	eye.SetZ(z*20);
}

void rotateZ(GLfloat n) {
	int nn = ((int)n) % 360;
	double angle = (2 * PI / 360) * nn;
	double x = cos(angle);
	double y = sin(angle);
	eye.SetX(x*20);
	eye.SetY(y*20);
}

void teclaPressionada(unsigned char tecla, int x, int y) {

	switch (tecla) {
	//case 'q':
	//	angleX += 5;
	//	rotateX(angleX);
	//break;
	//case 'a':
	//	angleX -= 5;
	//	rotateX(angleX);
	//break;
	case 'w':
		angleY += 5;
		rotateY(angleY);
	break;
	case 's':
		angleY -= 5;
		rotateY(angleY);
	break;
	//case 'e':
	//	angleZ += 5;
	//	rotateZ(angleZ);
	//break;
	//case 'd':
	//	angleZ -= 5;
	//	rotateZ(angleZ);
	//break;
	case 'z':
		translacaoMundo[0] += 1;
		anguloCubo[2] += 10;
		if (anguloCubo[2] > 360)  anguloCubo[2] = anguloCubo[2] - 360;
	break;
	case 'x':
		translacaoMundo[0] -= 1;
		anguloCubo[2] -= 10;
		if (anguloCubo[2] < 0)  anguloCubo[2] = 360 - anguloCubo[2];
	break;
	case 'c':
		translacaoMundo[2] += 1;
		anguloCubo[0] -= 10;
		if (anguloCubo[0] < 0)  anguloCubo[0] = 360 - anguloCubo[0];
	break;
	case 'v':
		translacaoMundo[2] -= 1;
		anguloCubo[0] += 10;
		if (anguloCubo[0] > 360)  anguloCubo[0] = anguloCubo[0] - 360;
	break;
	}

	//transform.MakeIdentity();

	std::cout << "Eye    =(" << eye.GetX() << ", " << eye.GetY() << ", " << eye.GetZ() << ")" << std::endl;
	std::cout << "ECenter=(" << center.GetX() << ", " << center.GetY() << ", " << center.GetZ() << ")" << std::endl;

	glutPostRedisplay();
}

void mouseEvento(GLint botao, GLint estado, GLint x, GLint y) {
	
	// calcula a posição como se o ponto 0,0 fosse no centro
	 float nx =  (float)(x - (janelaLargura/2));
	 float ny =  (float)(y - (janelaAltura/2));
	 
	 // inverte o Y para igualar as cordenadas do Opengl
	 ny *= -1;
	 
	 // calcula a porcentagem da posição com relação aos quadrantes da janela
	 nx = nx / (janelaLargura/2);
	 ny = ny / (janelaAltura/2);
	 
	 // calcula a posição correta com relação ao opengl
	 nx *= orthoLargura/2;
	 ny *= orthoAltura/2;
	 
	 std::cout << "x = " << nx << " y = " << ny << std::endl;
	 
	
    glutPostRedisplay();
}
void mouseMovimento(GLint x, GLint y) {
}

void redimensionaJanela(GLint w, GLint h){
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	//gluPerspective(45,ratio,1,1000);
	//gluPerspective(60.0f, w/h, 0.1, 1000); // projeção perspectiva 1 pto fuga 3D
	glFrustum(-5.0, 5.0, -5.0, 5.0, 10, 100); // projeção perspectiva 1 pto fuga 3D
	//glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0); // projeção Ortogonal 3D


	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
	
	// Update ortho variables
	ortho2D_minX  = -w;
	ortho2D_maxX  =  w;
	ortho2D_minY  = -h;
	ortho2D_maxY  =  h;
	janelaLargura =  w;
	janelaAltura  =  h;
	orthoLargura = ortho2D_maxX - ortho2D_minX;
	orthoAltura  = ortho2D_maxY - ortho2D_minY;
}

int main(int argc, const char * argv[]) {
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(300, 250);
	glutInitWindowSize(janelaLargura, janelaAltura);
	gJanelaPrincipal = glutCreateWindow("OpenGL app");
	inicializacao();
	glutDisplayFunc(exibicaoPrincipal);
	glutKeyboardFunc(teclaPressionada);
	glutMouseFunc(mouseEvento);
	glutMotionFunc(mouseMovimento);
	glutReshapeFunc(redimensionaJanela);
	glutMainLoop();
	return 0;
}
#ifdef WIN32 && DEFINED WINDOWS_APP
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
	return main(NULL, 0);
}
#endif
