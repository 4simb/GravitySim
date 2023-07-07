#include "GravitySimGraphics.h"

struct winSize {
	int w;
	int h;
};

extern winSize* p_winParams;

struct glColor {
	float m_red;
	float m_green;
	float m_blue;
	float m_alpha = 1.f;
};

void glPoint(float x, float y) {
	glVertex3f(crdX(x, p_winParams->w), -crdY(y, p_winParams->h), -1);
}

void drawEmptyCircle(float x, float y, float r, int w)
{
	int dots = 2.f * M_PI * r + 1;
	float delta = 2 * M_PI / dots;

	glLineWidth(w);

	glBegin(GL_LINE_LOOP);
	for (int angle = 0; angle < dots; angle++)
	{
		float rad = angle * delta;
		glPoint(x + cosf(rad) * r, y + sinf(rad) * r);
	}
	glEnd();
}

void drawCircle(float x, float y, float r, glColor innerColor, glColor externColor)
{
	int dots = 2.f * M_PI * r + 1;
	float delta = 2 * M_PI / dots;

	glLineWidth(1.5);

	glBegin(GL_LINE_STRIP);

	for (int angle = 0; angle < dots; angle++)
	{
		float rad = angle * delta;
		glColor3f(innerColor.m_red, innerColor.m_green, innerColor.m_blue);
		glPoint(x, y);
		glColor3f(externColor.m_red, externColor.m_green, externColor.m_blue);
		glPoint(x + cosf(rad) * r, y + sinf(rad) * r);
	}

	glEnd();
}

void drawCircle(float x, float y, float r, glColor color)
{
	int dots = 2.f * M_PI * r + 1;
	float delta = 2 * M_PI / dots;

	glLineWidth(1.5);

	glBegin(GL_LINE_STRIP);
	glColor3f(color.m_red, color.m_green, color.m_blue);

	for (int angle = 0; angle < dots; angle++)
	{
		float rad = angle * delta;

		glPoint(x, y);
		glPoint(x + cosf(rad) * r, y + sinf(rad) * r);
	}

	glEnd();
}

void drawString(float x, float y, const char* string) {
	glRasterPos3f(crdX(x, p_winParams->w), crdY(y, p_winParams->h), -1);
	for (const char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void drawString(float x, float y, char* string) {
	glRasterPos3f(crdX(x, p_winParams->w), crdY(y, p_winParams->h), -1);
	for (char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void drawString(float x, float y, std::string string) {
	glRasterPos3f(crdX(x, p_winParams->w), crdY(y, p_winParams->h), -1);
	for (int c = 0; string[c] != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[c]);
	}
}