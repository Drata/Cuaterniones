
#include "GLInclude.h"
#include "shapes.h"

void drawDot(VECTOR3D position, float sradius, COLOUR color)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);


	VECTOR3D p[4], n[4];
	int STEP = 30;
	for (int i = 0; i<360; i += STEP) {
		for (int j = -90; j<90; j += STEP) {

			p[0].x = sradius * cos(j*DTOR) * cos(i*DTOR);
			p[0].y = sradius * sin(j*DTOR);
			p[0].z = sradius * cos(j*DTOR) * sin(i*DTOR);
			n[0] = p[0];

			p[1].x = sradius * cos((j + STEP)*DTOR) * cos(i*DTOR);
			p[1].y = sradius * sin((j + STEP)*DTOR);
			p[1].z = sradius * cos((j + STEP)*DTOR) * sin(i*DTOR);
			n[1] = p[1];

			p[2].x = sradius * cos((j + STEP)*DTOR) * cos((i + STEP)*DTOR);
			p[2].y = sradius * sin((j + STEP)*DTOR);
			p[2].z = sradius * cos((j + STEP)*DTOR) * sin((i + STEP)*DTOR);
			n[2] = p[2];

			p[3].x = sradius * cos(j*DTOR) * cos((i + STEP)*DTOR);
			p[3].y = sradius * sin(j*DTOR);
			p[3].z = sradius * cos(j*DTOR) * sin((i + STEP)*DTOR);
			n[3] = p[3];

			glBegin(GL_POLYGON);
			if (i % (STEP * 4) == 0)
				glColor3f(color.r, color.g, color.b);
			else
				glColor3f(color.r*0.5, color.g*0.5, color.b*0.5);
			for (int k = 0; k<4; k++) {
				glNormal3f(n[k].x, n[k].y, n[k].z);
				glVertex3f(p[k].x, p[k].y, p[k].z);
			}
			glEnd();
		}
	}

	glPopMatrix();
}

void drawLine(LINE line, COLOUR color, bool doDrawDots) {
	//If doDrawDots is true then we paint the first and the last point.
	if (doDrawDots) {
		drawDot(line.P[0], 1.0, color);
		drawDot(line.P[line.P.size()-1], 1.0, color);
	}

	glColor3f(color.r, color.g, color.b);
	
	//Sends all the vertex of the line to OpenGL.
	glBegin(GL_LINE_STRIP);
	for (VECTOR3D v : line.P) {
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
}

void drawAxis() {
	LINE x, y, z;
	VECTOR3D origin = {0, 0, 0};

	//Initialize the values of the axis lines.
	x.P = { origin, {100, 0, 0} };
	y.P = { origin, { 0, 100, 0 } };
	z.P = { origin, { 0, 0, 100 } };

	//Draws the lines of the axis.
	drawLine(x, red);
	drawLine(y, green);
	drawLine(z, blue, true);
}

