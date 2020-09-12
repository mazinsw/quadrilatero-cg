#ifndef _QUADRILATERO_H_
#define _QUADRILATERO_H_
#include "brush.h"

/**
 * classe que representa uma coordenada no R2
 */
class Coordenada
{
private:
	int x;
	int y;
	float r, g, b;
public:
	/**
	 * Cria uma coordenada com x e y na origem
	 */
	Coordenada();

	/**
	 * Cria uma coordenada com o x e y
	 */
	Coordenada(int x, int y);

	/**
	 * Obt�m o x da coordenada
	 */
	inline int getX()
	{
		return x;
	}

	/**
	 * Atualiza o x da coordenada
	 */
	inline void setX(int x)
	{
		this->x = x;
	}

	/**
	 * Obt�m o y da coordenada
	 */
	inline int getY()
	{
		return y;
	}

	/**
	 * Atualiza o y da coordenada
	 */
	inline void setY(int y)
	{
		this->y = y;
	}

	/**
	 * Atualiza o x e y da coordenada
	 */
	inline void setXY(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	
	/**
	 * Obt�m o componente R da cor
	 */
	inline float getR()
	{
		return r;
	}

	/**
	 * Obt�m o componente G da cor
	 */
	inline float getG()
	{
		return g;
	}
	
	/**
	 * Obt�m o componente B da cor
	 */
	inline float getB()
	{
		return b;
	}

	/**
	 * Atualiza a cor da coordenada na renderiza��o
	 * 
	 */
	inline void setColor(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	/**
	 * faz uma c�pia de outra coordenada
	 *
	 */
	Coordenada& operator=(const Coordenada& other);
};

/**
 * classe que representa um quadril�tero
 */
class Quadrilatero
{
private:
	Coordenada p1;
	Coordenada p2;
	Coordenada p3;
	Coordenada p4;
	Brush* preenchimento;
public:
	/**
	 * Cria um quadril�tero sem preenchimento
	 */
	Quadrilatero();

	/**
	 * Desenha o quadril�tero no buffer
	 * 
	 */
	virtual void render();

	/**
	 * Obt�m a primeira coordenada do quadril�tero
	 */
	inline Coordenada& getP1()
	{
		return p1;
	}

	/**
	 * Obt�m a segunda coordenada do quadril�tero
	 */
	inline Coordenada& getP2()
	{
		return p2;
	}

	/**
	 * Obt�m a terceira coordenada do quadril�tero
	 */
	inline Coordenada& getP3()
	{
		return p3;
	}

	/**
	 * Obt�m a quarta coordenada do quadril�tero
	 */
	inline Coordenada& getP4()
	{
		return p4;
	}

	/**
	 * Atualiza o sistema de preenchimento no desenho do quadril�tero
	 */
	inline void setBrush(Brush* preenchimento)
	{
		this->preenchimento = preenchimento;
	}
	
	/**
	 * Obt�m o sistema de preenchimento do quadril�tero
	 */
	inline Brush* getBrush()
	{
		return preenchimento;
	}

	/**
	 * Verifica se um ponto est� dentro do quadril�tero
	 * 
	 * par�metros:
	 *   x: posi��o x do ponto
	 *   y: posi��o y do ponto
	 * returno
	 *   true se o ponto estiver dentro do quadril�tero ou false 
	 *   caso contr�rio
	 */
	bool isIn(int x, int y);
	
	/**
	 * Faz uma c�pia de outro quadril�tero
	 *
	 */
	Quadrilatero& operator=(const Quadrilatero& other);
};

#endif /* _QUADRILATERO_H_ */
