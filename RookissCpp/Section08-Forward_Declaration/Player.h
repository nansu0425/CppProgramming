#pragma once

#define FORWARD_DECLARATION true

#if FORWARD_DECLARATION == false
#include "Monster.h"
#endif // FORWARD_DECLARATION

class Player
{
public:
	void KillMonster();

#if FORWARD_DECLARATION
#define INCLUDE_ERROR false

#if INCLUDE_ERROR
	// Monster Class�� ���� ������ �����Ƿ� ����
	void killMonster2()
	{
		m_pMonster->KillMe();
		m_pMonster->m_hp = 0;
	}
#endif // INCLUDE_ERROR
#endif // FORWARD_DECLARATION
public:
	// 8����Ʈ
	int m_hp;
	int m_attack;

#if FORWARD_DECLARATION
	// x86->4����Ʈ, x64->8����Ʈ
	class Monster* m_pMonster; // Monster Ŭ������ ���� ���� �ʿ� ����
#else
	// sizeof(Monster) ����Ʈ
	Monster m_monster; // Monster Ŭ������ ���� ������ �ʿ��ϴ� 
#endif // FORWARD_DECLARATION

	Player* m_pPlayer; // Player class ���� �ʿ����
	// Player m_player; ������ Player class ������ �ʿ��ϴ�
};

