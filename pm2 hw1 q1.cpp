/* pm2 hw.cpp : This file contains the 'main' function. Program execution begins and ends there.
 db1039, Denys Bengizu
 question 3 hw 1... sorry I have it all in one file, We did not really use multiple files when we coded
 in either pm1 or pm2 so this is how I learned it... believe me I was getting tired of scrolling through all this
 just to get it to work haha, this problem alone took me 3 days totalling 19 hrs :(
 Date Started: 09/ 22/ 2018
 Date Submitted: 09/23/2018
*/
#include "pch.h"
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;


class No_index_Exception : public std::runtime_error {
public:
	// constructor specifies default error message
	No_index_Exception()
		:std::runtime_error{ "Value does not exist " } {}
};

template<typename Type> class List;

template<typename Type>
class ListNode {
	friend class List<Type>; // make List a friend

private:
	Type data; // data type
	int index;
	ListNode<Type>* nextPtr; // Move onto next listed number
public:
	explicit ListNode(const Type& info)
		: data{ info }, nextPtr{ nullptr } {}

	Type getData() const { return data; } // data is being returned in the node
};

class Exception_Empty : public std::runtime_error {
public:
	// constructor specifies default error message
	Exception_Empty()
		:std::runtime_error{ "Attempt for popping or dequeing from an empty list " } {}
};

template<typename TYPEDEC>
class List {
public:
	// destructor
	~List() {
		if (!isEmpty()) { // List is not empty
			std::cout << "Nodes deleting \n";

			ListNode<TYPEDEC>* currentPtr{ firstPtr };
			ListNode<TYPEDEC>* tPtr{ nullptr };

			while (currentPtr != nullptr) { // delete remaining nodes
				tPtr = currentPtr;
				std::cout << tPtr->data << '\n';
				currentPtr = currentPtr->nextPtr;
				delete tPtr;
			}
		}

		std::cout << "All nodes destroyed\n\n";
	}

	// insert node at front of list
	void Push(const TYPEDEC& value) {
		ListNode<TYPEDEC>* newPtr{ getNewNode(value) }; // new node

		if (isEmpty()) { // List is empty
			firstPtr = lastPtr = newPtr; // new list has only one node
			newPtr->index = 0;
		}
		else { // List is not empty
			newPtr->nextPtr = firstPtr; // point new node to old 1st node
			firstPtr = newPtr; // aim firstPtr at new node
			newPtr->index = 0;
			ListNode<TYPEDEC>* tempPtr = newPtr->nextPtr;
			while (tempPtr != nullptr) {
				tempPtr->index = tempPtr->index + 1;
				tempPtr = tempPtr->nextPtr;
			}
		}
	}

	// insert node at back of list
	void Enqueue(const TYPEDEC& value) {
		ListNode<TYPEDEC>* newPtr{ getNewNode(value) }; // new node

		if (isEmpty()) { // List is empty
			firstPtr = lastPtr = newPtr; // new list has only one node
			newPtr->index = 0;
		}
		else { // List is not empty
			int tempIndex = lastPtr->index;
			lastPtr->nextPtr = newPtr; // update previous last node
			lastPtr = newPtr; // new last node
			newPtr->index = tempIndex + 1;
		}
	}

	// delete node from front of list
	const Type& Pop() {
		TYPEDEC value;
		ListNode<TYPEDEC>* tempPtr{ firstPtr }; // grabs info for future deletion 

		if (firstPtr == lastPtr) {
			firstPtr = lastPtr = nullptr; // All nodes removed
		}
		else {
			firstPtr = firstPtr->nextPtr; // point to previous 2nd node
			ListNode<TYPEDEC>* tPtr2 = firstPtr;
			while (tPtr2 != nullptr) {
				tPtr2->index = tPtr2->index - 1;
				tPtr2 = tPtr2->nextPtr;
			}
		}

		value = tPtr->data; // return data being removed
		delete tempPtr; // reclaim previous front node
		return value; // delete successful
	}

	// delete node from back of list

	const TYPEDEC& Dequeue() {
		TYPEDEC value;
		ListNode<TYPEDEC>* tempPtr{ lastPtr }; // hold item to delete

		if (firstPtr == lastPtr) { // List has one element
			firstPtr = lastPtr = nullptr; // no nodes remain after removal
		}
		else {
			ListNode<TYPEDEC>* currentPtr{ firstPtr };

			// locate second-to-last element
			while (currentPtr->nextPtr != lastPtr) {
				currentPtr = currentPtr->nextPtr; // move to next node
			}

			lastPtr = currentPtr; // remove last node
			currentPtr->nextPtr = nullptr; // this is now the last node
		}

		value = tempPtr->data; // return value from old last node
		delete tempPtr; // reclaim former last node
		return value; // delete successful
	}

	// is List empty?

	bool isEmpty() const {
		return firstPtr == nullptr;
	}
	// all of this in the next set of braces will be a bunch of pointers that will help me in my later code for traverse
	const TYPEDEC& Traverse(int index) {
		TYPEDEC value;
		ListNode<TYPEDEC>* TemporaryPointer{ firstPtr };
		ListNode<TYPEDEC>* currentPtr{ TemporaryPointer };

		while (TemporaryPointer != nullptr && TemporaryPointer->index != index) {
			currentPtr = TemporaryPointer;
			TemporaryPointer = TemporaryPointer->nextPtr;
		}

		if (TemporaryPointer == nullptr) {// case when there is no matching index
			throw No_index_Exception{};
		}

		if (TemporaryPointer == firstPtr) {// case when retrieving an item from the front
			return Pop();
		}
		if (TemporaryPointer == lastPtr) {// case when retrieving an item from the back
			return Dequeue();
		}

		value = TemporaryPointer->data;
		currentPtr->nextPtr = TemporaryPointer->nextPtr;
		delete TemporaryPointer;

		TemporaryPointer = currentPtr->nextPtr;

		while (TemporaryPointer != nullptr) {
			TemporaryPointer->index = TemporaryPointer->index - 1;
			TemporaryPointer = TemporaryPointer->nextPtr;
		}

		return value;
	}

	// display contents of List
	void print() const {
		if (isEmpty()) { // List is empty
			std::cout << "Empty list here. \n";
			return;
		}

		ListNode<TYPEDEC>* currentPtr{ firstPtr };

		std::cout << "Here is the list: ";

		while (currentPtr != nullptr) { // each elements data is fetched
			std::cout << currentPtr->data << ' '; // pointers to data 
			currentPtr = currentPtr->nextPtr;
		}

		std::cout << "\n\n";
	}

private:
	ListNode<TYPEDEC>* firstPtr{ nullptr }; // pointer to first node
	ListNode<TYPEDEC>* lastPtr{ nullptr }; // pointer to last node

	// utility function to allocate new node
	ListNode<TYPEDEC>* getNewNode(const TYPEDEC& value) {
		return new ListNode<TYPEDEC>{ value };
	}
};
// Below is the instructions that will be displayed at each point later on in my code where I call this function
void instructions() {
	cout << "Enter any of the following numbers to do the accomponied execution: \n"
		<< "  1 to insert at beginning of list \n"
		<< "  2 to insert at end of list \n"
		<< "  3 to delete from beginning of list \n"
		<< "  4 to delete from end of list \n"
		<< "  5 to retrieve an item from list \n"
		<< "  6 to end list processing \n";
}

// Below is the List testing function
template<typename T>
void testList(List<T>& listObject, const string& typeName) {
	cout << "Testing a list of " << typeName << " values\n";
	instructions(); //  at this point the instructions will be displayed

	int choice; // grab users input
	T value; // hold the user input

	// now we use a loop with user interactions
	do {
		cout << "? ";
		if (cin >> choice) { // grabs the users choice for choosing the appropriate case as listed below

			switch (choice) {
			case 1: // Here we start grabbing inputs for the list
				cout << "Enter " << typeName << ": ";
				cin >> value;
				listObject.Push(value);
				listObject.print();
				break;
			case 2: // inserts a value at the end
				cout << "Enter " << typeName << ": ";
				cin >> value;
				listObject.Enqueue(value);
				listObject.print();
				break;
			case 3: // remove from the beginning of a list
				try {
					if (listObject.isEmpty() == 1) {
						throw Exception_Empty{};
					}
					cout << listObject.Pop() << " removed from list\n";
				}
				catch (const Exception_Empty& Exception_Empty) {
					cout << "Exception occurred: "
						<< Exception_Empty.what() << endl;
				}
				listObject.print();
				break;
			case 4: // Removes from the end of a list
				try {
					if (listObject.isEmpty() == 1) {
						throw Exception_Empty{};
					}
					cout << listObject.Dequeue() << " removed from list\n";
				}
				catch (const Exception_Empty& Exception_Empty) {
					cout << "Exception occurred: "
						<< Exception_Empty.what() << endl;
				}
				listObject.print();
				break;
			case 5:// does the traverse operation.. aka retrieves an index value 
				int index;
				cout << "Enter index you want to retrieve: ";
				cin >> index;
				try {
					if (listObject.isEmpty() == 1) {
						throw Exception_Empty{};
					}
					try { value = listObject.Traverse(index); }
					catch (const No_index_Exception& NoindexException) {
						cout << "Exception occurred: "
							<< NoindexException.what() << endl;
						listObject.print();
						break;
					}
					cout << value << " removed from list\n";
				}
				catch (const Exception_Empty& Exception_Empty) {
					cout << "Exception occurred: "
						<< Exception_Empty.what() << endl;
				}
				listObject.print();
				break;
			}
		}
		else { break; }
	} while (choice < 6);

	cout << "End list test\n\n";
}

// and finally the main function and we are done with this problem :D
int main() {
	List<int> intList;
	testList(intList, "integer");
}
#include "pch.h"