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
	//m_heading += m_input->GetMouseDeltaX() * m_rotationSpeed * timestep;

/*
	Matrix heading = Matrix::CreateRotationY(m_heading);

	Vector3 localRight = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

	Vector3 localForwardXZ = localRight.Cross(Vector3(0, 1, 0));

	Vector3 currentPos = GetPosition();

	// Combine pitch and heading into one matrix for convenience
	Matrix lookAtRotation = pitch * heading;

	// Transform a world forward vector into local space (take pitch and heading into account)
	Vector3 lookAt = Vector3::TransformNormal(Vector3(0, 0, 1), lookAtRotation);

	lookAt += currentPos;
	*/
}

void Bullet::Shoot(Vector3 Startposition, Vector3 heading,float timestep)
{
	m_position = Startposition;

	m_heading = heading;
}
