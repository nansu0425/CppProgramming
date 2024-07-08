#pragma once

class Monster;
class Player;

class Field
{
public:
	Field();
	~Field();

	void Update(Player* pPlayer);
	void CreateMonster();
	void StartBattle(Player* pPlayer);
private:
	Monster* m_pMonster;
};

