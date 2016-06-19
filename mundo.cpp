#include "mundo.h"

#include <list>
#include <vector>
#include <memory>
#include "objetografico.h"
#include "point4d.h"


#define PUSH(px, py, pz) pPontos.push_back(std::shared_ptr<VART::Point4D>(new VART::Point4D(px, py, pz, 1)))
Mundo::Mundo() {
	transformacao.MakeIdentity();
	c = 0;
	GLfloat x = 0;
	GLfloat y = 1;
	GLfloat z = 0;
	std::cout << "inicio PUSH" << std::endl;
	std::vector<std::shared_ptr<VART::Point4D>> pPontos;
	PUSH( 1.0f+x, 1.0f+y,-1.0f+z);					// Top Right Of The Quad (Top)
	PUSH(-1.0f+x, 1.0f+y,-1.0f+z);					// Top Left Of The Quad (Top)
	PUSH(-1.0f+x, 1.0f+y, 1.0f+z);					// Bottom Left Of The Quad (Top)
	PUSH( 1.0f+x, 1.0f+y, 1.0f+z);					// Bottom Right Of The Quad (Top)
	PUSH( 1.0f+x,-1.0f+y, 1.0f+z);					// Top Right Of The Quad (Bottom)
	PUSH(-1.0f+x,-1.0f+y, 1.0f+z);					// Top Left Of The Quad (Bottom)
	PUSH(-1.0f+x,-1.0f+y,-1.0f+z);					// Bottom Left Of The Quad (Bottom)
	PUSH( 1.0f+x,-1.0f+y,-1.0f+z);					// Bottom Right Of The Quad (Bottom)
	PUSH( 1.0f+x, 1.0f+y, 1.0f+z);					// Top Right Of The Quad (Front)
	PUSH(-1.0f+x, 1.0f+y, 1.0f+z);					// Top Left Of The Quad (Front)
	PUSH(-1.0f+x,-1.0f+y, 1.0f+z);					// Bottom Left Of The Quad (Front)
	PUSH( 1.0f+x,-1.0f+y, 1.0f+z);					// Bottom Right Of The Quad (Front)
	PUSH( 1.0f+x,-1.0f+y,-1.0f+z);					// Top Right Of The Quad (Back)
	PUSH(-1.0f+x,-1.0f+y,-1.0f+z);					// Top Left Of The Quad (Back)
	PUSH(-1.0f+x, 1.0f+y,-1.0f+z);					// Bottom Left Of The Quad (Back)
	PUSH( 1.0f+x, 1.0f+y,-1.0f+z);					// Bottom Right Of The Quad (Back)
	PUSH(-1.0f+x, 1.0f+y, 1.0f+z);					// Top Right Of The Quad (Left)
	PUSH(-1.0f+x, 1.0f+y,-1.0f+z);					// Top Left Of The Quad (Left)
	PUSH(-1.0f+x,-1.0f+y,-1.0f+z);					// Bottom Left Of The Quad (Left)
	PUSH(-1.0f+x,-1.0f+y, 1.0f+z);					// Bottom Right Of The Quad (Left)
	PUSH( 1.0f+x, 1.0f+y,-1.0f+z);					// Top Right Of The Quad (Right)
	PUSH( 1.0f+x, 1.0f+y, 1.0f+z);					// Top Left Of The Quad (Right)
	PUSH( 1.0f+x,-1.0f+y, 1.0f+z);					// Bottom Left Of The Quad (Right)
	PUSH( 1.0f+x,-1.0f+y,-1.0f+z);					// Bottom Right Of The Quad (Right)
	std::cout << "fim PUSH" << std::endl;
	cuboPrincipal = ObjetoGrafico(pPontos, nullptr);
}
void Mundo::adicionarNovoObjetoGrafico(std::vector<std::shared_ptr<VART::Point4D>> pPoints) {
	objetosGraficos.push_back(std::shared_ptr<ObjetoGrafico>(new ObjetoGrafico(pPoints, nullptr)));
}

int Mundo::contaObjetosGraficos() {
	int contagem = 0;
	for (auto x : objetosGraficos) {
		contagem += x->contaObjetosGraficos();			
	}
	return contagem + objetosGraficos.size();
}

void Mundo::drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4) {
	// if color is 0 then draw white box and change value of color = 1
	if (c == 0) {
		glColor3f(1, 1, 1); // white color value is 1 1 1
		c = 1;
	} // if color is 1 then draw black box and change value of color = 0
	else {
		glColor3f(0, 0, 0); // black color value is 0 0 0
		c = 0;
	}

	// Draw Square
	glPushMatrix();
	glMultMatrixd(transformacao.GetData());
	glBegin(GL_POLYGON);
	glVertex3f(x1, 0.0f, y1);
	glVertex3f(x2, 0.0f, y2);
	glVertex3f(x3, 0.0f, y3);
	glVertex3f(x4, 0.0f, y4);
	glEnd();
	glPopMatrix();
}

void Mundo::chessboard() {
	GLint x, y;
	c = 0;
	for (x = 0; x <= 80; x += 10) {
		for (y = 0; y <= 60; y += 7.5) {
		drawSquare(x, y + 7.5, x + 10, y + 7.5, x + 10, y, x, y);
		}
	}
}


void Mundo::translacao(GLfloat x, GLfloat y, GLfloat z) {
	VART::Transform t;
	t.MakeIdentity();
	t.MakeTranslation(x, y, z);
	transformacao = transformacao * t;
	
}
