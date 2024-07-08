#include <iostream>

#define POLYMORPHISM

#ifdef OBJECT
class Knight
{
public:
	Knight()
	{
		std::cout << "Knight() 기본 생성자 호출"
			<< std::endl;
	}

	Knight(int hp)
	{
		std::cout << "Knight() 변환 생성자 호출"
			<< std::endl;

		m_hp = hp;
		m_attack = 0;
		m_posY = 0;
		m_posX = 0;
	}

	Knight(const Knight& knight)
	{
		std::cout << "Knight() 복사 생성자 호출"
			<< std::endl;
		*this = knight;
	}

	~Knight()
	{
		std::cout << "Kngith() 기본 소멸자 호출"
			<< std::endl;
	}

	void Move(int y, int x);
	void Attack();
	void Die();
	void HelloKnight(const Knight& k);
public:
	int m_hp;
	int m_attack;
	int m_posY;
	int m_posX;
};

void Knight::Die()
{
	m_hp = 0;
	std::cout << "Die" << std::endl;
}

void Knight::Move(int y, int x)
{
	m_posY = y;
	m_posX = x;
	std::cout << "Move" << std::endl;
}

void Move(Knight* pKnight, int y, int x)
{
	pKnight->m_posY = y;
	pKnight->m_posX = x;
}

void Knight::Attack()
{
	std::cout << "Attack" << std::endl;
}

void HelloKnight(const Knight& k)
{
	std::cout << "Hello Knight!"
		<< std::endl;
}

int main()
{
	Knight k1(10);

	Knight k2; 
	k2 = k1;

	k1.Move(2, 2);
	Move(&k1, 3, 5);
	k1.Attack();
	k1.Die();

	Knight k3;
	k3 = (Knight)5;
	HelloKnight(10);
	

	return 0;
}
#endif // OBJECT

#ifdef INHERITANCE
class Player
{
public:
	Player() 
	{
		std::cout << "Player:\tPlayer()\n";

		m_hp = 0;
		m_attack = 0;
		m_defence = 0;
	}

	Player(int hp)
	{
		std::cout << "Player:\tPlayer(int hp)\n";

		m_hp = hp;
		m_attack = 0;
		m_defence = 0;
	}

	~Player() { std::cout << "Player:\tdefault destructor\n"; }

	int m_hp;
	int m_attack;
	int m_defence;
public:
	void Move() { std::cout << "Player:\tMove()\n"; }
	void Attack() { std::cout << "Player:\tAttack()\n"; }
	void Die() { std::cout << "Player:\tDie()\n"; }
};

class Knight : public Player
{
public:
	Knight() 
	{ 
		std::cout << "Knight:\tdefault constructor\n";
	
		m_stemina = 100;
	}

	Knight(int stemina) : Player(100)
	{
		std::cout << "Knight:\tdefault constructor\n";

		m_stemina = stemina;
	}

	~Knight() { std::cout << "Knight:\tdefault destructor\n"; }

	int m_stemina;
public:
	void Move() { std::cout << "Knight:\tMove()\n"; }
};

class Mage : public Player
{
public:
	int m_mp;
};	

int main()
{
	Knight k1(80);
	k1.m_attack = 10;
	k1.m_defence = 5;

	k1.Move();
	k1.Player::Move();
	k1.Die();

	return 0;
}
#endif // INHERITANCE

#ifdef ENCAPSULATION

#define BERSERKER

#ifdef CAR
class Car
{
public:
	void MoveHandle();
	void PushHandle();
	void OpenDoor();
	void TurnKey();
protected:
	void DisassembleCar();
	void RunEngine();
	void ConnectCircit();
};

void Car::TurnKey()
{
	RunEngine();
}

class SuperCar : public Car
{
public:
	void PushRemoteController();
};

void SuperCar::PushRemoteController()
{
	DisassembleCar();
}
#endif // CAR

#ifdef BERSERKER
class Berserker
{
public:
	void SetHp(int hp)
	{
		m_hp = hp;
		if (m_hp < 50)
			SetBerserkerMode();
	}
private:
	void SetBerserkerMode()
	{
		std::cout << "버서커 모드!"
			<< std::endl;
	}
private:
	int m_hp = 100;
};
#endif // BERSERKER

int main()
{
	//Car car;
	//car.DisassembleCar();
	//car.RunEngine();

	//SuperCar superCar;
	//superCar.OpenDoor();

	Berserker bsk;
	bsk.SetHp(20);

	return 0;
}
#endif // ENCAPSULATION

#ifdef POLYMORPHISM
class Player
{
public:
	int m_hp;
public:
	virtual void VMove()
	{
		std::cout << "Player: VMove()\n";
	}

	virtual void VAttack() = 0;
};

class Knight :public Player
{
public:
	int m_stamina;
public:
	void VMove()
	{
		std::cout << "Knight: VMove()\n";
	}

	void VAttack()
	{
		std::cout << "Knight: VAttack()\n";
	}
};

class Mage :public Player
{
public:
	int m_mp;
};

void MovePlayer(Player* player)
{
	player->VMove();
}

void MoveKnight(Knight* knight)
{
	knight->VMove();
}

void AttackPlayer(Player* player)
{
	// player->VAttack();
}

int main()
{
	// Player p;
	//MovePlayer(&p);

	Knight k;
	k.m_hp = 100;
	k.m_stamina = 50;
	//MoveKnight(&k);
	MovePlayer(&k);
	AttackPlayer(&k);

	return 0;
}
#endif // POLYMORPHYSM

#ifdef INITIALIZER_LIST
class Inventory
{
public:
	Inventory()
	{
		std::cout << "Inventory()\n";
	}

	Inventory(int size) :m_size(size)
	{
		std::cout << "Inventory(size)\n";
	}

	~Inventory()
	{
		std::cout << "~Inventory()\n";
	}
public:
	int m_size = 10;
};

class Player
{
public:
	Player()
	{

	}

	Player(int id)
	{
		
	}
};

class Knight :public Player
{
public:
	Knight() :Player(1), m_hp(100), m_inventory(20), m_refHp(m_hp), m_cHp(m_hp)
	{
		m_hp = 80;
	}
public:
	int m_hp;
	Inventory m_inventory;
	int& m_refHp;
	const int m_cHp;
};

int main()
{
	Knight k;

	std::cout << k.m_hp << std::endl;

	return 0;
}
#endif // INITIALIZE_LIST

#ifdef OPERATOR_OVERLOADING
class Position
{
public:
	Position(int x, int y) :m_x(x), m_y(y)
	{

	}

	Position operator+(const Position& rPos)
	{
		Position p(
			this->m_x + rPos.m_x,
			this->m_y + rPos.m_y
		);
		
		return p;
	}

	Position operator+(int arg)
	{
		Position p(
			this->m_x + arg,
			this->m_y + arg
		);

		return p;
	}

	Position& operator=(int arg)
	{
		m_x = arg;
		m_y = arg;

		return *this;
	}

	Position& operator=(const Position& rPos)
	{
		m_x = rPos.m_x;
		m_y = rPos.m_y;

		return *this;
	}

	bool operator==(const Position& rPos)
	{
		return this->m_x == rPos.m_x &&
			this->m_y == rPos.m_y;
	}

	Position& operator++()
	{
		m_x++;
		m_y++;

		return *this;
	}

	Position operator++(int)
	{
		Position ret = *this;
		m_x++;
		m_y++;

		return ret;
	}

public:
	int m_x;
	int m_y;
};

Position operator+(int arg, const Position& rPos)
{
	Position p(
		arg + rPos.m_x,
		arg + rPos.m_y
	);

	return p;
}

int main()
{
	Position p1(0, 0);
	Position p2(1, 1);
	
	Position p3 = p1 + p2;
	Position p4 = p3 + 1;
	Position p5 = 4 + p4;

	if (p2 == p3)
		std::cout << "p2 == p3" << std::endl;

	p5 = 6;
	p5 = ++p5;
	p4 = p5++;

	return 0;
}
#endif // OPERATOR_OVERLOADING

#ifdef STATIC
class Marine
{
public:
	static int s_attack;
	int m_hp;
	int m_id;
public:
	Marine() :m_hp(4), m_id(-1)
	{
		SetAttack(5);
	}

	void TakeDamage(int damage)
	{
		m_hp -= damage;
	}

	void SetId(int id)
	{
		m_id = id;
	}

	static void SetAttack(int attack)
	{
		s_attack = attack;
	}
};

int GenerateId() {
	static int id = 0;
	
	return ++id;
}

int Marine::s_attack = 10;

int main()
{
	Marine m;
	m.SetId(GenerateId());

	return 0;
}
#endif // STATIC