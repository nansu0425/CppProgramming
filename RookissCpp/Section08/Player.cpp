#include <iostream>
#include "Player.h"

void Player::PrintInfo()
{
	std::cout << "---------------------" << std::endl;
	std::cout << "[플레이어 정보] "
		<< "HP: " << m_hp
		<< " ATT: " << m_attack
		<< " DEF: " << m_defence
		<< std::endl;
	std::cout << "---------------------" << std::endl;
}