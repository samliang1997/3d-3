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
	PlayershootCount++;
	if(m_input->GetMouseUp(0))
	{
		if (PlayershootCount >= 60)
		{
			m_currentBoard->InitBullet(m_position, m_loaclForward);
			PlayershootCount = 0;
		}
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
