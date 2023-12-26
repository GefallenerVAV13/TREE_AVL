
#include "List.h"

struct node
{
	Date key;
	node* left = nullptr;
	node* right = nullptr;
	NodeList nextlist;
	int bal = 0;
};

node* q;

bool DateMore(node* p, Date date)
{
	if (p != nullptr)
	{
		if (date.year > p->key.year
			|| date.year == p->key.year && date.month > p->key.month
			|| date.year == p->key.year && date.month == p->key.month && date.day > p->key.day)
			return true;
		else return false;
	}
	else return false;
}

bool DateLess(node* p, Date date)
{
	if (p != nullptr)
	{
		if (date.year < p->key.year
			|| date.year == p->key.year && date.month < p->key.month
			|| date.year == p->key.year && date.month == p->key.month && date.day < p->key.day)
			return true;
		else return false;
	}
	else return false;
}

bool DateEqual(node* p, Date date)
{
	if (p != nullptr)
	{
		if (date.year == p->key.year && date.month == p->key.month && date.day == p->key.day)
			return true;
		else return false;
	}
	else return false;
}

void BalanceL(node*& p, bool& h)
{
	node* p1;
	node* p2;

	if (p->bal == -1)
		p->bal = 0;
	else if (p->bal == 0)
	{
		p->bal = 1;
		h = false;
	}
	else
	{
		p1 = p->right;
		if (p1->bal >= 0)
		{
			p->right = p1->left;
			p1->left = p;
			if (p1->bal == 0)
			{
				p->bal = 1;
				p1->bal = -1;
				h = false;
			}
			else
			{
				p->bal = 0;
				p1->bal = 0;
			}
			p = p1;
		}
		else {
			p2 = p1->left;
			p1->left = p2->right;
			p2->right = p1;
			p->right = p2->left;
			p2->left = p;
			if (p2->bal == 1)
				p->bal = -1;
			else p->bal = 0;
			if (p2->bal == -1)
				p1->bal = 1;
			else p1->bal = 0;
			p = p2;
			p2->bal = 0;
		}
	}
}

void BalanceR(node*& p, bool& h)
{
	node* p1;
	node* p2;

	if (p->bal == 1) p->bal = 0;
	else if (p->bal == 0)
	{
		p->bal = -1;
		h = false;
	}
	else {
		p1 = p->left;
		if (p1->bal <= 0)
		{
			p->left = p1->right;
			p1->right = p;
			if (p1->bal == 0)
			{
				p->bal = -1;
				p1->bal = 1;
				h = false;
			}
			else
			{
				p->bal = 0;
				p1->bal = 0;
			}
			p = p1;
		}
		else {
			p2 = p1->right;
			p1->right = p2->left;
			p2->left = p1;
			p->left = p2->right;
			p2->right = p;
			if (p2->bal == -1)
				p->bal = 1;
			else p->bal = 0;
			if (p2->bal == 1)
				p1->bal = -1;
			else p1->bal = 0;
			p = p2;
			p2->bal = 0;
		}
	}
}

void add(node*& p, Date date, int stroka, bool& h)
{
	node* p1;
	node* p2;
	node* tmp = new node();
	tmp->key.day = date.day;
	tmp->key.month = date.month;
	tmp->key.year = date.year;
	tmp->left = nullptr;
	tmp->right = nullptr;
	AddL(tmp->nextlist, stroka);
	tmp->bal = 0;

	if (p == nullptr)
	{	
		p = tmp;
		h = true;
	}
	else if (DateLess(p, date))
	{
		add(p->left, date, stroka, h);
		if (h)
		{
			if (p->bal == 1)
			{
				p->bal = 0;
				h = false;
			}
			else if (p->bal == 0)
				p->bal = 1;
			else
			{
				p1 = p->left;
				if (p1->bal == -1)
				{
					p->left = p1->right;
					p1->right = p;
					p->bal = 0;
					p = p1;
				}
				else
				{
					p2 = p1->right;
					p1->right = p2->left;
					p2->left = p1;
					p->left = p2->right;
					p2->right = p;
					if (p2->bal == -1) p->bal = 1;
					else p->bal = 0;
					if (p2->bal == 1) p1->bal = -1;
					else p1->bal = 0;
					p = p2;
				}
				p->bal = 0;
				h = false;
			}
		}
	}
	else if (DateMore(p, date))
	{
		add(p->right, date, stroka, h);
		if (h) {
			if (p->bal == -1) {
				p->bal = 0;
				h = false;
			}
			else if (p->bal == 0)
				p->bal = 1;
			else {
				p1 = p->right;
				if (p1->bal == 1) {
					p->right = p1->left;
					p1->left = p;
					p->bal = 0;
					p = p1;
				}
				else {
					p2 = p1->left;
					p1->left = p2->right;
					p2->right = p1;
					p->right = p2->left;
					p2->left = p;
					if (p2->bal == 1) p->bal = -1;
					else p->bal = 0;
					if (p2->bal == -1) p1->bal = 1;
					else  p1->bal = 0;
					p = p2;
				}
				p->bal = 0;
				h = false;
			}
		}
	}
	else if (DateEqual(p, date))
	{
		AddL(p->nextlist, stroka);
	}
}

void del(node*& r, bool& h)
{

	if (r->left != nullptr) {
		del(r->left, h);
		if (h) BalanceL(r, h);
	}
	else {
		q->key = r->key;
		q->nextlist = r->nextlist;
		q = r;
		r = r->right;
		h = true;
	}
}

void Delete(node*& p, Date date, int stroka, bool& h) //удаление при полном совпадении ключа и номера строки
{
	node* q;

	if (p == nullptr)
	{
		cout << "Ключа нет в дереве";
	}
	else if (DateEqual(p, date) && find(p->nextlist, stroka) == true && p->nextlist.head->next != nullptr)
	{
		deleteAfter(p->nextlist, stroka);

	}
	else if (DateLess(p, date))
	{
		Delete(p->left, date, stroka, h);
		if (h)
			BalanceL(p, h);
	}
	else if (DateMore(p, date))
	{
		Delete(p->right, date, stroka, h);
		if (h)
			BalanceR(p, h);
	}
	else if (DateEqual(p, date) && find(p->nextlist, stroka) == false)
	{
		cout << "Ключа с такой строкой не существует";
	}
	else 
	{
		q = p;
		if (q->right == nullptr)
		{
			p = q->left;
			h = true; 
		}
		else if (q->left == nullptr)
		{
			p = q->right;
			h = true; 
		}
		else {
			del(q->right, h);
			if (h)
				BalanceR(p, h);
		}
	}
}

void print(node* p, int level, const string& file) //номера строк 
{
	ofstream fout("fileout.txt");
	if (fout.is_open())
	{


		if (p)
		{
			print(p->left, level + 1, file);
			for (int i = 0; i < level; i++) fout << "  ";
			fout << p->key.day << " " << p->key.month << " " << p->key.year << "\t";
			printList(p->nextlist, file); fout << endl;
			print(p->right, level + 1, file);
		}
	}
	else
		cout << "Не удалось открыть файл";
}

void Clear(node* p)
{

	if (!p)
		return;
	Clear(p->left);
	Clear(p->right);
	ClearL(p->nextlist);
	delete p;
}

void InOrder(node* p, const string& file)
{
	ofstream fout("fileout.txt");
	if (fout.is_open())
	{
		Node* current;
		if (!p)
			return;
		else
		{
			InOrder(p->left, file);
			if (p->nextlist.head != nullptr)
			{
				current = p->nextlist.head;
				while (current != nullptr)
				{
					fout << p->key.day << "." << p->key.month << "." << p->key.year;
					fout << endl;
					current = current->next;
				}
			}
			InOrder(p->right, file);
		}
	}
	else cout << "Не удалось открыть файл";
}


int main()
{
	node* root = nullptr;
	bool hchange = false;

	int stroka = 1;

	setlocale(LC_ALL, "RUS");
	string str, str1;
	int day, month, year;
	string dd, mm, yy;
	ifstream fin;

	fin.open("filein.txt");

	if (!fin.is_open())
	{
		cout << "Файл не найден" << endl;
	}
	else
	{
		cout << "Файл открыт" << endl;
		while (!fin.eof())
		{
			getline(fin, str);
			for (int i = 0; i < 2; i++)
				dd = dd + str[i];
			day = stoi(dd, nullptr, 10);
			for (int j = 3; j < 5; j++)
				mm = mm + str[j];
			month = stoi(mm, nullptr, 10);
			for (int k = 6; k < 11; k++)
				yy = yy + str[k];
			year = stoi(yy, nullptr, 10);
			//cout << str << "\t" << day << "\t" << month << "\t" << year << endl;
			dd = mm = yy = "";
			if (CorrectDate(day, month, year))
			{
			Date date1;
			setDate(date1, day, month, year);
			cout << date1.day << "\t" << date1.month << "\t" << date1.year << "\t" << stroka << "\t" << DayInMonth(date1.month, date1.year) << endl;

			add(root, date1, stroka ,hchange);
			stroka++;
			}

		}
		cout << endl;
	}

		print(root, 1, "fileoutTree.txt");

		InOrder(root, "fileout.txt");

		Date date2;
		setDate(date2, 10, 02, 2001);
		Delete(root, date2, 5, hchange);

		print(root, 1, "fileoutTree.txt");

		Clear(root);
}



