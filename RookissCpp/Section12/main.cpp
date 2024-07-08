#include <iostream>

#define SMART_POINTER

#ifdef AUTO
class Knight
{

};

int main()
{
	// 컴파일 타임에 타입 추론(type deduction)
	auto a = 4;
	auto b = 3.5f;
	auto c = 1.454;
	auto d = Knight();
	auto e = "Hello World";

	// 레퍼런스와 상수 타입의 auto
	int& ref = a;
	const int cst = a;

	auto autoRef1 = ref; // 레퍼런스 타입으로 추론하지 않는다
	auto& autoRef2 = a; // 레퍼런스 타입 명시
	
	auto autoCst1 = cst; // 상수 타입으로 추론하지 않는다
	const auto autoCst2 = a; // 상수 타입 명시

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

	Knight k1{};	// 기본 생성자
	Knight k2{ k1 };// 복사 생성자
	Knight k3;
	k3 = k2;		// 복사 대입 연산자

	// 배열과 컨테이너 초기화
	int arr[]{ 1, 2, 3, 4, 5 };
	std::vector<int> v1{ 1, 2, 3, 4, 5 };
	std::list<int> li{ 1, 2, 3, 4, 5 };
	std::map<int, Knight&> m{ {1, k1}, {2, k2}, {3, k3} };

	// 자동 축소 변환 방지
	double db{ static_cast<double>(a) };

	// listinitializer_list 생성자 호출
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
	// T 타입 포인터 형변환 시 0 반환
	template<typename T>
	operator T* () const
	{
		return 0;
	}

	// T 타입 C 클래스 멤버 포인터 형변환 시 0 반환
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
	// NULL은 int 타입, nullptr은 포인터 타입
	auto valNull = NULL;
	auto ptrNull = nullptr;

	Test(0);
	Test(NULL);
	Test(nullptr);

	auto k1 = CreateKnight();
	
	// k1이 포인터 타입인 것을 알 수 있다
	if (k1 != nullptr)
	{
		std::cout << "Knight was created\n";
		delete k1;
		k1 = nullptr;
	}

	// nullptr을 구현한 nullPtr
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
// typedef std::vector<T> Vec; 템플릿 활용 불가

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
// 전역 스코프
enum PlayerType :char
{
	PT_Knight,
	PT_Archer,
	PT_Mage,
};

// 클래스의 이름 공간
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

	double db1 = PT_Archer; // 암묵적 변환 가능
	double db2 = static_cast<double>(ObjectType::Monster); // 명시적 변환 필수

	return 0;
}
#endif // ENUM_CLASS

#ifdef DELETE
class Knight
{
public:
	// 함수를 사용하지 못하도록 명시적으로 삭제
	Knight operator+(const Knight& knight) = delete;
private:
	void operator=(const Knight& knight);
	friend class Admin; // Admin 클래스는 Knight 멤버 접근 허용
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
	// k1 = k2; 복사 대입 연산자를 막았다
	
	Admin adm1;
	// adm1.CopyKnight(k1); 링크 에러, 컴파일 타임엔 오류를 잡을 수 없다

	// Knight k3 = k1 + k2; // + 연산을 막았다

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

	// Creature::Move()와 완전 다른 함수 취급 
	// -> override 키워드 사용 불가
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

	// 더 이상 Defence를 오버라이드할 수 없다
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
	// c1->Defence();	// 호출 불가: 어떤 클래스에서 처음 정의됐는지 알아야 한다
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

	// 복사 대입 연산자
	Knight& operator=(const Knight& knight)
	{
		std::cout << "Knight::operator=(const Knight&)\n";

		// 깊은 복사
		m_hp = knight.m_hp;
		if (knight.m_pet != nullptr)
		{
			if (m_pet != nullptr)
				delete m_pet;
			m_pet = new Pet(*knight.m_pet);
		}

		return *this;
	}

	// 이동 대입 연산자
	Knight& operator=(Knight&& knight) noexcept
	{
		std::cout << "Knight::operator=(Knight&&)\n";

		// 데이터 이동
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
	// knight.Test();	// 불가능; const 객체는 const 함수만 호출 가능
	knight.TestCst();
}

// rvalue로 전달됐기 때문에 원본은 임시적으로 사용된다는 것을 암시
void TestRvalueRef(Knight&& knight) {}

int main()
{
	// 모든 표현식 평가 값은 lvalue 아니면 rvalue
	// lvalue : 평가와 상관없이 존재
	// rvalue : 평가 과정에서만 임시적으로 존재
	// rvalue가 요구될 때 lvalue를 사용할 수 있지만 역은 불가능
	// (예외: rvalue reference)

	Knight knight;
	
	TestRvalue(knight);		// lvalue 전달
	TestRvalue(Knight());	// ravlue 전달

	TestLvalueRef(knight);
	// TestLvalueRef(Knight());	// 불가능; non-const 레퍼런스는 lvalue만 받는다
	TestCstRef(Knight());		// const 레퍼런스는 rvalue 가능

	// TestRvalueRef(knight);	// 불가능; rvalue 레퍼런스는 rvalue만 받는다
	TestRvalueRef(Knight());
	TestRvalueRef(static_cast<Knight&&>(knight));

	Knight src;
	src.m_hp = 1000;
	src.m_pet = new Pet();

	Knight dst1;
	dst1 = static_cast<Knight&&>(src);	// 이동 대입 -> 원본은 필요없다는 것을 암시
	
	Knight dst2;
	dst2 = std::move(dst1);				// dst1를 rvalue referece로 캐스팅 -> 이동 대입 호출

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
	// rvalRef는 변수이므로 표현식 평가 후 lvalue 반환
	// -> 복사 생성자 호출
	// TestCopy(rvalRef);
	// -> 이동 생성자 호출
	// TestCopy(std::move(rvalRef));

	// rvalue와 lvalue를 판단해서 전달
	TestCopy(std::forward<T>(rvalRef));
}

int main()
{
	Knight k1;
	TestRvalueRef(std::move(k1));	// k1를 rvalue reference로 전달

	// T&& or auto&& 형태일 때 lvalue 또는 rvalue reference로 추론
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

	// k8을 표현식으로 취급하여 평가할 때 변수이므로 lvalue를 return
	// -> rvalue reference 변환 필요
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

	// 람다 표현식의 런타임 객체를 클로저라고 하고 lvalue 형태로 생성된다
	// 클로저를 변수에 저장할 때 복사가 일어나고
	// 표현식이 끝나면 원본 클로저는 파괴된다
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
	
	// []: 외부 변수를 람다식 내부에서 사용할 때 전달 방법 설정, 캡처 모드
	// 기본 캡처 모드: [=] -> 모두 value 전달, [&] -> 모두 reference 전달
	auto findItemByItemIdLambda =
		[=](const Item& item) { return item.m_itemId == itemId; };

	itemId = 2;	// [&] 모드이면 조건이 바뀐다

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
			[&itemId, rarity, itemType](const Item& item) // itemId만 reference 전달
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
					m_hp = 200; // this->m_hp = 200 의미
				};

			return resetLambda;
		}
	public:
		int m_hp = 100;
	};

	Knight* k1 = new Knight();
	auto resetJob = k1->ResetHpJob();

	delete k1;	// 객체 삭제
	resetJob(); // this는 유효하지 않은 객체를 가리키는 포인터
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
		// weak ptr은 객체 수명과 상관 없으므로
		// 객체가 존재하는지 확인해야 한다
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

	// 사용 예정인 메모리를 해제
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
		// shrPtrK2의 객체는 m_target이 가리키고 있으므로
		// 스코프를 벗어나도 소멸되지 않는다
		std::shared_ptr<Knight> shrPtrK2 =
			std::make_shared<Knight>();
		shrPtrK1->m_target = shrPtrK2;
	}

	shrPtrK1->Attack();

	{
		// 순환 참조로 K1과 K2는 소멸되지 않는다
		std::shared_ptr<Knight> shrPtrK2 =
			std::make_shared<Knight>();
		shrPtrK1->m_target = shrPtrK2;
		shrPtrK2->m_target = shrPtrK1;

		// 순환을 끊어주는 객체가 있어야 한다
		shrPtrK2->m_target = nullptr;
	}
#endif // SHARED_PTR

#ifdef WEAK_PTR
	{
		// weak ptr의 참조는 객체 수명에 영향을 주지 않는다
		std::shared_ptr<Knight> shrPtrK2 =
			std::make_shared<Knight>();
		shrPtrK2->m_target = shrPtrK1;
		shrPtrK1->m_target = shrPtrK2;
	}

	// shrPtrK2가 가리키던 객체는 소멸됐으므로
	// m_target에 대한 작업이 이루어 지지 않는다
	shrPtrK1->Attack();
#endif // WEAK_PTR

#ifdef UNIQUE_PTR
	std::unique_ptr<Knight> uniPtrK = std::make_unique<Knight>();

	// shrPtrK1->m_target = uniPtrK;	// 주소 복사 불가능
	shrPtrK1->m_target = std::move(uniPtrK);	// 이동 연산만 가능
#endif // UNIQUE_PTR

	return 0;
}
#endif // SMART_POINTER
