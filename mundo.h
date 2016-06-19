#pragma once

#include <vector>
#include <memory>
#include <GL/glut.h>
#include "objetografico.h"
#include "point4d.h"

/// \class Mundo mundo.h
/// \brief representa o mundo onde guarda todo os objetos do programa
struct Mundo {

	Mundo();

	/// Contém a lista de objetos gráficos do programa
	std::vector<std::shared_ptr<ObjetoGrafico>> objetosGraficos;
	VART::Transform transformacao;
	ObjetoGrafico cuboPrincipal;
	ObjetoGrafico chao;
	int c;
	
	/// \brief Adiciona um novo objeto gráfico ao mundo
	void adicionarNovoObjetoGrafico(std::vector<std::shared_ptr<VART::Point4D>> pPoints);
	
	/// \brief COnta a quantidade de objetos gráficos no mundo 
	int contaObjetosGraficos();
	void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4);
	void chessboard();
	void translacao(GLfloat x, GLfloat y, GLfloat z);

};
