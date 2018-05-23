#include "CollisionManager.h"

CollisionManager::CollisionManager(Player* player, GameBoard* gameboard)
{
	m_player = player;
	m_gameboard = gameboard;

	// Clear our arrays to 0 (NULL)
	memset(m_currentCollisions, 0, sizeof(m_currentCollisions));
	memset(m_previousCollisions, 0, sizeof(m_previousCollisions));

	m_nextCurrentCollisionSlot = 0;
}

void CollisionManager::CheckCollisions()
{
	// Check kart to item box collisions
	PlayerToHeal();
	PlayerToMonster();
	//PlayerToWall();
	//PlayerToDisabled();

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

void CollisionManager::PlayerToHeal()
{
	//CBoundingBox playerCollision = m_player->GetBounds();

	for (unsigned int i = 0; i < m_gameboard->GetHeal().size(); i++) 
	{
		CBoundingBox playerCollision = m_player->GetBounds();
		CBoundingBox heal = m_gameboard->GetHeal()[i]->GetBounds();

		bool isColliding = CheckCollision(playerCollision, heal);

		bool wasColliding = ArrayContainsCollision(m_previousCollisions, m_player, m_gameboard->GetHeal()[i]);

		if (isColliding)
		{
			// Register the collision
			AddCollision(m_player, m_gameboard->GetHeal()[i]);//NEW ADD

			if (wasColliding)
			{
				// We are colliding this frame and we were also colliding last frame - that's a collision stay
				// Tell the item box a kart has collided with it (we could pass it the actual kart too if we like)
				OutputDebugString("Kart-Kart Collision Stay\n");
				
			}
			else
			{
				// We are colliding this frame and we weren't last frame - that's a collision enter	
				OutputDebugString("Kart-Kart Collision Enter\n");
			
			}
		}
		else
		{
			if (wasColliding)
			{
				// We aren't colliding this frame but we were last frame - that's a collision exit
				OutputDebugString("Kart-Kart Collision Exit\n");
			}
		}
	}
		
}

void CollisionManager::PlayerToMonster()
{
	CBoundingBox playerCollision = m_player->GetBounds();

	for (unsigned int i = 0; i < m_gameboard->GetMonster().size(); i++)
	{
		CBoundingBox monster = m_gameboard->GetMonster()[i]->GetBounds();

		bool isColliding = CheckCollision(playerCollision, monster);

		bool wasColliding = ArrayContainsCollision(m_previousCollisions, m_player, (m_gameboard->GetMonster())[i]);

		if (isColliding)
		{
			// Register the collision
			AddCollision(m_player, m_gameboard->GetMonster()[i]);//NEW ADD

			if (wasColliding)
			{
				// We are colliding this frame and we were also colliding last frame - that's a collision stay
				// Tell the item box a kart has collided with it (we could pass it the actual kart too if we like)
				OutputDebugString("Kart-Kart Collision Stay\n");				
			}
			else
			{
				// We are colliding this frame and we weren't last frame - that's a collision enter
				OutputDebugString("Kart-Kart Collision Enter\n");
			}
		}
		else
		{
			if (wasColliding)
			{
				// We aren't colliding this frame but we were last frame - that's a collision exit			
				OutputDebugString("Kart-Kart Collision Exit\n");
			}
		}
	}
}

void CollisionManager::PlayerToWall()
	{
		CBoundingBox playerCollision = m_player->GetBounds();

		for (unsigned int i = 0; i < m_gameboard->GetWall().size(); i++)
		{
			CBoundingBox monster = m_gameboard->GetWall()[i]->GetBounds();

			bool isColliding = CheckCollision(playerCollision, monster);

			bool wasColliding = ArrayContainsCollision(m_previousCollisions, m_player, (m_gameboard->GetWall())[i]);

			if (isColliding)
			{
				// Register the collision
				AddCollision(m_player, m_gameboard->GetWall()[i]);//NEW ADD

				if (wasColliding)
				{
					// We are colliding this frame and we were also colliding last frame - that's a collision stay
					// Tell the item box a kart has collided with it (we could pass it the actual kart too if we like)
					OutputDebugString("Kart-Kart Collision Stay\n");					
				}
				else
				{
					// We are colliding this frame and we weren't last frame - that's a collision enter					
					OutputDebugString("Kart-Kart Collision Enter\n");					
				}
			}
			else
			{
				if (wasColliding)
				{
					// We aren't colliding this frame but we were last frame - that's a collision exit
					OutputDebugString("Kart-Kart Collision Exit\n");
				}
			}
		}
}

void CollisionManager::PlayerToDisabled()
{
	CBoundingBox playerCollision = m_player->GetBounds();

	for (unsigned int i = 0; i < m_gameboard->GetDisabledItem().size(); i++)
	{
		CBoundingBox monster = m_gameboard->GetDisabledItem()[i]->GetBounds();

		bool isColliding = CheckCollision(playerCollision, monster);

		bool wasColliding = ArrayContainsCollision(m_previousCollisions, m_player, (m_gameboard->GetDisabledItem())[i]);

		if (isColliding)
		{
			// Register the collision
			AddCollision(m_player, m_gameboard->GetDisabledItem()[i]);//NEW ADD

			if (wasColliding)
			{
				// We are colliding this frame and we were also colliding last frame - that's a collision stay
				// Tell the item box a kart has collided with it (we could pass it the actual kart too if we like)
				OutputDebugString("Kart-Kart Collision Stay\n");
			}
			else
			{
				// We are colliding this frame and we weren't last frame - that's a collision enter					
				OutputDebugString("Kart-Kart Collision Enter\n");
			}
		}
		else
		{
			if (wasColliding)
			{
				// We aren't colliding this frame but we were last frame - that's a collision exit
				OutputDebugString("Kart-Kart Collision Exit\n");
			}
		}
	}
}