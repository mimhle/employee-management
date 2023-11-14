//#pragma once
#include <iostream>
#include "Node.cpp"

template <class DataType>
class LinkedList {
private:
    Node<DataType>* _pHead;
    Node<DataType>* _pTail;
    int _iSize;

public:
    // constructor
    LinkedList();

    // destructor
    ~LinkedList();

    // method
    void addHead(DataType data);
    void addTail(DataType data);
    void addAfter(Node<DataType>* node, DataType data);

    Node<DataType>* search(DataType data);
    Node<DataType>* searchPre(Node<DataType>* node);

    void removeHead();
    void removeTail();
    void removeAfter(Node<DataType>* node);
    void remove(DataType data);

    void selectionSort();
    int getSize() const;
    void display() const;
    void clear();
};

template <class DataType>
LinkedList<DataType>::LinkedList() {
    _pHead = NULL;
    _pTail = NULL;
    _iSize = 0;
}

template <class DataType>
LinkedList<DataType>::~LinkedList() {
    clear();
}

template <class DataType>
void LinkedList<DataType>::addHead(DataType data) {
    Node<DataType>* _pAdd = new Node<DataType>(data);
    if (_pHead == NULL)
        _pHead = _pTail = _pAdd;
    else {
        _pAdd->_pNext = _pHead;
        _pHead = _pAdd;
    }
    _iSize++;
}

template <class DataType>
void LinkedList<DataType>::addTail(DataType data) {
    Node<DataType>* _pAdd = new Node<DataType>(data);
    if (_pHead == NULL)
        _pHead = _pTail = _pAdd;
    else {
        _pTail->_pNext = _pAdd;
        _pTail = _pAdd;
    }
    _iSize++;
}

template <class DataType>
void LinkedList<DataType>::addAfter(Node<DataType>* node, DataType data) {
    Node<DataType>* _pAdd = new Node<DataType>(data);
    if (node == NULL) {
        addHead(data);
    } else {
        _pAdd->_pNext = node->_pNext;
        node->_pNext = _pAdd;
        if (_pAdd->_pNext == NULL)
            _pTail = _pAdd;
        _iSize++;
    }
}

template <class DataType>
Node<DataType>* LinkedList<DataType>::search(DataType data) {
    Node<DataType>* _p = _pHead;
    while (_p != NULL && _p->_data == data)
        _p = _p->_pNext;
    return _p;
}

template <class DataType>
Node<DataType>* LinkedList<DataType>::searchPre(Node<DataType>* node) {
    Node<DataType>* _p = _pHead;
    if (_p == node)
        return NULL;
    while (_p != NULL && _p->_pNext != node)
        _p = _p->_pNext;
    return _p;
}

template <class DataType>
void LinkedList<DataType>::removeHead() {
    if (_pHead != NULL) {
        Node<DataType>* _pTemp = _pHead;
        _pHead = _pHead->_pNext;
        delete _pTemp;
        if (_pHead == NULL)
            _pTail = NULL;
        _iSize--;
    }
}

template <class DataType>
void LinkedList<DataType>::removeTail() {
    if (_pHead == NULL)
        return;
    Node<DataType>* _pTemp = _pTail;
    _pTail = searchPre(_pTail);
    delete _pTemp;
    if (_pTail != NULL)
        _pTail->_pNext = NULL;
    else
        _pHead = NULL;
    _iSize--;
}

template <class DataType>
void LinkedList<DataType>::removeAfter(Node<DataType>* node) {
    if (node == NULL)
        removeHead();
    else {
        Node<DataType>* _pTemp = node->_pNext;
        node->_pNext = _pTemp->_pNext;
        delete _pTemp;
        if (node->_pNext == NULL)
            _pTail = node;
        _iSize--;
    }
}

template <class DataType>
void LinkedList<DataType>::remove(DataType data) {
    Node<DataType>* _p = search(data);
    if (_p == NULL)
        return;
    Node<DataType>* _pPre = searchPre(_p);
    if (_pPre == NULL)
        removeHead();
    else
        removeAfter(_pPre);
    _iSize--;
}

template <class DataType>
void LinkedList<DataType>::display() const {
    Node<DataType>* _pWalker = _pHead;
    while (_pWalker != NULL) {
        _pWalker->display();
        _pWalker = _pWalker->_pNext;
    }
}

template <class DataType>
void LinkedList<DataType>::clear() {
    while (_pHead != NULL)
        removeHead();
}

template <class DataType>
int LinkedList<DataType>::getSize() const {
    return _iSize;
}

template <class DataType>
void LinkedList<DataType>::selectionSort() {
    Node<DataType>* _p = _pHead;
    Node<DataType>* _q = _p->_pNext;
    Node<DataType>* _pMin = _p;
    while (_p != NULL) {
        _pMin = _p;
        _q = _p->_pNext;
        while (_q != NULL) {
            if (_q->_data < _pMin->_data)
                _pMin = _q;
            _q = _q->_pNext;
        }
        swap(_p->_data, _pMin->_data);
        _p = _p->_pNext;
    }
}