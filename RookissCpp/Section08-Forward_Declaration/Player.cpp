#include "Player.h"
#include "Monster.h"

// Monster Class�� ���� ������ �ʿ��ϴ�
void Player::KillMonster()
{
	m_pMonster->m_hp = 0; 
	m_pMonster->KillMe();
}