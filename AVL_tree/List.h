#ifndef LIST
#define LIST

#include "Date_struct.h"

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


void AddL(NodeList& list, int value)
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
	Node* tmp;
	if (list.head != NULL) {
		while (current != NULL && current->next != NULL)
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
			AddL(list, current1->info);

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
			AddL(list, current2->info);

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
			cout << "Заданное число находится под индексом - " << i;
			cout << endl;
		}
		current = current->next;
		i++;
	}
}

void ClearL(NodeList& list)
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
	else cout << "Cписок пуст";
}

void printList(NodeList& list, const string& file)
{
	ofstream fout("fileout.txt");
	if (fout.is_open())
	{
		Node* current = list.head;
		if (list.head == NULL) { cout << "Список пуст"; }
		else
			while (current != NULL)
			{
				fout << current->info << "->";;
				current = current->next;
			}
	}
	else cout << "Не удалось открыть файл";
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
	else cout << "Список пуст";
}

bool find(NodeList& list, int value)
{
	Node* current = list.head;
	if (current != nullptr) {
		do {
			if (current->info == value)
				return true;
			current = current->next;
		} while (current != nullptr || current->info != value);
	}
	return false;
}

#endif
