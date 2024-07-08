#include <iostream>

#define NAMED_CAST

#ifdef DYNAMIC_ALLOC
class Monster
{
public:
	Monster()
	{
		std::cout << "Monster()" << std::endl;
	}

	~Monster()
	{
		std::cout << "~Monster()" << std::endl;
	}

public:
	int m_hp;
	int m_x;
	int m_y;
};

int main()
{
	std::cout << "----------------malloc/free/nullptr----------------\n";

	void* p = malloc(sizeof(Monster));
	Monster* m1 = (Monster*)p;

	if (m1 != nullptr)
	{
		m1->m_hp = 100;
		m1->m_x = 1;
		m1->m_y = 2;
	
		free(m1);
		m1 = nullptr;
	}

	std::cout << "----------------new/delete/nullptr----------------\n";

	Monster* m2 = new Monster;

	if (m2 != nullptr)
	{
		m2->m_hp = 200;
		(*m2).m_x = 2;
		m2->m_y = 3;
	
		delete m2;
		m2 = nullptr;
	}

	std::cout << "----------------new[]/delete[]/nullptr----------------\n";

	Monster* arrM = new Monster[5];

	if (arrM != nullptr)
	{
		arrM[1].m_hp = 300;
		(arrM + 1)->m_x = 3;
		(*(arrM + 1)).m_y = 4;
	
		delete[] arrM;
		arrM = nullptr;
	}

	return 0;
}
#endif // DYNAMIC_ALLOC

#ifdef TYPE_CONVERSION
class Knight
{
public:
	int m_hp = 100;
};

class Dog
{
public:
	Dog()
	{

	}

	explicit Dog(const Knight& knight)
	{

	}

	explicit operator Knight()
	{

	}
public:
	int m_age = 2;
	int m_cuteness = 1;
};

class BullDog :public Dog
{
public:
	bool m_french;
};

int main()
{
	{ // float 타입으로 변환
		int a = 12345678;
		float b = (float)a;
		std::cout << b << std::endl;
	}

	{ // float 타입으로 해석
		int a = 12345678;
		float b = (float&)a;
		std::cout << b << std::endl;
	}

	{ // 묵시적 변환
		int a = 12345678;
		float b = a;
		std::cout << b << std::endl;
	}

	{ // 명시적 변환
		int a = 12345678;
		float* b = (float*)&a;
		std::cout << *b << std::endl;
	}

	{ // 명시적 변환 생성자
		Knight knight;
		Dog dog = (Dog)knight;
	}

	{ // 명시적 변환 연산자
		Dog dog;
		Knight knight = (Knight)dog;
	}

	{ // 참조/포인터 변환
		Knight knight;
		Dog& r_dog = (Dog&)knight;
		Dog* p_dog = (Dog*)&knight;
	}

	{ // 부모 = 자식만 가능, 자식 = 부모 불가능
		BullDog bulldog;
		Dog dog = bulldog;
	}

	{ // 상속 관계 참조/포인터
		Dog dog;
		BullDog& rBulldog = (BullDog&)dog;
		BullDog* pBulldog = (BullDog*)&dog;
	}

	return 0;
}
#endif // TYPE_CONVERSION

#ifdef POINTER_CONVERSION
class Knight
{
public:
	int m_hp = 100;
};

enum ItemType
{
	WEAPON = 1,
	ARMOR
};

class Item
{
public:
	Item()
	{
		std::cout << "Item()\n";
	}

	Item(int type) :m_type(type)
	{

	}

	Item(const Item& item)
	{
		std::cout << "Item(const Item& item)\n";
	}

	virtual ~Item()
	{
		std::cout << "~Item()\n";
	}
public:
	int m_type = 0;
	int m_id = 0;
	char m_dummy[4096] = {};
};

class Weapon :public Item
{
public:
	Weapon() :Item(WEAPON)
	{
		std::cout << "Weapon()\n";
	}

	~Weapon()
	{
		std::cout << "~Weapon()\n";
	}
public:
	int m_damage = 0;
};

class Armor :public Item
{
public:
	Armor() :Item(ARMOR)
	{
		std::cout << "Armor()\n";
	}

	~Armor()
	{
		std::cout << "~Armor()\n";
	}
public:
	int m_defence = 0;
};

void TestItem(Item item)
{

}

void TestItemPtr(Item* item)
{


}

int main()
{
	{ // 생성/소멸 시점 차이
		Item stackItem;
		Item* heapItem = new Item();

		TestItem(stackItem);
		TestItemPtr(heapItem);

		delete heapItem;
		heapItem = nullptr;
	}

	{ // heap corruption
		/*Knight* pKnight = new Knight();
		
		Item* pItem = (Item*)pKnight;
		pItem->m_type = 4;
		pItem->m_id = 10;
		
		delete pKnight;
		pKnight = nullptr;*/
	}

	std::cout << "--------가상 소멸자--------\n";
	{ 
		Item* inventory[20] = {};

		srand((unsigned)time(nullptr));

		for (auto& pItem : inventory)
		{
			pItem =
				(rand() % 2) ?
				(Item*)new Weapon() :
				(Item*)new Armor();
		}

		for (auto& pItem : inventory)
		{
			/*if (pItem != nullptr)
			{
				if (pItem->m_type == WEAPON)
				{
					Weapon* pWeapon = (Weapon*)pItem;
					delete pWeapon;
				}
				else if (pItem->m_type == ARMOR)
				{
					Armor* pArmor = (Armor*)pItem;
					delete pArmor;
				}

				pItem = nullptr;
			}*/

			delete pItem;
			pItem = nullptr;
		}
	}

	return 0;
}
#endif // POINTER_CONVERSION

#ifdef COPY
class Pet
{
public:
	Pet()
	{
		std::cout << "Pet()\n";
	}

	Pet(const Pet& pet)
	{
		std::cout << "Pet(const Pet& pet)\n";
	}

	Pet& operator=(const Pet& pet)
	{
		std::cout << "operator=(const Pet& pet)\n";

		return *this;
	}

	~Pet()
	{
		std::cout << "~Pet()\n";
	}
};

class Player
{
public:
	Player()
	{
		std::cout << "Player()\n";
	}

	Player(const Player& player) :m_level(player.m_level)
	{
		std::cout << "Player(const Player& player)\n";		
	}

	Player& operator=(const Player& player)
	{
		std::cout << "operator=(const Player& player)\n";
		m_level = player.m_level;

		return *this;
	}
public:
	int m_level = 0;
};

#define EXPLICIT_COPY_CONSTRUCTOR true
#define EXPLICIT_COPY_ASSIGNMENT_OPERATOR true

class Wizzard :public Player
{
public:
	Wizzard()
	{
		std::cout << "Wizzard()\n";

	}

#if EXPLICIT_COPY_CONSTRUCTOR
	Wizzard(const Wizzard& wizzard) :Player(wizzard), m_pet(wizzard.m_pet)
	{
		std::cout << "Wizzard(const Wizzard& wizzard)\n";
	}
#endif // EXPLICIT_COPY_CONSTRUCTOR

#if EXPLICIT_COPY_ASSIGNMENT_OPERATOR
	Wizzard& operator=(const Wizzard& wizzard)
	{
		std::cout << "operator=(const Wizzard& wizzard)\n";
		Player::operator=(wizzard);
		m_pet = wizzard.m_pet;

		return *this;
	}
#endif // EXPLICIT_COPY_ASSIGNMENT_OPERATOR

	~Wizzard()
	{
		std::cout << "~Wizzard()\n";
	}
public:
	int m_hp = 100;
	Pet m_pet;
};

class Knight
{
public:
	Knight()
	{
		m_pPet = new Pet();
	}

	Knight(const Knight& knight)
	{
		m_hp = knight.m_hp;
		m_pPet = new Pet(*knight.m_pPet); // deep copy
	}

	Knight& operator=(const Knight& knight)
	{
		m_hp = knight.m_hp;
		m_pPet = new Pet(*knight.m_pPet); // deep copy

		return *this;
	}

	~Knight()
	{
		delete m_pPet;
		m_pPet = nullptr;
	}

public:
	int m_hp = 100;
	Pet* m_pPet;
};

#define CONSTRUCTOR_STEPS

int main()
{
#ifdef DEEP_COPY
	Knight knight1;
	knight1.m_hp = 200;

	Knight knight2 = knight1;
	Knight knight3;
	knight3 = knight1;
#endif // DEEP_COPY

#ifdef CONSTRUCTOR_STEPS
	std::cout << "------------기본 생성자------------\n";
	Wizzard wizzard1;
	wizzard1.m_hp = 200;

#if EXPLICIT_COPY_CONSTRUCTOR
	std::cout << "------------명시적 복사 생성자------------\n";
#else
	std::cout << "------------암시적 복사 생성자------------\n";
#endif // EXPLICIT_COPY_CONSTRUCTOR
	Wizzard wizzard2 = wizzard1;

#if EXPLICIT_COPY_ASSIGNMENT_OPERATOR
	std::cout << "------------명시적 복사 대입 연산자------------\n";
#else
	std::cout << "------------암시적 복사 대입 연산자------------\n";
#endif // EXPLICIT_COPY_ASSIGNMENT_OPERATOR
	Wizzard wizzard3;
	wizzard3 = wizzard1;

	std::cout << "-------------------------------------\n";
#endif // CONSTRUCTOR_STEPS

	return 0;
}
#endif // COPY

#ifdef NAMED_CAST
class Player
{
public:
	// dynamic_cast를 위해선 가상 함수 필요
	virtual ~Player()
	{

	}
};

class Knight :public Player
{

};

class Archer :public Player
{

};

void PrintName(char* str)
{
	std::cout << str << std::endl;
}

int main()
{
	// static_cast
	int hp = 100;
	int maxHp = 200;
	float ratio = static_cast<float>(hp) / maxHp;

	Player* pPlayer1 = new Archer();
	Knight* pKnight1 = static_cast<Knight*>(pPlayer1); // 다운 캐스팅 가능
	
	Archer* pArcher1 = (Archer*)pKnight1;
	int* i = static_cast<int*>(malloc(sizeof(int) * 10));
	// Archer* pArcher = static_cast<Archer*>(pKnight);
	// 상속 관계가 없는 객체 포인터끼리 변환 불가능

	// dynamic_cast
	pKnight1 = dynamic_cast<Knight*>(pPlayer1);
	if (pKnight1 == nullptr)
		std::cout << "다운 캐스팅 실패\n";

	// const_cast
	PrintName(const_cast<char*>("NanSu"));

	// reinterpret_cast
	__int64 i64 = reinterpret_cast<__int64>(pArcher1);
	Knight* pKnight2 = reinterpret_cast<Knight*>(new Archer());

	return 0;
}
#endif // NAMED_CAST
