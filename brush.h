#ifndef _BRUSH_H_
#define _BRUSH_H_

/**
 * Classe abstrata para representar o preenchimento de um quadrilátero
 * 
 */
class Brush
{
public:
	/**
	 * Aplica os efeitos do preenchimento
	 * 
	 */
	virtual void apply() = 0;
};

#endif /* _BRUSH_H_ */