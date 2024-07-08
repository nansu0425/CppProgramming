#pragma once

enum CreatureType
{
	CT_PLAYER,
	CT_MONSTER,
};

class Creature
{
public:
	Creature(CreatureType creatureType) 
		:m_creatureType(creatureType), m_hp(0), m_attack(0), m_defence(0)
	{

	}

	virtual ~Creature()
	{

	}

	virtual void PrintInfo() = 0;
	void OnAttacked(Creature* creature);
	bool IsDead() { return m_hp <= 0; }
protected:
	CreatureType m_creatureType;
	int m_hp;
	int m_attack;
	int m_defence;
};

