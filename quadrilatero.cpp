#include "quadrilatero.h"
#include <GL/gl.h>
#include "solido.h"

Coordenada::Coordenada()
{
	setX(0);
	setY(0);
	setColor(0.0f, 0.0f, 0.0f);
}

Coordenada::Coordenada(int x, int y)
{
	setX(x);
	setY(y);
	setColor(0.0f, 0.0f, 0.0f);
}

Coordenada& Coordenada::operator=(const Coordenada& other)
{
	// não permite a = a;
	if(this == &other)
		return *this;
	x = other.x;
	y = other.y;
	r = other.r;
	g = other.g;
	b = other.b;
	return *this;
}

Quadrilatero::Quadrilatero()
{
	setBrush(0);
}

void Quadrilatero::render()
{
	glDisable(GL_POLYGON_STIPPLE);
	if(preenchimento != 0)
		preenchimento->apply();
	glBegin( GL_QUAD_STRIP );
	glColor3f( p4.getR(), p4.getG(), p4.getB());
	glVertex2i( p4.getX(), p4.getY() );
	glColor3f( p3.getR(), p3.getG(), p3.getB());
	glVertex2i( p3.getX(), p3.getY() );
	glColor3f( p1.getR(), p1.getG(), p1.getB());
	glVertex2i( p1.getX(), p1.getY() );
	glColor3f( p2.getR(), p2.getG(), p2.getB());
	glVertex2i( p2.getX(), p2.getY() );
	glEnd();
}

bool Quadrilatero::isIn(int x, int y)
{
	bool  oddNodes = false;
	Coordenada* v[4] = {&p1, &p2, &p3, &p4};
	Coordenada *p1, *p2;

	p2 = v[3];
	for(int i = 0; i < 4; i++)
	{
		p1 = v[i];
		if (((p1->getY() < y && p2->getY() >= y) || (p2->getY() < y && p1->getY() >= y)) &&
				(p1->getX() <= x || p2->getX() <= x))
		{

			if(p1->getX() + (float)(y - p1->getY()) / (p2->getY() - p1->getY()) * (p2->getX() - p1->getX()) < x)
				oddNodes = !oddNodes;
		}
		p2 = p1;
	}
	return oddNodes;
}


Quadrilatero& Quadrilatero::operator=(const Quadrilatero & other)
{
	// não permite a = a;
	if(this == &other)
		return *this;
	p1 = other.p1;
	p2 = other.p2;
	p3 = other.p3;
	p4 = other.p4;
	preenchimento = other.preenchimento;
	return *this;
}
