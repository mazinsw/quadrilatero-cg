#ifndef _GLWINDOW_H_
#define _GLWINDOW_H_
#include <SDL/SDL.h>

/**
 * representa��o de teclas de controle enviadas pelos m�todos
 * onKeyDown, onKeyPress, onKeyUp, onMouseDown e onMouseUp
 * por exemplo quando voc� pressiona Ctrl+P o state(estado) �
 * o LeftCtrl
**/
typedef enum
{
	LeftCtrl   = 0x01,
	RightCtrl  = 0x02,
	LeftShift  = 0x04,
	RightShift = 0x08,
	LeftAlt    = 0x10,
	RightAlt   = 0x20,
	FnKey      = 0x40,
	CapsLock   = 0x80
} KeyState;

/**
 * classe respons�vel por facilitar a implementa��o de uma janela
 * opengl, nela � poss�vel tamb�m receber eventos do mouse e do teclado
 * al�m de implementar fun��es que mudam a resolu��o para tela cheia, impedir
 * que o ponteiro do mouse saia da tela
**/
class GLWindowBase
{
public:
	GLWindowBase();
	~GLWindowBase();
	/****** Window *******/

	/** obt�m a largura em pixels da �rea da janela renderiz�vel */
	int getWidth();

	/** obt�m a altura em pixels da �rea da janela renderiz�vel */
	int getHeight();

	/** ajusta o quandro de renderiza��o para a configura��o atual do tamanho
	 * e configura para que seja criado objetos 3D
	**/
	void resize3DScene();

	/** ajusta o quadro de renderiza��o para a configura��o atual do tamanho
	 * e configura para que seja criado objetos 2D
	**/
	void resize2DScene();

	/** obt�m o estado atual da janela(tela cheia ou n�o) */
	bool inFullscreen();

	/** define o estado atual da janela(tela cheia ou n�o) */
	void setFullscreen(bool fullscreen);

	/** mostra ou esconde o cursor do mouse */
	void showMouse(bool show);

	/** move o cursor do mouse para a posi��o relativa � janela informada em x e y */
	void setMousePos(int x, int y);

	/** trava ou destrava o mouse da �rea da regi�o renderiz�vel */
	void lockMouse(bool lock);

	/** permite que o cursor do mouse, n�o perca o foco quando movido para
	 * fora da janela
	**/
	void setMouseCapture();

	/** libera o cursor do mouse e permite a perda de foco da janela */
	void releaseMouseCapture();

	/** inicia a execu��o da aplica��o criando a janela e configurando-a
	 * a fim de permitir a utiliza��o da biblioteca OpenGL
	**/
	int start(int argc, char * argv[]);

	/** Para a renderiza��o e fecha a aplica��o */
	void close();

	/** altera o t�tulo da janela para o informado no par�metro 'title' */
	void setTitle(const char * title);

	/** ont�m o t�tulo da janela */
	const char * getTitle();

	/** aplica na tela do monitor a imagem renderizada em 'render' */
	void swapBuffers();

	/** retorna a quantidade de quadros sendo desenhados a cada segundo */
	float getFPS();

	/** informa a quantidade de quandros a ser desenhado por segundo */
	void setFrameRate(int fps);

	/** controla o tempo da renderiza��o evitando a super acelera��o */
	void delay();
protected:
	//Render
	/** fun��o mais importante da aplica��o, respons�vel pelo desenho da janela
	 * para isso ela dever� ser herdada, a mesma j� � controlada por um
	 * temporizador que evita a acelera��o indesejada das anima��es
	**/
	virtual void render();

	/** obtem informa��o de como a janela ser�
	 * por padr�o a janela ter� 640x480 e 32 bits de profundidade,
	 * em tela normal, caso queira mudar basta herdar esse m�todo e atribuir
	 * os novos valores
	**/
	virtual void getWindowInfo(int & width, int & height, int & bpp,
							   bool & fullscreen);

	/** fun��o chamada pela fun��o 'start' no in�cio da mesma */
	virtual bool onInit(int argc, char * argv[]);

	/** fun��o chamda por 'start', ap�s a janela ter sido criada com sucesso */
	virtual void onCreate();

	/** fun��o chamada ao t�rmino do la�o que trata os eventos */
	virtual void onDestroy();

	//Events
	/** evento acionado quando � pressionado uma tecla, 'key' � essa tecla */
	virtual void onKeyDown(int key, int state);

	/** evento acionado quando � liberado uma tecla, 'key' � essa tecla */
	virtual void onKeyUp(int key, int state);

	/** evento acionado quando o mouse � movido */
	virtual void onMouseMove(int x, int y);

	/** evento acionado quando um bot�o do mouse � pressionado, 'button' �
	 * o n�mero desse bot�o e iniciado apartir do 1, x e y � a posi��o em que foi
	 * pressionado
	**/
	virtual void onMouseDown(int x, int y, int button, int state);

	/** evento acionado quando um bot�o do mouse � liberado, 'state' � o estado
	 * das teclas de controle Ctrl, Alt, Shift
	**/
	virtual void onMouseUp(int x, int y, int button, int state);

	/** evento acionado quando a janela � redimencionada */
	virtual void onResize(int newWidth, int newHeight);

	/** evento acionado quando a janela � movida */
	virtual void onMove(int x, int y);

	/** evento acionado quando o bot�o fechar da janela � clicado
	 * caso seja retornado true, a janela ser� fechada, e se false for
	 * retornado nada aconecer� com a janela
	**/
	virtual bool onClose();
private:
	/* M�todos privados acess�veis somente a essa classe ou por meio de
	 * fun��es get e set
	 */
	/* vari�vel respons�vel pelo la�o principal do programa
	 * enquanto seu valor for false, os eventos ser�o disparados, e a
	 * renderiza��o � continuada
	**/
	bool done;

	SDL_Surface* screen;    /* janela de desenho */
	bool fullscreen;        /* Guarda o estado da janela, tela cheia ou n�o */
	char * title;           /* cont�m o t�tulo da janela */

	int width, height;      /* informa a largura e altura da �rea renderiz�vel */
	int bpp;                /* quantidade de bits de profundidade das cores */
	int old_x, old_y;       /* usado para salvar a posi��o da janela, quando
                             * volta do estado de tela cheia
                            **/
	int x, y;               /* informa a posi��o x, y da janela */
	bool mlock;             /* informa se o mouse est� preso � tela */
	int mcapture;           /* informa se o mouse est� sendo usado apenas para
                             * essa janela, o mouse s� ser� liberado quando seu
                             * valor for 0, para isso usa-se a fun��o
                             * SetMouseCapture e ReleaseMouseCapture
                            **/
	//Timer
	Uint32 lastTicks;      /* guarda um tempo de rel�gio pra que seja poss�vel
                             * estabilizar o processo de renderiza��o para
                             * computadores muito r�pido
                            **/
	Uint32 startTicks;       /* guarda um tempo de rel�gio para que seja
                               * poss�vel calcular a taxa de quadros por segundo
                              **/

	unsigned char frameCount; /* Informa a quantidade de quadros processados */
	unsigned char frameRate;  /* informa a taxa de quadros que est� sendo usada */
	unsigned char fpsCount;   /* contagem dos quadros */
	float fps;                /* taxa de quandros medida em segundos */
	inline void handleEvents(); /* manipula os eventos da janela */
};

#endif

