#ifndef BULLET_H
#define	BULLET_H

#include "GameObject.h" 

class Bullet:public GameObject

{
public:
	Bullet(Mesh* mesh, Shader* shader, Texture*texture,Vector3 position, Vector3 heading);
	~Bullet();

	void Update(float timestep);
	int GetDamage() { return m_damage; }

	void Shoot(Vector3 Startposition, Vector3 heading,float timestep);
private:

	float m_movespeed;
	float m_rotationSpeed;
	Vector3 m_heading;
	

	int m_damage;


};

#endif