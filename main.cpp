#include <iostream>
#include <vector>
#include <memory>

#include <GL/glut.h>
#include <math.h>

#include "transform.h"
#include "constantes.h"
#include "mathdef.h"
#include "mundo.h"
#include "objetografico.h"

#define EDICAO 0
#define MANIPULACAO 1

#define PI 3.14159f


GLint gJanelaPrincipal = 0;
GLint janelaLargura = 400, janelaAltura = 400;
GLfloat ortho2D_minX = -400.0f, ortho2D_maxX = 400.0f, ortho2D_minY = -400.0f, ortho2D_maxY = 400.0f;
GLfloat orthoLargura = ortho2D_maxX - ortho2D_minX;
GLfloat orthoAltura  = ortho2D_maxY - ortho2D_minY;

Mundo mundo;

float angleX = 0.0;
float angleY = 0.0;
float angleZ = 0.0;

VART::Transform transform;
VART::Point4D eye(20.0f, 20.0f, 20.0f);
VART::Point4D center(0.0f, 0.0f, 0.0f);

void ligarLuz();
void drawbbox(ObjetoGrafico *objetoGrafico);
void checaColisao();

void inicializacao(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);

	//ligarLuz();

	//glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);

	transform.MakeIdentity();
}

void checaColisao() {
	for (auto x : mundo.objetosGraficos) {
	    x->bbox.ApplyTransform(mundo.transformacao);
            bool test = x->bbox.testAABBAABB(mundo.cuboPrincipal.bbox);
	    x->updateBBox();
	    std::cout << "AABBAABB = "<< test << std::endl;
		
	}
}

void drawbbox(ObjetoGrafico *objetoGrafico)
{
	GLfloat sX = objetoGrafico->bbox.GetSmallerX();
	GLfloat sY = objetoGrafico->bbox.GetSmallerY();
	GLfloat sZ = objetoGrafico->bbox.GetSmallerZ();
	GLfloat gX = objetoGrafico->bbox.GetGreaterX(); 
	GLfloat gY = objetoGrafico->bbox.GetGreaterY(); 
	GLfloat gZ = objetoGrafico->bbox.GetGreaterZ();
	std::cout << sX << " " << sY << " " << sZ << std::endl;
	std::cout << gX << " " << gY << " " << gZ << std::endl;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin (GL_LINE_LOOP);
		glVertex3d(gX, gY,sZ);					// Top Right Of The Quad (Top)
		glVertex3d(sX, gY,sZ);					// Top Left Of The Quad (Top)
		glVertex3d(sX, gY, gZ);					// Bottom Left Of The Quad (Top)
		glVertex3d(gX, gY, gZ);					// Bottom Right Of The Quad (Top)
		glVertex3d(gX, sY, gZ);					// Top Right Of The Quad (Bottom)
		glVertex3d(sX, sY, gZ);					// Top Left Of The Quad (Bottom)
		glVertex3d(sX, sY,sZ);					// Bottom Left Of The Quad (Bottom)
		glVertex3d(gX, sY,sZ);					// Bottom Right Of The Quad (Bottom)
		glVertex3d(gX, gY, gZ);					// Top Right Of The Quad (Front)
		glVertex3d(sX, gY, gZ);					// Top Left Of The Quad (Front)
		glVertex3d(sX, sY, gZ);					// Bottom Left Of The Quad (Front)
		glVertex3d(gX, sY, gZ);					// Bottom Right Of The Quad (Front)
		glVertex3d(gX, sY,sZ);					// Top Right Of The Quad (Back)
		glVertex3d(sX, sY,sZ);					// Top Left Of The Quad (Back)
		glVertex3d(sX, gY,sZ);					// Bottom Left Of The Quad (Back)
		glVertex3d(gX, gY,sZ);					// Bottom Right Of The Quad (Back)
		glVertex3d(sX, gY, gZ);					// Top Right Of The Quad (Left)
		glVertex3d(sX, gY,sZ);					// Top Left Of The Quad (Left)
		glVertex3d(sX, sY,sZ);					// Bottom Left Of The Quad (Left)
		glVertex3d(sX, sY, gZ);					// Bottom Right Of The Quad (Left)
		glVertex3d(gX, gY,sZ);					// Top Right Of The Quad (Right)
		glVertex3d(gX, gY, gZ);					// Top Left Of The Quad (Right)
		glVertex3d(gX, sY, gZ);					// Bottom Left Of The Quad (Right)
		glVertex3d(gX, sY,sZ);					// Bottom Right Of The Quad (Right)
    glEnd();
}

void exibicaoPrincipal(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.GetX(), eye.GetY(), eye.GetZ(), center.GetX(), center.GetY(), center.GetZ(), 0.0f, 1.0f, 0.0f);

	/////////	
	SRU();

	// chão
	mundo.chessboard();

	// objeto principal
	mundo.cuboPrincipal.draw();
	drawbbox(&mundo.cuboPrincipal);
	mundo.draw();

	///////
	glutSwapBuffers();
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
	VART::Point4D vector;
	vector.SetX(1.0f);
	vector.SetY(1.0f);
	vector.SetZ(1.0f);
	mundo.transformacao.ApplyTo(&vector);
	std::cout << "X = " << vector.GetX() << " Y = " << vector.GetY() << " Z = " << vector.GetZ() << std::endl;
	switch (tecla) {
	case 'w':
		angleY += 5;
		rotateY(angleY);
	break;
	case 's':
		angleY -= 5;
		rotateY(angleY);
	break;
	case 'z':
		if (vector.GetX() <= 0) {
			mundo.translacao(1.0, 0.0, 0.0);
			mundo.cuboPrincipal.rotacionaZ(10);
			mundo.cuboPrincipal.aplicaTransformacao();
			mundo.cuboPrincipal.updateBBox();
		}
	break;
	case 'x':
		if (vector.GetX() >= -88) {
			mundo.translacao(-1.0, 0.0, 0.0);
			mundo.cuboPrincipal.rotacionaZ(-10);
			mundo.cuboPrincipal.aplicaTransformacao();
			mundo.cuboPrincipal.updateBBox();
		}
	break;
	case 'c':
		if (vector.GetZ() <= 0) {
			mundo.translacao(0.0, 0.0, 1.0);
			mundo.cuboPrincipal.rotacionaX(-10);
			mundo.cuboPrincipal.aplicaTransformacao();
			mundo.cuboPrincipal.updateBBox();
		}
	break;
	case 'v':
		if (vector.GetZ() >= -61) {
			mundo.translacao(0.0, 0.0, -1.0);
			mundo.cuboPrincipal.rotacionaX(10);
			mundo.cuboPrincipal.aplicaTransformacao();
			mundo.cuboPrincipal.updateBBox();
		}
	break;
	case 'q':
		//mundo.cuboPrincipal = mundo.objetosGraficos[0].get();
	break;
	case 'p':
		mundo.adicionaCubo(20.0f, 1.0f, 20.0f);
	break;
	case 'e':
	break;
	}


	checaColisao();

	//std::cout << "Eye    =(" << eye.GetX() << ", " << eye.GetY() << ", " << eye.GetZ() << ")" << std::endl;
	//std::cout << "ECenter=(" << center.GetX() << ", " << center.GetY() << ", " << center.GetZ() << ")" << std::endl;

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
