#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/**
 * classe respons�vel por obter informa��es do monitor
 */
class Display
{
public:
	/** obt�m a largura em pixels da �rea do monitor */
	static int getWidth();
	/** obt�m a altura em pixels da �rea do monitor */
	static int getHeight();
};

#endif
