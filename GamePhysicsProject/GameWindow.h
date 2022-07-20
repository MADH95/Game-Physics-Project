/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#pragma once
#include <GL\glut.h>

class GameWindow
{
private:
	// Projection clipping area
	double clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
	int width, height;
public:

	GameWindow(const char* title, int width, int height, int posX, int posY):width(width),height(height)
	{
		glutInitDisplayMode(GLUT_DOUBLE);	// Enable double buffered mode
		glutInitWindowSize(width, height);	// Initial window width and height
		glutInitWindowPosition(posX, posY); // Initial window top-left corner (x, y)
		glutCreateWindow(title);			// Create window with given title
	}

	virtual ~GameWindow() {}

	void Reshape(GLsizei width, GLsizei height);
	int getWidth();
	int getHeight();
};