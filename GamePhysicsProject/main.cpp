/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include <GL\glut.h> // GLUT, includes glu.h and gl.h
#include "Game.h"
#include "Timer.h"
int refreshMillis = 16;      // Refresh period in milliseconds

Game* game;
LowResTimer timer;
double oldTime = 0;

/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}

/* Callback handler for window re-paint event */
void display() {
	game->Render();
}

/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) 
{
	game->ReshapeWindow(width, height);
}

/* Fixed Time Update */
void update(int value) 
{
	game->Update(timer.getTime()-oldTime);
	glutPostRedisplay();						// Post a paint request to activate display()
	glutTimerFunc(refreshMillis, update, 0);	// Subsequent timer call at milliseconds
	oldTime = timer.getTime();
}

void GLUTRenderer()
{
	glutDisplayFunc(display);		// Register callback handler for window re-paint
	glutReshapeFunc(reshape);		// Register callback handler for window re-shape
	glutTimerFunc(0, update, 0);	// First timer call immediately
	initGL();						// Our own OpenGL initialization
	glutMainLoop();					// Enter event-processing loop
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	game = new Game();
	game->Load();
	timer.startTimer();
	GLUTRenderer();

	delete game;

	return 0;
}