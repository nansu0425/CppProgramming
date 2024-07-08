#pragma once

#include "Creature.h"

enum PlayerType
{
	PT_Knight = 1,
	PT_Archer,
	PT_Mage,
};

class Player :public Creature
{
public:
	Player(PlayerType playerType) 
		:Creature(CT_PLAYER), m_playerType(playerType)
	{

	}

	~Player()
	{
		
	}

	virtual void PrintInfo();
protected:
	PlayerType m_playerType;
};

class Knight :public Player
{
public:
	Knight() :Player(PT_Knight)
	{
		m_hp = 150;
		m_attack = 10;
		m_defence = 5;
	}
};

class Archer :public Player
{
public:
	Archer() :Player(PT_Archer)
	{
		m_hp = 80;
		m_attack = 15;
		m_defence = 3;
	}
};

class Mage :public Player
{
public:
	Mage() :Player(PT_Mage)
	{
		m_hp = 50;
		m_attack = 25;
		m_defence = 0;
	}
};