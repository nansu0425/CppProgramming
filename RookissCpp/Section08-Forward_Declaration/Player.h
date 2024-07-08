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
	// Monster Class에 대한 정보가 없으므로 에러
	void killMonster2()
	{
		m_pMonster->KillMe();
		m_pMonster->m_hp = 0;
	}
#endif // INCLUDE_ERROR
#endif // FORWARD_DECLARATION
public:
	// 8바이트
	int m_hp;
	int m_attack;

#if FORWARD_DECLARATION
	// x86->4바이트, x64->8바이트
	class Monster* m_pMonster; // Monster 클래스에 대한 정보 필요 없다
#else
	// sizeof(Monster) 바이트
	Monster m_monster; // Monster 클래스에 대한 정보가 필요하다 
#endif // FORWARD_DECLARATION

	Player* m_pPlayer; // Player class 정보 필요없다
	// Player m_player; 완전한 Player class 정보가 필요하다
};

