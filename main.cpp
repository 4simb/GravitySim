#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <GL/glut.h>
#include "GravitySim.h"

#define G 2

volatile int winWidth = 1900, winHeight = 1000;
volatile float mouseX = (float)winWidth / 2, mouseY = (float)winHeight / 2;

int fps = 0;
long long elapsedTime = 0;

bool cursorAdded = false;

glColor colorSunCenter{0.9765f, 0.7343f, 0.3007f};
glColor colorSunBorder{0.9257f, 0.3125f, 0.0039f};

CosmicBody cursor(20, 20, 300.f, 25.f, 0, 0, colorSunCenter, colorSunBorder);
CosmicBody moon(winWidth / 2, winHeight / 2 - 300, 200, 25.f, Vector2d(-5.5f, 0)); //7.36e23f
CosmicBody earth(winWidth / 2.f, winHeight / 2.f + 400, 300, 25.f, Vector2d(6.5f, 0), glColor{0.f, 0.33f, 0.33f}); //5.97e24
CosmicBody sun(winWidth / 2.f, winHeight / 2.f, 1500, 60.f, Vector2d(0, 0), colorSunCenter, colorSunBorder); // 1.9889e30
CosmicBody sun1(winWidth / 2.f + 400, winHeight / 2.f, 1500, 60.f, Vector2d(0, -6.5f), colorSunCenter, colorSunBorder);

std::vector<CosmicBody> Bodies;

std::chrono::high_resolution_clock::time_point timer;

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

void renderBody(CosmicBody* body)
{
	drawCircle(body->getXpos() * 2, body->getYpos() * 2, body->getRadius(), body->getInnerColor(), body->getExternColor());
}

void drawString(float x, float y, float z, const char* string) {
	glRasterPos3f(crdX(x, winWidth), crdY(y, winHeight), z);
	for (const char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);  // Updates the position
	}
}

void drawString(float x, float y, float z, char* string) {
	glRasterPos3f(crdX(x, winWidth), crdY(y, winHeight), z);
	for (char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);  // Updates the position
	}
}

void drawString(float x, float y, float z, std::string string) {
	glRasterPos3f(crdX(x, winWidth), crdY(y, winHeight), z);
	for (int c = 0; string[c] != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[c]);  // Updates the position
	}
}

void applyForces()
{
	for (int i = 0; i < Bodies.size() - 1; i++)
	{
		for (int j = i + 1; j < Bodies.size(); j++)
		{
			// 45150 for 301 body takes ~60ms avg
			float deltax = Bodies[j].getXpos() - Bodies[i].getXpos();
			float deltay = Bodies[j].getYpos() - Bodies[i].getYpos();
			if (abs(deltax) < 10) deltax = (deltax > 0 ? 10 : -10);
			if (abs(deltay) < 10) deltay = (deltay > 0 ? 10 : -10);
			Vector2d dist(deltax, deltay);

			Force forceij(&dist, G * Bodies[i].getMass() * Bodies[j].getMass() / (pow(dist.module(), 2)));
			forceij.normalize();
			Bodies[i].applyForce(&forceij);

			forceij.setX(-forceij.getX());
			forceij.setY(-forceij.getY());
			Bodies[j].applyForce(&forceij);
		}
	}
}

void oldAnalyse()
{
	for (int i = 0; i < Bodies.size(); i++)
	{
		Force resultant(0, 0, 0);

		for (int j = 0; j < Bodies.size(); j++)
		{
			if (i == j) continue;
			// f = G(m1 * m2 / r^2)
			float deltax = Bodies[j].getXpos() - Bodies[i].getXpos();
			float deltay = Bodies[j].getYpos() - Bodies[i].getYpos();
			if (abs(deltax) < 10) deltax = (deltax > 0 ? 10 : -10);
			if (abs(deltay) < 10) deltay = (deltay > 0 ? 10 : -10);
			Vector2d dist(deltax, deltay);
			//if (dist.module() < Bodies[i].getRadius() + Bodies[j].getRadius())
			//	Bodies[i].setSpeed(-Bodies[i].getSpeed().getX(), -Bodies[i].getSpeed().getY());			
			Force force(&dist, G * Bodies[i].getMass() * Bodies[j].getMass() / (dist.module() * dist.module()));
			force.normalize();
			//std::cout << force.module() << "\n";
			resultant.setX(resultant.getX() + force.getX());
			resultant.setY(resultant.getY() + force.getY());
		}
		resultant.setValue(resultant.module());
		//resultant.normalize();
		Bodies[i].applyForce(&resultant);
	}
}

void renderScene()
{
	fps = 1e6f / (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timer)).count() + 0.5f;
	if (fps > 60) return;
	timer = std::chrono::high_resolution_clock::now();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1.0);
	// обнуление трансформации
	glLoadIdentity();

	glColor3f(0.15, 0.75, 0.15);

	//static int i = 0;
	applyForces(); // 55ms

	//drawBodies();

	for (int i = 0; i < Bodies.size(); i++)
	{
		if (i == Bodies.size() - 1)
		{

		}
		Bodies[i].proceed();
		renderBody(&Bodies[i]);
	}

	glColor3f(0.1, 0.9, 0.1);
	drawString(winWidth - 50, winHeight - 50, -1, std::to_string(fps));
	glutSwapBuffers();
}

void changeSize(int _w, int _h)
{
	winWidth = _w * 2;
	winHeight = _h * 2;
	glViewport(0, 0, _w, _h);
	//std::cout << "Width: " << _w << "\tHeight: " << _h << "\n";
}

void processMouse(int button, int state, int x, int y)
{

}

void processMouseMotion(int x, int y)
{
	if (!cursorAdded) {
		Bodies.push_back(cursor);
		cursorAdded = true;
	}
	mouseX = x;
	mouseY = y;
	Bodies[Bodies.size() - 1].setXpos(mouseX);
	Bodies[Bodies.size() - 1].setYpos(mouseY);
	//std::cout << cursor.getXpos() << "\t" << cursor.getYpos() << "\n";
}

int main(int argc, char** argv)
{
	// Инициализация GLUT и создание окна
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 70);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("gravsim 400 bodies");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.1, 1.0);

	// registration
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseMotion);

	std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - std::chrono::system_clock::now()).count();

	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	srand(now->tm_sec);

	for (int i = 0; i < 400; i++)
	{
		CosmicBody body(100 + rand() % 1700, 50 + rand() % 900, 1.9f, 4.5f, Vector2d{0, 0}, glColor{0.25f + rand() % 5000 / 10000.f, 0.25f + rand() % 5000 / 10000.f, 0.25f + rand() % 5000 / 10000.f}, glColor{0.25f + rand() % 5000 / 10000.f, 0.25f + rand() % 5000 / 10000.f, 0.25f + rand() % 5000 / 10000.f});
		//Vector2d{-5.f + (rand() % 1000) / 100.f, -5.f + (rand() % 1000) / 100.f}
		//CosmicBody body(rand() % 1900, rand() % 1000, (long long)10e21 * rand() % 50, 1 + rand() % 10, Vector2d{0, 0}, glColor{rand() % 1000 / 1000.f, rand() % 1000 / 1000.f, rand() % 1000 / 1000.f});
		Bodies.push_back(body);
	}
	sun.setMoovable(false);
	//Bodies.push_back(earth);
	//Bodies.push_back(moon);
	//Bodies.push_back(sun);
	cursor.setMoovable(false);
	//Bodies.push_back(cursor);

	glutMainLoop();

	return 0;
}