#include "Player.h"
#include "Monster.h"
#include "MathsHelper.h"

Player::Player()
{
	m_input = NULL;
	m_moveSpeed = 10.0f;
	//m_movesRemainingBar = NULL;
	m_health = 100.0f;
	m_score = 0;
	//m_monstersDefeated = 0;
	//m_movesRemaining = MAX_MOVES;

	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(),m_position + m_mesh->GetMax());
	
}

Player::Player(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input)
	: GameObject(mesh, shader, texture, position)
{
	m_input = input;
	m_moveSpeed = 10.0f;
	m_health = 100.0f;
	m_score = 0;
	//m_monstersDefeated = 0;
	//m_movesRemaining = MAX_MOVES;
	m_position = Vector3::Zero;

	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
}

Player::~Player() {}

void Player::Update(float timestep)
{
	// We need to identify the frame input was received so we can perform common logic
	// outside of the GetKeyDown IF statements below.

	if (m_input->GetKeyHold('W'))
	{
		m_position += Vector3(0.0f, 0.0f, 1.0f) * m_moveSpeed * timestep;
	}
	if (m_input->GetKeyHold('S'))
	{
		m_position += Vector3(0.0f, 0.0f, -1.0f) * m_moveSpeed * timestep;
	}
	if (m_input->GetKeyHold('A'))
	{
		m_position += Vector3(-1.0f, 0.0f, 0.0f) * m_moveSpeed * timestep;
	}
	if (m_input->GetKeyHold('D'))
	{
		m_position += Vector3(1.0f, 0.0f, 0.0f) * m_moveSpeed * timestep;
	}

	m_boundingBox.SetMin(m_position + m_mesh->GetMin());
	m_boundingBox.SetMax(m_position + m_mesh->GetMax());
}

void Player::OnKartCollisionEnter(Player * other)
{
	OutputDebugString("Kart-Kart Collision Enter\n");
}

void Player::OnKartCollisionStay(Player* other)
{
	OutputDebugString("Kart-Kart Collision Stay\n");
}

void Player::OnKartCollisionExit(Player* other)
{
	OutputDebugString("Kart-Kart Collision Exit\n");
}

void Player::OnItemBoxCollisionEnter(GameObject* other)
{
	OutputDebugString("Kart-ItemBox Collision Enter\n");

	// Bounce off box - how could you take our velocity into account?
	//ApplyForce((m_position - other->GetPosition()) * 0.5f);
}

void Player::OnItemBoxCollisionStay(GameObject* other)
{
	OutputDebugString("Kart-ItemBox Collision Stay\n");
}

void Player::OnItemBoxCollisionExit(GameObject* other)
{
	OutputDebugString("Kart-ItemBox Collision Exit\n");
}

/*void Player::FinishTurn()
{
	// Even though this is called in an Update function, it's essentially event-driven as it
	// is only called the frame we receive input from the keyboard.

	// React to tile we're standing on
	ReactToTile();
	CheckIfTrapped();

	// Decrease moves remaining
	m_movesRemaining--;

	// Show health visually as scale of player mesh
	SetUniformScale(m_health / 100.0f);
}

bool Player::CanMoveHere(Vector3 target)
{
	// Asks the GameBoard for the type of the target tile
	// We can't step onto a wall or a disabled tile

	TileType targetTileType = m_currentBoard->GetTileTypeForPosition(target.x, target.z);

	return targetTileType != TileType::DISABLED &&
		   targetTileType != TileType::WALL &&
		   targetTileType != TileType::INVALID;
}

void Player::CheckIfTrapped()
{
	// Using our target position, ask the GameBoard for the type of 
	// our surrounding tiles and check if we are surrounded by walls or grey tiles

	m_isTrapped = !CanMoveHere(m_targetPosition + Vector3(0, 0, 1)) &&  // Above
				  !CanMoveHere(m_targetPosition + Vector3(0, 0, -1)) && // Below
				  !CanMoveHere(m_targetPosition + Vector3(-1, 0, 0)) && // Left
				  !CanMoveHere(m_targetPosition + Vector3(1, 0, 0));    // Right
}

void Player::ReactToTile()
{
	TileType targetTileType = m_currentBoard->GetTileTypeForPosition(m_targetPosition.x, m_targetPosition.z);

	switch (targetTileType)
	{
	case TileType::HEALTH:
		m_health += 5;
		break;
	case TileType::DAMAGE:
		m_health -= 10;
		break;
	case TileType::TELEPORT:
		TeleportToTileOfType(TileType::TELEPORT);
		break;
	case TileType::MONSTER_VAR1:
		// We'll react the same to both types of monster. TODO how could we differentiate them?
		DoMonsterBattle();
		break;
	default:
		break;
	}
}

void Player::TeleportToTileOfType(TileType type)
{
	Tile* destinationTile = m_currentBoard->GetRandomTileOfType(type);

	if (destinationTile)
	{
		// We need to set both the current position and the target
		// The only time the player remains still is when these two positions match
		m_targetPosition = destinationTile->GetPosition();
		m_position = destinationTile->GetPosition();

		// Tiles start up in the sky and fall down. Ensure player starts on the ground.
		m_targetPosition.y = 0.0f;
		m_position.y = 0.0f;
	}
}*/

int Player::Attack()
{
	// The player is much stronger than any monster on the board
	return MathsHelper::RandomRange(0, 20);
}

void Player::BeHit(int amount)
{
	// "abs" keeps a value positive
	m_health -= abs(amount);
}

void Player::DoMonsterBattle()
{
	// A battle takes place within a single frame.

	// Slightly hacky, but we only need a Monster when a battle is about to occur.
	// The Player creates a Monster then fights it. Asking the GameBoard for a Monster
	// would perhaps be a more proper way of doing this, however storing Monsters in Tiles
	// would be unnecessary work for this implementation.
	
	Monster monster = Monster();
	

	// We keep fighting until someone dies
	while (m_health > 0 && monster.IsAlive())
	{
		int playerAttackValue = Attack();
		int monsterAttackValue = monster.Attack();

		if (playerAttackValue > monsterAttackValue)
		{
			// Player wins the round - the monster will receive some damage
			monster.BeHit(playerAttackValue - monsterAttackValue);
		}
		else
		{
			// Monster wins round - the player will receive some damage
			BeHit(monsterAttackValue - playerAttackValue);
		}
	}

	if (!monster.IsAlive())
	{
		// If the player won the overall battle, increment our score
		m_score += monster.GetSkill();
		m_monstersDefeated++;
	}
}