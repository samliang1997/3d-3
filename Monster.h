/*	FIT2096 - Assignment 1 Sample Solution
*	Monster.h
*	Created by Mike Yeates - 2017 - Monash University
*	A simpe object which has a health, can attack, and can be hit.
*/

#ifndef MONSTER_H
#define MONSTER_H

#include "GameObject.h"


class Monster:public GameObject
{
private:
	int m_health;
	bool m_isAlive;
	Vector3 m_objectTolookAt;
	float m_movespeed;

	CBoundingBox m_boundingBox;
public:
	Monster();
	Monster(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position);
	~Monster();

	void BeHit(int amount);

	void MonFaceTo(float timestep);
	
	CBoundingBox GetBounds() { return m_boundingBox; }
	bool IsAlive() { return m_isAlive; }
	float GetMovespeed() { return m_movespeed; }

	void Update(float timestep);
	void Update(float timestep, Vector3 playerposition);

	
};

#endif