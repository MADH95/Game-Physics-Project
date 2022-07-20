/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include <GL\glut.h>
#include <vector>
#include <memory>
#include <Windows.h>
#include <iostream>
#include <ctime>

#include "GameWindow.h"

#include "ForceRegistry.h"
#include "Solver.h"
#include "ContactResolver.h"
#include "CollisionData.h"

#include "Ball.h"
#include "Box.h"
#include "Segment.h"

#include "VerletSolver.h"
#include "Gravity.h"
#include "CollisionDetector.h"


using namespace std;
#pragma once
class Game
{
private:
	ForceRegistry* forceRegistry = nullptr;
	Solver* solver = nullptr; 
	vector<PhysicsEntity*> dynObjs;
	GameWindow* window;
	vector<unique_ptr<CollisionData>> collisionData; 
	ContactResolver* resolver = nullptr;
	Gravity* gravity;
	char currentKey;
	char state = 0;
	bool hasRendered = false;

public:
	void Load();
	//void GameLoop();
	void Render();
	void renderPlains();
	void renderDunes();
	void renderMountains();
	void createWalls();
	void clearScene();
	void Inputs();
	void Update(float dt);
	void ReshapeWindow(int weigth, int height);
	void getCollisionData();
	void spawnObject(bool shape);

	Game() {};
	virtual ~Game() 
	{ 
		for (vector<PhysicsEntity*>::iterator it = dynObjs.begin(); it < dynObjs.end(); it++)
		{
			delete(*it);
		}

		if (solver != nullptr) delete solver;
		if (window != nullptr) delete window;
		if (forceRegistry != nullptr) delete forceRegistry;
	}

	//Timer* gameTimer;
	//float lastFrameTime;

};