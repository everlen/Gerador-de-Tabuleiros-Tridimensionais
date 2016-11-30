#include "Aux_tabuleiro.h"
 

void montar_tabuleiro() {

	float largura_tabuleiro = 160;
	float comprimento_tabuleiro = 160;
	float espessura_tabuleiro = 10;
	int quant_casas_v = 9;
	int quant_casas_h = 9;
	char preencher = 'n';
	cor_rgb cor_tabuleiro;
	cor_rgb cor_casa;
	char aresta = 'n';
	

	int angulo = 45;
	float largura_area = 800;
	float altura_area = 700;
	float distancia_minima = 0.1;
	float distancia_maxima = 500;

	posicao_camera camera;
	camera.pos_x = 0;
	camera.pos_y = 3;
	camera.pos_z = 0;
	camera.mira_x = 0;
	camera.mira_y = 0;
	camera.mira_z = 0;
	camera.lado_x = 0;
	camera.lado_y = 0;
	camera.lado_z = -1;


	float cor_luz[] = { 0.1, 0.1, 0.1, 0.1 };
	float posicao_luz[] = { 0.1, 0.1, 1.0 };

	cor_tabuleiro.r = 0.4;
	cor_tabuleiro.g = 0.0;
	cor_tabuleiro.b = 0.0;

	cor_casa.r = 1.0;
	cor_casa.g = 1.0;
	cor_casa.b = 1.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	posicionar_camera(angulo, largura_area, altura_area, distancia_minima, distancia_maxima, camera);
	rotacionar(rotate_x, rotate_y, rotate_z);
	glShadeModel(GL_SMOOTH);

	//Obter vertices base do tabuleiro
	vertice v = calcular_vertice_tabuleiro(comprimento_tabuleiro, espessura_tabuleiro, largura_tabuleiro);

	//Renderizar faces do tabuleiro
	
	renderizar_corpo_tabuleiro(v, cor_tabuleiro, false);

	// Casas       

	// Triangulares

	aplicar_casas_triangulares(v, quant_casas_h, quant_casas_v, 0.002, cor_casa, 1, preencher, aresta);
	cor_casa.r = 1.0;
	cor_casa.g = 0.0;
	cor_casa.b = 0.0;
	aplicar_casas_triangulares(v, quant_casas_h, quant_casas_v, 0.002, cor_casa, 2, preencher, aresta);

	aresta = 's';
	cor_casa.r = 0.0;
	cor_casa.g = 0.0;
	cor_casa.b = 0.0;
	aplicar_casas_triangulares(v, quant_casas_h, quant_casas_v, 0.003, cor_casa, 1, preencher, aresta);
	aplicar_casas_triangulares(v, quant_casas_h, quant_casas_v, 0.003, cor_casa, 2, preencher, aresta);

	//// Quadradas

	//aplicar_casas_quadrilateras(v, quant_casas_h, quant_casas_v, 0.002, cor_casa, 1, preencher, aresta);
	//cor_casa.r = 0.0;
	//cor_casa.g = 0.0;
	//cor_casa.b = 0.0;
	//aplicar_casas_quadrilateras(v, quant_casas_h, quant_casas_v, 0.002, cor_casa, 2, preencher, aresta);

	//aresta = 's';
	//cor_casa.r = 0.4;
	//cor_casa.g = 0.0;
	//cor_casa.b = 0.0;
	//aplicar_casas_quadrilateras(v, quant_casas_h, quant_casas_v, 0.003, cor_casa, 1, preencher, aresta);
	//aplicar_casas_quadrilateras(v, quant_casas_h, quant_casas_v, 0.003, cor_casa, 2, preencher, aresta);
	
	////Hexagonais
	//
	//aplicar_casas_hexagonais(v, quant_casas_h, quant_casas_v, 0.002, cor_casa, 1, preencher, aresta);
	//cor_casa.r = 0.7;
	//cor_casa.g = 0.0;
	//cor_casa.b = 0.0;
	//aplicar_casas_hexagonais(v, quant_casas_h, quant_casas_v, 0.002, cor_casa, 2, preencher, aresta);
	//
	//aresta = 's';
	//cor_casa.r = 0.0;
	//cor_casa.g = 0.0;
	//cor_casa.b = 0.0;
	//aplicar_casas_hexagonais(v, quant_casas_h, quant_casas_v, 0.003, cor_casa, 1, preencher, aresta);
	//aplicar_casas_hexagonais(v, quant_casas_h, quant_casas_v, 0.003, cor_casa, 2, preencher, aresta);

	// Luz
	//alterar_iluminacao_tabuleiro();
   
	// Textura
	//aplicar_textura(v, "textura1.jpg");

  glFlush();
  glutSwapBuffers(); 
 
}

int main(int argc, char** argv){

  glutInit(&argc,argv);
 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  glutInitWindowPosition(-1, 0);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Tabuleiro");
 
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(montar_tabuleiro);
  glutSpecialFunc(tecla_rotacionar);
 
  glutMainLoop();
 
  return 0;
}


// implementar um vetor de cores para ser utilizado na captura de cores das celulas por celula
