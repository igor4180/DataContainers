﻿#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------------\n"

class ForwardList;
class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элементна
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

int Element::count = 0;

class ForwardList 
{
	Element* Head;	//Голова списка
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr; //Когда Голова списка указывает на 0 - список пуст
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int> il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
		
	}
	
	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	//				Adding Elements:
	void push_front(int Data)
	{
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Присоединяем новый элемент к началу списка:
		//New->pNext = Head;
		//3) Говорим, что новый элемент является головой списка:
		Head = new Element (Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)	Temp = Temp->pNext;
		//3) Присоединяем новый элемент к последнему:
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_front(Data);
		if (Index > size)
		{
			cout << "Error: Out of range" << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	

	//				Removing elements:
	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента;
		Element* erased = Head;
		//2) Исключаем элемент из списка:
		Head = Head->pNext;
		//3) Удаляем элемент из памяти
		delete erased;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//				Methods:
	void print()const
	{
		//Element* Temp = Head;	//Temp - это итератор.
		////Итератор - это указатель, при помощи которого 
		////можно получить доступ к элементам структуры данных.
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;	//Переход на следующий элемент
		//}
		for (Element* Temp = Head; Temp; Temp = Temp -> pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка:" << size << endl;
		cout << "Общее количество элементов списка:" << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	/*Element* Temp = right.Head;
	while (Temp)
	{
		cat.push_back(Temp->Data);
		Temp = Temp->pNext;
	}*/
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	cout << "Operator +" << endl;
	return cat;
}
//#define BASE_CHECK
//#define COUNT_CHECK
//#define RANGE_BASED_ARRAY
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	int arr[5];
	ForwardList list;	//Односвязный список list
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	
		list.print();
//list.push_back(123);
	list.pop_front();
	list.pop_back();
	list.print();
	int value;
	int index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	list.insert(value, index);
	list.print();

	//ForwardList list2 = list;	//CopyConstructor
	ForwardList list2;
	list2 = list;
	list2.print();
#endif BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
	ForwardList list3 = list1 + list2;
	list3.print();
#endif 
#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		cout << arr[i] << tab;
	cout << endl;
	for (int i : arr)
		cout << i << tab;
	cout << endl;
#endif
	
	ForwardList list = { 3,5,8,13,21 };
	list.print();

}