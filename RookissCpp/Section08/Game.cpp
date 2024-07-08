#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Field.h"

Game::Game() :m_pPlayer(nullptr), m_pField(nullptr)
{

}

Game::~Game()
{
	if (m_pPlayer != nullptr)
		delete m_pPlayer;
	if (m_pField != nullptr)
		delete m_pField;
}

void Game::init()
{
	if (m_pField == nullptr)
		m_pField = new Field();
}

void Game::update()
{
	if (m_pPlayer == nullptr)
		CreatePlayer();

	if (m_pPlayer->IsDead())
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
		CreatePlayer();
	}

	m_pField->Update(m_pPlayer);
}

void Game::CreatePlayer()
{
	while (m_pPlayer == nullptr)
	{
		std::cout << "---------------------" << std::endl;
		std::cout << "캐릭터를 생성하세요!" << std::endl;
		std::cout << "1) Knight 2) Archer 3) Maze" << std::endl;
		std::cout << "---------------------" << std::endl;
		
		std::cout << "> ";

		int n = 0;

		std::cin >> n;

		switch (n)
		{
		case PT_Knight:
			m_pPlayer = new Knight();
			break;
		case PT_Archer:
			m_pPlayer = new Archer();
			break;
		case PT_Mage:
			m_pPlayer = new Mage();
			break;
		default:
			break;
		}
	}
}