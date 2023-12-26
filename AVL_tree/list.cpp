#include <iostream>

using namespace std;

struct Node
{
	Node* next = NULL;
	Node* prev = NULL;
	int info;
};

struct NodeList
{
	Node* head = NULL;
	Node* tail = NULL;
};

void Add(NodeList& list, int value)
{
	bool flag = false;
	Node* tmp = new Node;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->info = value;

	if (list.head == NULL)
	{
		list.head = tmp;
		list.tail = tmp;
	}
	else if (value >= list.head->info)
	{
		tmp->next = list.head;
		list.head->prev = tmp;
		list.head = tmp;

	}
	else
	{
		Node* current = list.head;
		while (current->next != NULL && flag == false)
		{
			if ((current->info >= value) && (value >= current->next->info))
			{
				tmp->prev = current;
				tmp->next = current->next;
				current->next->prev = tmp;
				current->next = tmp;
				
				flag = true;
			}
			current = current->next;
		}
		if (current->next == NULL)
		{
			tmp->prev = current;
			current->next = tmp;
			list.tail = tmp;
			flag = true;
		}
	}
}

void deleteAfter(NodeList& list, int value)
{
	Node* current = list.head;
	Node* tmp = new Node;
	if (list.head != NULL) {
		while (current->next != NULL)
		{
			if (current->info == value && current->next->next != NULL)
			{
				tmp = current->next;
				current->next->next->prev = current;
				current->next = current->next->next;
				free(tmp);
			}
			else if (current->info == value && current->next->next == NULL)
			{
				tmp = current->next;
				current->next = current->next->next;
				list.tail = current;
				free(tmp);
			}
			current = current->next;
		}
	}

}

void SymDif(NodeList& list, NodeList& list1, NodeList& list2)
{
	Node* current1 = list1.head;
	Node* current2 = list2.head;
	Node* current = list.head;
	Node* tmp = new Node;

	while (current1 != NULL)
	{
		
		while (current2->next != NULL && (current1->info != current2->info)) 
		{
			current2 = current2->next;
		}
		if (current1->info != current2->info) 
			Add(list, current1->info);
			
		current2 = list2.head;
		current1 = current1->next;
	}

	current1 = list1.head;
	current2 = list2.head;

	while (current2 != NULL)
	{

		while (current1->next != NULL && (current1->info != current2->info))
		{
			current1 = current1->next;
		}
		if (current1->info != current2->info)
			Add(list, current2->info);

		current1 = list1.head;
		current2 = current2->next;
	}
}

void SearchSel(NodeList& list, int value)
{
	Node* current = list.head;
	int i = 1;
	while (current->next != NULL)
	{
		
		if (current->info == value)
		{
			cout << "�������� ����� ��������� ��� �������� - " << i;
			cout << endl;
		}
		current = current->next;
		i++;
	}
}

void Clear(NodeList& list)
{
	Node* current = list.head->next;
	Node* tmp;

	if (list.head != NULL)
	{
		while (current != NULL)
		{
			tmp = current;
			current = current->next;
			free(tmp);
		}
		free(list.head);
		list.head = NULL;
	}
	else cout << "C����� ����";
}

void printList(NodeList& list)
{
	Node* current = list.head;
	if (list.head == NULL) { cout << "������ ����"; }
	else
		while (current != NULL)
		{
		cout << current->info << "->";
		current = current->next;
		}
}

void printListFromEnd(NodeList& list)
{
	Node* current = list.tail;
	if (list.head != NULL)
	{
		while (current != NULL)
		{
			cout << current->info << "->";
			current = current->prev;
		}
	}
	else cout << "������ ����";
}

int main()
{
	setlocale(LC_ALL, "Russian");

	NodeList list1;
	NodeList list2;
	NodeList list;

	Add(list1, 1);
	Add(list1, 1);
	Add(list1, 1);
	Add(list1, 1);
	Add(list1, 1);
	Add(list1, 1);
	Add(list1, 0);
	Add(list1, 9);
	Add(list1, 9);
	Add(list1, 5);
	Add(list1, 6);

	cout << "������ ������ : ";
	printList(list1);
	cout << endl;
	cout << "������ ������ � ����� : ";
	printListFromEnd(list1);
	cout << endl;
	deleteAfter(list1, 9);
	cout<< "������ ������ ����� �������� : ";
	printList(list1);
	cout << endl;
	cout << "������ ������ ����� �������� � ����� : ";
	printListFromEnd(list1);
	cout << endl;

	Add(list2, 9);
	Add(list2, 2);
	Add(list2, 8);
	Add(list2, 5);
	Add(list2, 4);
	Add(list2, 1);
	Add(list2, 1);
	Add(list2, 5);
	Add(list2, 9);

	cout << "������ ������ : ";
	printList(list2);
	cout << endl;
	cout << "������ ������ � ����� : ";
	printListFromEnd(list2);
	cout << endl;
	deleteAfter(list2, 5);
	cout<< "������ ������ ����� �������� : ";
	printList(list2);
	cout << endl;
	cout << "������ ������ ����� �������� c ����� : ";
	printListFromEnd(list2);
	cout << endl;

	SymDif(list, list1, list2);
	cout << "�������������� �������� ���� ������� : ";
	printList(list);
	cout << endl;
	cout << "�������������� �������� ���� ������� c ����� : ";
	printListFromEnd(list);
	cout << endl;

	SearchSel(list1, 1);
	cout << endl;
	cout << "������ ����� ������� : ";
	Clear(list1);
	cout << "1 ������ : ";
	printList(list1);
	cout << endl;
	cout << "1 ������ c ����� : ";
	printListFromEnd(list1);
	cout << endl;

	Clear(list2);
	cout << "2 ������ : ";
	printList(list2);
	cout << endl;
	cout << "2 ������ c ����� : ";
	printListFromEnd(list2);
	cout << endl;

	Clear(list);
	cout << "3 ������ : ";
	printList(list);
	cout << endl;
	cout << "3 ������ c ����� : ";
	printListFromEnd(list);
	cout << endl;

	return 0;
}