#ifndef HEALTHCAPSULE_H
#define HEALTHCAPSULE_H

#include "GameObject.h"

class HealthCapsule:public GameObject
{

public:
	HealthCapsule(Mesh* mesh, Shader* shader, Texture*texture, Vector3 position);

	void Update(float timestep);

	CBoundingBox GetBounds() { return m_boundingBox; }
	void OnKartCollisionEnter();
	void OnKartCollisionStay();
	void OnKartCollisionExit();

	~HealthCapsule();
private:
	CBoundingBox m_boundingBox;
};

#endif