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
	 * Obtém o x da coordenada
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
	 * Obtém o y da coordenada
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
	 * Obtém o componente R da cor
	 */
	inline float getR()
	{
		return r;
	}

	/**
	 * Obtém o componente G da cor
	 */
	inline float getG()
	{
		return g;
	}
	
	/**
	 * Obtém o componente B da cor
	 */
	inline float getB()
	{
		return b;
	}

	/**
	 * Atualiza a cor da coordenada na renderização
	 * 
	 */
	inline void setColor(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	/**
	 * faz uma cópia de outra coordenada
	 *
	 */
	Coordenada& operator=(const Coordenada& other);
};

/**
 * classe que representa um quadrilátero
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
	 * Cria um quadrilátero sem preenchimento
	 */
	Quadrilatero();

	/**
	 * Desenha o quadrilátero no buffer
	 * 
	 */
	virtual void render();

	/**
	 * Obtém a primeira coordenada do quadrilátero
	 */
	inline Coordenada& getP1()
	{
		return p1;
	}

	/**
	 * Obtém a segunda coordenada do quadrilátero
	 */
	inline Coordenada& getP2()
	{
		return p2;
	}

	/**
	 * Obtém a terceira coordenada do quadrilátero
	 */
	inline Coordenada& getP3()
	{
		return p3;
	}

	/**
	 * Obtém a quarta coordenada do quadrilátero
	 */
	inline Coordenada& getP4()
	{
		return p4;
	}

	/**
	 * Atualiza o sistema de preenchimento no desenho do quadrilátero
	 */
	inline void setBrush(Brush* preenchimento)
	{
		this->preenchimento = preenchimento;
	}
	
	/**
	 * Obtém o sistema de preenchimento do quadrilátero
	 */
	inline Brush* getBrush()
	{
		return preenchimento;
	}

	/**
	 * Verifica se um ponto está dentro do quadrilátero
	 * 
	 * parãmetros:
	 *   x: posição x do ponto
	 *   y: posição y do ponto
	 * returno
	 *   true se o ponto estiver dentro do quadrilátero ou false 
	 *   caso contrário
	 */
	bool isIn(int x, int y);
	
	/**
	 * Faz uma cópia de outro quadrilátero
	 *
	 */
	Quadrilatero& operator=(const Quadrilatero& other);
};

#endif /* _QUADRILATERO_H_ */
