#include<iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int length = 5;

struct List {
	int val;
	List* next;
};

void Push_back(int val, List** q)
{
	if (*q == NULL)
	{
		*q = (List*)malloc(sizeof(List));
		(*q)->val = val;
		(*q)->next = NULL;
		return;
	}
	Push_back(val, &(*q)->next);
}

List* Push_forward(int val, List* head) {
	List* newItem;
	newItem = (List*)malloc(sizeof(List));
	newItem->val = val;
	newItem->next = NULL;
	if (NULL == head)
		newItem = head;
	else
		newItem->next = head;
	return newItem;
}

List* Push(int val, int pos, List* head) {
	if (pos < 0) {
		cout << "Индекс не может быть меньше 0!" << endl;
		return head;
	}
	else if (pos == 0) {
		head = Push_forward(val, head);
		return head;
	}
	List* tmp = head;
	List* pred = tmp;
	List* newItem = (List*)malloc(sizeof(List));
	newItem->val = val;
	newItem->next = NULL;
	for (int i = 0; i < pos; i++)
	{
		if (tmp == NULL) {
			cout << "Индекс больше возможного размера массива!\n";
			return head;
		}
		pred = tmp;
		tmp = tmp->next;
	}
	newItem->next = tmp;
	pred->next = newItem;
	return head;
}

void PrintList(List* head) {
	while (head != NULL) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << "\n";
}

int SameNumber(List* head) {
	int x;
	while (head != NULL) {
		List* tmp = head->next;
		x = head->val;
		while (tmp != NULL) {
			if (x == tmp->val) {
				return x;
			}
			tmp = tmp->next;
		}
		head = head->next;
	}
	return NULL;
}

int MinusSort(List** head) {
	List* prev = *head;
	List* tmp = *head;
	int pos = 0;
	int minus = 0;
	while (tmp != NULL) {
		if (tmp->val < 0 && pos != 0) {
			(*head) = Push_forward(tmp->val, (*head));
			prev->next = tmp->next;
			free(tmp);
			minus++;
			tmp = prev->next;
		}
		else {
			prev = tmp;
			tmp = tmp->next;
			pos++;
		}

	}
	return minus;
	//return (*head);
}

void main() {
	setlocale(LC_ALL, "RU");
	//---------------Тестовые данные---------------
	List* list = NULL;

	Push_back(-7, &list);
	Push_back(1, &list);
	Push_back(-5, &list);
	Push_back(1, &list);
	list = Push(13, 0, list);

	//---------------Первая задача---------------

	cout << "Одинаковые значения: " << SameNumber(list) << endl;

	//---------------Вторая задача---------------
	PrintList(list);
	cout << "Кол-во переносов отрицательных значений: " << MinusSort(&list) << endl;
	PrintList(list);
}