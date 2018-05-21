#include "HealthCapsule.h"
#include "MathsHelper.h"

HealthCapsule::HealthCapsule(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) :
	GameObject(mesh, shader, texture, position)
{
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
}


HealthCapsule::~HealthCapsule()
{
}

void HealthCapsule::Update(float timestep)
{
	
	m_boundingBox.SetMin(m_position +
		m_mesh->GetMin());
	m_boundingBox.SetMax(m_position +
		m_mesh->GetMax());
}

void HealthCapsule::OnKartCollisionEnter()
{

}

void HealthCapsule::OnKartCollisionStay()
{

}

void HealthCapsule::OnKartCollisionExit()
{

}