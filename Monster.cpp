#include "Monster.h"
#include "MathsHelper.h"

Monster::Monster()
{
	m_health = 100;
	m_skill = MathsHelper::RandomRange(3, 10);
	m_isAlive = true;
}

Monster::~Monster() {}

int Monster::Attack()
{
	// A monster's attack power is limited to its skill
	return MathsHelper::RandomRange(0, m_skill);
}

void Monster::BeHit(int amount)
{
	// "abs" keeps a value positive
	m_health -= abs(amount);

	if (m_health <= 0)
	{
		m_isAlive = false;
	}
}

void Monster::MonFaceTo(float timestep)
{
	//m_objectToLookAt must be set as the player object when the game is initialised
	// directionToPlayer = the vector from the Enemy to the player/ monster heading
	// calculated using vector subtraction (see lecture notes for week 2)
	Vector3 directionToPlayer = m_objectTolookAt - m_position;
	// Normalize the vector to get a vector of unit length 
	directionToPlayer.Normalize();
	// Calculate the angle the enemy should be facing
	// There are a couple of ways to do this, atan2 is fairly straightforward
	m_rotY = atan2(directionToPlayer.x, directionToPlayer.z);

	m_position += directionToPlayer * m_movespeed * timestep;

}


Monster::Monster(Mesh* mesh, Shader* shader, Texture* texture,Vector3 position):GameObject(mesh,shader,texture,position)
{
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
	m_movespeed = 0.6f;
}


void Monster::Update(float timestep, Vector3 playerposition)
{
	m_objectTolookAt = playerposition;
	MonFaceTo(timestep);

	
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
}

void Monster::Update(float timestep)
{

}
