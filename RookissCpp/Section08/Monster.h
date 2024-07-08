#pragma once
#include "Creature.h"

enum MonsterType
{
	MT_Slime = 1,
	MT_Orc,
	MT_Skeleton
};

class Monster :public Creature
{
public:
	Monster(MonsterType monsterType)
		:Creature(CT_MONSTER), m_monsterType(monsterType)
	{

	}

	~Monster()
	{

	}

	virtual void PrintInfo();
protected:
	MonsterType m_monsterType;
};

class Slime :public Monster
{
public:
	Slime() 
		:Monster(MT_Slime)
	{
		m_hp = 50;
		m_attack = 5;
		m_defence = 2;
	}
};

class Orc :public Monster
{
public:
	Orc() :Monster(MT_Orc)
	{
		m_hp = 80;
		m_attack = 8;
		m_defence = 3;
	}
};

class Skeleton :public Monster
{
public:
	Skeleton() :Monster(MT_Skeleton)
	{
		m_hp = 100;
		m_attack = 15;
		m_defence = 4;
	}
};