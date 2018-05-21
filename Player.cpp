#include "Player.h"
#include "MathsHelper.h"

/*Player::Player()
{
	m_input = NULL;
	m_moveSpeed = 10.0f;
	//m_movesRemainingBar = NULL;
	m_health = 100.0f;
	m_score = 0;
	//m_monstersDefeated = 0;
	//m_movesRemaining = MAX_MOVES;

	//m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(),m_position + m_mesh->GetMax());
	
}*/

Player::Player(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input,GameBoard* board)
	: GameObject(mesh, shader, texture, position)
{
	m_input = input;
	m_moveSpeed = 10.0f;
	m_health = 100.0f;
	m_score = 0;
	m_loaclForward = Vector3(0, 0, 0);
	m_loaclright = Vector3(0, 0, 0);
	m_loaclleft = Vector3(0, 0, 0);

	m_heading = 0.0f;
	m_rotationSpeed = 1.0f;
	//m_monstersDefeated = 0;
	//m_movesRemaining = MAX_MOVES;
	//m_position = Vector3::Zero;

	m_currentBoard = board;
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
}

Player::~Player() {}

void Player::Update(float timestep)
{
	// We need to identify the frame input was received so we can perform common logic
	// outside of the GetKeyDown IF statements below.
	m_heading += m_input->GetMouseDeltaX() * m_rotationSpeed * timestep;
	Matrix heading = Matrix::CreateRotationY(m_heading);
	m_loaclForward = Vector3::TransformNormal(Vector3(0, 0, 1), heading);
	m_loaclbackward = Vector3::TransformNormal(Vector3(0, 0, -1), heading);
	m_loaclright = Vector3::TransformNormal(Vector3(1, 0, 0), heading);
	m_loaclleft = Vector3::TransformNormal(Vector3(-1, 0, 0), heading);

	if (m_input->GetKeyHold(VK_UP))
	{
		m_position += m_loaclForward * m_moveSpeed * timestep;
	}
	if (m_input->GetKeyHold(VK_DOWN))
	{
		m_position += m_loaclbackward* m_moveSpeed * timestep;
	}
	if (m_input->GetKeyHold(VK_LEFT))
	{
		m_position += m_loaclleft * m_moveSpeed * timestep;
	}
	if (m_input->GetKeyHold(VK_RIGHT))
	{
		m_position += m_loaclright * m_moveSpeed * timestep;
	}

	if(m_input->GetMouseUp(0))
	{
		m_currentBoard->InitBullet(m_position, m_loaclForward); 
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

void Player::BeHit(int amount)
{
	// "abs" keeps a value positive
	m_health -= abs(amount);
}

/*void Player::DoMonsterBattle()
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
}*/