/*	FIT2096 - Assignment 1 Sample Solution
*	Player.h
*	Created by Mike Yeates - 2017 - Monash University
*	A Player listens to the keyboard and responds to arrow key presses.
*	It LERPs itself between cells and also asks the GameBoard where it can move.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "InputController.h"
#include "Collisions.h"
#include "GameBoard.h"

class Player : public GameObject
{
private:
	// A Player should listen for its own input
	InputController* m_input;

	
	float m_moveSpeed;
	Vector3 m_loaclForward;
	Vector3 m_loaclbackward;
	Vector3 m_loaclright;
	Vector3 m_loaclleft;

	float m_heading;
	float m_rotationSpeed;

	// Game variables
	float m_health;
	int m_score;
	int m_monstersDefeated;
	
	CBoundingBox m_boundingBox;

	GameBoard* m_currentBoard;
	// For Monster battles
	void BeHit(int amount);
	void DoMonsterBattle();

public:
	Player();
	Player(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position,InputController* input, GameBoard* board);
	~Player();

	void Update(float timestep);

	// The Game class will use these to determine if the game should end
	float GetHealth() { return m_health; }

	// Game will use these to output info to the player
	int GetNumberOfMonstersDefeated() { return m_monstersDefeated; }
	int GetScore() { return m_score; }

	CBoundingBox GetBounds() { return m_boundingBox;}

	void OnKartCollisionEnter(Player* other);
	void OnKartCollisionStay(Player* other);
	void OnKartCollisionExit(Player* other);

	void OnItemBoxCollisionEnter(GameObject* other);
	void OnItemBoxCollisionStay(GameObject* other);
	void OnItemBoxCollisionExit(GameObject* other);

};

#endif
