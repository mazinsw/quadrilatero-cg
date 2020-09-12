#include "mascara.h"
#include <GL/gl.h>

const unsigned char FA[] =
{
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x07, 0x80, 0x00,
	0x00, 0x00, 0xC0, 0x00,
	0x00, 0x00, 0x60, 0x00,
	0x0F, 0xE0, 0x30, 0x7C,
	0x07, 0x00, 0x38, 0x70,
	0x03, 0x80, 0x18, 0x70,
	0x03, 0x80, 0x0C, 0x70,
	0x01, 0x80, 0x07, 0xF0,
	0x19, 0xC0, 0x06, 0x30,
	0x39, 0xC0, 0x03, 0x30,
	0x31, 0xFC, 0x01, 0xB8,
	0x30, 0xC4, 0x01, 0xB8,
	0x18, 0xE0, 0x0E, 0xF8,
	0x18, 0xE0, 0x0C, 0x78,
	0x0C, 0xE0, 0x0E, 0x78,
	0x06, 0x61, 0x87, 0x38,
	0x03, 0xFF, 0x81, 0xF8,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
};



void Mascara::apply()
{
	glEnable(GL_POLYGON_STIPPLE);
	glColor3f(1.0, 0.0, 1.0);
	glPolygonStipple(FA);
	glPolygonMode(GL_BACK, GL_FILL);
}