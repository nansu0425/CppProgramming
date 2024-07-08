#include <iostream>

#define CALLBACK

#ifdef FUNCTION_POINTER
typedef int(FUNC)(int, int);
typedef int(*P_FUNC)(int, int);

class Item
{
public:
	Item() :m_itemId(0), m_rarity(0), m_ownerId(0)
	{

	}
public:
	int m_itemId;
	int m_rarity;
	int m_ownerId;
};

Item* FindItem(Item items[], int itemCount, 
	bool (*selector)(Item* p_item, int value), int value)
{
	for (int i = 0; i < itemCount; i++)
	{
		Item* p_i = &items[i];
		if (selector(p_i, value))
			return p_i;
	}

	return nullptr;
}

bool IsRareItem(Item* p_item, int rarity)
{
	return p_item->m_rarity >= rarity;
}

bool IsOwnerItem(Item* p_item, int ownerId)
{
	return p_item->m_ownerId == ownerId;
}

int Add(int a, int b)
{
	return a + b;
}

int main()
{
	// typedef을 활용한 function pointer
	// 전역 함수/정적 함수만 가능
	FUNC* addFunc = &Add;
	int res = addFunc(4, 5);
	P_FUNC p_addFunc = &Add;
	res = p_addFunc(6, 9);

	// 함수 동작의 일부를 함수 포인터로 전달
	Item items[10] = {};
	items[3].m_rarity = 2;
	items[6].m_ownerId = 100;
	Item* rareItem = FindItem(items, 10, IsRareItem, 2);
	Item* ownerItem = FindItem(items, 10, IsOwnerItem, 100);

	return 0;
}
#endif // FUNCTION_POINTER

#ifdef MEMBER_FUNCTION_POINTER
class Knight
{
public:
	static void PrintHelloKnight()
	{
		std::cout << "Knight::PrintHelloKnight()\n";
		std::cout << "Hello Knight!\n";
	}

	int GetHp(int a, int b)
	{
		std::cout << "Knight::GetHp()\n";
		return m_hp;
	}
public:
	int m_hp = 100;
};

typedef void (*P_FUNC)();
typedef int (Knight::*P_MEMFUNC)(int, int);

int main()
{
	P_FUNC p_func = &Knight::PrintHelloKnight;
	p_func();

	P_MEMFUNC p_memFunc = &Knight::GetHp;
	
	Knight k1;
	(k1.*p_memFunc)(4, 5);

	Knight* p_k1 = new Knight();
	(p_k1->*p_memFunc)(8, 3);
	delete p_k1;

	return 0;
}
#endif // MEMBER_FUNCTION_POINTER

#ifdef FUNCTOR
class Functor
{
public:
	void operator()()
	{
		std::cout << "Functor::operator()()\n";
		std::cout << m_value << std::endl;
	}

	bool operator()(int num)
	{
		std::cout << "Functor::operator()(int num)\n";
		m_value += num;
		std::cout << m_value << std::endl;

		return true;
	}
private:
	int m_value = 0;
};

class MoveTask
{
public:
	void operator()()
	{
		std::cout << "해당 좌표로 플레이어 이동\n";
	}
public:
	int m_playerId;
	int m_posX;
	int m_posY;
};

int main()
{
	Functor functor;
	
	// 다양한 함수 시그니처에 대응 가능 
	functor();
	if (functor(4))
		std::cout << "Succeeded in adding num\n";

	// 호출 상태 저장 후 원하는 시점에 호출
	MoveTask task;
	task.m_playerId = 100;
	task.m_posX = 19;
	task.m_posY = 4;

	task();

	return 0;
}
#endif // FUNCTOR

#ifdef FUNCTION_TEMPLATE
class Knight
{
public:
	int m_hp = 100;
};

std::ostream& operator<<(std::ostream& os, const Knight& k)
{
	os << k.m_hp;

	return os;
}

template<typename T>
void Print(T a)
{
	std::cout << a << std::endl;
}

// 템플릿 특수화
template<>
void Print(Knight k)
{
	std::cout << "Print<Knight>(Knight k)" << std::endl;
	std::cout << k << std::endl;
}

void Print(Knight k)
{
	std::cout << "Print(Knight k)" << std::endl;
	std::cout << k << std::endl;
}

template<typename T1, typename T2>
void Print(T1 a, T2 b)
{
	std::cout << a << " " << b << std::endl;
}

template<typename T>
T Add(T a, T b)
{
	return a + b;
}

int main()
{
	Print<int>(50.0f);
	Print(50.0);
	Print("Hello World");
	Print(12, "Hi");

	int resInt = Add(3, 5);
	double resDouble = Add(4.2, 2.9);

	Knight k1;
	Print(k1);
	Print<Knight>(k1);

	return 0;
}
#endif // FUNCTION_TEMPLATE

#ifdef CLASS_TEMPLATE
template<typename T, int SIZE>
class RandomBox
{
public:
	T GetRandomData()
	{
		int idx = rand() % SIZE;
		return m_data[idx];
	}
public:
	T m_data[SIZE];
};

template<int SIZE>
class RandomBox<double, SIZE>
{
public:
	double GetRandomData()
	{
		std::cout << "RandomBox double\n";
		int idx = rand() % SIZE;
		return m_data[idx];
	}
public:
	double m_data[SIZE];
};

template<typename T>
class RandomBox<T, 10>
{
public:
	T GetRandomData()
	{
		std::cout << "RandomBox 10 size\n";
		int idx = rand() % 10;
		return m_data[idx];
	}
public:
	T m_data[10];
};

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));

	RandomBox<int, 10> rb1;
	for (int i = 0; i < 10; i++)
	{
		rb1.m_data[i] = i;
	}
	int random1 = rb1.GetRandomData();
	std::cout << "rb1 random: " << random1 << std::endl;

	RandomBox<double, 20> rb2;
	for (int i = 0; i < 20; i++)
	{
		rb2.m_data[i] = i + 0.5;
	}
	double random2 = rb2.GetRandomData();
	std::cout << "rb2 random: " << random2 << std::endl;

	return 0;
}
#endif // CLASS_TEMPLATE

#ifdef CALLBACK
class Item
{
public:

public:
	int m_itemId = 0;
	int m_rarity = 0;
	int m_ownerId = 0;
};

class FindByOwnerId
{
public:
	bool operator()(const Item* p_item)
	{
		return p_item->m_ownerId == m_ownerId;
	}

public:
	int m_ownerId;
};

class FindByRarity
{
public:
	bool operator()(const Item* p_item)
	{
		return p_item->m_rarity >= m_rarity;
	}

public:
	int m_rarity;
};

template<typename T>
Item* FindItem(Item items[], int itemCount, T selector)
{
	for (int i = 0; i < itemCount; i++)
	{
		Item* p_item = &items[i];

		if (selector(p_item))
			return p_item;
	}

	return nullptr;
}

int main()
{
	Item items[10] = {};
	items[3].m_ownerId = 100;
	items[6].m_rarity = 4;

	FindByOwnerId functor1;
	functor1.m_ownerId = 100;
	FindByRarity functor2;
	functor2.m_rarity = 2;

	Item* item1 = FindItem(items, 10, functor1);
	Item* item2 = FindItem(items, 10, functor2);

	return 0;
}
#endif // CALLBACK
