#include "GameBoard.h"
#include "MathsHelper.h"
#include <vector>

GameBoard::GameBoard()
{
	m_meshManager = NULL;
	m_textureManager = NULL;
	m_diffuseTexturedShader = NULL;
}

GameBoard::GameBoard(MeshManager* meshManager, Shader* shader, TextureManager* textureManager)
{
	m_meshManager = meshManager;  
	m_textureManager = textureManager;
	m_diffuseTexturedShader = shader;

	
	Generate();
}

GameBoard::~GameBoard()
{
}

void GameBoard::Update(float timestep,Vector3 playerposition)
{

	m_ground->Update(timestep);

	for (int i = 0; i < m_disableditem.size(); i++)
	{
		m_disableditem[i]->Update(timestep);		
	}
	
	for (int i = 0; i < m_heal.size(); i++)
	{
		m_heal[i]->Update(timestep);
	}
	for (int i = 0; i < m_wall.size(); i++)
	{
		m_wall[i]->Update(timestep);
	}
	for (int i = 0; i < m_monster.size(); i++)
	{ 
		m_monster[i]->Update(timestep, playerposition);
	
		monsterShootCount1++;
		monsterShootCount2++;
		monsterShootCount3++;
		monsterShootCount4++;
		monsterShootCount5++;

		if (monsterShootCount1 >= 2400)
		{
			Vector3 monsterheading = playerposition - m_monster[0]->GetPosition();
			monsterheading.Normalize();
			InitBullet(m_monster[0]->GetPosition(), monsterheading);
			monsterShootCount1 = 0;
		}
		else if (monsterShootCount2 >= 2400) 
		{
			Vector3 monsterheading = playerposition - m_monster[1]->GetPosition();
			monsterheading.Normalize();
			InitBullet(m_monster[1]->GetPosition(), monsterheading);
			monsterShootCount2 = 0;
		}
		else if (monsterShootCount3 >= 2400)
		{
			Vector3 monsterheading = playerposition - m_monster[2]->GetPosition();
			monsterheading.Normalize();
			InitBullet(m_monster[2]->GetPosition(), monsterheading);
			monsterShootCount3 = 0;
		}
		else if (monsterShootCount4 >= 2400)
		{
			Vector3 monsterheading = playerposition - m_monster[3]->GetPosition();
			monsterheading.Normalize();
			InitBullet(m_monster[3]->GetPosition(), monsterheading);
			monsterShootCount4 = 0;
		}
		else if (monsterShootCount5 >= 2400)
		{
			Vector3 monsterheading = playerposition - m_monster[4]->GetPosition();
			monsterheading.Normalize();
			InitBullet(m_monster[4]->GetPosition(), monsterheading);
			monsterShootCount5 = 0;
		}
		
	}

	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->Update(timestep);
	}
}

void GameBoard::Render(Direct3D* renderer, Camera* camera)
{
	m_ground->Render(renderer, camera);

	for (int i = 0; i < m_wall.size(); i++)
	{
		m_wall[i]->Render(renderer, camera);
	}

	for (int i = 0; i < m_disableditem.size(); i++)
	{
		m_disableditem[i]->Render(renderer, camera);
	}

	for (int i = 0; i < m_heal.size(); i++)
	{
		m_heal[i]->Render(renderer, camera);
	}

	for (int i = 0; i < m_monster.size(); i++) 
	{
		m_monster[i]->Render(renderer, camera); 
	}

	for (int i = 0; i < m_bullet.size(); i++)
	{
		m_bullet[i]->Render(renderer, camera);
	}
}

void GameBoard::Generate()
{
	m_ground = new StaticObject(m_meshManager->GetMesh("Assets/Meshes/ground.obj"),
		m_diffuseTexturedShader,
		m_textureManager->GetTexture("Assets/Textures/ground.png"));

	m_ground->SetXScale(0.5f);
	m_ground->SetZScale(0.5f);

	InitMonster();
	InitHealthCapsule();
	InitGameWorld();
	InitWall();

}

void GameBoard::InitGameWorld()
{
	for (int i = 0; i<200; i++)
	{
		Vector3 position = Vector3(MathsHelper::RandomRange(-69.0f, 69.0f), 0.0f, MathsHelper::RandomRange(-69.0f, 69.0f));

		m_disableditem.push_back(new StaticObject(m_meshManager->GetMesh("Assets/Meshes/wall_tile.obj"),
			m_diffuseTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"),
			position));
	}
}

void GameBoard::InitHealthCapsule()
{
	for (int i = 0; i<20; i++)
	{
		Vector3 position = Vector3(MathsHelper::RandomRange(-69.0f, 69.0f), 0.0f, MathsHelper::RandomRange(-69.0f, 69.0f));

		m_heal.push_back(new HealthCapsule(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
			m_diffuseTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/tile_green.png"),
			position));
	}
}

void GameBoard::InitMonster()
{
	for (int i = 0; i < 5; i++) 
	{
		Vector3 position = Vector3(MathsHelper::RandomRange(-69.0f, 69.0f), 0.0f, MathsHelper::RandomRange(-69.0f, 69.0f));
		m_monster.push_back(new Monster(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
			m_diffuseTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/gradient_redPink.png"),
			position));
	}

}

void GameBoard::InitWall()
{
	for (float i = -70; i < 71; i++)
	{
		for (float j = -70; j < 71; j++)
		{
			if (i == -70 || j == -70 || i==70||j==70)
			{
				m_wall.push_back( new StaticObject(m_meshManager->GetMesh("Assets/Meshes/wall_tile.obj"),
					m_diffuseTexturedShader,
					m_textureManager->GetTexture("Assets/Textures/tile_blue.png"),
					Vector3(i,0,j)));
			}
		}
	}
}

void GameBoard::InitBullet(Vector3 position, Vector3 heading)
{
	m_bullet.push_back(new Bullet(
			m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
			m_diffuseTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/gradient_redDarker.png"),
			position,
			heading));
}



