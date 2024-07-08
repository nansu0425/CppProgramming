#include <iostream>

#define ALGORITHM

#ifdef VECTOR
#include <vector>

#define IMPLEMENT_VECTOR

#ifdef SIZE_CAP
#define RESERVE false
#define RESIZE false
#endif // SIZE_CAP

#ifdef IMPLEMENT_VECTOR
template<typename T>
class Iterator
{
public:
	Iterator() :m_ptr(nullptr)
	{

	}

	Iterator(T* ptr) :m_ptr(ptr)
	{

	}

	~Iterator()
	{

	}

	// 전위 증가
	Iterator& operator++()
	{
		m_ptr++;
		return *this;
	}

	// 후위 증가
	Iterator operator++(int)
	{
		Iterator tmp = *this;
		m_ptr++;
		return tmp;
	}

	// 전위 감소
	Iterator& operator--()
	{
		m_ptr--;
		return *this;
	}

	// 후위 감소
	Iterator operator--(int)
	{
		Iterator tmp = *this;
		m_ptr--;
		return tmp;
	}

	bool operator==(const Iterator& itr)
	{
		return m_ptr == itr.m_ptr;
	}

	bool operator!=(const Iterator& itr)
	{
		return m_ptr != itr.m_ptr;
	}

	Iterator operator+(int count)
	{
		Iterator tmp(m_ptr);
		tmp.m_ptr += count;
		return tmp;
	}

	Iterator operator-(int count)
	{
		Iterator tmp(m_ptr);
		tmp.m_ptr -= count;
		return tmp;
	}

	T& operator*()
	{
		return *m_ptr;
	}
public:
	T* m_ptr;
};

template<typename T>
class Vector
{
public:
	Vector() :m_arr(nullptr), m_size(0), m_capacity(0)
	{

	}

	~Vector()
	{
		if (m_arr != nullptr)
			delete[] m_arr;
	}

	void push_back(const T& e)
	{
		if (m_size == m_capacity)
		{
			size_t newCapacity = static_cast<size_t>(m_capacity * 1.5);
			if (newCapacity == m_capacity) 
				newCapacity++;
			reserve(newCapacity);
		}

		m_arr[m_size] = e;
		m_size++;
	}

	void reserve(size_t capacity)
	{
		if (m_capacity < capacity)
		{
			T* newArr = new T[capacity];

			if (newArr != nullptr)
			{
				if (m_arr != nullptr)
				{
					memcpy_s(newArr, capacity * sizeof(T),
						m_arr, m_size * sizeof(T));

					delete[] m_arr;
				}

				m_arr = newArr;
				m_capacity = capacity;
			}
		}
	}

	T& operator[](const size_t pos)
	{
		return m_arr[pos];
	}

	size_t size()
	{
		return m_size;
	}

	size_t capacity()
	{
		return m_capacity;
	}
public:
	typedef Iterator<T> iterator;

	iterator begin()
	{
		return iterator(&m_arr[0]);
	}

	iterator end()
	{
		return begin() + m_size;
	}
private:
	T* m_arr;
	size_t m_size;
	size_t m_capacity;
};
#endif // IMPLEMENT_VECTOR

int main()
{
#ifdef SIZE_CAP
	std::vector<int> v;

#if RESERVE
	v.reserve(500);
#endif // RESERVE

#if RESIZE
	v.resize(1000);
#endif // RESIZE

	for (size_t i = 0; i < 1000; i++)
	{
#if RESIZE
		v[i] = i;
		std::cout << v[i];
#else
		v.push_back(i);
		std::cout << v.size();
#endif // RESIZE
		std::cout << " " << v.capacity() << std::endl;
	}

	v.clear();
	std::cout << v.size() << " " << v.capacity() << std::endl;

	std::vector<int>().swap(v);
	std::cout << v.size() << " " << v.capacity() << std::endl;

	std::vector<int> v1(1000, 4);
	std::vector<int> v2 = v1;
#endif // SIZE_CAP

#ifdef ITERATOR
	std::vector<int> v(10);

	for (size_t i = 0; i < v.size(); i++)
		v[i] = i;

	std::vector<int>::iterator itr = v.begin();
	int* ptr = &v[0];

	std::cout << *itr << std::endl;
	std::cout << *ptr << std::endl;

	std::vector<int>::iterator begItr = v.begin();
	std::vector<int>::iterator endItr = v.end();
	int* begPtr = &v[0];
	int* endPtr = &v[0] + v.size();

	for (
		std::vector<int>::iterator itr = v.begin();
		itr != v.end(); ++itr
		)
	{
		std::cout << *itr << std::endl;
	}

	for (
		std::vector<int>::reverse_iterator itr = v.rbegin();
		itr != v.rend(); ++itr
		)
	{
		std::cout << *itr << std::endl;
	}

	std::vector<int>::const_iterator cbeg = v.cbegin();
	std::vector<int>::const_iterator cend = v.cend();
#endif // ITERATOR

#ifdef ACC_INS_DEL
	std::vector<int> v1;

	for (size_t i = 0; i < 10; i++)
		v1.push_back(i);

	std::vector<int>::iterator insItr = v1.insert(v1.begin() + 2, 5);
	std::vector<int>::iterator eraItr1 = v1.erase(v1.begin() + 2);
	std::vector<int>::iterator eraItr2 = v1.erase(v1.begin() + 2, v1.begin() + 4);
	
	std::vector<int> v2;

	for (size_t i = 0; i < 20; i++)
		v2.push_back(i);

	std::vector<int>::iterator itr = v2.begin();

	while (itr != v2.end())
	{
		auto tmp = itr;

		if (*itr % 3 == 0)
		{
			itr = v2.insert(tmp, *itr);
			itr += 2;
		}
		else
			itr = v2.erase(tmp);
	}
	
#endif // ACC_INS_DEL

#ifdef IMPLEMENT_VECTOR
	Vector<int> v;
	v.reserve(50);

	for (size_t i = 0; i < 100; i++)
	{
		v.push_back(i);
		std::cout << v.size() << " " << v.capacity() << std::endl;
	}

	for (size_t i = 0; i < v.size(); i++)
	{
		// v[i] = 1;
		std::cout << v[i] << std::endl;
	}

	for (Vector<int>::iterator itr = v.begin();
		itr != v.end(); ++itr)
	{
		std::cout << *itr << std::endl;
	}

#endif // IMPLEMENT_VECTOR
	return 0;
}
#endif // VECTOR

#ifdef LIST

#include <list>

#define IMPLEMENT_LIST

#ifdef IMPLEMENT_LIST
template<typename T>
class Node
{
public:
	Node() :m_next(nullptr), m_prev(nullptr), m_data(0)
	{

	}

	Node(const T& data) :m_next(nullptr), m_prev(nullptr), m_data(data)
	{

	}
public:
	Node<T>* m_next;
	Node<T>* m_prev;
	T m_data;
};

template<typename T>
class Iterator
{
public:
	Iterator() :m_ptrNode(nullptr)
	{

	}

	Iterator(Node<T>* ptrNode) :m_ptrNode(ptrNode)
	{

	}

	~Iterator()
	{

	}

	Iterator& operator++()
	{
		m_ptrNode = m_ptrNode->m_next;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator tmp = *this;
		m_ptrNode = m_ptrNode->m_next;
		return tmp;
	}

	Iterator& operator--()
	{
		m_ptrNode = m_ptrNode->m_prev;
		return *this;
	}

	Iterator operator--(int)
	{
		Iterator tmp = *this;
		m_ptrNode = m_ptrNode->m_prev;
		return tmp;
	}

	bool operator==(const Iterator& refItr)
	{
		return m_ptrNode == refItr.m_ptrNode;
	}

	bool operator!=(const Iterator& refItr)
	{
		return m_ptrNode != refItr.m_ptrNode;
	}

	T& operator*()
	{
		return m_ptrNode->m_data;
	}
public:
	Node<T>* m_ptrNode;
};

template<typename T>
class List
{
public:
	List() :m_header(new Node<T>()), m_size(0)
	{
		m_header->m_next = m_header;
		m_header->m_prev = m_header;
	}

	~List()
	{
		while (m_size > 0)
			pop_back();

		delete m_header;
	}

	void push_back(const T& val)
	{
		AddNode(m_header, val);
	}

	void pop_back()
	{
		RemoveNode(m_header->m_prev);
	}

	Node<T>* AddNode(Node<T>* targetNode, const T& val)
	{
		Node<T>* newNode = new Node<T>(val);
		
		newNode->m_prev = targetNode->m_prev;
		newNode->m_prev->m_next = newNode;

		newNode->m_next = targetNode;
		targetNode->m_prev = newNode;

		m_size++;

		return newNode;
	}

	Node<T>* RemoveNode(Node<T>* targetNode)
	{
		if (m_size > 0 && targetNode != nullptr)
		{
			targetNode->m_prev->m_next = targetNode->m_next;
			targetNode->m_next->m_prev = targetNode->m_prev;

			Node<T>* retNode = targetNode->m_next;
			
			delete targetNode;
			m_size--;

			return retNode;
		}

		return targetNode;
	}

	int size() { return m_size; }
public:
	typedef Iterator<T> iterator;

	iterator begin()
	{
		return iterator(m_header->m_next);
	}

	iterator end()
	{
		return iterator(m_header->m_prev);
	}

	iterator insert(iterator itr, const T& refVal)
	{
		Node<T>* retNode = AddNode(itr.m_ptrNode, refVal);

		return iterator(retNode);
	}

	iterator erase(iterator itr)
	{
		Node<T>* retNode = RemoveNode(itr.m_ptrNode);

		return iterator(retNode);
	}
private:
	Node<T>* m_header;
	int m_size;
};
#endif // IMPLEMENT_LIST


int main()
{
#ifdef ONE
	std::list<int> li;

	for (size_t i = 0; i < 50; i++)
	{
		li.push_front(i);
		li.push_back(i);
	}

	// capacity 개념 없다
	size_t sz = li.size();
	
	// 임의 접근 불가능
	int front = li.front();
	int back = li.back();

	std::list<int>::iterator begItr = li.begin();
	std::list<int>::iterator endItr = li.end();

	// std::list<int>::iterator firstItr = ++endItr; 불가능
	std::list<int>::iterator lastItr = --endItr;
	// std::list<int>::iterator dummyItr = --begItr; 불가능

	std::list<int>::iterator itr = li.begin();
	while (itr != li.end())
	{
		std::cout << *itr << std::endl;
		++itr;
	}

	li.insert(li.begin(), 100);
	li.pop_back();
	li.pop_front();
	li.remove(0);
#endif // ONE

#ifdef TWO
	std::list<int> li;
	std::list<int>::iterator rememberItr;

	for (size_t i = 0; i < 100; i++)
	{
		if (i == 50)
			rememberItr = li.insert(li.end(), i);
		else
			li.push_back(i);
	}

	// 리스트의 효율적인 중간 삭제
	li.erase(rememberItr);
#endif // TWO

#ifdef IMPLEMENT_LIST
	List<int> li;
	List<int>::iterator eraseItr;

	for (size_t i = 0; i < 10; i++)
	{
		if (i == 5)
			eraseItr = li.insert(li.end(), i);
		else
			li.push_back(i);
	}

	li.pop_back();
	li.erase(eraseItr);

	for (List<int>::iterator itr = li.begin();
		itr != li.end(); ++itr)
		std::cout << *itr << std::endl;
#endif // IMPLEMENT_LIST
	return 0;
}
#endif // LIST

#ifdef DEQUE

#include <deque>
#include <vector>

int main()
{
	std::deque<int> dq1;

	dq1.push_back(2);
	dq1.push_front(1);
	
	// size 개념만 존재
	std::cout << dq1.size() << std::endl;
	std::cout << dq1[0] << " " << dq1[1] << std::endl;

	// deque vs vector
	std::vector<int> v(3, 1);
	std::deque<int> dq2(3, 1);

	v.push_back(2);
	v.push_back(2);

	// 빠른 양끝 삽입/삭제
	dq2.push_back(2);
	dq2.push_back(2);
	dq2.push_front(3);
	dq2.push_front(3);

	// 빠른 임의 접근
	// 인덱스의 메모리 블록, 블록 내 오프셋으로 위치 계산
	dq2[4] = 10;

	return 0;
}
#endif // DEQUE

#ifdef MAP

#include <map>
#include <vector>

class Player
{
public:
	Player() :m_playerId(0)
	{

	}

	Player(int playerId) :m_playerId(playerId)
	{

	}
public:
	int m_playerId;
};

#define ASSOCIATIVE_CONTAINERS

int main()
{
#ifdef SEQUENCE_CONTAINERS
	std::vector<Player*> v;

	for (size_t i = 0; i < 100000; i++)
	{
		v.push_back(new Player(i));
	}

	srand((unsigned)time(nullptr));

	for (size_t i = 0; i < 50000; i++)
	{
		size_t randIdx = rand() % v.size();

		delete v[randIdx];
		v.erase(v.begin() + randIdx);
	}

	bool isFound = false;

	// playerId == 10000인 플레이어 검색
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i]->m_playerId == 10000)
		{
			isFound = true;
			break;
		}
	}
	// 시퀀스 컨테이너는 조건에 맞는 
	// 원소 검색이 매우 느리다
#endif // SEQUENCE_CONTAINERS 

#ifdef ASSOCIATIVE_CONTAINERS
	std::map<int, Player*> m1;
	
	// 삽입
	for (size_t i = 0; i < 100000; i++)
	{
		m1.insert(std::pair<int, Player*>(i, new Player(i)));
	}

	srand(static_cast<unsigned>(time(nullptr)));

	// 삭제
	for (size_t i = 0; i < 50000; i++)
	{
		int randKey = rand() % m1.size();

		if (m1.find(randKey) != m1.end())
		{
			delete m1[randKey];
			m1.erase(randKey);
		}
	}

	// 검색
	std::map<int, Player*>::iterator findItr = m1.find(10000);
	std::cout << (findItr != m1.end() ? "found\n" : "not found\n");

	std::map<int, int> m2;
	
	// 없으면 추가, 있으면 수정
	m2[3] = 5;
	m2[3] = 8;
	m2[1] = 4;

	size_t firstErase = m2.erase(3);
	size_t secondErase = m2.erase(3);

	std::pair<std::map<int, int>::iterator, bool> pairRet;
	pairRet = m2.insert(std::make_pair(1, 100));
	pairRet = m2.insert(std::make_pair(1, 200));

	// 순회
	for (std::map<int, Player*>::iterator itr = m1.begin();
		itr != m1.end(); ++itr)
	{
		std::pair<const int, Player*>& p = *itr;
		
		int key = itr->first;
		Player* value = itr->second;

		std::cout << key << " " << value << std::endl;
	}
#endif // ASSOCIATIVE_CONTAINERS
	
	return 0;
}
#endif // MAP

#ifdef SET
#include <set>

int main()
{
	std::set<int> s;

	// 삽입
	std::pair<std::set<int>::iterator, bool> pairRet;
	pairRet = s.insert(10);
	pairRet = s.insert(42);
	pairRet = s.insert(33);
	pairRet = s.insert(42);
	pairRet = s.insert(8);

	// 삭제
	size_t isErased = 0;
	isErased = s.erase(42);
	isErased = s.erase(10);
	isErased = s.erase(2);
	isErased = s.erase(10);

	// 검색
	std::set<int>::iterator findItr = s.find(8);
	bool isFound = (findItr != s.end());

	// 순회
	for (std::set<int>::iterator itr = s.begin();
		itr != s.end(); ++itr)
	{
		std::cout << *itr << std::endl;
	}

	return 0;
}
#endif // SET

#ifdef MULTI
#include <map>
#include <set>

#define MULTISET

int main()
{
#ifdef MULTIMAP
	std::multimap<int, int> mm;

	// 삽입
	mm.insert(std::make_pair(1, 100));
	mm.insert(std::make_pair(1, 200));
	mm.insert(std::make_pair(1, 300));
	mm.insert(std::make_pair(2, 400));
	mm.insert(std::make_pair(2, 500));

	// 삭제
	size_t isErased = mm.erase(1);

	// 검색
	std::multimap<int, int>::iterator itrFind = mm.find(2);

	// 하나의 원소 삭제
	if (itrFind != mm.end())
		mm.erase(itrFind);

	mm.insert(std::make_pair(1, 100));
	mm.insert(std::make_pair(1, 200));
	mm.insert(std::make_pair(1, 300));
	mm.insert(std::make_pair(2, 400));

	// 순회
	std::pair<
		std::multimap<int, int>::iterator,
		std::multimap<int, int>::iterator
	> pairRange = mm.equal_range(1);

	for (std::multimap<int, int>::iterator itr = pairRange.first;
		itr != pairRange.second; ++itr)
	{
		std::cout << itr->second << std::endl;
	}

	std::multimap<int, int>::iterator itrBeg = mm.lower_bound(1);
	std::multimap<int, int>::iterator itrEnd = mm.upper_bound(1);

	for (std::multimap<int, int>::iterator itr = itrBeg;
		itr != itrEnd; ++itr)
	{
		std::cout << itr->second << std::endl;
	}
#endif // MULTIMAP

#ifdef MULTISET
	std::multiset<int> ms;

	// 삽입
	ms.insert(100);
	ms.insert(100);
	ms.insert(100);
	ms.insert(200);
	ms.insert(200);

	// 삭제
	size_t isErased = ms.erase(200);

	ms.insert(200);
	ms.insert(200);

	// 검색
	std::multiset<int>::iterator itrFind = ms.find(100);
	
	if (itrFind != ms.end())
		ms.erase(itrFind);

	// 순회
	std::pair<
		std::multiset<int>::iterator,
		std::multiset<int>::iterator
	> pairRange = ms.equal_range(100);

	for (std::multiset<int>::iterator itr = pairRange.first;
		itr != pairRange.second; ++itr)
	{
		std::cout << *itr << std::endl;
	}

	std::multiset<int>::iterator itrBeg = ms.lower_bound(200);
	std::multiset<int>::iterator itrEnd = ms.upper_bound(200);

	for (std::multiset<int>::iterator itr = itrBeg;
		itr != itrEnd; ++itr)
	{
		std::cout << *itr << std::endl;
	}
#endif // MULTISET

	return 0;
}
#endif // MULTI

#ifdef ALGORITHM
#include <vector>
#include <algorithm>

int main()
{
	std::vector<int> v;

	srand(static_cast<unsigned>(time(nullptr)));

	for (size_t i = 0; i < 100; i++)
	{
		int numRand = rand() % 100;
		v.push_back(numRand);
	}

	// Q1) 특정 숫자가 벡터에 존재하는지 확인
	int number = 65;
	std::vector<int>::iterator itrNum = v.end();

	for (std::vector<int>::iterator itr = v.begin();
		itr != v.end(); ++itr)
	{
		if (*itr == number)
		{
			itrNum = itr;
			break;
		}
	}

	std::vector<int>::iterator itrFind = std::find(v.begin(), v.end(), number);
	bool isFound = (itrFind != v.end());

	// Q2) 11로 나누어 떨어지는 숫자가 벡터에 존재하는지 확인
	itrNum = v.end();

	for (std::vector<int>::iterator itr = v.begin();
		itr != v.end(); ++itr)
	{
		if (*itr % 11 == 0)
		{
			itrNum = itr;
			break;
		}
	}

	class IsDivideBy11
	{
	public:
		bool operator()(int n)
		{
			return n % 11 == 0;
		}
	};

	itrFind = std::find_if(v.begin(), v.end(), IsDivideBy11());
	isFound = (itrFind != v.end());
	
	// Q3) 홀수인 숫자의 갯수 확인
	int count = 0;

	for (std::vector<int>::iterator itr = v.begin();
		itr != v.end(); ++itr)
	{
		if (*itr % 2 == 1)
			count++;
	}

	class IsOdd
	{
	public:
		bool operator()(int n)
		{
			return n % 2 == 1;
		}
	};

	count = std::count_if(v.begin(), v.end(), IsOdd());

	// 모든 원소가 홀수인가?
	bool isAllOdd = std::all_of(v.begin(), v.end(), IsOdd());
	// 모든 원소가 홀수가 아닌가?
	bool isNoneOdd = std::none_of(v.begin(), v.end(), IsOdd());
	// 홀수인 원소가 있는가?
	bool isAnyOdd = std::any_of(v.begin(), v.end(), IsOdd());
	
	// Q4) 벡터의 모든 원소에 3을 곱한다
	for (std::vector<int>::iterator itr = v.begin();
		itr != v.end(); ++itr)
	{
		*itr *= 3;
	}

	class MultiplyBy3
	{
	public:
		void operator()(int& n)
		{
			n *= 3;
		}
	};

	std::for_each(v.begin(), v.end(), MultiplyBy3());

	// 홀수인 원소를 삭제
	v.clear();
	v.push_back(1);
	v.push_back(4);
	v.push_back(6);
	v.push_back(3);
	v.push_back(8);
	v.push_back(9);
	v.push_back(3);
	v.push_back(4);
	v.push_back(6);

	std::vector<int>::iterator itrBeg = 
		std::remove_if(v.begin(), v.end(), IsOdd());
	v.erase(itrBeg, v.end());

	return 0;
}
#endif // ALGORITHM
