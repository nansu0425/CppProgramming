#pragma once

// 전방 선언
class Player;
class Field;

class Game
{
public:
	Game();
	~Game();

	void init();
	void update();
	void CreatePlayer();
public:
	Player* m_pPlayer;
	Field* m_pField;
};

