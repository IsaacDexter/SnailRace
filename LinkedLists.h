#ifndef _LINKED_LISTS_H
#define _LINKED_LISTS_H


#include "Structures.h"
#include <iostream>	//In Out STREAMing
#include <iomanip>	//In Out MANIPulators
class Primitive;

/// <summary>The LinkedLists class, containing a massive variety of methods used in the manipulation of linked lists.</summary>
class LinkedLists
{
private:
	ListNode* head = nullptr;
public:
	LinkedLists();
	~LinkedLists();

	ListNode* AppendNode(ListNode** head, Primitive* obj);
	ListNode* InsertFirst(ListNode** head, Primitive* obj);
	ListNode* InsertAfter(ListNode* lastNode, Primitive* obj);

	void Deletelist(ListNode** node);
	void DeleteAfter(ListNode* node);
	void DeleteAt(ListNode** node, int pos);

	ListNode* GetNode(ListNode* node, int pos);
	ListNode* Find(ListNode* node, Primitive* searchedObj);

	void UpdateList(ListNode* node);
	void RenderList(ListNode* node);
};


#endif // !_LINKED_LISTS_H