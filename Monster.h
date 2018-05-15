/*	FIT2096 - Assignment 1 Sample Solution
*	Monster.h
*	Created by Mike Yeates - 2017 - Monash University
*	A simpe object which has a health, can attack, and can be hit.
*/

#ifndef MONSTER_H
#define MONSTER_H

#include "GameObject.h"
#include "Player.h"

class Monster:public GameObject
{
private:
	int m_health;
	int m_skill;
	bool m_isAlive;
	Player* m_objectTolookAt;

public:
	Monster();
	Monster(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position,Player* lookat);
	~Monster();

	int Attack();
	void BeHit(int amount);

	void MonFaceTo();

	bool IsAlive() { return m_isAlive; }
	int GetSkill() { return m_skill; }

	void Update(float timestep);

};

#endif