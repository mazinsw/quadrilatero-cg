#include "degrade.h"
#include <GL/gl.h>

void Degrade::apply()
{
	glPolygonMode(GL_BACK, GL_FILL);	
}
