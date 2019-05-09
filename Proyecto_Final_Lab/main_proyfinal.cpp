//Semestre 2019 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************	Sánchez Arenas Osvaldo					******//
//*************											******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


//NEW// Keyframes
//Variables de dibujo y manipulacion
float posX =0, posY = 2.5, posZ =-3.5, rotRodIzq = 0, rotRodDer = 0, rotBraIzq = 0, rotBraDer = 0;
float giroMonito = 0;

#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotRodDer;
	float rotBraIzq;
	float rotBraDer;
	float rotInc;
	float rotInc2;
	float rotInc3;
	float rotInc4;
	float giroMonito;
	float giroMonitoInc;
	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=0;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01


//NEW///////////////////////////7

CTexture t_zaguan;
CTexture t_pared;
CTexture t_pared2;
CTexture t_bloque;
CTexture t_ventana;
CTexture t_barandal;
CTexture t_madera;
CTexture t_puerta;
CTexture t_tejas;
CTexture t_piso;
CTexture t_madera2;
CTexture t_metal;
CTexture t_tela1;
CTexture t_telacafe;
CTexture t_tela2;

CFiguras esferaCama;
CFiguras pataCama;
CFiguras baseCama;
CFiguras cilindroCama;
CFiguras Colchon;
CFiguras Almohada;

CFiguras tablaMesa;
CFiguras pataMesa;
CFiguras asientoSilla;
CFiguras respaldoSilla;
CFiguras puerta;
CFiguras pared;
CFiguras ventana;
CFiguras columna;
CFiguras buro;
CFiguras cono;
CFiguras lampara;
CFiguras barandal;
CFiguras zaguan;
CFiguras techoCasa;
CFiguras pisoCasa;


CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito


void saveFrame ( void )
{
	
	printf("frameindex %d\n",FrameIndex);			

	KeyFrame[FrameIndex].posX=posX;
	KeyFrame[FrameIndex].posY=posY;
	KeyFrame[FrameIndex].posZ=posZ;

	KeyFrame[FrameIndex].rotRodIzq=rotRodIzq;
	KeyFrame[FrameIndex].rotRodDer = rotRodDer;
	KeyFrame[FrameIndex].rotBraDer = rotBraDer;
	KeyFrame[FrameIndex].rotBraIzq = rotBraIzq;
	KeyFrame[FrameIndex].giroMonito=giroMonito;
			
	FrameIndex++;
}

void resetElements( void )
{
	posX=KeyFrame[0].posX;
	posY=KeyFrame[0].posY;
	posZ=KeyFrame[0].posZ;

	rotRodIzq=KeyFrame[0].rotRodIzq;
	rotRodDer = KeyFrame[0].rotRodDer;
	rotBraDer = KeyFrame[0].rotBraDer;
	rotBraIzq = KeyFrame[0].rotBraIzq;
	giroMonito=KeyFrame[0].giroMonito;

}

void interpolation ( void )
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;	
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;	
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;	

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;	
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBraIzq - KeyFrame[playIndex].rotBraIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotBraDer - KeyFrame[playIndex].rotBraDer) / i_max_steps;
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}


void ciudad ()
{

		glPushMatrix(); //Camino1
			glTranslatef(23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino2
			glTranslatef(-23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,-4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,7.0);
			glRotatef(90,1,0,0);
			glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,-7.0);
			glRotatef(90,1,0,0);
			//glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(text6.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

}

void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
		glScalef(0.5, 0.5, 0.5);
		fig7.prisma(2.0 ,2.0 ,1 ,text2.GLindex);

		glPushMatrix();//Cuello
			glTranslatef(0, 1.0, 0.0);
			fig7.cilindro(0.25, 0.25, 15, 0);
			glPushMatrix();//Cabeza
				glTranslatef(0, 1.0, 0);
				fig7.esfera(0.75, 15, 15, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo derecho-->
			glTranslatef(1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(0.25, 0, 0);
				glRotatef(-45+rotBraDer, 0, 1, 0); 
				glTranslatef(0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo izquierdo <--
			glTranslatef(-1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(-0.25, 0, 0);
				glRotatef(45+rotBraIzq, 0, 1, 0); 
				glRotatef(25, 0, 0, 1);
				glRotatef(25, 1, 0, 0); 
				glTranslatef(-0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();//Cintura
			glColor3f(0, 0, 1);
			glTranslatef(0, -1.5, 0);
			fig7.prisma(1, 2, 1, 0);

			glPushMatrix(); //Pie Derecho -->
				glTranslatef(0.75, -0.5, 0);
				glRotatef(-15, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15+rotRodDer, 1, 0, 0);
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


			glPushMatrix(); //Pie Izquierdo -->
				glTranslatef(-0.75, -0.5, 0);
				glRotatef(-5, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15+rotRodIzq, 1, 0, 0);
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


		glPopMatrix();


		glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}

///// Casa
void casa(void) {
	glPushMatrix();

////zaguan

		glPushMatrix();//Zaguan 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0, -2.0f, 0);
			glScalef(5.0, 4.0, 1.0);
			zaguan.plano(t_zaguan.GLindex, 6, 5);
		glPopMatrix();

		glPushMatrix();//columna zaguan_izq
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(-0.13, 0, 0);
			glScalef(0.25, 4.0, 0.5);
			columna.prisma3(t_pared.GLindex, t_pared.GLindex, 1.0, 4.0);
		glPopMatrix();

		glPushMatrix();//columna izq
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(-0.5, 0.18, 0);
			glScalef(0.5, 4.4, 0.25);
			columna.prisma3(t_bloque.GLindex, t_bloque.GLindex, 1, 7.5);
		glPopMatrix();


		glPushMatrix();//columna zaguan_der
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(5.13f, 0, 0);
			glScalef(0.25f, 4.0f, 0.5f);
			columna.prisma3(t_pared.GLindex, t_pared.GLindex, 1, 4);
		glPopMatrix();

		glPushMatrix();//columna der
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(5.5, 0.18, 0.1);
			glScalef(0.5, 4.4, 0.7);
			columna.prisma3(t_bloque.GLindex, t_bloque.GLindex, 1, 7.5);
		glPopMatrix();

		glPushMatrix();//columna zaguan_arriba
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(2.5, 2.25f, 0);
			glScalef(5.5f, 0.5f, 0.5f);
			columna.prisma3(t_pared2.GLindex, t_pared.GLindex, 5, 1);
		glPopMatrix();

		glPushMatrix();//marquesina
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(2.5, 2.5f, -2.75f);
			glScalef(7.0f, 0.25f, 7.0f);
			columna.prisma3(t_pared2.GLindex, t_pared.GLindex, 10, 1);
		glPopMatrix();

////pared izquierda

		glPushMatrix();//ventana izquierda 
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1f);
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1, 0);
			glTranslatef(2.0f, -1.0f, -0.75);
			glScalef(2.0, 2.5, 1.0);
			ventana.plano(t_ventana.GLindex, 1, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();//Pared_izq1 
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1, 0);
			glTranslatef(0.12, -2.0f, -0.75);
			glScalef(1.88, 4.5, 1.0);
			pared.plano(t_pared.GLindex, 6, 5);
		glPopMatrix();

		glPushMatrix();//Pared_izq2 
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1, 0);
			glTranslatef(4.0, -2.0f, -0.75);
			glScalef(1.88, 4.5, 1.0);
			pared.plano(t_pared.GLindex, 6, 5);
		glPopMatrix();

		glPushMatrix();//Pared_izq3
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1, 0);
			glTranslatef(2.0, -2.0f, -0.75);
			glScalef(2.0, 1.0, 1.0);
			pared.plano(t_pared.GLindex, 6, 5);
		glPopMatrix();

		glPushMatrix();//Pared_izq4 
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1, 0);
			glTranslatef(2.0, 1.5f, -0.75);
			glScalef(2.0, 0.87, 1.0);
			pared.plano(t_pared.GLindex, 6, 5);
		glPopMatrix();

/////pared fondo

		glPushMatrix();//ventana fondo 
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1f);
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(4.0f, -1.0f, -5.87);
			glScalef(2.5, 2.5, 1.0);
			ventana.plano(t_ventana.GLindex, 1, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();//Pared_fondo1 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(-0.75, -2.0f, -5.87);
			glScalef(4.75, 4.5, 1.0);
			pared.plano(t_pared.GLindex, 6, 5);
		glPopMatrix();

		glPushMatrix();//Pared_fondo2 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(6.5, -2.0f, -5.87);
			glScalef(4.5, 4.5, 1.0);
			pared.plano(t_pared.GLindex, 6, 5);
		glPopMatrix();

		glPushMatrix();//Pared_fondo3
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(4.0, -2.0f, -5.87);
			glScalef(2.5, 1.0, 1.0);
			pared.plano(t_pared.GLindex, 6, 5);
		glPopMatrix();

		glPushMatrix();//Pared_fondo4 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(4.0, 1.5f, -5.87);
			glScalef(2.5, 0.87, 1.0);
			pared.plano(t_pared.GLindex, 6, 5);
		glPopMatrix();

////primer piso

		glPushMatrix();//ventana_sup1 
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1f);
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(1.5f, 2.65f, 0);
			glScalef(3.0, 3.25, 1.0);
			ventana.plano(t_ventana.GLindex, 1, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();//barandal ventana_sup1 
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1f);
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(1.11f, 2.65f, 0.25);
			glScalef(3.92, 2.0, 1.0);
			barandal.plano(t_barandal.GLindex, 1, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();//pared ventana _izq
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(1.0f, 2.65f, 0);
			glScalef(0.5, 4.0, 1.0);
			pared.plano(t_pared2.GLindex, 1, 1);
		glPopMatrix();

		glPushMatrix();//pared ventana _der
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(4.5f, 2.65f, 0);
			glScalef(0.51, 4.0, 1.0);
			pared.plano(t_pared2.GLindex, 1, 1);
		glPopMatrix();


		glPushMatrix();//columna ventana_izq
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(1.0, 4.65, 0);
			glScalef(0.25, 4.0, 0.5);
			columna.prisma3(t_pared.GLindex, t_pared.GLindex, 1, 4);
		glPopMatrix();

		glPushMatrix();//columna izq
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0.63, 4.65, 0);
			glScalef(0.5, 4.0, 0.25);
			columna.prisma3(t_bloque.GLindex, t_bloque.GLindex, 1, 6);

		glPopMatrix();

		glPushMatrix();//columna ventana_der
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(5.13f, 4.65, 0);
			glScalef(0.25f, 4.0f, 0.5f);
			columna.prisma3(t_pared.GLindex, t_pared.GLindex, 1, 4);
		glPopMatrix();

		glPushMatrix();//columna der
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(5.5, 4.65, 0.1);
			glScalef(0.5, 4.0f, 0.7);
			columna.prisma3(t_bloque.GLindex, t_bloque.GLindex, 1, 6);
		glPopMatrix();

		glPushMatrix();//columna ventana_arriba
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(1.0, 5.86f, 0);
			glScalef(4.0f, 0.78f, 0.5f);
			columna.plano(t_pared2.GLindex, 1, 1);
		glPopMatrix();

		glPushMatrix();//marquesina sup
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(3.0, 6.65f, -2.75f);
			glScalef(6.0f, 0.25f, 7.0f);
			columna.prisma3(t_madera.GLindex, t_pared.GLindex, 6, 5);
		glPopMatrix();

////puerta

		glPushMatrix();//puerta 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(6.0, -2.0f, 0);
			glScalef(1.5, 3.5, 1.0);
			puerta.plano(t_puerta.GLindex, 1, 1);
		glPopMatrix();

		glPushMatrix();//pared1 puerta 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(5.75, -2.0f, 0);
			glScalef(0.25, 4.35, 1.0);
			pared.plano(t_pared.GLindex, 1, 4);
		glPopMatrix();

		glPushMatrix();//pared2 puerta 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(7.5, -2.0f, 0);
			glScalef(0.25, 4.35, 1.0);
			pared.plano(t_pared.GLindex, 1, 4);
		glPopMatrix();


		glPushMatrix();//pared3 puerta 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(6.0, 1.5f, 0);
			glScalef(1.5, 0.85, 1.0);
			pared.plano(t_pared.GLindex, 4, 1);
		glPopMatrix();

		glPushMatrix();//marquesina puerta
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(7.0, 2.5f, -3.0f);
			glScalef(2.25f, 0.25f, 6.5f);
			columna.prisma3(t_pared2.GLindex, t_pared.GLindex, 10, 1);
		glPopMatrix();

		glPushMatrix();//columna der puerta
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(7.9, 0.18, 0);
			glScalef(0.36, 4.4, 0.25);
			columna.prisma3(t_bloque.GLindex, t_bloque.GLindex, 1, 7.5);
		glPopMatrix();

		glPushMatrix();//Pared_der puerta 
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1, 0);
			glTranslatef(0.12, -2.0f, 8.05);
			glScalef(1.88, 4.5, 1.0);
			pared.plano(t_pared.GLindex, 6, 5);
		glPopMatrix();

		//balcon puerta


		glPushMatrix();//ventana balcon
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1f);
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(6.25, 2.65f, 0);
			glScalef(1.0, 3.35, 1.0);
			ventana.plano(t_ventana.GLindex, 1, 2);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();//barandal balcon
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1f);
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(6.25, 2.65f, 0);
			glScalef(1.0, 1.5, 1.0);
			barandal.plano(t_barandal.GLindex, 1, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();//pared1 balcon 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(5.75, 2.65f, 0);
			glScalef(0.5, 3.85, 1.0);
			pared.plano(t_pared.GLindex, 1, 4);
		glPopMatrix();

		glPushMatrix();//pared2 balcon 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(7.23, 2.65f, 0);
			glScalef(0.5, 3.85, 1.0);
			pared.plano(t_pared.GLindex, 1, 4);
		glPopMatrix();


		glPushMatrix();//pared3 balcon 
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(6.0, 6.0f, 0);
			glScalef(1.5, 0.5, 1.0);
			pared.plano(t_pared.GLindex, 4, 1);
		glPopMatrix();

		glPushMatrix();//columna der balcon
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(7.9, 4.6, 0);
			glScalef(0.36, 3.9, 0.25);
			columna.prisma3(t_bloque.GLindex, t_bloque.GLindex, 1, 6);
		glPopMatrix();


		glPushMatrix();//marquesina sup balcon
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(7.0, 6.65f, -3.0f);
			glScalef(2.18f, 0.25f, 6.5f);
			columna.prisma3(t_madera.GLindex, t_pared.GLindex, 2, 4.65);
		glPopMatrix();

		glPushMatrix();//marquesina inf balcon
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(6.75F, 2.5f, 0.3f);
			glScalef(1.0f, 0.25f, 0.15f);
			columna.prisma3(t_pared2.GLindex, t_pared.GLindex, 2, 2);
		glPopMatrix();

		glPushMatrix();//Pared_der balcon 
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1, 0);
			glTranslatef(0.12, 2.65f, 8.05);
			glScalef(1.88, 3.9, 1.0);
			pared.plano(t_pared.GLindex, 6, 5);
		glPopMatrix();

		// ventana derecha
		glPushMatrix();//ventana derecha
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1f);
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(8.5f, -1.0f, -2.0);
			glScalef(2.0, 2.5, 1.0);
			ventana.plano(t_ventana.GLindex, 1, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();//pared ventana _izq
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(8.0f, -2.0, -2.0f);
			glScalef(0.5, 4.38, 1.0);
			pared.plano(t_pared.GLindex, 1, 1);
		glPopMatrix();

		glPushMatrix();//pared ventana _der
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(10.5f, -2.0, -2.0f);
			glScalef(0.51, 4.38, 1.0);
			pared.plano(t_pared.GLindex, 1, 1);
		glPopMatrix();


		glPushMatrix();//pared ventana _abajo
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(8.5f, -2.0, -2.0f);
			glScalef(2.0, 1.0, 1.0);
			pared.plano(t_pared.GLindex, 3, 1);
		glPopMatrix();

		glPushMatrix();//pared ventana _arriba
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(8.5f, 1.5, -2.0f);
			glScalef(2.0, 0.88, 1.0);
			pared.plano(t_pared.GLindex, 3, 1);
		glPopMatrix();

		glPushMatrix();//marquesina ventana
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(9.6F, 2.5f, -3.95f);
			glScalef(3.0f, 0.25f, 4.6f);
			columna.prisma3(t_pared2.GLindex, t_pared.GLindex, 2, 2);
		glPopMatrix();

////ventana derecha costado

		glPushMatrix();//ventana derecha costado
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1f);
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1.0, 0);
			glTranslatef(3.0f, -0.5f, 11.0);
			glScalef(2.0, 2.0, 1.0);
			ventana.plano(t_ventana.GLindex, 1, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();//pared ventana _izq costado
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1.0, 0);
			glTranslatef(2.0f, -2.0, 11.0f);
			glScalef(1.0, 4.38, 1.0);
			pared.plano(t_pared.GLindex, 1, 1);
		glPopMatrix();

		glPushMatrix();//pared ventana _der costado
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1.0, 0);
			glTranslatef(5.0f, -2.0, 11.0f);
			glScalef(0.87, 4.38, 1.0);
			pared.plano(t_pared.GLindex, 1, 1);
		glPopMatrix();

		glPushMatrix();//pared ventana _abajo
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1.0, 0);
			glTranslatef(3.0f, -2.0, 11.0f);
			glScalef(2.0, 1.5, 1.0);
			pared.plano(t_pared.GLindex, 3, 1);
		glPopMatrix();

		glPushMatrix();//pared ventana _arriba
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1.0, 0);
			glTranslatef(3.0f, 1.5, 11.0f);
			glScalef(2.0, 0.88, 1.0);
			pared.plano(t_pared.GLindex, 3, 1);
		glPopMatrix();


		// ventana derecha arriba
		glPushMatrix();//ventana derecha arriba 
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1f);
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(8.5f, 3.65f, -2.0);
			glScalef(2.0, 2.04, 1.0);
			ventana.plano(t_ventana.GLindex, 1, 1);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		glPushMatrix();//pared ventana derecha arriba_izq
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(8.0f, 2.65, -2.0f);
			glScalef(0.5, 3.9, 1.0);
			pared.plano(t_pared.GLindex, 1, 1);
		glPopMatrix();

		glPushMatrix();//pared ventana derecha arriba_der
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(10.5f, 2.65, -2.0f);
			glScalef(0.51, 3.9, 1.0);
			pared.plano(t_pared.GLindex, 1, 1);
		glPopMatrix();


		glPushMatrix();//pared ventana derecha arriba_abajo
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(8.5f, 2.65, -2.0f);
			glScalef(2.0, 1.0, 1.0);
			pared.plano(t_pared.GLindex, 3, 1);
		glPopMatrix();

		glPushMatrix();//pared ventana derecha arriba_arriba
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(8.5f, 5.67, -2.0f);
			glScalef(2.0, 0.88, 1.0);
			pared.plano(t_pared.GLindex, 3, 1);
		glPopMatrix();

		glPushMatrix();//marquesina ventana derecha arriba
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(9.58F, 6.65f, -3.95f);
			glScalef(3.0f, 0.25f, 4.6f);
			columna.prisma3(t_madera.GLindex, t_pared.GLindex, 2, 3.28);
		glPopMatrix();

		//paredes primer piso
		glPushMatrix();//pared arriba_izq
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1.0, 0);
			glTranslatef(0, 2.65f, 0.5f);
			glScalef(6.0, 3.9, 1.0);
			pared.plano(t_pared.GLindex, 6, 4);
		glPopMatrix();

		glPushMatrix();//pared arriba_der
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 0, 1.0, 0);
			glTranslatef(2.0, 2.65f, 11.0f);
			glScalef(4.0, 3.9, 1.0);
			pared.plano(t_pared.GLindex, 4, 4);
		glPopMatrix();

		glPushMatrix();//pared arriba_fondo
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0.5, 2.65f, -6.0f);
			glScalef(10.5, 3.9, 1.0);
			pared.plano(t_pared.GLindex, 8, 4);
		glPopMatrix();

////techo

		glPushMatrix();//techo1
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0, 6.78f, 0.75);
			glScalef(3.0f, 2.0f, 0.5f);
			techoCasa.techo(t_tejas.GLindex);
		glPopMatrix();

		glPushMatrix();//techo2
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0, 6.78f, 0.26);
			glScalef(4.05f, 4.0f, 3.25f);
			techoCasa.techo(t_tejas.GLindex);
		glPopMatrix();


		glPushMatrix();//techo3
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(7.08, 6.78f, -1.65f);
			glScalef(2.0f, 2.0f, 2.3f);
			techoCasa.techo(t_tejas.GLindex);
		glPopMatrix();

////piso
		glPushMatrix();//piso1
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 1.0, 0, 0);
			glTranslatef(-0.75, -5.88, 2.0);
			glScalef(8.8, 5.88, 1.0);
			pisoCasa.plano(t_piso.GLindex, 8, 6);
		glPopMatrix();

		glPushMatrix();//piso2
			glColor3f(1.0, 1.0, 1.0);
			glRotatef(90.0, 1.0, 0, 0);
			glTranslatef(7.0, -5.88, 2.0);
			glScalef(4.0, 3.88, 1.0);
			pisoCasa.plano(t_piso.GLindex, 8, 6);
		glPopMatrix();
				
	glPopMatrix();
}

////////////////////////////////////////////////////////////

void escritorio(void) {
	glPushMatrix();
////escritorio
		glPushMatrix();//escritorio sup
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0, 2.0, 0);
			glScalef(5.0, 0.25, 2.0);
			tablaMesa.prisma3(t_madera2.GLindex, t_madera2.GLindex, 1, 2);
		glPopMatrix();

		glPushMatrix();//escritorio pata der
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(2.38, 0, 0);
			glScalef(0.25, 3.75, 2.0);
			pataMesa.prisma3(t_madera2.GLindex, t_madera2.GLindex, 2, 1);
		glPopMatrix();

		glPushMatrix();//escritorio pata izq
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(-2.38, 0, 0);
			glScalef(0.25, 3.75, 2.0);
			pataMesa.prisma3(t_madera2.GLindex, t_madera2.GLindex, 2, 1);
		glPopMatrix();
	glPopMatrix();
}

void cama(void) {
	glPushMatrix();
	////patas
	glPushMatrix();//esf_pata cama 1
	glTranslatef(-2.0, 0, 0);
	esferaCama.esfera(0.25, 4, 6, t_metal.GLindex);
	glPopMatrix();

	glPushMatrix();//pata cama 1
	glTranslatef(-2.0, 0.6, 0);
	glScalef(0.25, 1, 0.25);
	pataCama.prisma2(t_metal.GLindex, t_metal.GLindex);
	glPopMatrix();

	glPushMatrix();//esf_pata cama 2
	glTranslatef(2.0, 0, 0);
	esferaCama.esfera(0.25, 4, 6, t_metal.GLindex);
	glPopMatrix();

	glPushMatrix();//pata cama 2
	glTranslatef(2.0, 0.6, 0);
	glScalef(0.25, 1, 0.25);
	pataCama.prisma2(t_metal.GLindex, t_metal.GLindex);
	glPopMatrix();


	glPushMatrix();//esf_pata cama 3
	glTranslatef(-2.0, 0, -8.0);
	esferaCama.esfera(0.25, 4, 6, t_metal.GLindex);
	glPopMatrix();

	glPushMatrix();//pata cama 3
	glTranslatef(-2.0, 0.6, -8.0);
	glScalef(0.25, 1, 0.25);
	pataCama.prisma2(t_metal.GLindex, t_metal.GLindex);
	glPopMatrix();

	glPushMatrix();//esf_pata cama 4
	glTranslatef(2.0, 0, -8.0);
	esferaCama.esfera(0.25, 4, 6, t_metal.GLindex);
	glPopMatrix();

	glPushMatrix();//pata cama 1
	glTranslatef(2.0, 0.6, -8.0);
	glScalef(0.25, 1, 0.25);
	pataCama.prisma2(t_metal.GLindex, t_metal.GLindex);
	glPopMatrix();

	//// base

	glPushMatrix();//base cama
	glTranslatef(0, 1.2, -4.0);
	baseCama.prisma(1.0, 4.5, 8.5, t_metal.GLindex);
	glPopMatrix();

	////colchon

	glPushMatrix();//colchon1
	glTranslatef(2.25, 1.96, -0.1);
	glRotatef(90.0, 0, 0, 1.0);
	glRotatef(90.0, 0, 1.0, 0);
	cilindroCama.cilindro(0.5, 4.5, 25, t_tela1.GLindex);
	glPopMatrix();

	glPushMatrix();//colchon2
	glTranslatef(-0.01, 2.08, -3.25);
	baseCama.prisma(0.75, 4.5, 6.5, t_tela1.GLindex);
	glPopMatrix();

	glPushMatrix();//colchon2 izq
	glRotatef(90.0, 0, 1.0, 0);
	glTranslatef(-0.4, 0.8, -2.26);
	glScalef(6.65, 1.25, 1);
	Colchon.plano(t_tela1.GLindex, 3, 1);
	glPopMatrix();

	glPushMatrix();//colchon2 der
	glRotatef(90.0, 0, 1.0, 0);
	glTranslatef(-0.4, 0.8, 2.26);
	glScalef(6.65, 1.25, 1);
	Colchon.plano(t_tela1.GLindex, 3, 1);
	glPopMatrix();

	glPushMatrix();//colchon2 frente
	glTranslatef(-2.29, 0.8, 0.4);
	glScalef(4.55, 1.25, 1.0);
	Colchon.plano(t_tela1.GLindex, 3, 1);
	glPopMatrix();

	glPushMatrix();//colchon cafe 
	glTranslatef(-0.01, 2.08, -7.25);
	baseCama.prisma(0.8, 4.65, 2.0, t_telacafe.GLindex);
	glPopMatrix();

	glPushMatrix();//colchon cafe izq
	glTranslatef(-2.29, 1.15, -7.25);
	baseCama.prisma(1.25, 0.05, 2.01, t_telacafe.GLindex);
	glPopMatrix();

	glPushMatrix();//colchon cafe izq
	glTranslatef(2.29, 1.15, -7.25);
	baseCama.prisma(1.25, 0.05, 2.0, t_telacafe.GLindex);
	glPopMatrix();

	////Almohadas

	glPushMatrix();//colchon cafe izq
	glTranslatef(-1.3, 2.85, -7.5);
	glRotatef(45.0, 1.0, 0, 0);
	Almohada.cilindro(1.3, 1.0, 8, t_tela2.GLindex);
	glPopMatrix();

	glPushMatrix();//colchon cafe izq
	glTranslatef(1.3, 2.85, -7.5);
	glRotatef(45.0, 1.0, 0, 0);
	Almohada.cilindro(1.3, 1.0, 8, t_tela2.GLindex);
	glPopMatrix();

	glPopMatrix();
}






GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

    
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	//////////////////////////////////////////

	t_zaguan.LoadTGA("zaguan.tga");
	t_zaguan.BuildGLTexture();
	t_zaguan.ReleaseImage();

	t_pared.LoadTGA("pared.tga");
	t_pared.BuildGLTexture();
	t_pared.ReleaseImage();

	t_pared2.LoadTGA("pared2.tga");
	t_pared2.BuildGLTexture();
	t_pared2.ReleaseImage();

	t_bloque.LoadTGA("bloque.tga");
	t_bloque.BuildGLTexture();
	t_bloque.ReleaseImage();

	t_ventana.LoadTGA("ventana.tga");
	t_ventana.BuildGLTexture();
	t_ventana.ReleaseImage();

	t_barandal.LoadTGA("barandal.tga");
	t_barandal.BuildGLTexture();
	t_barandal.ReleaseImage();

	t_madera.LoadTGA("madera.tga");
	t_madera.BuildGLTexture();
	t_madera.ReleaseImage();

	t_puerta.LoadTGA("puerta.tga");
	t_puerta.BuildGLTexture();
	t_puerta.ReleaseImage();

	t_tejas.LoadTGA("tejas.tga");
	t_tejas.BuildGLTexture();
	t_tejas.ReleaseImage();

	t_piso.LoadTGA("piso.tga");
	t_piso.BuildGLTexture();
	t_piso.ReleaseImage();

	t_madera2.LoadTGA("madera2.tga");
	t_madera2.BuildGLTexture();
	t_madera2.ReleaseImage();

	t_metal.LoadTGA("metal.tga");
	t_metal.BuildGLTexture();
	t_metal.ReleaseImage();

	t_tela1.LoadTGA("tela1.tga");
	t_tela1.BuildGLTexture();
	t_tela1.ReleaseImage();

	t_telacafe.LoadTGA("telacafe.tga");
	t_telacafe.BuildGLTexture();
	t_telacafe.ReleaseImage();

	t_tela2.LoadTGA("tela2.tga");
	t_tela2.BuildGLTexture();
	t_tela2.ReleaseImage();


	///////////////////////////////////

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
		KeyFrame[i].rotRodIzq =0;
		KeyFrame[i].rotRodDer = 0;
		KeyFrame[i].rotBraIzq = 0;
		KeyFrame[i].rotBraDer = 0;
		KeyFrame[i].rotInc =0;
		KeyFrame[i].rotInc2 = 0;
		KeyFrame[i].rotInc3 = 0;
		KeyFrame[i].rotInc4 = 0;
		KeyFrame[i].giroMonito =0;
		KeyFrame[i].giroMonitoInc =0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glPushMatrix();
	

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(130.0, 130.0, 130.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glEnable ( GL_COLOR_MATERIAL );
					glColor3f(1, 1, 1);
					//glScalef(0.5, 0.5, 0.5);
					//monito();
					glCallList(ciudad_display_list);
					glTranslatef(posX, posY, posZ);
					glRotatef(giroMonito, 0, 1, 0);
					monito();
				glDisable ( GL_COLOR_MATERIAL );
			glPopMatrix();			

			glPushMatrix(); //Flecha
				glScalef(7,0.1,7);
				glDisable(GL_LIGHTING);
				fig3.prisma_anun(text3.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();


			//CASA///////////////////
			//¨****casa*****
			glPushMatrix();
				glScalef(1.0, 0.75, 1.0);
				glTranslatef(30, 2.5, -4.0);
				glDisable(GL_LIGHTING);
				glScalef(1.2, 1.2, 1.2);
					casa();
				glEnable(GL_LIGHTING);
			glPopMatrix();
//cama
			glPushMatrix();
				//glScalef(1.0, 1.0, 1.0);
				glTranslatef(32.5, 0.24, -7.5);
				glDisable(GL_LIGHTING);
				glScalef(0.4, 0.4, 0.4);
				glRotatef(90.0, 0, 1.0, 0);
				cama();
				glEnable(GL_LIGHTING);
			glPopMatrix();

//escritorio
			glPushMatrix();
			//glScalef(1.0, 1.0, 1.0);
			glTranslatef(40.5, 0.9, -10.64);
			glDisable(GL_LIGHTING);
			glScalef(0.4, 0.4, 0.4);
			escritorio();
			glEnable(GL_LIGHTING);
			glPopMatrix();

			glColor3f(1.0,1.0,1.0);

		glPopMatrix();
	glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,12.0,-14.0,(void *)font,"Proyecto Final");
			pintaTexto(-11,10.5,-14,(void *)font,"Sánchez Arenas Osvaldo");
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.001;
	fig3.text_der-= 0.001;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;

	//Movimiento del monito
	if(play)
	{		
		
		if(	i_curr_steps >= i_max_steps) //end of animation between frames?
		{			
			playIndex++;		
			if(playIndex>FrameIndex-2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex=0;
				play=false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			posX+=KeyFrame[playIndex].incX;
			posY+=KeyFrame[playIndex].incY;
			posZ+=KeyFrame[playIndex].incZ;

			rotRodIzq+=KeyFrame[playIndex].rotInc;
			rotRodDer += KeyFrame[playIndex].rotInc2;
			rotBraIzq += KeyFrame[playIndex].rotInc3;
			rotBraDer += KeyFrame[playIndex].rotInc4;
			giroMonito+=KeyFrame[playIndex].giroMonitoInc;

			i_curr_steps++;
		}
		
	}


	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'k':		//
		case 'K':
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		case 'l':						
		case 'L':
			if(play==false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;

		case 'y':						
		case 'Y':
			posZ++;
			printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			printf("%f \n", rotRodIzq);
			break;

		case 'n':
			rotRodDer++;
			printf("%f \n", rotRodDer);
			break;

		case 'N':
			rotRodDer--;
			printf("%f \n", rotRodDer);
			break;

		case 'c':
			rotBraIzq++;
			printf("%f \n", rotBraIzq);
			break;

		case 'C':
			rotBraIzq--;
			printf("%f \n", rotBraIzq);
			break;

		case 'v':
			rotBraDer++;
			printf("%f \n", rotBraDer);
			break;

		case 'V':
			rotBraDer--;
			printf("%f \n", rotBraDer);
			break;
		case 'p':						
			giroMonito++;
			break;

		case 'P':						
			giroMonito--;
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame( int id)
{
	switch (id)
	{
		case 0:	//Save KeyFrame
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}
			break;

		case 1:	//Play animation
			if(play==false && FrameIndex >1)
			{

				resetElements();
				//First Interpolation
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;


	}
}


void menu( int id)
{
	
}



int main ( int argc, char** argv )   // Main Function
{
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto Final-Sánchez Arenas"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  submenu = glutCreateMenu	  ( menuKeyFrame );
  glutAddMenuEntry	  ("Guardar KeyFrame", 0);
  glutAddMenuEntry	  ("Reproducir Animacion", 1);
  glutCreateMenu	  ( menu );
  glutAddSubMenu	  ("Animacion Monito", submenu);
 
  glutAttachMenu	  (GLUT_RIGHT_BUTTON);


  glutMainLoop        ( );          // 

  return 0;
}