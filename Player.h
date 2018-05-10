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



class Player : public GameObject
{
private:
	// A Player should listen for its own input
	InputController* m_input;

	float m_moveSpeed;

	// Game variables
	float m_health;
	int m_score;
	int m_monstersDefeated;
	
	CBoundingBox m_boundingBox;

	// Ask the GameBoard if we are allowed to move to a particular tile
	bool CanMoveHere(Vector3 target);

	
	// Housekeeping after we receive input
	void FinishTurn();

	// Check what type of tile is beneth us and react
	void ReactToTile();


	// For Monster battles
	int Attack();
	void BeHit(int amount);
	void DoMonsterBattle();

public:
	Player();
	Player(Mesh* mesh, Shader* shader, Texture* texture, InputController* input, Vector3 position);
	~Player();

	void Update(float timestep);

	// The Game class will use these to determine if the game should end
	float GetHealth() { return m_health; }
	//int GetMovesRemaining() { return m_movesRemaining; }

	// Game will use these to output info to the player
	int GetNumberOfMonstersDefeated() { return m_monstersDefeated; }
	int GetScore() { return m_score; }

	CBoundingBox GetBounds() { return m_boundingBox; }
};

#endif
