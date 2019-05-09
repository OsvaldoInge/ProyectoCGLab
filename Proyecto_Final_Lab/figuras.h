//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Funcíon creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Funcíon creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Funcíon creacion cono
	void prisma_anun (GLuint text, GLuint text2);							//Funcíon creacion movimiento
	void prisma (float altura, float largo, float profundidad, GLuint text);//Funcíon creacion prisma
	void prisma2 (GLuint text, GLuint text2);
	void prisma3 (GLuint text, GLuint text2, float u, float v);								//Función creacion prisma 3
	void skybox(float altura, float largo, float profundidad, GLuint text);	//Funcion creacion cielo
	void skybox2 (float altura, float largo, float profundidad, GLuint text);
	

	//void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos, GLuint text );
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);

	void tecla (float altura, float largo, float profundidad, GLuint text);
	void plano (GLuint textura2, float u, float v);							//funcion creacion plano
	void techo(GLuint textura2);											//funcion creacion techo
};
