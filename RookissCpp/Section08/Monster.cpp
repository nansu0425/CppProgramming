#include <iostream>
#include "Monster.h"

void Monster::PrintInfo()
{
	std::cout << "---------------------" << std::endl;
	std::cout << "[몬스터 정보] " 
		<< "HP: " << m_hp
		<< " ATT: " << m_attack
		<< " DEF: " << m_defence
		<< std::endl;
	std::cout << "---------------------" << std::endl;
}