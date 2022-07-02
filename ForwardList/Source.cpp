#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;		//�������� ��������
	Element* pNext;	//����� ���������� ���������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList 
{
	Element* Head;	//������ ������
public:
	ForwardList()
	{
		Head = nullptr; //����� ������ ������ ��������� �� 0 - ������ ����
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
		
	}
	
	
	//				Adding Elements:
	void push_front(int Data)
	{
		//1) ������� ����� �������:
		Element* New = new Element(Data);
		//2) ������������ ����� ������� � ������ ������:
		New->pNext = Head;
		//3) �������, ��� ����� ������� �������� ������� ������:
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) ������� ����� �������:
		Element* New = new Element(Data);
		//2) ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext)	Temp = Temp->pNext;
		//3) ������������ ����� ������� � ����������:
		Temp->pNext = New;
	}

	//				Removing elements:
	void pop_front()
	{
		//1) ���������� ����� ���������� ��������;
		Element* erased = Head;
		//2) ��������� ������� �� ������:
		Head = Head->pNext;
		//3) ������� ������� �� ������
		delete erased;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	//				Methods:
	void print()const
	{
		Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� 
		//����� �������� ������ � ��������� ��������� ������.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������: "; cin >> n;
	int arr[5];
	ForwardList list;	//����������� ������ list
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		
	}
	
	list.print();
	//list.push_back(123);
	list.pop_front();
	list.pop_back();
	list.print();
}