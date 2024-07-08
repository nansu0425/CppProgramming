#include <stdlib.h>
#include "Field.h"
#include "Player.h"
#include "Monster.h"

Field::Field() :m_pMonster(nullptr)
{

}

Field::~Field()
{
	if (m_pMonster != nullptr)
		delete m_pMonster;
}

void Field::Update(Player* pPlayer)
{
	if (m_pMonster == nullptr)
		CreateMonster();

	StartBattle(pPlayer);
}

void Field::CreateMonster()
{
	int randVal = rand() % 3 + 1;

	switch (randVal)
	{
	case MT_Slime:
		m_pMonster = new Slime();
		break;
	case MT_Orc:
		m_pMonster = new Orc();
		break;
	case MT_Skeleton:
		m_pMonster = new Skeleton();
		break;
	default:
		break;
	}
}

void Field::StartBattle(Player* pPlayer)
{
	while (true)
	{
		pPlayer->PrintInfo();
		m_pMonster->PrintInfo();
		
		m_pMonster->OnAttacked(pPlayer);
		if (m_pMonster->IsDead())
		{
			m_pMonster->PrintInfo();
			delete m_pMonster;
			m_pMonster = nullptr;
			break;
		}

		pPlayer->OnAttacked(m_pMonster);
		if (pPlayer->IsDead())
		{
			pPlayer->PrintInfo();
			break;
		}
	}
}