/*	FIT2096 - Assignment 1 Sample Solution
*	GameBoard.h
*	Created by Mike Yeates - 2017 - Monash University
*	Generates the board and manages a collection of Tiles.
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H


#include "MeshManager.h"
#include "TextureManager.h"
#include "TexturedShader.h"
#include "Shader.h"
#include "Direct3D.h"
#include "Camera.h"
#include "HealthCapsule.h"
#include "Monster.h"
#include "GameObject.h"
#include "Wall.h"
#include "Bullet.h"
#include "StaticObject.h"


#include <vector>

using namespace std;
class GameBoard
{
private:
	MeshManager* m_meshManager;
	TextureManager* m_textureManager;

	//Shaders
	Shader* m_diffuseTexturedShader;

	//gameobject
	StaticObject* m_ground;
	vector<StaticObject*> m_wall;
	vector<StaticObject*> m_disableditem;
	vector<HealthCapsule*> m_heal;
	vector<Monster*> m_monster;
	vector<Bullet*> m_bullet;

	//Player* m_player;

	void Generate();
	void InitMonster();
	void InitHealthCapsule();
	void InitGameWorld();
	void InitWall();
	
	int monsterShootCount = 0;

public:
	GameBoard();
	GameBoard(MeshManager* meshManager, Shader* diffuseTexturedShader, TextureManager* textureManager);
	~GameBoard();

	void Update(float timestep, Vector3 playerposition);
	void Render(Direct3D* renderer, Camera* camera);

	void InitBullet(Vector3 position, Vector3 heading);
	vector<HealthCapsule*> GetHeal() { return m_heal; }
	vector<Monster*> GetMonster() { return m_monster; }
	vector<StaticObject*> GetWall() { return m_wall; }
	vector<StaticObject*> GetDisabledItem() { return m_disableditem; }
	vector<Bullet*> GetBullet() { return m_bullet; }
};

#endif

