#include "LinkedLists.h"
#include "Primitive.h"

LinkedLists::LinkedLists()
{
}

LinkedLists::~LinkedLists()
{
}

/// <summary>Creates a new node using the data provided and places it at the first available free space in the list, becoming the head if necessary.</summary>
/// <param name="head">The first node of the list. If nullptr, the new node becomes the head.</param>
/// <param name="d">The data for the new node to contain.</param>
/// <returns>The new node created, pointing to nullptr.</returns>
ListNode* LinkedLists::AppendNode(ListNode** head, Primitive* obj)
{
	ListNode* newNode = new ListNode;
	ListNode* last = *head;
	newNode->sceneObject = obj;	//Set the new node equal to the data passed in.
	newNode->next = nullptr;	//Don't know what the next node will be so leave it nullptr for now.

	if (*head == nullptr)	//Check if head actually contains a node
	{
		*head = newNode;	//If head is nullptr, make new node the start of our list.
		return newNode;
	}

	while (last->next != nullptr)	//Find the next node that points to a nullptr
	{
		last = last->next;
	}

	last->next = newNode;	//Once a free spot has been found, place the new node here.
	return newNode;
}

/// <summary>Makes a new node, and makes it the new head. Makes the old head the second node in the linked list. If there is no head, make this the new head pointing to nothing.</summary>
/// <param name="head">The original list head.</param>
/// <param name="d">The data to store in the new node.</param>
/// <returns>The new list head.</returns>
ListNode* LinkedLists::InsertFirst(ListNode** head, Primitive* obj)
{
	ListNode* newNode = new ListNode;
	newNode->sceneObject = obj;	//Create a new node and populate it with the data passed in.

	newNode->next = *head;	//Make this new node point to the old head.
	*head = newNode;	//Make head point to this node.
	return newNode;
}

/// <summary>Places a node after the one passed in. If passed nullptr, outputs an error and returns null.</summary>
/// <param name="previousNode">The node to insert the new node after.</param>
/// <param name="d">The data for the new node to contain.</param>
/// <returns>The new node created, or nullptr if creation was unsuccessful.</returns>
ListNode* LinkedLists::InsertAfter(ListNode* previousNode, Primitive* obj)
{
	if (previousNode == nullptr)
	{
		std::cerr << "ERROR: Cannot insert after null!" << std::endl;
		return nullptr;
	}

	ListNode* newNode = new ListNode;
	newNode->sceneObject = obj;	//Create a new node and set its data to the data passed in.
	newNode->next = previousNode->next;	//Set this new node to point to the node the one before it pointed to
	previousNode->next = newNode;	//Make the previous node point to the new node.

	return newNode;
}

/// <summary>Deletes all items in the list after the head node specified, by going through each element in the list and deleteing it.</summary>
/// <param name="node">The head node to start deleteing from. It will also be deleted.</param>
void LinkedLists::Deletelist(ListNode** head)
{
	ListNode* pTemp = *head;	//Temporary pointer to hold the data to be deleted
	ListNode* next;	//Holds the address of the next peice of data to be deleted

	while (pTemp != nullptr)	//Go through each element of the list and delete it.
	{
		next = pTemp->next;
		delete pTemp;
		pTemp = next;
	}
	*head = nullptr;	//Set the node passed in to be nothing.
}

/// <summary>Deletes the node immediately after the one passed in. If the node passed in, or the node after, is nullptr, no deletion will occur.</summary>
/// <param name="node">The node preceding the one to be deleted.</param>
void LinkedLists::DeleteAfter(ListNode* node)
{
	ListNode* pTemp;
	if (node == nullptr || node->next == nullptr)	//Makes sure node passed in was valid
	{
		std::cerr << "ERROR: Cannot delete, as there is no node after this node!" << std::endl;
		return;
	}
	pTemp = node->next;
	node->next = pTemp->next;	//Set the previous node to point to the node that the node to be deleted was pointing to

	delete pTemp;	//Delete the node to free space.
}

void LinkedLists::DeleteAt(ListNode** head, int pos)
{
	ListNode* pTemp;
	ListNode* prevNode;
	if (pos == 0)	//If there is no previous node
	{
		pTemp = *head;
		*head = pTemp->next;
		delete pTemp;
		return;
	}
	prevNode = GetNode(*head, pos - 1);
	pTemp = GetNode(*head, pos);

	if (pTemp == nullptr || prevNode == nullptr)
	{
		std::cerr << "ERROR: Cannot delete, as node is out of range!" << std::endl;
		return;
	}

	prevNode->next = pTemp->next;
	delete pTemp;
	return;
}

/// <summary>Returns the node n nodes after the node passed in, by going through each node, starting at the node passed in. Outputs an error and returns nullptr if the position is out of range.</summary>
/// <param name="node">The node to start from. Use the head for most cases.</param>
/// <param name="pos">The position, n, from the node passed in.</param>
/// <returns>The found node.</returns>
ListNode* LinkedLists::GetNode(ListNode* node, int pos)
{
	int count = 0;

	while (node != nullptr)
	{
		if (count == pos)	//If we have reached the position specified...
		{
			return node;
		}
		count++;
		node = node->next;
	}
	std::cerr << "ERROR: " << pos << " was an invalid position." << std::endl;
	return nullptr;
}

/// <summary>Searches through the list one element at a time, starting at the node passed in. Upon encountering the first node with the data specified, return it. If not, return nullptr.</summary>
/// <param name="node">The node to start from. Use the head for most cases.</param>
/// <param name="val">The value to search for.</param>
/// <returns>The found node.</returns>
ListNode* LinkedLists::Find(ListNode* node, Primitive* searchedObject)
{
	while (node != nullptr)
	{
		if (node->sceneObject == searchedObject)
		{
			return node;
		}
		node = node->next;
	}
	std::cerr << "ERROR: No node with value " << &searchedObject << " was found." << std::endl;
	return nullptr;
}

/// <summary>Perfroms while loop, calling each node's data's render function.</summary>
/// <param name="node">The starting node.</param>
void LinkedLists::UpdateList(ListNode* node)
{
	while (node != nullptr)
	{
		node->sceneObject->Update();
		node = node->next;
	}

	if (node == nullptr)
	{
		return;
	}
}

/// <summary>Perfroms while loop, calling each node's data's draw function.</summary>
/// <param name="node">The starting node.</param>
void LinkedLists::RenderList(ListNode* node)
{
	while (node != nullptr)
	{
		node->sceneObject->Draw();
		node = node->next;
	}

	if (node == nullptr)
	{
		return;
	}
}

/// <summary>Performs a while loop through the list, incrementing a counter variable</summary>
/// <param name="node">The starting (head) node.</param>
/// <returns>the length of the list.</returns>
int LinkedLists::GetListLength(ListNode* node)
{
	int length = 0;
	while (node != nullptr)
	{
		node = node->next;
		length++;
	}
	
	if (node == nullptr)
	{
		return length;
	}
}
