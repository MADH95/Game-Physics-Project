/*

Name: Martin Harvey

Student ID: B00329330

I declare that the following code was produced by Martin Harvey & David Irvine as a group assignment for the Game Physics module and that this is our own work.

I am aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.

*/
#include "Game.h"

using namespace std;

void Game::Load()
{

	srand(time(NULL)); // set seed for rand function

	// Create window
	window = new GameWindow("Game Physiscs Project", 1300, 900, 50, 50);

	// Initialize Physics
	solver = new VerletSolver();
	forceRegistry = new ForceRegistry();
	resolver = new ContactResolver();
	gravity = new Gravity(vec2(0, -300));
	
	createWalls();
}

void Game::Update(float dt)
{
	Inputs();

	forceRegistry->updateForces(dt); //Update forces and computes their resultant
	solver->integrate(dynObjs, dt); //Updates Position, Velocity and Acceleration of each object
	forceRegistry->clear();//Set the resultant of the forces of each object to 0

	for (vector<PhysicsEntity*>::iterator it = dynObjs.begin(); it < dynObjs.end(); it++)
	{
		(*it)->update(dt);
	}

	getCollisionData();

	while (!collisionData.empty())
	{
		unique_ptr<CollisionData>& data = collisionData.back();
		resolver->setNumIterations(data->maxNumContacts - data->numContactsLeft);
		if (data->contact != nullptr)
		{
			resolver->resolveContacts(data->contact, data->maxNumContacts, dt);
		}

		collisionData.pop_back(); //remove the last element from the vector, being it a smart pointer delete is called automatically on it
	}
}

void Game::ReshapeWindow(int width, int height)
{
	window->Reshape(width, height);
}

void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer
	glMatrixMode(GL_MODELVIEW);		// To operate on the model-view matrix

	switch (state)
	{
	case 1:
		renderDunes();
		break;
	case 2:
		renderMountains();
		break;
	default:
		renderPlains();
		break;
	}

	for (vector<PhysicsEntity*>::iterator it = dynObjs.begin(); it < dynObjs.end(); it++)
	{
		(*it)->draw(window->getWidth(), window->getHeight());
	}

	glutSwapBuffers();				// Swap front and back buffers (of double buffered mode)
}

void Game::renderPlains()
{

	// Draw Background
	PhysParameters* BackgroundParams = new PhysParameters(0, vec2(650, 450), vec2(0), 0.0f);
	Box* Background = new Box(vec2(650, 450), BackgroundParams, vec3(0.0, 0.5, 1.0));
	Background->draw(window->getWidth(), window->getHeight());
	// Draw Floor
	PhysParameters* FloorParams = new PhysParameters(0, vec2(650, 20), vec2(0, 0), 0.5f, 0.0f);
	Box* FlatFloor = new Box(vec2(650, 40), FloorParams, vec3(1.0f, 1.0f, 0.0f));
	FlatFloor->draw(window->getWidth(), window->getHeight());

	if (!hasRendered)
	{
		clearScene();
		createWalls();
		dynObjs.push_back(FlatFloor);
		hasRendered = true;
	}
}

void Game::renderDunes()
{
	// Draw Background
	PhysParameters* BackgroundParams = new PhysParameters(0, vec2(650, 450), vec2(0), 0.0f);
	Box* Background = new Box(vec2(650, 450), BackgroundParams, vec3(1.0, 0.5, 0.0));
	Background->draw(window->getWidth(), window->getHeight());
	// Draw Floor
	PhysParameters* SlopeParams = new PhysParameters(0, vec2(650, 0), vec2(0, 0), 0.5f, 15.0f);
	Box* SlopedFloor = new Box(vec2(800, 170), SlopeParams, vec3(1.0f, 0.3f, 0.0f));
	SlopedFloor->draw(window->getWidth(), window->getHeight());

	if (!hasRendered)
	{
		clearScene();
		createWalls();
		dynObjs.push_back(SlopedFloor);
		hasRendered = true;
	}
}

void Game::renderMountains()
{
	// Draw Background
	PhysParameters* BackgroundParams = new PhysParameters(0, vec2(650, 450), vec2(0), 0.0f);
	Box* Background = new Box(vec2(650, 450), BackgroundParams, vec3(0.7, 0.7, 1.0));
	Background->draw(window->getWidth(), window->getHeight());

	// Draw Background Mountains
	PhysParameters* BackJaggedParams1 = new PhysParameters(0, vec2(800, 20), vec2(0, 0), 0.5f, 45.0f);
	Box* BackJagged1 = new Box(vec2(150, 300), BackJaggedParams1, vec3(0.2f));
	BackJagged1->draw(window->getWidth(), window->getHeight());
	PhysParameters* BackJaggedParams2 = new PhysParameters(0, vec2(140, 50), vec2(0, 0), 0.5f, 45.0f);
	Box* BackJagged2 = new Box(vec2(100, 100), BackJaggedParams2, vec3(0.2f));
	BackJagged2->draw(window->getWidth(), window->getHeight());

	// Draw Midground Mountains
	PhysParameters* MidJaggedParams1 = new PhysParameters(0, vec2(500, 50), vec2(0, 0), 0.5f, 45.0f);
	Box* MidJagged1 = new Box(vec2(300, 300), MidJaggedParams1, vec3(0.3f));
	MidJagged1->draw(window->getWidth(), window->getHeight());
	PhysParameters* MidJaggedParams2 = new PhysParameters(0, vec2(1000, 30), vec2(0, 0), 0.5f, 45.0f);
	Box* MidJagged2 = new Box(vec2(250, 250), MidJaggedParams2, vec3(0.3f));
	MidJagged2->draw(window->getWidth(), window->getHeight());

	//Draw Foreground Mountains
	PhysParameters* ForeJaggedParams1 = new PhysParameters(0, vec2(40, 0), vec2(0, 0), 0.5f, 45.0f);
	Box* ForeJagged1 = new Box(vec2(150, 150), ForeJaggedParams1, vec3(0.4f));
	ForeJagged1->draw(window->getWidth(), window->getHeight());
	PhysParameters* ForeJaggedParams2 = new PhysParameters(0, vec2(540, 0), vec2(0, 0), 0.5f, 45.0f);
	Box* ForeJagged2 = new Box(vec2(220, 220), ForeJaggedParams2, vec3(0.4f));
	ForeJagged2->draw(window->getWidth(), window->getHeight());
	PhysParameters* ForeJaggedParams3 = new PhysParameters(0, vec2(1200, 20), vec2(0, 0), 0.5f, 45.0f);
	Box* ForeJagged3 = new Box(vec2(300, 300), ForeJaggedParams3, vec3(0.4f));
	ForeJagged3->draw(window->getWidth(), window->getHeight());

	// Draw Front Mountains
	PhysParameters* FrontJaggedParams1 = new PhysParameters(0, vec2(300, -10), vec2(0, 0), 0.5f, 45.0f);
	Box* FrontJagged1 = new Box(vec2(90, 90), FrontJaggedParams1, vec3(0.5f));
	FrontJagged1->draw(window->getWidth(), window->getHeight());
	PhysParameters* FrontJaggedParams2 = new PhysParameters(0, vec2(800, 0), vec2(0, 0), 0.5f, 45.0f);
	Box* FrontJagged2 = new Box(vec2(110, 110), FrontJaggedParams2, vec3(0.5f));
	FrontJagged2->draw(window->getWidth(), window->getHeight());

	if (!hasRendered)
	{
		clearScene();
		createWalls();
		dynObjs.push_back(BackJagged1);
		dynObjs.push_back(BackJagged2);

		dynObjs.push_back(MidJagged1);
		dynObjs.push_back(MidJagged2);

		dynObjs.push_back(ForeJagged1);
		dynObjs.push_back(ForeJagged2);
		dynObjs.push_back(ForeJagged3);

		dynObjs.push_back(FrontJagged1);
		dynObjs.push_back(FrontJagged2);

		hasRendered = true;
	}
}

void Game::createWalls()
{
	//Roof
	PhysParameters* RoofParams = new PhysParameters(0, vec2(650, 900), vec2(0, 0), 0.5f, 0.0f);
	Segment* Roof = new Segment(650, RoofParams, vec3(1.0f, 0.3f, 0.0f));
	dynObjs.push_back(Roof);

	//Left Wall
	PhysParameters* LeftWallParams = new PhysParameters(0, vec2(0, 450), vec2(0, 0), 0.5f, 90.0f);
	Segment* LeftWall = new Segment(450, LeftWallParams, vec3(1.0f, 0.3f, 0.0f));
	dynObjs.push_back(LeftWall);

	//Right Wall
	PhysParameters* RightWallParams = new PhysParameters(0, vec2(1300, 450), vec2(0, 0), 0.5f, 90.0f);
	Segment* RightWall = new Segment(450, RightWallParams, vec3(1.0f, 0.3f, 0.0f));
	dynObjs.push_back(RightWall);
}

void Game::clearScene()
{
	for (auto it = dynObjs.begin(); it != dynObjs.end();)
	{
		delete (*it);
		it = dynObjs.erase(it);
	}
	dynObjs.clear();
}

int mouseX, mouseY;
void getMouseCoords(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void Game::Inputs()
{
	if (GetAsyncKeyState(VK_RIGHT) && GetKeyState(VK_RIGHT) != currentKey)
	{
		cout << "right" << endl;
		currentKey = GetKeyState(VK_RIGHT);
		hasRendered = false;
		if (state == 2)
			state = 0;
		else
			state++;
	}
	if (GetAsyncKeyState(VK_LEFT) && GetKeyState(VK_LEFT) != currentKey)
	{
		currentKey = GetKeyState(VK_LEFT);
		hasRendered = false;
		if (state == 0)
			state = 2;
		else
			state--;
	}

	glutPassiveMotionFunc(getMouseCoords);
	if (GetKeyState(VK_LBUTTON) < 0 && GetKeyState(VK_LBUTTON) != currentKey)
	{
		currentKey = GetKeyState(VK_LBUTTON);
		if (mouseX > 0.0f && mouseX < window->getWidth() && mouseY > 0.0f && mouseY < window->getHeight())
			spawnObject(false);
	}
	if (GetKeyState(VK_RBUTTON) < 0 && GetKeyState(VK_RBUTTON) != currentKey)
	{
		currentKey = GetKeyState(VK_RBUTTON);
		if (mouseX > 0.0f && mouseX < window->getWidth() && mouseY > 0.0f && mouseY < window->getHeight())
			spawnObject(true);
	}
}

void Game::spawnObject(bool shape)
{
	vec2 position = vec2(mouseX, window->getHeight() - mouseY); // vec2 for position derived from mouse coords
	vec2 randVelocity = vec2(static_cast<float> ((rand() % 100) + 100), static_cast<float>((rand() % 100) + 100)); // random velocity from 100 to 200
	float randAngle = static_cast<float> ((rand() % 360)); // create a random angle betwee 0 and 360
	float randMass = static_cast<float> ((rand() % 400) + 100); // create a random mass between 100 and 500
	float randRestitution = (static_cast<float>(rand() % 100)) / 100; // create a random restitution betwee 0 and 1
	bool leftRight = rand() % 2; // randomly determine if the velocity vector is facing left or right
	bool upDown = rand() % 2; // randomly determine if the velocity vector is facing up or down
	float randRed = (static_cast<float>(rand() % 100)) / 100; // Random red colour between 0 and 1
	float randGreen = (static_cast<float>(rand() % 100)) / 100; // Random green colour between 0 and 1
	float randBlue = (static_cast<float>(rand() % 100)) / 100; // Random blue colour between 0 and 1

	if (leftRight) randVelocity.x = -randVelocity.x; // make the x component of the velocity vector negative sometimes
	if (upDown) randVelocity.y = -randVelocity.y; // make the y component of the velocity vector negative sometimes

	// PhysParameters(mass, position, velocity, restitution, rotation angle(defaults to 0.0f if left blank)
	PhysParameters* physParams = new PhysParameters(randMass, position, randVelocity, randRestitution, randAngle); // pointer container for physics parameters

	if (shape)
	{
		float randRadius = static_cast<float> ((rand() % 50) + 50); // create a random radius between 50 and 100
		Ball* ball = new Ball(randRadius, physParams, vec3(randRed, randGreen, randBlue));
		forceRegistry->Add(ball, gravity);
		dynObjs.push_back(ball);
	}
	else
	{
		vec2 randRadii = vec2(static_cast<float> ((rand() % 50) + 50), static_cast<float> ((rand() % 50) + 50)); // create random radii between 50 and 100
		Box* box = new Box(randRadii, physParams, vec3(randRed, randGreen, randBlue));
		forceRegistry->Add(box, gravity);
		dynObjs.push_back(box);
	}
}

void Game::getCollisionData()
{
	for (vector<PhysicsEntity*>::iterator it_obj1 = dynObjs.begin(); it_obj1 < dynObjs.end() - 1; ++it_obj1)
	{
		for (vector<PhysicsEntity*>::iterator it_obj2 = it_obj1 + 1; it_obj2 < dynObjs.end(); ++it_obj2) // we make sure that we check a collision between the same objcts only once
		{
			CollisionData* data = CollisionDetector::CheckCollision(*it_obj1, *it_obj2); //it automatically checks the types
			if (data != nullptr)
			{
				collisionData.push_back(unique_ptr<CollisionData>(data));
			}
		}
	}
}