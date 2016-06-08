/// \file constantes.h
/// \brief Implementation file for "CG-N2_HelloWorld".
/// \version $Revision: 1.0 $
/// \author Dalton Reis.
/// \date 05/09/13.


#ifndef CG_N2_HelloWorld_constantes_h
#define CG_N2_HelloWorld_constantes_h

inline void SRU(void) {
	// eixo X - Red
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);
	glEnd();
	// eixo Y - Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	// eixo Z - Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();
}

#endif
