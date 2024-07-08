#include "Player.h"
#include "Monster.h"

// Monster Class에 대한 정보가 필요하다
void Player::KillMonster()
{
	m_pMonster->m_hp = 0; 
	m_pMonster->KillMe();
}