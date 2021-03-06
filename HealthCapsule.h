#ifndef HEALTHCAPSULE_H
#define HEALTHCAPSULE_H

#include "GameObject.h"
#include "MathsHelper.h"

class HealthCapsule:public GameObject
{

public:
	HealthCapsule(Mesh* mesh, Shader* shader, Texture*texture, Vector3 position);

	void Update(float timestep);
	int GetaddHealth() { return addHeal; }

	CBoundingBox GetBounds() { return m_boundingBox; }

	void OnKartCollisionEnter();
	void OnKartCollisionStay();
	void OnKartCollisionExit();

	~HealthCapsule();
private:
	int addHeal;
	
	CBoundingBox m_boundingBox;
	int SetaddHeal(int amount) { addHeal = MathsHelper::RandomRange(0, 20); }
};

#endif