#include "CollisionManager.h"

CollisionManager::CollisionManager(Player* player, vector<GameObject*>* itemBoxes)
{
	m_playerCollision = player;
	m_itemBoxes = itemBoxes;//new add

	// Clear our arrays to 0 (NULL)
	memset(m_currentCollisions, 0, sizeof(m_currentCollisions));
	memset(m_previousCollisions, 0, sizeof(m_previousCollisions));

	m_nextCurrentCollisionSlot = 0;
}

void CollisionManager::CheckCollisions()
{
	// Check kart to item box collisions
	PlayerToItemBox();//new add
	

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

void CollisionManager::PlayerToItemBox()
{
	// We'll check each kart against every item box
	// Note this is not overly efficient, both in readability and runtime performance
		for (unsigned int j = 0; j < m_itemBoxes->size(); j++)//new add
		{
			// Don't need to store pointer to these objects again but favouring clarity
			// Can't index into these directly as they're a pointer to a vector. We need to dereference them first
			Player* player = m_playerCollision;
			GameObject* itemBox = (*m_itemBoxes)[j];//new add

			CBoundingBox playerBounds = player->GetBounds();
			CBoundingBox itemBoxBounds = itemBox->GetBounds();//new add

			// Are they colliding this frame?
			bool isColliding = CheckCollision(playerBounds, itemBoxBounds);//new add

			// Were they colliding last frame?
			bool wasColliding = ArrayContainsCollision(m_previousCollisions, player, itemBox);//new add

			if (isColliding)
			{
				// Register the collision
				AddCollision(player, itemBox);//NEW ADD

				if (wasColliding)
				{
					// We are colliding this frame and we were also colliding last frame - that's a collision stay
					// Tell the item box a kart has collided with it (we could pass it the actual kart too if we like)
					//OutputDebugString("Kart-Kart Collision Stay\n");
					//healthCapslue->OnKartCollisionStay();
					player->OnItemBoxCollisionStay(itemBox);//new add
				}
				else
				{
					// We are colliding this frame and we weren't last frame - that's a collision enter
					//itemBox->OnKartCollisionEnter();
					//kart->OnItemBoxCollisionEnter(itemBox);
					//OutputDebugString("Kart-Kart Collision Enter\n");
					player->OnItemBoxCollisionEnter(itemBox);//new add
				}
			}
			else
			{
				if (wasColliding)
				{
					// We aren't colliding this frame but we were last frame - that's a collision exit
					//itemBox->OnKartCollisionExit();
					//kart->OnItemBoxCollisionExit(itemBox);
					//OutputDebugString("Kart-Kart Collision Exit\n");
					player->OnItemBoxCollisionExit(itemBox);//new add
				}
			}
		}
	}


