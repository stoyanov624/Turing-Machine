#pragma once
#include <iostream>
#include <algorithm>
#include <string>

template <class T>
class DLList
{
public:
	DLList();
	DLList(const DLList&);
	DLList& operator=(const DLList&);
	~DLList();
	void push_back(const T&);
	void push_front(const T&);
	void pop_back();
	void pop_front();
	void printList() const;

private:
	struct Cell {
		T data;
		Cell* left;
		Cell* right;
	};
	Cell* head, * last;
	void copy(const DLList&);
	void erase();
	
public:
	class Iterator {
		Cell* current;
	public:
		Iterator();
		Iterator(Cell* current);
		Cell* getCurrent() const;
		bool isLast() const;
		bool isFirst() const;
		void operator++();
		void operator--();
		T& operator*() const;
		bool operator != (const Iterator& other) const;
		bool operator == (const Iterator& other) const;
	};

public:
	Iterator begin();
	Iterator end();
	Iterator const_begin() const;
	Iterator const_end() const;
};

template <class T>
DLList<T>::DLList() : head(nullptr), last(nullptr) {}

template <class T>
void DLList<T>::copy(const DLList& other_list) {
	if (other_list.head == nullptr) {
		return;
	}
	head = new Cell {other_list.head->data,nullptr,nullptr};

	Cell* crr = head;
	Cell* crr_other = other_list.head;

	while (crr_other->right != nullptr) {
		crr->right = new Cell { crr_other->right->data,nullptr,nullptr };
		crr->right->left = crr;
		crr = crr->right;
		crr_other = crr_other->right;
	}
	last = crr;
}

template <class T>
void DLList<T>::erase() {
	Cell* save = nullptr;
	Cell* temp = nullptr;
	while (head != nullptr) {
		temp = new Cell { head->data,nullptr,nullptr };
		head = head->right;
		delete temp;
	}

	last = nullptr;
	
}

template <class T>
DLList<T>::DLList(const DLList& other_list) {
	copy(other_list);
}

template <class T>
DLList<T>& DLList<T>::operator=(const DLList& other_list) {
	if (this != &other_list) {
		erase();
		copy(other_list);
	}

	return *this;
}

template <class T>
DLList<T>::~DLList() {
	erase();
}

template <class T>
void DLList<T>::push_back(const T& element) {
	Cell* temp = new Cell{ element,nullptr,nullptr };
	if (head == nullptr) {
		head = temp;
		last = temp;
		return;
	}
	last->right = temp;
	temp->left = last;
	last = temp;
}

template <class T>
void DLList<T>::push_front(const T& element) {
	Cell* temp = new Cell{ element,nullptr,nullptr };
	if (head == nullptr) {
		head = temp;
		last = temp;
		return;
	}
	head->left = temp;
	temp->right = head;
	head = temp;
}

template <class T>
void DLList<T>::pop_back() {
	if (last == nullptr) {
		return;
	}
	Cell* save = new Cell{ last->data,nullptr,nullptr };
	last = last->left;
	last->right = nullptr;
	delete save;
}

template <class T>
void DLList<T>::pop_front() {
	if (head == nullptr) {
		return;
	}

	Cell* save = new Cell{ head->data,nullptr,nullptr };
	head = head->right;
	delete save;
}


template <class T>
void DLList<T>::printList() const {
	Cell* crr = head;

	while (crr != nullptr) {
		std::cout << crr->data << " ";
		crr = crr->right;
	}

	std::cout << std::endl;
}

template <class T>
DLList<T>::Iterator::Iterator() {
	current = nullptr;
}

template <class T>
DLList<T>::Iterator::Iterator(Cell* _current) {
	current = _current;
}

template <class T>
bool DLList<T>::Iterator::isFirst() const {
	return current->left == nullptr;
}

template <class T>
bool DLList<T>::Iterator::isLast() const {
	return current->right == nullptr;
}

template <class T>
void DLList<T>::Iterator::operator++() {
	current = current->right;
}

template <class T>
void DLList<T>::Iterator::operator--() {
	current = current->left;
}

template <class T>
T& DLList<T>::Iterator::operator*() const {
	return current->data;
}

template <class T>
bool DLList<T>::Iterator::operator != (const Iterator& other) const {
	return this->current != other.current;
}

template <class T>
bool DLList<T>::Iterator::operator == (const Iterator& other) const {
	return this->current == other.current;
}

template <class T>
typename DLList<T>::Cell* DLList<T>::Iterator::getCurrent () const {
	return this->current;
}

template <class T>
typename DLList<T>::Iterator DLList<T>::begin() {
	return Iterator(head);
}

template <class T>
typename DLList<T>::Iterator DLList<T>::end() {
	return Iterator(nullptr);
}

template <class T>
typename DLList<T>::Iterator DLList<T>::const_begin() const {
	return Iterator(head);
}

template <class T>
typename DLList<T>::Iterator DLList<T>::const_end() const {
	return Iterator(nullptr);
}

