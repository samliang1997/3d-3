#include "Wall.h"



Wall::Wall(Mesh* mesh, Shader* shader, Texture* texture): GameObject(mesh, shader, texture)
{
	//m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
}


Wall::~Wall()
{
}

void Wall::Update(float timestep)
{

}