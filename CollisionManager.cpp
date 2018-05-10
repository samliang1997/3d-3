#include "CollisionManager.h"

CollisionManager::CollisionManager(std::vector<Player*>* player, std::vector<HealthCapsule*>* healthCapslue)
{
	m_player = player;
	m_healthCapslue = healthCapslue;

	// Clear our arrays to 0 (NULL)
	memset(m_currentCollisions, 0, sizeof(m_currentCollisions));
	memset(m_previousCollisions, 0, sizeof(m_previousCollisions));

	m_nextCurrentCollisionSlot = 0;
}

void CollisionManager::CheckCollisions()
{
	// Check kart to item box collisions
	KartToItemBox();
	//KartToKart();

	// Move all current collisions into previous
	memcpy(m_previousCollisions, m_currentCollisions, sizeof(m_currentCollisions));

	// Clear out current collisions
	memset(m_currentCollisions, 0, sizeof(m_currentCollisions));

	// Now current collisions is empty, we'll start adding from the start again
	m_nextCurrentCollisionSlot = 0;

}

bool CollisionManager::ArrayContainsCollision(GameObject* arrayToSearch[], GameObject* first, GameObject* second)
{
	// See if these two GameObjects appear one after the other in specified collisions array
	// Stop one before length so we don't overrun as we'll be checking two elements per iteration
	for (int i = 0; i < MAX_ALLOWED_COLLISIONS - 1; i += 2)
	{
		if ((arrayToSearch[i] == first && arrayToSearch[i + 1] == second) ||
			arrayToSearch[i] == second && arrayToSearch[i + 1] == first)
		{
			// Found them!
			return true;
		}
	}

	// These objects were not colliding last frame
	return false;
}

void CollisionManager::AddCollision(GameObject* first, GameObject* second)
{
	// Add the two colliding objects to the current collisions array
	// We keep track of the next free slot so no searching is required
	m_currentCollisions[m_nextCurrentCollisionSlot] = first;
	m_currentCollisions[m_nextCurrentCollisionSlot + 1] = second;

	m_nextCurrentCollisionSlot += 2;
}

void CollisionManager::KartToItemBox()
{
	// We'll check each kart against every item box
	// Note this is not overly efficient, both in readability and runtime performance

	for (unsigned int i = 0; i < m_player->size(); i++)
	{
		for (unsigned int j = 0; j < m_healthCapslue->size(); j++)
		{
			// Don't need to store pointer to these objects again but favouring clarity
			// Can't index into these directly as they're a pointer to a vector. We need to dereference them first
			Player* player = (*m_player)[i];
			HealthCapsule* healthCapslue = (*m_healthCapslue)[i];

			CBoundingBox playerBounds = player->GetBounds();
			CBoundingBox  healthCapslueBounds = healthCapslue->GetBounds();

			// Are they colliding this frame?
			bool isColliding = CheckCollision(playerBounds, healthCapslueBounds);

			// Were they colliding last frame?
			bool wasColliding = ArrayContainsCollision(m_previousCollisions, player, healthCapslue);

			if (isColliding)
			{
				// Register the collision
				AddCollision(player, healthCapslue);

				if (wasColliding)
				{
					// We are colliding this frame and we were also colliding last frame - that's a collision stay
					// Tell the item box a kart has collided with it (we could pass it the actual kart too if we like)
					OutputDebugString("Kart-Kart Collision Stay\n");
					//healthCapslue->OnKartCollisionStay();
					//player->OnItemBoxCollisionStay(itemBox);
				}
				else
				{
					// We are colliding this frame and we weren't last frame - that's a collision enter
					//itemBox->OnKartCollisionEnter();
					//kart->OnItemBoxCollisionEnter(itemBox);
					OutputDebugString("Kart-Kart Collision Enter\n");
				}
			}
			else
			{
				if (wasColliding)
				{
					// We aren't colliding this frame but we were last frame - that's a collision exit
					//itemBox->OnKartCollisionExit();
					//kart->OnItemBoxCollisionExit(itemBox);
					OutputDebugString("Kart-Kart Collision Exit\n");
				}
			}
		}
	}
}

/*void CollisionManager::KartToKart()
{
	// We'll check each kart against every other kart
	// Note this is not overly efficient, both in readability and runtime performance

	for (int i = 0; i < m_karts->size(); i++)
	{
		for (int j = 0; j < m_karts->size(); j++)
		{
			// Don't need to store pointer to these objects again but favouring clarity
			Kart* firstKart = (*m_karts)[i];
			Kart* secondKart = (*m_karts)[j];

			// Don't compare a kart to itself
			// Comparing memory addresses - beauty of pointers
			if (firstKart != secondKart)
			{
				CBoundingBox firstBounds = firstKart->GetBounds();
				CBoundingBox secondBounds = secondKart->GetBounds();

				// Do we already know about a collision between these two karts
				bool alreadyHandled = ArrayContainsCollision(m_currentCollisions, firstKart, secondKart);

				if (!alreadyHandled)
				{
					// Are they colliding this frame?
					bool isColliding = CheckCollision(firstBounds, secondBounds);

					// Were they colliding last frame?
					bool wasColliding = ArrayContainsCollision(m_previousCollisions, firstKart, secondKart);

					if (isColliding)
					{
						// Register the collision
						AddCollision(firstKart, secondKart);

						if (wasColliding)
						{
							// We are colliding this frame and we were also colliding last frame - that's a collision stay
							// Tell both karts so they can respond. Also give each one the other kart.
							firstKart->OnKartCollisionStay(secondKart);
							secondKart->OnKartCollisionStay(firstKart);
						}
						else
						{
							// We are colliding this frame and we weren't last frame - that's a collision enter
							firstKart->OnKartCollisionEnter(secondKart);
							secondKart->OnKartCollisionEnter(firstKart);
						}
					}
					else
					{
						if (wasColliding)
						{
							// We aren't colliding this frame but we were last frame - that's a collision exit
							firstKart->OnKartCollisionExit(secondKart);
							secondKart->OnKartCollisionExit(firstKart);
						}
					}
				}
			}
		}
	}
}*/