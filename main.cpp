#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <list>
#include "classes/glwindow.h"
#include "quadrilatero.h"
#include "mascara.h"
#include "solido.h"
#include "degrade.h"
#include "vazado.h"

const float cores[10][3] =
{
	{ 1.0f, 1.0f, 1.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 1.0f },
	{ 1.0f, 0.0f, 1.0f },
	{ 1.0f, 0.5f, 0.2f },
	{ 0.5f, 0.5f, 0.5f },
	{ 0.1f, 0.4f, 0.8f },
	{ 0.0f, 0.0f, 0.0f }
};

class Preenchimento: public GLWindowBase
{
private:
	std::list<Quadrilatero*> quads;
	/* quadrilátero que está sendo desenhado */
	Quadrilatero quad_atu;
	/* quantidade de pontos já definidos */
	int qtd_coord;
	/* cor da próxima linha */
	float r_fg, g_fg, b_fg;
	/* cor do fundo */
	float r_bg, g_bg, b_bg;
	/* posição do mouse */
	int x, y;
	/* quandriláterosde preenchimento */
	Quadrilatero itens[4];
	Mascara mascara;
	Solido solido;
	Degrade degrade;
	Vazado vazado;
protected:
	/**
	 * Limpa todos os quadriláteros
	 */
	void limpar()
	{
		std::list<Quadrilatero*>::iterator it;
		// como os quadriláteros são ponteiros é necessário destruí-los primeiro
		for(it = quads.begin(); it != quads.end(); it++)
			delete *it;
		quads.clear();
	}

	/**
	 * Altera a cor dos itens de preenchimento
	 */
	void setItensColor(float r, float g, float b)
	{
		// sólido
		itens[0].getP1().setColor(r, g, b);
		itens[0].getP2().setColor(r, g, b);
		itens[0].getP3().setColor(r, g, b);
		itens[0].getP4().setColor(r, g, b);

		// preenchimento
		itens[2].getP1().setColor(r, g, b);
		itens[2].getP2().setColor(r, g, b);
		itens[2].getP3().setColor(r, g, b);
		itens[2].getP4().setColor(r, g, b);

		// vazado
		itens[3].getP1().setColor(r, g, b);
		itens[3].getP2().setColor(r, g, b);
		itens[3].getP3().setColor(r, g, b);
		itens[3].getP4().setColor(r, g, b);
	}


	/**
	 * Altera a cor atual do quadrilátero que setá sendo desenhado
	 */
	void setCorAtual(float r, float g, float b)
	{
		quad_atu.getP1().setColor(r, g, b);
		quad_atu.getP2().setColor(r, g, b);
		quad_atu.getP3().setColor(r, g, b);
		quad_atu.getP4().setColor(r, g, b);
	}

	/**
	 * desenha no plano 2D
	 */
	virtual void onCreate()
	{
		int x_offset = (getWidth() - 32 * 4 - 3 * 10) / 2;

		resize2DScene();
		for(int i = 0; i < 4; i++)
		{
			itens[i].getP1().setXY(x_offset +  i      * (32 + 10), 10);
			itens[i].getP2().setXY(x_offset +  i      * (32 + 10), 10 + 32);
			itens[i].getP3().setXY(x_offset + (i + 1) * (32 + 10) - 10, 10 + 32);
			itens[i].getP4().setXY(x_offset + (i + 1) * (32 + 10) - 10, 10);
		}
	}

	/**
	 * Obtem as coordenadas do clique do mouse para formar os quadriláteros
	 */
	virtual void onMouseDown(int x, int y, int button, int state)
	{
		std::list<Quadrilatero*>::reverse_iterator rit;
		Quadrilatero* quad;
		Coordenada* coord;
		int i;

		if(button == SDL_BUTTON_LEFT)
		{
			// clique sobre quadriláteros somente quando não estiver criando
			if(qtd_coord == 0)
			{
				// verifica se clicou em alguns do itens
				for(i = 0; i < 4; i++)
				{
					if(itens[i].isIn(x, y))
					{
						// clicou! atualiza o preenchimento atual
						quad = &itens[i];
						quad_atu.setBrush(quad->getBrush());
						setCorAtual(quad->getP1().getR(),
									quad->getP1().getG(),
									quad->getP1().getB());
						return;
					}
				}
				// percorre todos os quadriláteros verificando se clicou sobre
				for(rit = quads.rbegin(); rit != quads.rend(); rit++)
				{
					quad = *rit;
					if(quad->isIn(x, y))
					{
						// clicou! atualiza para o brush atual
						quad->setBrush(quad_atu.getBrush());
						// escolhe uma cor aleatóriamente
						if(quad->getBrush() == &degrade)
						{
							// com degradê
							i = rand() % 10;
							quad->getP1().setColor(cores[i][0], cores[i][1], cores[i][2]);
							i = rand() % 10;
							quad->getP2().setColor(cores[i][0], cores[i][1], cores[i][2]);
							i = rand() % 10;
							quad->getP3().setColor(cores[i][0], cores[i][1], cores[i][2]);
							i = rand() % 10;
							quad->getP4().setColor(cores[i][0], cores[i][1], cores[i][2]);
						}
						else
						{
							// cor única
							i = rand() % 10;
							quad->getP1().setColor(cores[i][0], cores[i][1], cores[i][2]);
							quad->getP2().setColor(cores[i][0], cores[i][1], cores[i][2]);
							quad->getP3().setColor(cores[i][0], cores[i][1], cores[i][2]);
							quad->getP4().setColor(cores[i][0], cores[i][1], cores[i][2]);
						}
						return;
					}
				}
			}
			qtd_coord++;
			switch(qtd_coord)
			{
			case 1:
				coord = &quad_atu.getP1();
				break;
			case 2:
				coord = &quad_atu.getP2();
				break;
			case 3:
				coord = &quad_atu.getP3();
				break;
			default:
				coord = &quad_atu.getP4();
			}
			coord->setX(x);
			coord->setY(y);
			// já formou 4 pontos
			if(qtd_coord > 3)
			{
				quad = new Quadrilatero();
				*quad = quad_atu;
				quads.push_back(quad);
				qtd_coord = 0;
			}
		}
	}

	/**
	 * atualiza a posição do mouse
	 */
	virtual void onMouseMove(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	/**
	 * trata os eventos do teclado
	 */
	virtual void onKeyDown(int key, int state)
	{
		int cor;

		// o primeiro ESC cancela o desenho da linha
		if(key == SDLK_ESCAPE)
		{
			if(qtd_coord > 0)
				qtd_coord = 0;
			else
				close();
		}
		// limpa a tela
		else if(key == SDLK_DELETE)
		{
			limpar();
			qtd_coord = 0;
		}
		// teclas de 0 até 9 para controle das cores
		else if((key >= SDLK_0 && key <= SDLK_9) || (key >= SDLK_KP0 && key <= SDLK_KP9))
		{
			// transforma de 0 à 9
			if(key >= SDLK_KP0)
				cor = key - SDLK_KP0;
			else
				cor = key - SDLK_0;
			// alterando a cor da linha
			if((state & LeftCtrl) == 0)
			{
				r_fg = cores[cor][0];
				g_fg = cores[cor][1];
				b_fg = cores[cor][2];
				setItensColor(r_fg, g_fg, b_fg);
				// atualiza a cor do quadrilátero que está sendo desenhado
				if(quad_atu.getBrush() != &degrade)
					setCorAtual(r_fg, g_fg, b_fg);
			}
			else // alterando a cor do fundo com o Ctrl pressionado
			{
				r_bg = cores[cor][0];
				g_bg = cores[cor][1];
				b_bg = cores[cor][2];
			}
		}
		// apaga os pontos da linha com o backspace
		else if(key == SDLK_BACKSPACE)
		{
			if(qtd_coord > 1)
			{
				// a coordenada no ultimo ponto volta a ser a do penúltimo ponto
				qtd_coord--;
			}
		}
		else  // o outro ESC fecha a janela
			GLWindowBase::onKeyDown(key, state);
	}

	/**
	 * desenha as quads
	 */
	virtual void render()
	{
		std::list<Quadrilatero*>::iterator it;
		Quadrilatero* quad;

		// limpa o buffer
		glClearColor( r_bg, g_bg, b_bg, 0.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		// desenha os itens
		for(int i = 0; i < 4; i++)
			itens[i].render();

		// percorre todos os quadriláteros e desenha um por um
		for(it = quads.begin(); it != quads.end(); it++)
		{
			quad = *it;
			quad->render();
		}
		// desenha uma linha para sabermos o início e fim da mesma
		if(qtd_coord > 0)
		{
			glBegin( GL_LINE_STRIP );
			if(qtd_coord == 1)
				glColor3f( r_fg, g_fg, b_fg );
			else
				glColor3f( quad_atu.getP1().getR(), quad_atu.getP1().getG(), quad_atu.getP1().getB() );
			glVertex2i( quad_atu.getP1().getX(), quad_atu.getP1().getY() );
			if(qtd_coord > 1)
			{
				if(qtd_coord == 2)
					glColor3f( r_fg, g_fg, b_fg );
				else
					glColor3f( quad_atu.getP2().getR(), quad_atu.getP2().getG(), quad_atu.getP2().getB() );
				glVertex2i( quad_atu.getP2().getX(), quad_atu.getP2().getY() );
			}
			if(qtd_coord > 2)
			{
				if(qtd_coord == 3)
					glColor3f( r_fg, g_fg, b_fg );
				else
					glColor3f( quad_atu.getP3().getR(), quad_atu.getP3().getG(), quad_atu.getP3().getB() );
				glVertex2i( quad_atu.getP3().getX(), quad_atu.getP3().getY() );
			}
			glVertex2i( x, y );
			if(qtd_coord == 3)
			{
				glColor3f( r_fg, g_fg, b_fg );
				glVertex2i( quad_atu.getP1().getX(), quad_atu.getP1().getY() );
			}
			glEnd();
		}
		// mostra os quadriláteros
		swapBuffers();
	}
public:
	Preenchimento()
	{
		qtd_coord = 0;
		r_fg = g_fg = b_fg = 0.0f; // inicializa a cor da linha com branco
		r_bg = g_bg = b_bg = 1.0f; // inicializa a cor de fundo com preto
		quad_atu.setBrush(&solido);
		itens[0].setBrush(&solido);
		itens[1].setBrush(&degrade);
		itens[2].setBrush(&mascara);
		itens[3].setBrush(&vazado);
		// inicializa as cores do degradê
		itens[1].getP1().setColor(cores[1][0], cores[1][1], cores[1][2]);
		itens[1].getP2().setColor(cores[2][0], cores[2][1], cores[2][2]);
		itens[1].getP3().setColor(cores[3][0], cores[3][1], cores[3][2]);
		itens[1].getP4().setColor(cores[4][0], cores[4][1], cores[4][2]);
		setItensColor(0.0f, 0.0f, 0.0f);
	}

	~Preenchimento()
	{
		// antes de destruir a janela destroi os quadriláteros
		limpar();
	}
};

int main(int argc, char *argv[])
{
	Preenchimento lp;

	lp.setTitle("Preenchimento");
	return lp.start(argc, argv);
}

