#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <Windows.h>
#include <SOIL.h>

double rotate_x = 0; 
double rotate_y = 0;
double rotate_z = 0;

typedef struct vertice {
	float x;
	float y;
	float z;
}vertice;
typedef struct cor_rgb {
	float r;
	float g;
	float b;
}cor_rgb;
typedef struct posicao_camera {
	float pos_x;
	float pos_y;
	float pos_z;
	float mira_x;
	float mira_y;
	float mira_z;
	float lado_x;
	float lado_y;
	float lado_z;
}posicao_camera;

void renderizar_casa_triangular();

void renderizar_casa_quadrilatera();

void renderizar_casa_hexagonal();

void aplicar_casas_triangulares();

void aplicar_casas_quadrilateras();

void aplicar_casas_hexagonais();

void alterar_iluminacao_tabuleiro();

void aplicar_textura();

vertice calcular_vertice_tabuleiro();

void renderizar_corpo_tabuleiro();

void posicionar_camera();

void rotacionar();

void renderizar_casa_triangular(cor_rgb cor_casa, vertice v1, vertice v2, vertice v3, float distancia_tabuleiro, char aresta) {
	if (aresta == 'n')
		glBegin(GL_POLYGON);
	else {
		glBegin(GL_LINE_LOOP);
	}
	glColor3f(cor_casa.r, cor_casa.g, cor_casa.b);
	glVertex3f(v1.x, v1.y + distancia_tabuleiro, v1.z);
	glVertex3f(v2.x, v2.y + distancia_tabuleiro, v2.z);
	glVertex3f(v3.x, v3.y + distancia_tabuleiro, v3.z);

	glEnd();
}

void renderizar_casa_quadrilatera(cor_rgb cor_casa, vertice v1, vertice v2, vertice v3, vertice v4, float distancia_tabuleiro, char aresta) {

if (aresta == 'n')
glBegin(GL_POLYGON);
else {
	glBegin(GL_LINE_LOOP);
}

glColor3f(cor_casa.r, cor_casa.g, cor_casa.b);
glVertex3f(v1.x, v1.y + distancia_tabuleiro, v1.z);
glVertex3f(v2.x, v2.y + distancia_tabuleiro, v2.z);
glVertex3f(v3.x, v3.y + distancia_tabuleiro, v3.z);
glVertex3f(v4.x, v4.y + distancia_tabuleiro, v4.z);
glEnd();

}

void renderizar_casa_hexagonal(cor_rgb cor_casa, vertice v1, vertice v2, vertice v3, vertice v4, vertice v5, vertice v6, float distancia_tabuleiro, char aresta) {
	if (aresta == 'n')
		glBegin(GL_POLYGON);
	else {
		glBegin(GL_LINE_LOOP);
	}
	glColor3f(cor_casa.r, cor_casa.g, cor_casa.b);

	glVertex3f(v1.x, v1.y + distancia_tabuleiro, v1.z);
	glVertex3f(v2.x, v2.y + distancia_tabuleiro, v2.z);
	glVertex3f(v3.x, v3.y + distancia_tabuleiro, v3.z);
	glVertex3f(v4.x, v4.y + distancia_tabuleiro, v4.z);
	glVertex3f(v5.x, v5.y + distancia_tabuleiro, v5.z);
	glVertex3f(v6.x, v6.y + distancia_tabuleiro, v6.z);

	glEnd();

}

void aplicar_casas_triangulares(vertice v, int quant_casas_h, int quant_casas_v, float distancia_tabuleiro, cor_rgb cor_casa, int alternar, char preencher, char aresta) {
	float tamanho_casa_v, tamanho_casa_h;
	int bandeira = 0;
	int alterar_inicial = bandeira;

	tamanho_casa_v = (v.z * 2 / quant_casas_v);
	tamanho_casa_h = (v.x * 4 / (quant_casas_h + 1));
	vertice v_atual1, v_atual2, v_atual3;

	if (preencher == 's') {

		for (int c = 0; c < quant_casas_v; c++) {

			v_atual1 = v;
			v_atual1.z = v.z - tamanho_casa_v * c;
			v_atual2 = v_atual1;
			v_atual2.x = v_atual1.x - tamanho_casa_h / 2;
			v_atual2.z = v_atual1.z - tamanho_casa_v;
			v_atual3 = v_atual1;
			v_atual3.x = v_atual1.x - tamanho_casa_h;

			for (int i = 0; i < quant_casas_h; i++) {
				if (i == 0) {
					alterar_inicial = bandeira;
				}

				if (alternar == 0)
					renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);

				else if (alternar == 1) {
					if (bandeira == 0) {
						renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);
						bandeira = 1;
					}
					else
						bandeira = 0;
				}

				else if (alternar == 2) {
					if (bandeira == 1) {
						renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);
						bandeira = 0;
					}
					else
						bandeira = 1;
				}

				v_atual1 = v_atual2;
				v_atual2 = v_atual3;
				v_atual3 = v_atual1;
				v_atual3.x = v_atual1.x - tamanho_casa_h;
			}

			if (alterar_inicial == 0) {
				bandeira = 1;
			}
			else
				bandeira = 0;
		}
	}
	else if (preencher == 'n') {
		float aux_vx;

			v_atual1 = v;	
			v_atual2 = v_atual1;
			v_atual2.x = v_atual1.x - tamanho_casa_h / 2;
			v_atual2.z = v_atual1.z - tamanho_casa_v;
			v_atual3 = v_atual1;
			v_atual3.x = v_atual1.x - tamanho_casa_h;

			for (int i = 0; i < quant_casas_h; i++) {

				if (alternar == 0)
					renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);

				else if (alternar == 1) {
					if (bandeira == 0) {
						renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);
						bandeira = 1;
					}
					else
						bandeira = 0;
				}

				else if (alternar == 2) {
					if (bandeira == 1) {
						renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);
						bandeira = 0;
					}
					else
						bandeira = 1;
				}

				v_atual1 = v_atual2;
				v_atual2 = v_atual3;
				v_atual3 = v_atual1;
				v_atual3.x = v_atual1.x - tamanho_casa_h;
			}
			aux_vx = v_atual1.x + tamanho_casa_h/2;

		for (int c = 0; c < 2; c++) {
			v_atual1 = v;
			if (c == 0)
				v_atual1.x = aux_vx;
			else
				bandeira = 1;
			for (int i = 0; i < (quant_casas_v - 2); i++) {
				
				v_atual1.z = v.z - tamanho_casa_v * (i + 1);
				v_atual2 = v_atual1;
				v_atual2.x = v_atual1.x - tamanho_casa_h / 2;
				v_atual2.z = v_atual1.z - tamanho_casa_v;
				v_atual3 = v_atual1;
				v_atual3.x = v_atual1.x - tamanho_casa_h;
				if (alternar == 0)
					renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);

				else if (alternar == 1) {
					if (bandeira == 0) {
						renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);
						bandeira = 1;
					}
					else
						bandeira = 0;
				}

				else if (alternar == 2) {
					if (bandeira == 1) {
						renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);
						bandeira = 0;
					}
					else
						bandeira = 1;
				}

			}
		}

		v_atual1 = v;
		v_atual1.z = v.z - tamanho_casa_v * (quant_casas_v - 1);
		v_atual2 = v_atual1;
		v_atual2.x = v_atual1.x - tamanho_casa_h / 2;
		v_atual2.z = v_atual1.z - tamanho_casa_v;
		v_atual3 = v_atual1;
		v_atual3.x = v_atual1.x - tamanho_casa_h;

		for (int i = 0; i < quant_casas_h; i++) {

			if (alternar == 0)
				renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);

			else if (alternar == 1) {
				if (bandeira == 0) {
					renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);
					bandeira = 1;
				}
				else
					bandeira = 0;
			}

			else if (alternar == 2) {
				if (bandeira == 1) {
					renderizar_casa_triangular(cor_casa, v_atual1, v_atual2, v_atual3, distancia_tabuleiro, aresta);
					bandeira = 0;
				}
				else
					bandeira = 1;
			}
			v_atual1 = v_atual2;
			v_atual2 = v_atual3;
			v_atual3 = v_atual1;
			v_atual3.x = v_atual1.x - tamanho_casa_h;
		}
	}
	else
		return;


}

void aplicar_casas_quadrilateras(vertice v, int quant_casas_h, int quant_casas_v, float distancia_tabuleiro, cor_rgb cor_casa, int alternar, char preencher, char aresta) {
	float tamanho_casa_v, tamanho_casa_h;
	int bandeira = 0;
	int alterar_inicial = bandeira;

	tamanho_casa_v = (v.z * 2 / quant_casas_v);
	tamanho_casa_h = (v.x * 2 / quant_casas_h);
	vertice v_atual1, v_atual2, v_atual3, v_atual4;

	if (preencher == 's') {

		for (int c = 0; c < quant_casas_v; c++) {

			v_atual1 = v;
			v_atual1.z = v.z - tamanho_casa_v * c;
			v_atual2 = v_atual1;
			v_atual2.z = v_atual1.z - tamanho_casa_v;
			v_atual3 = v_atual2;
			v_atual3.x = v_atual2.x - tamanho_casa_h;
			v_atual4 = v_atual1;
			v_atual4.x = v_atual1.x - tamanho_casa_h;

			for (int i = 0; i < quant_casas_h; i++) {
				if (i == 0) {
					alterar_inicial = bandeira;
				}
				if (alternar == 0)
					renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);

				else if (alternar == 1) {
					if (bandeira == 0) {
						renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);
						bandeira = 1;
					}
					else
						bandeira = 0;
				}

				else if (alternar == 2) {
					if (bandeira == 1) {
						renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);
						bandeira = 0;
					}
					else
						bandeira = 1;
				}

				v_atual1 = v_atual4;
				v_atual2 = v_atual3;
				v_atual3.x = v_atual2.x - tamanho_casa_h;
				v_atual4.x = v_atual1.x - tamanho_casa_h;
			}
			if (alterar_inicial == 0) {
				bandeira = 1;
			}
			else
				bandeira = 0;
		}
	}

	else if (preencher == 'n') {

			v_atual1 = v;
			v_atual2 = v_atual1;
			v_atual2.z = v_atual1.z - tamanho_casa_v;
			v_atual3 = v_atual2;
			v_atual3.x = v_atual2.x - tamanho_casa_h;
			v_atual4 = v_atual1;
			v_atual4.x = v_atual1.x - tamanho_casa_h;

			for (int i = 0; i < quant_casas_h; i++) {
				if (alternar == 0)
					renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);

				else if (alternar == 1) {
					if (bandeira == 0) {
						renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);
						bandeira = 1;
					}
					else
						bandeira = 0;
				}

				else if (alternar == 2) {
					if (bandeira == 1) {
						renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);
						bandeira = 0;
					}
					else
						bandeira = 1;
				}

				v_atual1 = v_atual4;
				v_atual2 = v_atual3;
				v_atual3.x = v_atual2.x - tamanho_casa_h;
				v_atual4.x = v_atual1.x - tamanho_casa_h;
			}

		for (int c = 0; c < 2; c++) {
			v_atual1 = v;
			if (c == 0) {
				v_atual1.x = v.x - tamanho_casa_h * (quant_casas_h - 1);
			
			}
			else 
				bandeira = 1;
			

			for (int i = 0; i < (quant_casas_v - 2); i++) {
				v_atual1.z = v.z - tamanho_casa_v * (i+1);
				v_atual2 = v_atual1;
				v_atual2.z = v_atual1.z - tamanho_casa_v;
				v_atual3 = v_atual2;
				v_atual3.x = v_atual2.x - tamanho_casa_h;
				v_atual4 = v_atual1;
				v_atual4.x = v_atual1.x - tamanho_casa_h;

				if (alternar == 0)
					renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);

				else if (alternar == 1) {
					if (bandeira == 0) {
						renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);
						bandeira = 1;
					}
					else
						bandeira = 0;
				}

				else if (alternar == 2) {
					if (bandeira == 1) {
						renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);
						bandeira = 0;
					}
					else
						bandeira = 1;
				}

			}
		}

		v_atual1 = v;
		v_atual1.z = v.z - tamanho_casa_v * (quant_casas_v - 1);
		v_atual2 = v_atual1;
		v_atual2.z = v_atual1.z - tamanho_casa_v;
		v_atual3 = v_atual2;
		v_atual3.x = v_atual2.x - tamanho_casa_h;
		v_atual4 = v_atual1;
		v_atual4.x = v_atual1.x - tamanho_casa_h;
	
		for (int i = 0; i < quant_casas_h; i++) {
			if (i == 0) {
				alterar_inicial = bandeira;
			}
			if (alternar == 0)
				renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);

			else if (alternar == 1) {
				if (bandeira == 0) {
					renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);
					bandeira = 1;
				}
				else
					bandeira = 0;
			}

			else if (alternar == 2) {
				if (bandeira == 1) {
					renderizar_casa_quadrilatera(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, distancia_tabuleiro, aresta);
					bandeira = 0;
				}
				else
					bandeira = 1;
			}

			v_atual1 = v_atual4;
			v_atual2 = v_atual3;
			v_atual3.x = v_atual2.x - tamanho_casa_h;
			v_atual4.x = v_atual1.x - tamanho_casa_h;
		}
	}
	else
		return;

}

void aplicar_casas_hexagonais(vertice v, int quant_casas_h, int quant_casas_v, float distancia_tabuleiro, cor_rgb cor_casa, int alternar, char preencher, char aresta) {
	float tamanho_casa_v, tamanho_casa_h;
	int bandeira = 0;
	int alterar_inicial = bandeira;
	float x;
	x = quant_casas_v % 2;

	tamanho_casa_v = (v.z * 2) / (((quant_casas_v - 1) / 4) * 3 + 1);
	if (x == 0)
		tamanho_casa_v = v.z * 2 / (((quant_casas_v - 1) / 4 * 3 + 1) + 0.75);


	tamanho_casa_h = (v.x * 2 / (quant_casas_h + 0.5));
	if (quant_casas_v == 1) 
		tamanho_casa_h = (v.x * 2 / quant_casas_h);

	vertice v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6;

	if (preencher == 's') {

		for (int c = 0; c < quant_casas_v; c++) {

			if (c > 0)
				v.z = v.z - (tamanho_casa_v / 4) * 3;

			v_atual1 = v;

			if (bandeira == 1) {
				v_atual1.x = v.x - tamanho_casa_h;
			}
			else {
				v_atual1.x = v.x - tamanho_casa_h / 2;
			}
			v_atual2 = v_atual1;
			v_atual2.x = v_atual1.x - tamanho_casa_h / 2;
			v_atual2.z = v_atual1.z - tamanho_casa_v / 4;
			v_atual3 = v_atual2;
			v_atual3.z = v_atual2.z - tamanho_casa_v / 2;
			v_atual4 = v_atual1;
			v_atual4.z = v_atual1.z - tamanho_casa_v;
			v_atual5 = v_atual4;
			v_atual5.x = v_atual4.x + tamanho_casa_h / 2;
			v_atual5.z = v_atual4.z + tamanho_casa_v / 4;
			v_atual6 = v_atual5;
			v_atual6.z = v_atual5.z + tamanho_casa_v / 2;

			for (int i = 0; i < quant_casas_h; i++) {
				if (i == 0) {
					alterar_inicial = bandeira;
				}
				if (alternar == 0)
					renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);

				else if (alternar == 1) {
					if (bandeira == 0) {
						renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);
						bandeira = 1;
					}
					else
						bandeira = 0;
				}

				else if (alternar == 2) {
					if (bandeira == 1) {
						renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);
						bandeira = 0;
					}
					else
						bandeira = 1;
				}
				v_atual1.x = v_atual1.x - tamanho_casa_h;
				v_atual2 = v_atual1;
				v_atual2.x = v_atual1.x - tamanho_casa_h / 2;
				v_atual2.z = v_atual1.z - tamanho_casa_v / 4;
				v_atual3 = v_atual2;
				v_atual3.z = v_atual2.z - tamanho_casa_v / 2;
				v_atual4 = v_atual1;
				v_atual4.z = v_atual1.z - tamanho_casa_v;
				v_atual5 = v_atual4;
				v_atual5.x = v_atual4.x + tamanho_casa_h / 2;
				v_atual5.z = v_atual4.z + tamanho_casa_v / 4;
				v_atual6 = v_atual5;
				v_atual6.z = v_atual5.z + tamanho_casa_v / 2;

			}

			if (alterar_inicial == 0) {
				bandeira = 1;
			}
			else
				bandeira = 0;
		}
	}

	else if (preencher == 'n') {
		int aux_bandeira;
		v_atual1 = v;
		v_atual1.x = v.x - tamanho_casa_h / 2;
		v_atual2 = v_atual1;
		v_atual2.x = v_atual1.x - tamanho_casa_h / 2;
		v_atual2.z = v_atual1.z - tamanho_casa_v / 4;
		v_atual3 = v_atual2;
		v_atual3.z = v_atual2.z - tamanho_casa_v / 2;
		v_atual4 = v_atual1;
		v_atual4.z = v_atual1.z - tamanho_casa_v;
		v_atual5 = v_atual4;
		v_atual5.x = v_atual4.x + tamanho_casa_h / 2;
		v_atual5.z = v_atual4.z + tamanho_casa_v / 4;
		v_atual6 = v_atual5;
		v_atual6.z = v_atual5.z + tamanho_casa_v / 2;

		for (int i = 0; i < quant_casas_h; i++) {
			if (alternar == 0)
				renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);

			else if (alternar == 1) {
				if (bandeira == 0) {
					renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);
					bandeira = 1;
				}
				else
					bandeira = 0;
			}

			else if (alternar == 2) {
				if (bandeira == 1) {
					renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);
					bandeira = 0;
				}
				else
					bandeira = 1;
			}
			v_atual1.x = v_atual1.x - tamanho_casa_h;
			v_atual2 = v_atual1;
			v_atual2.x = v_atual1.x - tamanho_casa_h / 2;
			v_atual2.z = v_atual1.z - tamanho_casa_v / 4;
			v_atual3 = v_atual2;
			v_atual3.z = v_atual2.z - tamanho_casa_v / 2;
			v_atual4 = v_atual1;
			v_atual4.z = v_atual1.z - tamanho_casa_v;
			v_atual5 = v_atual4;
			v_atual5.x = v_atual4.x + tamanho_casa_h / 2;
			v_atual5.z = v_atual4.z + tamanho_casa_v / 4;
			v_atual6 = v_atual5;
			v_atual6.z = v_atual5.z + tamanho_casa_v / 2;

		}
		aux_bandeira = bandeira;
		vertice aux_v = v;

		for (int c = 0; c < 2; c++) {
			aux_v = v;
			if (c == 0) {
				if(bandeira == 0)
					aux_v.x = aux_v.x - tamanho_casa_h * (quant_casas_h - 0.5);
				else
					aux_v.x = aux_v.x - tamanho_casa_h * (quant_casas_h - 1);
			}
			else
				bandeira = 1;

			for (int i = 0; i < quant_casas_v - 2; i++) {

					aux_v.z = aux_v.z - (tamanho_casa_v / 4) * 3;

				v_atual1 = aux_v;
				if (c == 0) {
					if (bandeira == 1) {
						if (aux_bandeira == 1)
							v_atual1.x = aux_v.x - tamanho_casa_h;
						else
							v_atual1.x = aux_v.x;
					}
					else {
						v_atual1.x = aux_v.x - tamanho_casa_h / 2;
					}
				}
				else {
					if (bandeira == 1) {
						v_atual1.x = aux_v.x - tamanho_casa_h;
					}
					else {
						v_atual1.x = aux_v.x - tamanho_casa_h / 2;
					}
				}
				v_atual2 = v_atual1;
				v_atual2.x = v_atual1.x - tamanho_casa_h / 2;
				v_atual2.z = v_atual1.z - tamanho_casa_v / 4;
				v_atual3 = v_atual2;
				v_atual3.z = v_atual2.z - tamanho_casa_v / 2;
				v_atual4 = v_atual1;
				v_atual4.z = v_atual1.z - tamanho_casa_v;
				v_atual5 = v_atual4;
				v_atual5.x = v_atual4.x + tamanho_casa_h / 2;
				v_atual5.z = v_atual4.z + tamanho_casa_v / 4;
				v_atual6 = v_atual5;
				v_atual6.z = v_atual5.z + tamanho_casa_v / 2;

				if (alternar == 0)
					renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);

				else if (alternar == 1) {
					if (bandeira == 0) {
						renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);
						bandeira = 1;
					}
					else
						bandeira = 0;
				}

				else if (alternar == 2) {
					if (bandeira == 1) {
						renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);
						bandeira = 0;
					}
					else
						bandeira = 1;
				}
			}
		}
		v_atual1.z = v_atual1.z - (tamanho_casa_v / 4) * 3;
		if(bandeira == 0)
			v_atual1.x = v_atual1.x + tamanho_casa_h * 1.5;
		else
			v_atual1.x = v_atual1.x + tamanho_casa_h/2;
		for (int i = 0; i < quant_casas_h; i++) {
			
			v_atual1.x = v_atual1.x - tamanho_casa_h;
			v_atual2 = v_atual1;
			v_atual2.x = v_atual1.x - tamanho_casa_h / 2;
			v_atual2.z = v_atual1.z - tamanho_casa_v / 4;
			v_atual3 = v_atual2;
			v_atual3.z = v_atual2.z - tamanho_casa_v / 2;
			v_atual4 = v_atual1;
			v_atual4.z = v_atual1.z - tamanho_casa_v;
			v_atual5 = v_atual4;
			v_atual5.x = v_atual4.x + tamanho_casa_h / 2;
			v_atual5.z = v_atual4.z + tamanho_casa_v / 4;
			v_atual6 = v_atual5;
			v_atual6.z = v_atual5.z + tamanho_casa_v / 2;

			if (i == 0) {
				alterar_inicial = bandeira;
			}
			if (alternar == 0)
				renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);

			else if (alternar == 1) {
				if (bandeira == 0) {
					renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);
					bandeira = 1;
				}
				else
					bandeira = 0;
			}

			else if (alternar == 2) {
				if (bandeira == 1) {
					renderizar_casa_hexagonal(cor_casa, v_atual1, v_atual2, v_atual3, v_atual4, v_atual5, v_atual6, distancia_tabuleiro, aresta);
					bandeira = 0;
				}
				else
					bandeira = 1;
			}
		}
	}
	else
		return;
}

void alterar_iluminacao_tabuleiro(int tipo_luz, float cor_luz[], float posicao_luz[]) {

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	if(tipo_luz == 0)
	glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz);
	else if(tipo_luz == 1)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
	else if(tipo_luz == 2)
	glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);

	glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);

}

void posicionar_camera(int angulo, float largura_area, float altura_area, float distancia_minima, float distancia_maxima, posicao_camera camera) {
	gluPerspective(angulo, largura_area / altura_area, distancia_minima, distancia_maxima);
	gluLookAt(camera.pos_x, camera.pos_y, camera.pos_z, camera.mira_x, camera.mira_y, camera.mira_z, camera.lado_x, camera.lado_y, camera.lado_z);
}

void aplicar_textura(vertice v1, vertice v2, vertice v3, vertice v4, char nome_imagem[100]) {
	glEnable(GL_TEXTURE_2D);
	int quant_texturas = 1;
	/*int *texture_id;
	texture_id = malloc(sizeof(GLuint)*quant_texturas);*/
	GLuint texture_id[1];

	glGenTextures(quant_texturas, texture_id);
	texture_id[0] = 1;
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);

	int largura_imagem, altura_imagem;
	unsigned char* imagem = SOIL_load_image(nome_imagem, &largura_imagem, &altura_imagem, 0, SOIL_LOAD_RGB);
	//unsigned char* imagem = SOIL_load_image("textura.jpg", &largura_imagem, &altura_imagem, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura_imagem, altura_imagem, 0, GL_RGB, GL_UNSIGNED_BYTE, imagem);
	SOIL_free_image_data(imagem);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(v1.x, v1.y, v1.z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(v2.x, v2.y, v2.z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(v3.x, v3.y, v3.z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(v4.x, v4.y, v4.z);

}

vertice calcular_vertice_tabuleiro(float comprimento_tabuleiro, float espessura_tabuleiro, float largura_tabuleiro) {

	vertice v;
	v.x = comprimento_tabuleiro / 200;
	v.z = largura_tabuleiro / 200;
	v.y = espessura_tabuleiro / 200;
	return v;
}

void renderizar_corpo_tabuleiro(vertice v, cor_rgb cor_tabuleiro, bool ativar_clear) {

	if (ativar_clear == true)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TOPO
	glBegin(GL_POLYGON);
	glColor3f(cor_tabuleiro.r, cor_tabuleiro.g, cor_tabuleiro.b);
	glVertex3f(v.x, v.y, -v.z);
	glVertex3f(v.x, v.y, v.z);
	glVertex3f(-v.x, v.y, v.z);
	glVertex3f(-v.x, v.y, -v.z);

	glEnd();

	// BASE
	glBegin(GL_POLYGON);
	glColor3f(cor_tabuleiro.r, cor_tabuleiro.g, cor_tabuleiro.b);
	glVertex3f(v.x, -v.y, -v.z);
	glVertex3f(v.x, -v.y, v.z);
	glVertex3f(-v.x, -v.y, v.z);
	glVertex3f(-v.x, -v.y, -v.z);
	glEnd();

	// LATERAL DIREITA
	glBegin(GL_POLYGON);
	glColor3f(cor_tabuleiro.r, cor_tabuleiro.g, cor_tabuleiro.b);
	glVertex3f(v.x, -v.y, -v.z);
	glVertex3f(v.x, -v.y, v.z);
	glVertex3f(v.x, v.y, v.z);
	glVertex3f(v.x, v.y, -v.z);
	glEnd();

	// ESQUERDA
	glBegin(GL_POLYGON);
	glColor3f(cor_tabuleiro.r, cor_tabuleiro.g, cor_tabuleiro.b);
	glVertex3f(-v.x, v.y, -v.z);
	glVertex3f(-v.x, v.y, v.z);
	glVertex3f(-v.x, -v.y, v.z);
	glVertex3f(-v.x, -v.y, -v.z);
	glEnd();

	// LATERAL FRONTAL
	glBegin(GL_POLYGON);
	glColor3f(cor_tabuleiro.r, cor_tabuleiro.g, cor_tabuleiro.b);
	glVertex3f(v.x, v.y, v.z);
	glVertex3f(v.x, -v.y, v.z);
	glVertex3f(-v.x, -v.y, v.z);
	glVertex3f(-v.x, v.y, v.z);
	glEnd();

	// LATERAL TRASEIRA
	glBegin(GL_POLYGON);
	glColor3f(cor_tabuleiro.r, cor_tabuleiro.g, cor_tabuleiro.b);
	glVertex3f(v.x, -v.y, -v.z);
	glVertex3f(v.x, v.y, -v.z);
	glVertex3f(-v.x, v.y, -v.z);
	glVertex3f(-v.x, -v.y, -v.z);
	glEnd();

}

void tecla_rotacionar(int tecla, int x, int y) {

	if (tecla == GLUT_KEY_RIGHT)
		rotate_z += 5;

	else if (tecla == GLUT_KEY_LEFT)
		rotate_z -= 5;

	else if (tecla == GLUT_KEY_UP)
		rotate_x += 5;

	else if (tecla == GLUT_KEY_DOWN)
		rotate_x -= 5;
	else if (tecla == GLUT_KEY_F1)
		rotate_y += 5;
	else if (tecla == GLUT_KEY_F2)
		rotate_y -= 5;

	glutPostRedisplay();
	
}

void rotacionar(double rotate_x, double rotate_y, double rotate_z) {
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
}