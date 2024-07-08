#include <iostream>

#define SMART_POINTER

#ifdef AUTO
class Knight
{

};

int main()
{
	// ������ Ÿ�ӿ� Ÿ�� �߷�(type deduction)
	auto a = 4;
	auto b = 3.5f;
	auto c = 1.454;
	auto d = Knight();
	auto e = "Hello World";

	// ���۷����� ��� Ÿ���� auto
	int& ref = a;
	const int cst = a;

	auto autoRef1 = ref; // ���۷��� Ÿ������ �߷����� �ʴ´�
	auto& autoRef2 = a; // ���۷��� Ÿ�� ���
	
	auto autoCst1 = cst; // ��� Ÿ������ �߷����� �ʴ´�
	const auto autoCst2 = a; // ��� Ÿ�� ���

	return 0;
}
#endif // AUTO

#ifdef INITIALIZER_LIST
#include <vector>
#include <list>
#include <map>
#include <initializer_list>

class Knight
{
public:
	Knight()
	{
		std::cout << "Knight::Knight()\n";
	}

	Knight(const Knight& knight)
	{
		std::cout << "Knight::Knight(const Knight&)\n";
		*this = knight;
	}

	Knight(int a, int b)
	{
		std::cout << "Knight::Knight(int, int)\n";
	}

	Knight(std::initializer_list<int> li)
	{
		std::cout << "Knight::Knight(initializer_list<int>)\n";
	}
};

int main()
{
	int a{ 4 };
	int b{};

	Knight k1{};	// �⺻ ������
	Knight k2{ k1 };// ���� ������
	Knight k3;
	k3 = k2;		// ���� ���� ������

	// �迭�� �����̳� �ʱ�ȭ
	int arr[]{ 1, 2, 3, 4, 5 };
	std::vector<int> v1{ 1, 2, 3, 4, 5 };
	std::list<int> li{ 1, 2, 3, 4, 5 };
	std::map<int, Knight&> m{ {1, k1}, {2, k2}, {3, k3} };

	// �ڵ� ��� ��ȯ ����
	double db{ static_cast<double>(a) };

	// listinitializer_list ������ ȣ��
	Knight k5{ 1, 2, 3, 4 };
	Knight k6{ 5, 6 };
	std::vector<int> v2{ 10 ,1 };

	return 0;
}
#endif // INITIALIZER_LIST

#ifdef NULLPTR
class Knight
{
public:
	void Test()
	{
		std::cout << "Knight::Test()\n";
	}
};

void Test(int val)
{
	std::cout << "Test(int)\n";
}

void Test(void* ptr)
{
	std::cout << "Test(void*)\n";
}

Knight* CreateKnight()
{
	return new Knight();
}

const class
{
public:
	// T Ÿ�� ������ ����ȯ �� 0 ��ȯ
	template<typename T>
	operator T* () const
	{
		return 0;
	}

	// T Ÿ�� C Ŭ���� ��� ������ ����ȯ �� 0 ��ȯ
	template<typename C, typename T>
	operator T C::* () const
	{
		return 0;
	}
private:
	void operator&() const {}
} nullPtr;

int main()
{
	// NULL�� int Ÿ��, nullptr�� ������ Ÿ��
	auto valNull = NULL;
	auto ptrNull = nullptr;

	Test(0);
	Test(NULL);
	Test(nullptr);

	auto k1 = CreateKnight();
	
	// k1�� ������ Ÿ���� ���� �� �� �ִ�
	if (k1 != nullptr)
	{
		std::cout << "Knight was created\n";
		delete k1;
		k1 = nullptr;
	}

	// nullptr�� ������ nullPtr
	Test(nullPtr);

	void (*ptrFunc)(int) = &Test;
	if (ptrFunc != nullPtr)
	{
		(*ptrFunc)(10);
	}
	
	auto k2 = CreateKnight();
	if (k2 != nullPtr)
	{
		std::cout << "Knight was created\n";
		delete k2;
		k2 = nullPtr;
	}

	void (Knight::*ptrMemFunc)();
	ptrMemFunc = &Knight::Test;

	if (ptrMemFunc != nullPtr)
	{
		Knight k3;
		(k3.*ptrMemFunc)();
	}

	return 0;
}
#endif // NULLPTR

#ifdef USING
#include <vector>

typedef __int64 ID1;
using ID2 = __int64;

typedef void (*PtrFunc1)();
using PtrFunc2 = void (*)();

template<typename T>
using Vec = std::vector<T>;
// typedef std::vector<T> Vec; ���ø� Ȱ�� �Ұ�

void Func()
{

}

int main()
{
	ID1 id1 = 100;
	ID2 id2 = 200;

	PtrFunc1 ptrFunc1 = &Func;
	PtrFunc2 ptrFunc2 = &Func;

	Vec<int> v;
	v.push_back(1);
	v.push_back(2);

	return 0;
}
#endif // USING

#ifdef ENUM_CLASS
// ���� ������
enum PlayerType :char
{
	PT_Knight,
	PT_Archer,
	PT_Mage,
};

// Ŭ������ �̸� ����
enum class ObjectType
{
	Player,
	Monster,
	Projectile,
};

int main()
{
	PlayerType pt;
	int size = sizeof(pt);

	double db1 = PT_Archer; // �Ϲ��� ��ȯ ����
	double db2 = static_cast<double>(ObjectType::Monster); // ����� ��ȯ �ʼ�

	return 0;
}
#endif // ENUM_CLASS

#ifdef DELETE
class Knight
{
public:
	// �Լ��� ������� ���ϵ��� ��������� ����
	Knight operator+(const Knight& knight) = delete;
private:
	void operator=(const Knight& knight);
	friend class Admin; // Admin Ŭ������ Knight ��� ���� ���
private:
	int m_hp = 100;
};

class Admin
{
public:
	void CopyKnight(const Knight& knight)
	{
		m_knight = knight;
	}
private:
	Knight m_knight;
};

int main()
{
	Knight k1;
	Knight k2;
	// k1 = k2; ���� ���� �����ڸ� ���Ҵ�
	
	Admin adm1;
	// adm1.CopyKnight(k1); ��ũ ����, ������ Ÿ�ӿ� ������ ���� �� ����

	// Knight k3 = k1 + k2; // + ������ ���Ҵ�

	return 0;
}
#endif // DELETE

#ifdef OVERRIDE_FINAL
class Creature
{
public:
	virtual void Attack()
	{
		std::cout << "Creature::Attack()\n";
	}

	virtual void Move()
	{
		std::cout << "Creature::Move()\n";
	}
};

class Player :public Creature
{
public:
	virtual void Attack() override
	{
		std::cout << "Player::Attack()\n";
	}

	virtual void Defence()
	{
		std::cout << "Player::Defence()\n";
	}

	// Creature::Move()�� ���� �ٸ� �Լ� ��� 
	// -> override Ű���� ��� �Ұ�
	virtual void Move() const
	{
		std::cout << "Player::Move()\n";
	}
};

class Knight :public Player
{
public:
	virtual void Attack() override
	{
		std::cout << "Knight::Attack()\n";
	}

	// �� �̻� Defence�� �������̵��� �� ����
	virtual void Defence() final
	{
		std::cout << "Knight::Defence()\n";
	}
};

int main()
{
	Knight* k1 = new Knight();
	k1->Attack();
	Player* p1 = new Knight();
	p1->Attack();

	Creature* c1 = new Knight();
	// c1->Defence();	// ȣ�� �Ұ�: � Ŭ�������� ó�� ���ǵƴ��� �˾ƾ� �Ѵ�
	p1->Defence();
	p1->Move();
	c1->Move();

	return 0;
}
#endif // OVERRIDE_FINAL

#ifdef RVALUE_REFERENCE
class Pet
{
public:
};

class Knight
{
public:
	Knight()
	{
		std::cout << "Knight()\n";
	}

	Knight(const Knight& knight) 
		:m_hp(knight.m_hp), m_pet(knight.m_pet)
	{
		std::cout << "Knight(const Knight&)\n";
	}

	~Knight()
	{
		if (m_pet != nullptr)
			delete m_pet;
	}

	// ���� ���� ������
	Knight& operator=(const Knight& knight)
	{
		std::cout << "Knight::operator=(const Knight&)\n";

		// ���� ����
		m_hp = knight.m_hp;
		if (knight.m_pet != nullptr)
		{
			if (m_pet != nullptr)
				delete m_pet;
			m_pet = new Pet(*knight.m_pet);
		}

		return *this;
	}

	// �̵� ���� ������
	Knight& operator=(Knight&& knight) noexcept
	{
		std::cout << "Knight::operator=(Knight&&)\n";

		// ������ �̵�
		m_hp = knight.m_hp;
		m_pet = knight.m_pet;
		knight.m_pet = nullptr;

		return *this;
	}

	void Test()
	{

	}

	void TestCst() const
	{

	}
public:
	int m_hp = 100;
	Pet* m_pet = nullptr;
};

void TestRvalue(Knight knight) {}
void TestLvalueRef(Knight& knight) {}

void TestCstRef(const Knight& knight) 
{
	// knight.Test();	// �Ұ���; const ��ü�� const �Լ��� ȣ�� ����
	knight.TestCst();
}

// rvalue�� ���޵Ʊ� ������ ������ �ӽ������� ���ȴٴ� ���� �Ͻ�
void TestRvalueRef(Knight&& knight) {}

int main()
{
	// ��� ǥ���� �� ���� lvalue �ƴϸ� rvalue
	// lvalue : �򰡿� ������� ����
	// rvalue : �� ���������� �ӽ������� ����
	// rvalue�� �䱸�� �� lvalue�� ����� �� ������ ���� �Ұ���
	// (����: rvalue reference)

	Knight knight;
	
	TestRvalue(knight);		// lvalue ����
	TestRvalue(Knight());	// ravlue ����

	TestLvalueRef(knight);
	// TestLvalueRef(Knight());	// �Ұ���; non-const ���۷����� lvalue�� �޴´�
	TestCstRef(Knight());		// const ���۷����� rvalue ����

	// TestRvalueRef(knight);	// �Ұ���; rvalue ���۷����� rvalue�� �޴´�
	TestRvalueRef(Knight());
	TestRvalueRef(static_cast<Knight&&>(knight));

	Knight src;
	src.m_hp = 1000;
	src.m_pet = new Pet();

	Knight dst1;
	dst1 = static_cast<Knight&&>(src);	// �̵� ���� -> ������ �ʿ���ٴ� ���� �Ͻ�
	
	Knight dst2;
	dst2 = std::move(dst1);				// dst1�� rvalue referece�� ĳ���� -> �̵� ���� ȣ��

	std::unique_ptr<Knight> uptr1 = std::make_unique<Knight>();
	std::unique_ptr<Knight> uptr2 = std::move(uptr1);

	return 0;
}
#endif // RVALUE_REFERENCE

#ifdef FORWARDING_REFERENCE
#include <utility>

class Knight
{
public:
	Knight()
	{
		std::cout << "Knight()\n";
	}

	Knight(const Knight& knight)
	{
		std::cout << "Knight(const Knight&)\n";
	}

	Knight(Knight&& knight) noexcept
	{
		std::cout << "Knight(Knight&&)\n";
	}
};

void TestRvalueRef(Knight&& knight)
{

}

void TestCopy(Knight knight)
{

}

template<typename T>
void TestForwardingRef(T&& rvalRef)
{
	// rvalRef�� �����̹Ƿ� ǥ���� �� �� lvalue ��ȯ
	// -> ���� ������ ȣ��
	// TestCopy(rvalRef);
	// -> �̵� ������ ȣ��
	// TestCopy(std::move(rvalRef));

	// rvalue�� lvalue�� �Ǵ��ؼ� ����
	TestCopy(std::forward<T>(rvalRef));
}

int main()
{
	Knight k1;
	TestRvalueRef(std::move(k1));	// k1�� rvalue reference�� ����

	// T&& or auto&& ������ �� lvalue �Ǵ� rvalue reference�� �߷�
	// -> forwarding reference
	Knight k2;
	TestForwardingRef(k2);				// lvalue reference
	TestForwardingRef(std::move(k2));	// rvalue reference
	Knight k3;
	auto&& k4 = k3;				// lvalue reference
	auto&& k5 = std::move(k3);	// rvalue reference

	Knight k6;
	Knight& k7 = k6;
	Knight&& k8 = std::move(k6);

	// k8�� ǥ�������� ����Ͽ� ���� �� �����̹Ƿ� lvalue�� return
	// -> rvalue reference ��ȯ �ʿ�
	TestRvalueRef(std::move(k8));

	Knight k9;
	TestForwardingRef(std::move(k9));

	return 0;
}
#endif // FORWARDING_REFERENCE

#ifdef LAMBDA
#include <vector>

enum class ItemType
{
	None,
	Armor,
	Weapon,
	Jewelry,
	Consumable,
};

enum class Rarity
{
	Common,
	Rare,
	Unique,
};

class Item
{
public:
	Item() 
	{

	}

	Item(int itemId, Rarity rarity, ItemType itemType)
		:m_itemId(itemId), m_rarity(rarity), m_itemType(itemType)
	{

	}
public:
	int m_itemId = 0;
	Rarity m_rarity = Rarity::Common;
	ItemType m_itemType = ItemType::None;
};

int main()
{
	std::vector<Item> v;
	v.push_back(Item(1, Rarity::Common, ItemType::Weapon));
	v.push_back(Item(2, Rarity::Common, ItemType::Armor));
	v.push_back(Item(3, Rarity::Rare, ItemType::Jewelry));
	v.push_back(Item(4, Rarity::Unique, ItemType::Weapon));

	class IsUniqueItem
	{
	public:
		bool operator()(const Item& item)
		{
			return item.m_rarity == Rarity::Unique;
		}
	};

	// ���� ǥ������ ��Ÿ�� ��ü�� Ŭ������� �ϰ� lvalue ���·� �����ȴ�
	// Ŭ������ ������ ������ �� ���簡 �Ͼ��
	// ǥ������ ������ ���� Ŭ������ �ı��ȴ�
	auto lambdaIsUniqueItem
		= [](const Item& item)->bool {return item.m_rarity == Rarity::Unique; };
	
	bool isUniqueItem = lambdaIsUniqueItem(v[3]);
	auto itrFind = std::find_if(v.begin(), v.end(), lambdaIsUniqueItem);

	if (itrFind != v.end())
		std::cout << "Found Item ID: " << itrFind->m_itemId << std::endl;

	class FindItemByItemId
	{
	public:
		FindItemByItemId(int itemId) :m_itemId(itemId)
		{

		}

		bool operator()(const Item& item)
		{
			return item.m_itemId == m_itemId;
		}
	public:
		int m_itemId;
	};
	
	int itemId = 3;
	
	// []: �ܺ� ������ ���ٽ� ���ο��� ����� �� ���� ��� ����, ĸó ���
	// �⺻ ĸó ���: [=] -> ��� value ����, [&] -> ��� reference ����
	auto findItemByItemIdLambda =
		[=](const Item& item) { return item.m_itemId == itemId; };

	itemId = 2;	// [&] ����̸� ������ �ٲ��

	auto itrFindId =
		std::find_if(v.begin(), v.end(), findItemByItemIdLambda);
	if (itrFindId != v.end())
		std::cout << "Found Item ID: " << itrFindId->m_itemId << std::endl;

	class FindItem
	{
	public:
		FindItem(int itemId, Rarity rarity, ItemType itemType) 
			:m_itemId(itemId), m_rarity(rarity), m_itemType(itemType)
		{

		}

		bool operator()(const Item& item)
		{
			return item.m_itemId == m_itemId &&
				item.m_rarity == m_rarity &&
				item.m_itemType == m_itemType;
		}
	public:
		int m_itemId;
		Rarity m_rarity;
		ItemType m_itemType;
	};

	itemId = 4;
	Rarity rarity = Rarity::Unique;
	ItemType itemType = ItemType::Weapon;

	auto itrFindItem =
		std::find_if(v.begin(), v.end(), 
			[&itemId, rarity, itemType](const Item& item) // itemId�� reference ����
			{
				return item.m_itemId == itemId &&
					item.m_rarity == rarity &&
					item.m_itemType == itemType;
			});
	if (itrFindItem != v.end())
		std::cout << "Found Item ID: " << itrFindItem->m_itemId << std::endl;

	class Knight
	{
	public:
		auto ResetHpJob()
		{
			auto resetLambda =
				[this]()
				{
					m_hp = 200; // this->m_hp = 200 �ǹ�
				};

			return resetLambda;
		}
	public:
		int m_hp = 100;
	};

	Knight* k1 = new Knight();
	auto resetJob = k1->ResetHpJob();

	delete k1;	// ��ü ����
	resetJob(); // this�� ��ȿ���� ���� ��ü�� ����Ű�� ������
				// -> memory corruption

	return 0;
}
#endif // LAMBDA

#ifdef SMART_POINTER

#define UNIQUE_PTR

class Knight
{
public:
	Knight()
	{
		std::cout << "Knight()\n";
	}

	~Knight()
	{
		std::cout << "~Knight()\n";
	}

	void Attack()
	{
#ifdef WEAK_PTR
		// weak ptr�� ��ü ����� ��� �����Ƿ�
		// ��ü�� �����ϴ��� Ȯ���ؾ� �Ѵ�
		if (m_target.expired() == false)
		{
			std::shared_ptr<Knight> shrPtr = m_target.lock();
			
			shrPtr->m_hp -= m_damage;
			std::cout << "target HP: "
				<< shrPtr->m_hp << std::endl;
		}
#else
		if (m_target != nullptr)
		{
			m_target->m_hp -= m_damage;
			std::cout << "target HP: "
				<< m_target->m_hp << std::endl;
		}
#endif // WEAK_PTR
	}
public:
	int m_hp = 100;
	int m_damage = 10;
#ifdef POINTER
	Knight* m_target = nullptr;
#endif // POINTER
#ifdef SHARED_PTR
	std::shared_ptr<Knight> m_target = nullptr;
#endif // SHARED_PTR
#ifdef WEAK_PTR
	std::weak_ptr<Knight> m_target;
#endif // WEAK_PTR
#ifdef UNIQUE_PTR
	std::unique_ptr<Knight> m_target;
#endif // UNIQUE_PTR


};

#define CUSTOM_SHARED_PTR false

class RefCountBlock
{
public:
	int m_refCount = 1;
#ifdef WEAK_PTR
	int m_weakCount = 1;
#endif // WEAK_PTR

};

template<typename T>
class SharedPtr
{
public:
	SharedPtr()
	{

	}

	SharedPtr(T* ptr) :m_ptr(ptr)
	{
		if (m_ptr != nullptr)
		{
			m_refBlock = new RefCountBlock();
			std::cout << "refCount: " 
					  << m_refBlock->m_refCount << std::endl;
		}
	}
	
	SharedPtr(const SharedPtr& shrPtr)
		:m_ptr(shrPtr.m_ptr), m_refBlock(shrPtr.m_refBlock)
	{
		if (m_ptr != nullptr)
		{
			m_refBlock->m_refCount++;
			std::cout << "refCount: "
				<< m_refBlock->m_refCount << std::endl;
		}
	}

	SharedPtr& operator=(const SharedPtr& shrPtr)
	{
		m_ptr = shrPtr.m_ptr;
		m_refBlock = shrPtr.m_refBlock;

		if (m_ptr != nullptr)
		{
			m_refBlock->m_refCount++;
			std::cout << "refCount: "
				<< m_refBlock->m_refCount << std::endl;
		}

		return *this;
	}

	~SharedPtr()
	{
		if (m_ptr != nullptr)
		{
			m_refBlock->m_refCount--;
			std::cout << "refCount: "
				<< m_refBlock->m_refCount << std::endl;

			if (m_refBlock->m_refCount == 0)
			{
				delete m_ptr;
#ifndef WEAK_PTR
				delete m_refBlock;
#endif // !WEAK_PTR
				std::cout << "Delete ptr\n";
			}
		}
	}
public:
	T* m_ptr = nullptr;
	RefCountBlock* m_refBlock = nullptr;
};

int main()
{
#ifdef POINTER
	Knight* k1 = new Knight();
	Knight* k2 = new Knight();

	k1->m_target = k2;

	// ��� ������ �޸𸮸� ����
	delete k2;
	// memory corruption
	k1->Attack();

	delete k1;
#endif // POINTER

#if CUSTOM_SHARED_PTR
	SharedPtr<Knight> ptrK1;
	{
		SharedPtr<Knight> ptrK2(new Knight());
		ptrK1 = ptrK2;
	}
#endif // CUSTOM_SHARED_PTR

	std::shared_ptr<Knight> shrPtrK1 = 
		std::make_shared<Knight>();

#ifdef SHARED_PTR
	{	
		// shrPtrK2�� ��ü�� m_target�� ����Ű�� �����Ƿ�
		// �������� ����� �Ҹ���� �ʴ´�
		std::shared_ptr<Knight> shrPtrK2 =
			std::make_shared<Knight>();
		shrPtrK1->m_target = shrPtrK2;
	}

	shrPtrK1->Attack();

	{
		// ��ȯ ������ K1�� K2�� �Ҹ���� �ʴ´�
		std::shared_ptr<Knight> shrPtrK2 =
			std::make_shared<Knight>();
		shrPtrK1->m_target = shrPtrK2;
		shrPtrK2->m_target = shrPtrK1;

		// ��ȯ�� �����ִ� ��ü�� �־�� �Ѵ�
		shrPtrK2->m_target = nullptr;
	}
#endif // SHARED_PTR

#ifdef WEAK_PTR
	{
		// weak ptr�� ������ ��ü ���� ������ ���� �ʴ´�
		std::shared_ptr<Knight> shrPtrK2 =
			std::make_shared<Knight>();
		shrPtrK2->m_target = shrPtrK1;
		shrPtrK1->m_target = shrPtrK2;
	}

	// shrPtrK2�� ����Ű�� ��ü�� �Ҹ�����Ƿ�
	// m_target�� ���� �۾��� �̷�� ���� �ʴ´�
	shrPtrK1->Attack();
#endif // WEAK_PTR

#ifdef UNIQUE_PTR
	std::unique_ptr<Knight> uniPtrK = std::make_unique<Knight>();

	// shrPtrK1->m_target = uniPtrK;	// �ּ� ���� �Ұ���
	shrPtrK1->m_target = std::move(uniPtrK);	// �̵� ���길 ����
#endif // UNIQUE_PTR

	return 0;
}
#endif // SMART_POINTER
