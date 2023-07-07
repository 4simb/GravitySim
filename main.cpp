#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include <GL/glut.h>

#include "GravitySim.h"

#define G 2
#define BODY_AMOUNT 1500

//volatile int win.w = WIN_WIDTH, win.h = WIN_HEIGHT;

winSize win{ 1900, 1000 };

volatile float mouseX = (float)win.w / 2, mouseY = (float)win.h / 2;

int fps = 0;
long long elapsedTime = 0;

bool cursorAdded = false;

glColor colorSunCenter{0.9765f, 0.7343f, 0.3007f};
glColor colorSunBorder{0.9257f, 0.3125f, 0.0039f};

CosmicBody cursor(20, 20, 300.f, 25.f, 0, 0, colorSunCenter, colorSunBorder);
CosmicBody moon(win.w / 2, win.h / 2 - 300, 200, 25.f, Vector2d(-5.5f, 0)); //7.36e23f
CosmicBody earth(win.w / 2.f, win.h / 2.f + 400, 300, 25.f, Vector2d(6.5f, 0), glColor{0.f, 0.33f, 0.33f}); //5.97e24
CosmicBody sun(win.w / 2.f, win.h / 2.f, 1500, 60.f, Vector2d(0, 0), colorSunCenter, colorSunBorder); // 1.9889e30
CosmicBody sun1(win.w / 2.f + 400, win.h / 2.f, 1500, 60.f, Vector2d(0, -6.5f), colorSunCenter, colorSunBorder);

std::vector<CosmicBody> Bodies;

std::chrono::high_resolution_clock::time_point timer;

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

			Force forceij(&dist, G * Bodies[i].getMass() * Bodies[j].getMass() / (dist.module() * dist.module()));
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
	drawString(win.w - 50, win.h - 50, std::to_string(fps));
	glutSwapBuffers();
}

void changeSize(int _w, int _h)
{
	win.w = _w * 2;
	win.h = _h * 2;
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
	p_winParams = &win;
	// Инициализация GLUT и создание окна
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 70);
	glutInitWindowSize(win.w, win.h);
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

	for (int i = 0; i < BODY_AMOUNT; i++)
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