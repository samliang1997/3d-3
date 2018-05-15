#ifndef WALL_H
#define WALL_H

#include "GameObject.h"

class Wall:public GameObject
{

public:
	Wall(Mesh* mesh, Shader* shader, Texture*texture);
	~Wall();

	void Update(float timestep);

	CBoundingBox GetBounds() { return m_boundingBox; }

private:
	CBoundingBox m_boundingBox;
};

#endif