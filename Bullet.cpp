#include "Bullet.h"
#include "MathsHelper.h"

Bullet::Bullet(Mesh* mesh, Shader* shader, Texture*texture,Vector3 position, Vector3 heading):GameObject(mesh, shader, texture,position)
{
	m_heading = heading;
	m_damage = MathsHelper::RandomRange(5, 10);
	m_movespeed = 5.0f;
	m_position = position;
	SetPosition(position+Vector3(0.1f,0.4f,0.0f));
	m_rotY = atan2(m_heading.x, m_heading.z);
}

Bullet::~Bullet()
{
}

void Bullet::Update(float timestep)
{
	m_position += m_heading* m_movespeed*timestep;
}

void Bullet::Shoot(Vector3 Startposition, Vector3 heading,float timestep)
{
	m_position = Startposition;
	m_heading = heading;
}
