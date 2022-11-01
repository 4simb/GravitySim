#define _USE_MATH_DEFINES

#include <iostream>
#include <Windows.h>
#include <math.h>
#include <GL/glut.h>
#include <GravitySim.h>

glColor colorSunCenter{0.9765f, 0.7343f, 0.3007f};
glColor colorSunBorder{0.9257f, 0.3125f, 0.0039f};

volatile int winWidth = 1900, winHeight = 1000;

float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float crdX(float coord, int _winWidth) {
	return map(coord, 0, _winWidth, -1, 1);
}

float crdY(float coord, int _winHeight) {
	return map(coord, 0, _winHeight, -1, 1);
}

void glPoint(float x, float y) {
	glVertex3f(crdX(x, winWidth), -crdY(y, winHeight), -1);
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

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1.0);
	// обнуление трансформации
	glLoadIdentity();

	glColor3f(0.75, 0.75, 0.75);

	static int i = 0;

	//glColor3f((float)i / 600.f, 0.5, 1.f - (float)i / 600.f);
	//drawEmptyCircle(100, 100, i, 0);
	//Sleep(2);
	//
	//i++;
	//if (i > 600) i = 0;

	drawCircle(350, 200, 300, colorSunCenter, colorSunBorder);

	glutSwapBuffers();
}

void changeSize(int _w, int _h) {
	winWidth = _w;
	winHeight = _h;
	glViewport(0, 0, _w, _h);
	std::cout << "Width: " << _w << "\tHeight: " << _h << "\n";
}

int main(int argc, char** argv)
{
	// Инициализация GLUT и создание окна
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 70);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("gravsim");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1.0);

	// registration
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutMainLoop();

	return 0;
}