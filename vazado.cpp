#include "vazado.h"
#include <GL/gl.h>

void Vazado::apply()
{
	glPolygonMode(GL_BACK, GL_LINE);
}
